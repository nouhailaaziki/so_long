/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_motion_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 11:50:09 by noaziki           #+#    #+#             */
/*   Updated: 2025/03/24 15:44:51 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	alloc_arr(t_game *game)
{
	if (game->enemies == 0)
		return ;
	game->enemies_x = malloc(sizeof(int) * game->enemies);
	if (!game->enemies_x)
		print_error("Error\nMemory allocation failed!\n", game);
	game->enemies_y = malloc(sizeof(int) * game->enemies);
	if (!game->enemies_y)
	{
		free(game->enemies_x);
		print_error("Error\nMemory allocation failed!\n", game);
	}
}

void	fill_arr(t_game *game)
{
	int	i;
	int	j;
	int	n;

	i = 0;
	n = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			if (game->map[i][j] == 'N')
			{
				game->enemies_x[n] = i;
				game->enemies_y[n] = j;
				n++;
			}
			j++;
		}
		i++;
	}
}

void	count_enemies(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	game->enemies = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			if (game->map[i][j] == 'N')
				game->enemies++;
			j++;
		}
		i++;
	}
	alloc_arr(game);
	fill_arr(game);
}

void	enemy_refresh(t_game *game, int *i)
{
	int			n;
	int			j;

	if (*i < 8000)
		(*i)++;
	else
		*i = 0;
	if (*i == 0)
	{
		n = 0;
		while (game->map[n])
		{
			j = 0;
			while (game->map[n][j])
			{
				if (game->map[n][j] == 'N')
				{
					mlx_put_image_to_window(game->mlx, game->window,
						game->floor, 64 * j, 64 * n);
				}
				j++;
			}
			n++;
		}
	}
}

int	enemy_moves(t_game *game)
{
	static int	i = 0;
	int			n;
	int			j;

	enemy_refresh(game, &i);
	if (i == 4000)
	{
		n = 0;
		while (game->map[n])
		{
			j = 0;
			while (game->map[n][j])
			{
				if (game->map[n][j] == 'N')
				{
					mlx_put_image_to_window(game->mlx, game->window,
						game->enemy, 64 * j, 64 * n);
				}
				j++;
			}
			n++;
		}
	}
	game_over(game);
	return (0);
}
