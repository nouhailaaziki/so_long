/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   motion_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 19:41:30 by noaziki           #+#    #+#             */
/*   Updated: 2025/03/01 12:11:21 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	player_up(t_game *game)
{
	count_collected(game);
	position(game, 'P');
	if (game->map[game->player_x - 1][game->player_y] == '0'
		|| game->map[game->player_x - 1][game->player_y] == 'C')
	{
		if (game->map[game->player_x - 1][game->player_y] == 'C')
			game->collected--;
		game->map[game->player_x - 1][game->player_y] = 'P';
		game->map[game->player_x][game->player_y] = '0';
	}
	if (game->map[game->player_x - 1][game->player_y] == 'E'
		&& game->collected == 0)
		(write(1, "Victory! You did it!\n", 22), close_game(game));
	game->pikachu = mlx_xpm_file_to_image(game->mlx,
			"textures/player_back.xpm", &game->img_width, &game->img_height);
	draw_map(game);
}

void	player_down(t_game *game)
{
	count_collected(game);
	position(game, 'P');
	if (game->map[game->player_x + 1][game->player_y] == '0'
		|| game->map[game->player_x + 1][game->player_y] == 'C')
	{
		if (game->map[game->player_x + 1][game->player_y] == 'C')
			game->collected--;
		game->map[game->player_x + 1][game->player_y] = 'P';
		game->map[game->player_x][game->player_y] = '0';
	}
	if (game->map[game->player_x + 1][game->player_y] == 'E'
		&& game->collected == 0)
		(write(1, "Victory! You did it!\n", 22), close_game(game));
	game->pikachu = mlx_xpm_file_to_image(game->mlx,
			"textures/player.xpm", &game->img_width, &game->img_height);
	draw_map(game);
}

void	player_right(t_game *game)
{
	count_collected(game);
	position(game, 'P');
	if (game->map[game->player_x][game->player_y + 1] == '0'
		|| game->map[game->player_x][game->player_y + 1] == 'C')
	{
		if (game->map[game->player_x][game->player_y + 1] == 'C')
			game->collected--;
		game->map[game->player_x][game->player_y + 1] = 'P';
		game->map[game->player_x][game->player_y] = '0';
	}
	if (game->map[game->player_x][game->player_y + 1] == 'E'
		&& game->collected == 0)
		(write(1, "Victory! You did it!\n", 22), close_game(game));
	game->pikachu = mlx_xpm_file_to_image(game->mlx,
			"textures/player_right.xpm", &game->img_width, &game->img_height);
	draw_map(game);
}

void	player_left(t_game *game)
{
	count_collected(game);
	position(game, 'P');
	if (game->map[game->player_x][game->player_y - 1] == '0'
		|| game->map[game->player_x][game->player_y - 1] == 'C')
	{
		if (game->map[game->player_x][game->player_y - 1] == 'C')
			game->collected--;
		game->map[game->player_x][game->player_y - 1] = 'P';
		game->map[game->player_x][game->player_y] = '0';
	}
	if (game->map[game->player_x][game->player_y - 1] == 'E'
		&& game->collected == 0)
		(write(1, "Victory! You did it!\n", 22), close_game(game));
	game->pikachu = mlx_xpm_file_to_image(game->mlx,
			"textures/player_left.xpm", &game->img_width, &game->img_height);
	draw_map(game);
}

int	handle_keypress(int keycode, t_game *game)
{
	count_collected(game);
	if (game->collected == 0)
	{
		game->door = mlx_xpm_file_to_image(game->mlx,
				"textures/door.xpm", &game->img_width, &game->img_height);
		draw_map(game);
	}
	if (keycode == 126)
		player_up(game);
	if (keycode == 125)
		player_down(game);
	if (keycode == 124)
		player_right(game);
	if (keycode == 123)
		player_left(game);
	else if (keycode == 53)
		close_game(game);
	return (0);
}
