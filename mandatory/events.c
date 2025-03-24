/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 11:52:18 by noaziki           #+#    #+#             */
/*   Updated: 2025/03/24 15:48:46 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
	mlx_destroy_window(game->mlx, game->window);
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
			free_game(game->map);
	}
	write(2, message, ft_strlen(message));
	exit(1);
}

int	close_game(t_game *game)
{
	if (game->map)
		free_game(game->map);
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
