/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   motion_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 11:51:05 by noaziki           #+#    #+#             */
/*   Updated: 2025/03/13 16:59:26 by noaziki          ###   ########.fr       */
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
		game->moves++;
		game->map[game->player_x - 1][game->player_y] = 'P';
		game->map[game->player_x][game->player_y] = '0';
	}
	if (game->map[game->player_x - 1][game->player_y] == 'E'
		&& game->collected == 0)
		(write(1, "Victory! You did it!\n", 22), close_game(game));
	game->pikachu = mlx_xpm_file_to_image(game->mlx,
			"textures/pikachu_back.xpm", &game->img_width, &game->img_height);
	draw_map(game);
	render_moves_counter(game);
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
		game->moves++;
		game->map[game->player_x + 1][game->player_y] = 'P';
		game->map[game->player_x][game->player_y] = '0';
	}
	if (game->map[game->player_x + 1][game->player_y] == 'E'
		&& game->collected == 0)
		(write(1, "Victory! You did it!\n", 22), close_game(game));
	game->pikachu = mlx_xpm_file_to_image(game->mlx,
			"textures/pikachu.xpm", &game->img_width, &game->img_height);
	draw_map(game);
	render_moves_counter(game);
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
		game->moves++;
		game->map[game->player_x][game->player_y + 1] = 'P';
		game->map[game->player_x][game->player_y] = '0';
	}
	if (game->map[game->player_x][game->player_y + 1] == 'E'
		&& game->collected == 0)
		(write(1, "Victory! You did it!\n", 22), close_game(game));
	game->pikachu = mlx_xpm_file_to_image(game->mlx,
			"textures/pikachu_right.xpm", &game->img_width, &game->img_height);
	draw_map(game);
	render_moves_counter(game);
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
		game->moves++;
		game->map[game->player_x][game->player_y - 1] = 'P';
		game->map[game->player_x][game->player_y] = '0';
	}
	if (game->map[game->player_x][game->player_y - 1] == 'E'
		&& game->collected == 0)
		(write(1, "Victory! You did it!\n", 22), close_game(game));
	game->pikachu = mlx_xpm_file_to_image(game->mlx,
			"textures/pikachu_left.xpm", &game->img_width, &game->img_height);
	draw_map(game);
	render_moves_counter(game);
}

int	handle_keypress(int keycode, t_game *game)
{
	count_collected(game);
	if (game->collected == 0)
	{
		game->door = mlx_xpm_file_to_image(game->mlx,
				"textures/door_bonus.xpm", &game->img_width, &game->img_height);
		draw_map(game);
	}
	if (keycode == 126 || keycode == 13)
		player_up(game);
	if (keycode == 125 || keycode == 1)
		player_down(game);
	if (keycode == 124 || keycode == 2)
		player_right(game);
	if (keycode == 123 || keycode == 0)
		player_left(game);
	else if (keycode == 53)
		close_game(game);
	return (0);
}
