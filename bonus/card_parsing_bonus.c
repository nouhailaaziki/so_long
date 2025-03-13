/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   card_parsing_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 11:48:03 by noaziki           #+#    #+#             */
/*   Updated: 2025/03/12 15:58:36 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	check_content(t_game *game, char **map, char *str)
{
	game->i = 0;
	while (map[game->i])
	{
		game->j = 0;
		while (map[game->i][game->j])
		{
			if (ft_strchr(str, map[game->i][game->j]) == NULL)
				return (1);
			game->j++;
		}
		game->i++;
	}
	return (0);
}

int	check_valid(t_game *game)
{
	game->i = 0;
	game->player = 0;
	game->collectibles = 0;
	game->exit = 0;
	while (game->map[game->i])
	{
		game->j = 0;
		while (game->map[game->i][game->j])
		{
			if (game->map[game->i][game->j] == 'P')
				game->player++;
			if (game->map[game->i][game->j] == 'C')
				game->collectibles++;
			if (game->map[game->i][game->j] == 'E')
				game->exit++;
			game->j++;
		}
		game->i++;
	}
	if (game->player != 1 || !game->collectibles || game->exit != 1)
		return (1);
	return (0);
}

int	check_close(t_game *game)
{
	game->map_height = 0;
	while (game->map[game->map_height])
	{
		if (game->map[game->map_height][0] != '1'
		|| game->map[game->map_height][game->map_width - 1] != '1')
			return (1);
		game->map_height++;
	}
	game->map_width = 0;
	while (game->map[game->map_height - 1][game->map_width])
	{
		if (game->map[0][game->map_width] != '1'
		|| game->map[game->map_height - 1][game->map_width] != '1')
			return (1);
		game->map_width++;
	}
	return (0);
}

int	check_rectangular(t_game *game)
{
	game->map_width = 0;
	while (game->map[0][game->map_width])
		game->map_width++;
	game->i = 1;
	game->j = 0;
	while (game->map[game->i])
	{
		while (game->map[game->i][game->j])
			game->j++;
		if (game->j != game->map_width)
			return (1);
		game->j = 0;
		game->i++;
	}
	return (0);
}

int	check_map_validity(t_game *game, char *filename)
{
	if (check_rectangular(game))
		print_error("Error\nthe map must be rectangular!\n", game);
	if (check_close(game))
		print_error("Error\nthe map must be closed!\n", game);
	if (check_valid(game) || check_content(game, game->map, "01PCE"))
		print_error("Error\nthe map is not valid!\n", game);
	if (game->map_height > 22 || game->map_width > 40)
		print_error("Error!\nThe map exceeds the screen area!\n", game);
	if (check_path(game, filename))
		print_error("Error\nthe path is not valid!\n", game);
	render_map(game);
	return (0);
}
