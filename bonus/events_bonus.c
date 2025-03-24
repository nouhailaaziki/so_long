/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 11:52:18 by noaziki           #+#    #+#             */
/*   Updated: 2025/03/24 15:49:04 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	destroy_images(t_game *game)
{
	if (game->wall)
		mlx_destroy_image(game->mlx, game->wall);
	if (game->floor)
		mlx_destroy_image(game->mlx, game->floor);
	if (game->door)
		mlx_destroy_image(game->mlx, game->door);
	if (game->pikachu)
		mlx_destroy_image(game->mlx, game->pikachu);
	if (game->coin)
		mlx_destroy_image(game->mlx, game->coin);
	if (game->enemy)
		mlx_destroy_image(game->mlx, game->enemy);
	mlx_destroy_window(game->mlx, game->window);
}

void	print_error(char *message, t_game *game)
{
	if (game)
	{
		if (game->map)
			free_game(game->map);
	}
	write(2, message, ft_strlen(message));
	exit (1);
}

int	close_game(t_game *game)
{
	if (game->map)
		free_game(game->map);
	if (game->enemies_x)
		free (game->enemies_x);
	if (game->enemies_y)
		free (game->enemies_y);
	destroy_images(game);
	exit(0);
}

void	free_game(char **map)
{
	int	i;

	i = 0;
	if (!map)
		return ;
	while (map[i])
	{
		free (map[i]);
		i++;
	}
	free (map);
}

void	game_over(t_game *game)
{
	int	i;

	i = 0;
	position(game, 'P');
	while (i < game->enemies)
	{
		if (game->player_x == game->enemies_x[i]
			&& game->player_y == game->enemies_y[i])
		{
			write(1, "Game over : You lose!!\n", 24);
			close_game(game);
		}
		i++;
	}
}
