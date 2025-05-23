/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 11:50:09 by noaziki           #+#    #+#             */
/*   Updated: 2025/03/24 15:02:25 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	draw_map(t_game *game)
{
	game->i = 0;
	while (game->map[game->i])
	{
		game->j = 0;
		while (game->map[game->i][game->j])
		{
			draw_game_objects(game);
			game->j++;
		}
		game->i++;
	}
}

void	xpm_to_img(t_game *game)
{
	game->pikachu = mlx_xpm_file_to_image(game->mlx,
			"textures/pikachu.xpm", &game->img_width, &game->img_height);
	game->door = mlx_xpm_file_to_image(game->mlx,
			"textures/door_bonus.xpm", &game->img_width, &game->img_height);
	game->wall = mlx_xpm_file_to_image(game->mlx,
			"textures/wall_bonus.xpm", &game->img_width, &game->img_height);
	game->coin = mlx_xpm_file_to_image(game->mlx,
			"textures/pokeball_bonus.xpm", &game->img_width, &game->img_height);
	game->floor = mlx_xpm_file_to_image(game->mlx,
			"textures/floor_bonus.xpm", &game->img_width, &game->img_height);
	game->enemy = mlx_xpm_file_to_image(game->mlx,
			"textures/enemy_left.xpm", &game->img_width, &game->img_height);
	if (!game->pikachu || !game->door || !game->wall
		|| !game->coin || !game->floor || !game->enemy)
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

void	render_moves_counter(t_game *game)
{
	char	*moves_str;

	moves_str = ft_itoa(game->moves);
	mlx_string_put(game->mlx, game->window, 10, 20, 0xFFFFFF, moves_str);
	free(moves_str);
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
	count_enemies(game);
	mlx_loop_hook(game->mlx, enemy_moves, game);
	mlx_hook(game->window, 17, 0, close_game, game);
	mlx_loop(game->mlx);
}
