/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nqueens.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 14:40:02 by mzimeris          #+#    #+#             */
/*   Updated: 2026/02/16 10:52:22 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int	check_board(int *board, int value, int index)
{
	int	i;

	i = 0;
	while (i < index)
	{
		if (board[i] == value)
			return (0);
		if (board[i] - value == i - index
			|| board[i] - value == index - i)
			return (0);
		i++;
	}
	return (1);
}

/*
3 choses à définir :
1- la condition d'arrêt de la récursion : dans les nqueens, c'est lorsque index == N, c'est à dire qu'on a placé toutes les reines sur le plateau.
2- la condition de validité : c'est la fonction check_board, qui vérifie si la position actuelle est valide par rapport aux reines déjà placées. (fonction check_board qui vérifie les diagonales et les colonnes)
3- la récursion : c'est la partie où on place une reine sur le plateau et on appelle récursivement la fonction pour placer la suivante. (dans nqueens, c'est la partie où on place une reine sur le plateau et on appelle récursivement la fonction pour placer la suivante) et surtout ne pas oublier de retirer la reine après l'appel récursif pour explorer d'autres configurations (backtracking).
*/

/*
index : représente la colonne sur laquelle on essaie de placer une reine.
value : représente la ligne sur laquelle on essaie de placer une reine.
*/

void	nqueens(int *board, int N, int index)
{
	int	i;
	int	value;

	i = 0;
	value = 0;
// 1- condition d'arrêt.
	if (index == N)
	{
		while (i < N)
			printf("%d", board[i++]);
		printf("\n");
		return ;
	}
	while (value < N)
	{
// 2- condition de validité. Si la valeur est valide :
		if (check_board(board, value, index))
		{
// 3- récursion : on place la reine.
			board[index] = value;
// 3- récursion : On appelle récursivement pour la suivante.
			nqueens(board, N, index + 1);
// 3- récursion : on retire la reine qu'on vient de placer.
			board[index] = -1;
		}
		value++;
	}
}

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		write(1, "Usage: ./nqueens N\n", 19);
		return (1);
	}

	int N = atoi(argv[1]);
	if (N < 1 || N > 20)
	{
		write(1, "N must be between 1 and 20\n", 27);
		return (1);
	}

	int *board = malloc(sizeof(int) * N);
	if (!board)
		return (1);

	int i = 0;
	while (i < N)
	{
		board[i] = -1;
		i++;
	}
	nqueens(board, N, 0);
	free(board);
	return (0);
}