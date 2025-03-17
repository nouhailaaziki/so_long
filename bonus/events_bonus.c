/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 11:52:18 by noaziki           #+#    #+#             */
/*   Updated: 2025/03/17 16:30:16 by noaziki          ###   ########.fr       */
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

void	putuns(unsigned int nbr)
{
	char	c;

	c = nbr + 48;
	if (nbr <= 9)
		write(1, &c, 1);
	else
	{
		putuns(nbr / 10);
		putuns(nbr % 10);
	}
}

void	print_error(char *message, t_game *game)
{
	if (game)
	{
		if (game->map)
		{
			free_game(game->map);
		}
		free(game);
	}
	write(2, message, ft_strlen(message));
	exit (1);
}

int	close_game(t_game *game)
{
	if (game)
	{
		if (game->map)
			free_game(game->map);
		free(game);
	}
	exit(0);
	return (0);
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
