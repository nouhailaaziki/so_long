/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_path_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 18:21:46 by noaziki           #+#    #+#             */
/*   Updated: 2025/03/01 11:06:41 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	verify(char **map, t_game *game)
{
	game->i = 0;
	while (map[game->i])
	{
		game->j = 0;
		while (map[game->i][game->j])
		{
			if ((map[game->i][game->j] == 'C') || (map[game->i][game->j] == 'E'
			&& map[game->i][game->j - 1] != 'N' && map[game->i][game->j + 1] != 'N'
			&& map[game->i - 1][game->j] != 'N' && map[game->i + 1][game->j] != 'N'))
				return (0);
			game->j++;
		}
		game->i++;
	}
	return (1);
}
void	check_enemy_path(t_game *game, char *filename)
{
	int		lines;

	while (1)
	{
		lines = count_lines(filename, game);
		position(game, 'P');
		game->map2 = malloc((lines + 1) * sizeof(char *));
		if (!game->map2)
			print_error("Error\nMemory allocation failed for map!\n", game);
		read_map(filename, game, game->map2);
		game->map2[game->enemy_y][game->enemy_x1] = 'N';
		flood_fill(game->map2, game->player_x, game->player_y);
		if (verify(game->map2, game))
		{
			free_game (game->map2);
			break ;
		}
		if (game->enemy_y + 1 >= game->img_height - 2)
		{
			free_game (game->map2);
			print_error("Error\nYour map is unwinnable! Try adjusting it.\n", game);
		}
		game->enemy_y += 1;
		initialize_enemy(game);
	}
}
