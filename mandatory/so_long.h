/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 11:14:51 by noaziki           #+#    #+#             */
/*   Updated: 2025/03/13 17:37:04 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <mlx.h>
# include <limits.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include "../libft/libft.h"
# include "get_next_line.h"

typedef struct s_game
{
	int				i;
	int				j;
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
	unsigned int	moves;
}	t_game;

int		check_valid(t_game *game);
int		check_close(t_game *game);
int		check_rectangular(t_game *game);
int		check_content(t_game *game, char **map, char *str);
int		check_map_validity(t_game *game, char *filename);
int		check_path(t_game *game, char *filename);
int		count_lines(char *filename, t_game *game);
int		close_game(t_game *game);
int		handle_keypress(int keycode, t_game *game);
void	position(t_game *game, char c);
void	free_game(char **map);
void	print_error(char *message, t_game *game);
void	read_map(char *filename, t_game *game, char **map);
void	render_map(t_game *game);
void	count_collected(t_game	*game);
void	draw_map(t_game *game);
void	putuns(unsigned int nbr);

#endif
