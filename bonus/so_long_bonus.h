/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 11:14:51 by noaziki           #+#    #+#             */
/*   Updated: 2025/03/17 15:45:08 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_BONUS_H
# define SO_LONG_BONUS_H

# include <mlx.h>
# include <limits.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include "../libft/libft.h"
# include "get_next_line_bonus.h"

typedef struct s_game
{
	int				i;
	int				j;
	int				x;
	int				y;
	int				map_width;
	int				map_height;
	int				player;
	int				collectibles;
	int				exit;
	int				img_width;
	int				img_height;
	int				player_x;
	int				player_y;
	int				collected;
	int				lines;
	char			**map;
	char			**map2;
	void			*mlx;
	void			*window;
	void			*pikachu;
	void			*wall;
	void			*door;
	void			*coin;
	void			*floor;
	void			*enemy;
	unsigned int	moves;
}	t_game;

int		check_valid(t_game *game);
int		check_close(t_game *game);
int		check_rectangular(t_game *game);
int		check_content(t_game *game, char **map, char *str);
int		check_map_validity(t_game *game, char *filename);
int		check_path(t_game *game, char *filename);
int		close_game(t_game *game);
int		handle_keypress(int keycode, t_game *game);
int		check_exit(t_game *game);
int		enemy_moves(t_game *game);
void	count_lines(char *filename, t_game *game);
void	position(t_game *game, char c);
void	free_game(char **map);
void	print_error(char *message, t_game *game);
void	read_map(char *filename, t_game *game, char **map);
void	render_map(t_game *game);
void	count_collected(t_game	*game);
void	draw_map(t_game *game);
void	render_moves_counter(t_game *game);
void	place_enemy(t_game *game);
void	draw_game_objects(t_game *game);
int		enemy_moves(t_game *game);
#endif
