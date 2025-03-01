/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_location_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 16:57:52 by noaziki           #+#    #+#             */
/*   Updated: 2025/03/01 11:37:58 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	check(t_game *game, int *s)
{
	game->enemy_y = game->i;
	game->enemy_x1 = game->j;
	while (game->map[game->i][game->j] == '0')
	{
		(*s)++;
		game->j++;
	}
}

void	initialize_enemy(t_game *game)
{
	int	s;

	game->i = 1;
	while(game->i < game->map_height - 1)
	{
		game->j = 1;
		s = 0;
		while(game->j < game->map_width - 1)
		{
			if (game->map[game->i][game->j] == '0')
			{
				check(game, &s);
				game->enemy_x2 = game->j - 1;
				break ;
			}
			game->j++;
		}
		if (s > 2)
			break ;
		game->i++;
	}
}

void	game_over(t_game *game)
{
	if (game->player_x == game->enemy_y
	&& game->player_y == game->enemy_pos)
		print_error("Game Over! You lost this time!", game);
}
int	handle_enemy_move(t_game *game)
{
	static int	counter = 0;
	static int	direction = 1;

	if (counter < 6000)
		counter++;
	else
		counter = 0;
	if (counter == 0)
	{
		mlx_put_image_to_window(game->mlx, game->window, game->floor,
			64 * game->enemy_pos, 64 * game->enemy_y);
		if (game->enemy_pos == game->enemy_x2)
			direction = -1;
		else if (game->enemy_pos == game->enemy_x1)
			direction = 1;
		if (direction > 0 && game->enemy_pos < game->enemy_x2)
			game->enemy_pos++;
		else if (direction < 0 && game->enemy_pos > game->enemy_x1)
			game->enemy_pos--;
	}
	if (counter == 3000)
		mlx_put_image_to_window(game->mlx, game->window, game->enemy,
			64 * game->enemy_pos, 64 * game->enemy_y);
	game_over(game);
	return (0);
}
