/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 11:50:09 by noaziki           #+#    #+#             */
/*   Updated: 2025/03/24 13:54:19 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	draw_map(t_game *game)
{
	game->i = 0;
	while (game->map[game->i])
	{
		game->j = 0;
		while (game->map[game->i][game->j])
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
			game->j++;
		}
		game->i++;
	}
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
	if (!game->pikachu || !game->door || !game->wall
		|| !game->coin || !game->floor)
	{
		destroy_images(game);
		print_error("Error\nimage name is not compatible!\n", game);
	}
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
	mlx_key_hook(game->window, handle_keypress, game);
	mlx_hook(game->window, 17, 0, close_game, game);
	mlx_loop(game->mlx);
}
