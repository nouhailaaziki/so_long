/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 15:21:21 by noaziki           #+#    #+#             */
/*   Updated: 2025/03/24 15:25:25 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	copy_map(t_game *game)
{
	int	i;

	i = 0;
	game->map2 = (char **)malloc(sizeof(char *) * (game->lines + 1));
	if (!game->map2)
		print_error("Error\nMemory allocation failed for map!\n", game);
	while (game->map[i])
	{
		game->map2[i] = ft_strdup(game->map[i]);
		i++;
	}
	game->map2[i] = NULL;
}

void	flood_fill(char **map, int x, int y)
{
	if (map[x][y] == '1' || map[x][y] == 'A' || map[x][y] == 'E')
		return ;
	if (map[x][y] == '0' || map[x][y] == 'C' || map[x][y] == 'P')
		map[x][y] = 'A';
	flood_fill(map, x + 1, y);
	flood_fill(map, x - 1, y);
	flood_fill(map, x, y + 1);
	flood_fill(map, x, y - 1);
}

void	position(t_game *game, char c)
{
	game->i = 0;
	while (game->map[game->i])
	{
		game->j = 0;
		while (game->map[game->i][game->j])
		{
			if (game->map[game->i][game->j] == c)
			{
				game->player_x = game->i;
				game->player_y = game->j;
			}
			game->j++;
		}
		game->i++;
	}
}

int	check_exit(t_game *game)
{
	position(game, 'E');
	if (game->map2[game->player_x + 1][game->player_y] == 'A'
	|| game->map2[game->player_x - 1][game->player_y] == 'A'
	|| game->map2[game->player_x][game->player_y + 1] == 'A'
	|| game->map2[game->player_x][game->player_y - 1] == 'A')
		return (0);
	return (1);
}

int	check_path(t_game *game, char *filename)
{
	position(game, 'P');
	game->map2 = (char **)malloc(sizeof(char *) * (game->lines + 1));
	if (!game->map2)
		print_error("Error\nMemory allocation failed for map!\n", game);
	read_map(filename, game, game->map2);
	flood_fill(game->map2, game->player_x, game->player_y);
	if (check_content(game, game->map2, "01PAE") || check_exit(game))
		return (free_game(game->map2), 1);
	return (free_game(game->map2), 0);
}
