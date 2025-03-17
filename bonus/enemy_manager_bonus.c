/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_manager_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 11:50:09 by noaziki           #+#    #+#             */
/*   Updated: 2025/03/17 16:34:47 by noaziki          ###   ########.fr       */
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

void	floodfill_enemy(char **map, int x, int y)
{
	if (map[x][y] == '1' || map[x][y] == 'A'
	|| map[x][y] == 'E' || map[x][y] == 'N')
		return ;
	if (map[x][y] == '0' || map[x][y] == 'C')
		map[x][y] = 'A';
	floodfill_enemy(map, x + 1, y);
	floodfill_enemy(map, x - 1, y);
	floodfill_enemy(map, x, y + 1);
	floodfill_enemy(map, x, y - 1);
}

void	check_enemy_path(t_game *game)
{
	game->map2[game->x][game->y] = 'N';
	position(game, 'P');
	floodfill_enemy(game->map2, game->player_x, game->player_y);
	if (check_content(game, game->map2, "01PAEN") || check_exit(game))
	{
		free_game(game->map2);
		copy_map(game);
	}
	else
	{
		game->map[game->x][game->y] = 'N';
		free_game(game->map2);
		copy_map(game);
	}
}

void	check_enemy_zone(t_game *game)
{
	if (game->map2[game->x][game->y] == '0'
		&& game->map2[game->x][game->y - 1] == '0'
		&& game->map2[game->x][game->y + 1] == '0'
		&& game->map2[game->x][game->y - 2] == '0'
		&& game->map2[game->x][game->y + 2] == '0'
		&& game->map2[game->x][game->y - 3] != 'N'
		&& game->map2[game->x][game->y + 3] != 'N'
		&& game->map2[game->x][game->y - 4] != 'N'
		&& game->map2[game->x][game->y + 4] != 'N'
		&& game->map2[game->x - 1][game->y] != 'N'
		&& game->map2[game->x - 1][game->y - 1] != 'N'
		&& game->map2[game->x - 1][game->y + 1] != 'N'
		&& game->map2[game->x - 1][game->y - 2] != 'N'
		&& game->map2[game->x - 1][game->y + 2] != 'N'
		&& game->map2[game->x - 1][game->y - 3] != 'N'
		&& game->map2[game->x - 1][game->y + 3] != 'N'
		&& game->map2[game->x - 1][game->y - 4] != 'N'
		&& game->map2[game->x - 1][game->y + 4] != 'N')
	{
		check_enemy_path(game);
	}
}

void	place_enemy(t_game *game)
{
	copy_map(game);
	game->x = 0;
	while (game->map2[game->x])
	{
		game->y = 0;
		while (game->map2[game->x][game->y])
		{
			check_enemy_zone(game);
			game->y++;
		}
		game->x++;
	}
	if (!check_content(game, game->map, "01PEC"))
	{
		free_game(game->map2);
		print_error("Error\nNo suitable space for enemy!\n", game);
	}
	else
		free_game(game->map2);
}
