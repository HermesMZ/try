#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>

int		g_client_ids[1024];
char	*g_client_bufs[1024];
int		g_max_fd = 0;
int		g_next_id = 0;
fd_set	g_active_fds, g_read_fds, g_write_fds;

int extract_message(char **buf, char **msg)
{
	char	*newbuf;
	int	i;

	*msg = 0;
	if (*buf == 0)
		return (0);
	i = 0;
	while ((*buf)[i])
	{
		if ((*buf)[i] == '\n')
		{
			newbuf = calloc(1, sizeof(*newbuf) * (strlen(*buf + i + 1) + 1));
			if (newbuf == 0)
				return (-1);
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

char *str_join(char *buf, char *add)
{
	char	*newbuf;
	int		len;

	if (buf == 0)
		len = 0;
	else
		len = strlen(buf);
	newbuf = malloc(sizeof(*newbuf) * (len + strlen(add) + 1));
	if (newbuf == 0)
		return (0);
	newbuf[0] = 0;
	if (buf != 0)
		strcat(newbuf, buf);
	free(buf);
	strcat(newbuf, add);
	return (newbuf);
}

void fatal_error()
{
	write(2, "Fatal error\n", 12);
	exit(1);
}

void send_all(int except_fd, char *msg)
{
	for (int fd = 0; fd <= g_max_fd; fd++)
	{
		if (g_client_ids[fd] != -1 && fd != except_fd && FD_ISSET(fd, &g_write_fds))
		{
			send(fd, msg, strlen(msg), 0);
		}
	}
}

int	main(int argc, char **argv)
{
	int					sockfd;
	struct sockaddr_in	servaddr;

	if (argc != 2)
	{
		write(2, "Wrong number of arguments\n", 26);
		exit(1);
	}

	// socket create and verification 
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1)
		fatal_error();
	bzero(&servaddr, sizeof(servaddr));

	// assign IP, PORT 
	servaddr.sin_family = AF_INET; 
	servaddr.sin_addr.s_addr = htonl(2130706433);
	servaddr.sin_port = htons(atoi(argv[1]));

	// Binding newly created socket to given IP and verification 
	if ((bind(sockfd, (const struct sockaddr *)&servaddr,
				sizeof(servaddr))) != 0)
		fatal_error();
	if (listen(sockfd, 128) != 0)
		fatal_error();

	FD_ZERO(&g_active_fds);
	FD_SET(sockfd, &g_active_fds);
	g_max_fd = sockfd;

	memset(g_client_bufs, 0, sizeof(g_client_bufs));
	for (int i = 0; i < 1024; i++)
		g_client_ids[i] = -1;

	char msg_buffer[1024];
	char read_buffer[1024];

	while (1)
	{
		g_read_fds = g_write_fds = g_active_fds;

		if (select(g_max_fd + 1, &g_read_fds, &g_write_fds, NULL, NULL) < 0)
			fatal_error();
		for (int fd = 0; fd <= g_max_fd; fd++)
		{
			if (!FD_ISSET(fd, &g_read_fds))
				continue;

			// socket principal = nouveau client
			if (fd == sockfd)
			{
				struct sockaddr_in cli;
				socklen_t len = sizeof(cli);
				int connfd = accept(sockfd, (struct sockaddr *)&cli, &len);
				if (connfd < 0)
					continue;
				if (connfd > g_max_fd)
					g_max_fd = connfd;
				g_client_ids[connfd] = g_next_id++;
				g_client_bufs[connfd] = NULL;

				FD_SET(connfd, &g_active_fds);
				sprintf(msg_buffer, "server: client %d just arrived\n", g_client_ids[connfd]);
				send_all(connfd, msg_buffer);
				break;
			}
			else {
				int n = recv(fd, read_buffer, sizeof(read_buffer) - 1, 0);
				if (n <= 0)
				{
					sprintf(msg_buffer, "server: client %d just left\n", g_client_ids[fd]);
					send_all(fd, msg_buffer);

					if (g_client_bufs[fd])
					{
						free(g_client_bufs[fd]);
						g_client_bufs[fd] = NULL;
					}
					g_client_ids[fd] = -1;
					FD_CLR(fd, &g_active_fds);
					close(fd);
					break;
				}
				read_buffer[n] = 0;
				g_client_bufs[fd] = str_join(g_client_bufs[fd], read_buffer);
				if (g_client_bufs[fd] == NULL)
					fatal_error();
				char *msg = NULL;
				while (extract_message(&g_client_bufs[fd], &msg))
				{
					sprintf(msg_buffer, "client %d: %s", g_client_ids[fd], msg);
					send_all(fd, msg_buffer);
					free(msg);
					msg = NULL;
			}
		}
	}

	}

	return (0);
}