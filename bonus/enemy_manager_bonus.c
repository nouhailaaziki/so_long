/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_manager_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 11:50:09 by noaziki           #+#    #+#             */
/*   Updated: 2025/03/24 15:25:04 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	draw_game_objects(t_game *game)
{
	if (game->map[game->i][game->j] == 'E')
		mlx_put_image_to_window(game->mlx, game->window,
			game->door, game->j * 64, game->i * 64);
	if (game->map[game->i][game->j] == 'P')
		mlx_put_image_to_window(game->mlx, game->window,
			game->pikachu, game->j * 64, game->i * 64);
	if (game->map[game->i][game->j] == '1')
		mlx_put_image_to_window(game->mlx, game->window,
			game->wall, game->j * 64, game->i * 64);
	if (game->map[game->i][game->j] == '0')
		mlx_put_image_to_window(game->mlx, game->window,
			game->floor, game->j * 64, game->i * 64);
	if (game->map[game->i][game->j] == 'C')
		mlx_put_image_to_window(game->mlx, game->window,
			game->coin, game->j * 64, game->i * 64);
	if (game->map[game->i][game->j] == 'N')
		mlx_put_image_to_window(game->mlx, game->window,
			game->enemy, game->j * 64, game->i * 64);
}

void	floodfill_enemy(char **map, int x, int y)
{
	if (map[x][y] == '1' || map[x][y] == 'A'
	|| map[x][y] == 'E' || map[x][y] == 'N')
		return ;
	if (map[x][y] == '0' || map[x][y] == 'C' || map[x][y] == 'P')
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
	if (game->x > 0 && game->y > 4 && game->y + 4 < game->map_width
		&& game->map2[game->x][game->y] == '0'
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
