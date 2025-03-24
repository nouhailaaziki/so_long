/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 11:14:51 by noaziki           #+#    #+#             */
/*   Updated: 2025/03/24 15:44:37 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_BONUS_H
# define SO_LONG_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <mlx.h>
# include <limits.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include "../libft/libft.h"

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
	int				enemies;
	int				*enemies_x;
	int				*enemies_y;
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

char	*get_next_line(int fd);
char	*ft_strdup(const char *s);
char	*ft_strchr(const char *s, int c);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_substr(const char *s, unsigned int start, size_t len);
size_t	ft_strlen(const char *str);

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
void	copy_map(t_game *game);
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
void	game_over(t_game *game);
void	count_enemies(t_game *game);
void	destroy_images(t_game *game);

#endif
