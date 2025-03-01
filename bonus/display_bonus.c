/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 19:42:52 by noaziki           #+#    #+#             */
/*   Updated: 2025/02/26 13:01:50 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	put_image(char c, t_game *game)
{
	if (c == 'E')
		mlx_put_image_to_window(game->mlx, game->window,
			game->door, game->j * 64, game->i * 64);
	if (c == 'P')
		mlx_put_image_to_window(game->mlx, game->window,
			game->pikachu, game->j * 64, game->i * 64);
	if (c == '1')
		mlx_put_image_to_window(game->mlx, game->window,
			game->wall, game->j * 64, game->i * 64);
	if (c == '0')
		mlx_put_image_to_window(game->mlx, game->window,
			game->floor, game->j * 64, game->i * 64);
	if (c == 'C')
		mlx_put_image_to_window(game->mlx, game->window,
			game->coin, game->j * 64, game->i * 64);
}
void	draw_map(t_game *game)
{
	game->i = 0;
	while (game->map[game->i])
	{
		game->j = 0;
		while (game->map[game->i][game->j])
		{
			put_image(game->map[game->i][game->j], game);
			game->j++;
		}
		game->i++;
	}
	char *moves_str;
	moves_str = ft_itoa(game->moves);
	mlx_string_put(game->mlx, game->window, 10, 10, 0xFFFFFF, moves_str);
	free(moves_str);
}

void	xpm_to_img(t_game *game)
{
	game->pikachu = mlx_xpm_file_to_image(game->mlx,
			"textures/player.xpm", &game->img_width, &game->img_height);
	game->door = mlx_xpm_file_to_image(game->mlx,
			"textures/door.xpm", &game->img_width, &game->img_height);
	game->wall = mlx_xpm_file_to_image(game->mlx,
			"textures/wall.xpm", &game->img_width, &game->img_height);
	game->coin = mlx_xpm_file_to_image(game->mlx,
			"textures/pokeball.xpm", &game->img_width, &game->img_height);
	game->floor = mlx_xpm_file_to_image(game->mlx,
			"textures/floor.xpm", &game->img_width, &game->img_height);
	game->enemy = mlx_xpm_file_to_image(game->mlx,
			"textures/enemy.xpm", &game->img_width, &game->img_height);
	if (!game->pikachu || !game->door || !game->wall
		|| !game->coin || !game->floor || !game->enemy)
		print_error("Error\nimage name is not compatible!\n", game);
}

void	count_collected(t_game	*game)
{
	game->i = 0;
	game->collected = 0;
	while (game->map[game->i])
	{
		game->j = 0;
		while (game->map[game->i][game->j])
		{
			if (game->map[game->i][game->j] == 'C')
				game->collected++;
			game->j++;
		}
		game->i++;
	}
}

void	render_map(t_game *game)
{
	game->moves = 0;
	game->mlx = mlx_init();
	if (!game->mlx)
		(print_error("Error\nUnable to initialize MLX!\n", game));
	game->window = mlx_new_window(game->mlx,
			game->map_width * 64, game->map_height * 64,
			"Welcome to Pikachu's game! Let the adventure begin!");
	if (!game->window)
		print_error("Error\nfailed to create MLX window!\n", game);
	xpm_to_img(game);
	draw_map(game);
	mlx_hook(game->window, 2, 1L << 0, handle_keypress, game);
	if (game->enemy_y != 0 && game->enemy_x1 != 0 && game->enemy_x2 != 0)
	{
		game->enemy_pos = game->enemy_x1;
		mlx_loop_hook(game->mlx, handle_enemy_move, game);
	}
	else
		print_error("Error\nno valid space for enemy!\n", game);
	mlx_hook(game->window, 17, 1L << 0, close_game, game);
	mlx_loop(game->mlx);
}
