#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <netinet/ip.h>

int     count = 0, max_fd = 0;
int     ids[65536];
char    *msgs[65536];

fd_set  readfds, writefds, activefds;
char    buf_read[1001];
char    buf_write[200000];

// --- Fonctions fournies par le sujet ---
int extract_message(char **buf, char **msg) {
    char    *newbuf;
    int i = 0;
    if (*buf == 0) return (0);
    while ((*buf)[i]) {
        if ((*buf)[i] == '\n') {
            newbuf = calloc(1, sizeof(*newbuf) * (strlen(*buf + i + 1) + 1));
            if (newbuf == 0) return (-1);
            strcpy(newbuf, *buf + i + 1);
            *msg = *buf;
            (*msg)[i + 1] = 0;
            *buf = newbuf;
            return (1);
        }
        i++;
    }
    return (0);
}

char *str_join(char *buf, char *add) {
    char    *newbuf;
    int     len = (buf == 0) ? 0 : strlen(buf);
    newbuf = malloc(sizeof(*newbuf) * (len + strlen(add) + 1));
    if (newbuf == 0) return (0);
    newbuf[0] = 0;
    if (buf != 0) strcat(newbuf, buf);
    free(buf);
    strcat(newbuf, add);
    return (newbuf);
}

void    fatal_error() {
    write(2, "Fatal error\n", 12);
    exit(1);
}

void    notify_other(int author, char *str) {
    for (int fd = 0; fd <= max_fd; fd++) {
        if (FD_ISSET(fd, &writefds) && fd != author)
            send(fd, str, strlen(str), 0);
    }
}

void    send_msg(int fd) {
    char *msg;
    while (extract_message(&(msgs[fd]), &msg)) {
        sprintf(buf_write, "client %d: ", ids[fd]);
        notify_other(fd, buf_write);
        notify_other(fd, msg);
        free(msg);
    }
}

int     create_socket() {
    max_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (max_fd < 0)
        fatal_error();
    FD_SET(max_fd, &activefds);
    return max_fd;
}

void    new_client(int sockfd, struct sockaddr_in *servaddr) {
    socklen_t addr_len = sizeof(*servaddr);
    int client_fd = accept(sockfd, (struct sockaddr *)servaddr, &addr_len);
    if (client_fd >= 0) {
		max_fd = client_fd > max_fd ? client_fd : max_fd;
		ids[client_fd] = count++;
		msgs[client_fd] = NULL;
		FD_SET(client_fd, &activefds);
		sprintf(buf_write, "server: client %d just arrived\n", ids[client_fd]);
		notify_other(client_fd, buf_write);
    }
}

void    new_message(int fd) {
    int read_bytes = recv(fd, buf_read, 1000, 0);
    if (read_bytes <= 0) {
		sprintf(buf_write, "server: client %d just left\n", ids[fd]);
		notify_other(fd, buf_write);
		free(msgs[fd]);
		msgs[fd] = NULL;
		FD_CLR(fd, &activefds);
		close(fd);
    } else {
        buf_read[read_bytes] = '\0';
        msgs[fd] = str_join(msgs[fd], buf_read);
        if (msgs[fd] == NULL)
            fatal_error();
        send_msg(fd);
    }
}

int     main(int ac, char **av) {
	if (ac != 2) {
		write(2, "Wrong number of arguments\n", 26);
		exit(1);
	}

	FD_ZERO(&activefds);
	int sockfd = create_socket();

	struct sockaddr_in servaddr;
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(2130706433);
	servaddr.sin_port = htons(atoi(av[1]));

	if (bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)))
		fatal_error();
	if (listen(sockfd, SOMAXCONN))
		fatal_error();

	while (1) {
		readfds = writefds = activefds;
		if (select(max_fd + 1, &readfds, &writefds, NULL, NULL) < 0)
			fatal_error();

		for (int fd = 0; fd <= max_fd; fd++) {
			if (!FD_ISSET(fd, &readfds))
				continue;

			if (fd == sockfd)
				new_client(sockfd, &servaddr);
			else
				new_message(fd);
			break ;
		}
	}
	return 0;
}