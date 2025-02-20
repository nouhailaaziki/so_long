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
	int				map_width;    // Largeur de la carte
	int				map_height;   // Hauteur de la carte
	int				player;       // Number of players
	int				collectibles; // Nombre total de collectibles
	int				exit;         // Number of exit doors
	int				img_width;    // Largeur de l'image
	int				img_height;   // Hauteur de l'image
	char			**map;        // Carte du jeu (tableau 2D)
	char			**map2;       // Carte du jeu (tableau 2D)
	int				player_x;     // Player's X position
	int				player_y;     // Player's Y position
	int				collected;    // Nombre de collectibles ramassés
	void			*mlx;         // Pointeur pour MiniLibX
	void			*window;      // Fenêtre MiniLibX
	void			*pikachu;     // the player
	void			*wall;        // It is symbolized by 1 on the map
	void			*door;        // It is symbolized by E on the map.
	void			*coin;        // It is symbolized by C on the map.
	void			*floor;       // It is symbolized by 0 on the map.
	unsigned int	moves;        // Nombre de déplacements du joueur
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
