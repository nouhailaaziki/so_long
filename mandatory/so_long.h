/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 11:14:51 by noaziki           #+#    #+#             */
/*   Updated: 2025/02/18 16:02:45 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <mlx.h>
# include <limits.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include "../libraries/libft/libft.h"
# include "../libraries/get_next_line/get_next_line.h"

// Structure principale du jeu
typedef struct s_game
{
	int				i;            // first index
	int				j;            //second index
	int				map_width;    // Map width
	int				map_height;   // Map height
	int				player;       // Number of players
	int				collectibles; // Total number of collectibles
	int				exit;         // Number of exit doors
	int				img_width;    // Image width
	int				img_height;   // Image height
	char			**map;        // Game Map (2D array)
	char			**map2;       // Game Map (2D array)
	int				player_x;     // Player's X position
	int				player_y;     // Player's Y position
	int				collected;    // number of remaining collectibles
	void			*mlx;         // Pointer for MiniLibX
	void			*window;      // MiniLibX Window
	void			*pikachu;     // the player and It is symbolized by P on the map.
	void			*wall;        // It is symbolized by 1 on the map.
	void			*door;        // It is symbolized by E on the map.
	void			*coin;        // It is symbolized by C on the map.
	void			*floor;       // It is symbolized by 0 on the map.
	unsigned int	moves;        // Number of player moves
}	t_game;

int		check_valid(t_game *game);
int		check_close(t_game *game);
int		check_rectangular(t_game *game);
int		check_content(t_game *game, char **map, char *str);
int		check_map_validity(t_game *game, char *filename);
int		check_path(t_game *game, char *filename);
int		count_lines(char *filename);
int		close_game(t_game *game);
int		handle_keypress(int keycode, t_game *game);
void	position(t_game *game, char c);
void	free_game(char **map);
void	print_error(char *message, t_game *game);
void	read_map(char *filename,t_game *game, char **map);
void	render_map(t_game *game);
void	count_collected(t_game	*game);
void	draw_map(t_game *game);
void	putuns(unsigned int nbr);

#endif
