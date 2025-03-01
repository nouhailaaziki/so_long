/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 19:42:19 by noaziki           #+#    #+#             */
/*   Updated: 2025/02/24 17:19:45 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	print_error(char *message, t_game *game)
{
	if (game)
	{
		if (game->map)
			free_game(game->map);
		free(game);
	}
	write(2, message, ft_strlen(message));
	exit (1);
}

int	close_game(t_game *game)
{
	if (game)
	{
		if (game->map)
			free_game(game->map);
		free(game);
	}
	exit(0);
	return (0);
}

void	free_game(char **map)
{
	int	i;

	i = 0;
	if (!map)
		return ;
	while (map[i])
	{
		free (map[i]);
		i++;
	}
	free (map);
}
