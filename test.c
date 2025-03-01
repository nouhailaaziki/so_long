#ifndef SO_LONG_BONUS_H
# define SO_LONG_BONUS_H

# include <mlx.h>
# include <limits.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include "../libraries/libft/libft.h"
# include "../libraries/get_next_line/get_next_line.h"

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
	int				enemy_count;
	int				enemy_y;
	int				enemy_x1;
	int				enemy_x2;
	int				enemy_pos;
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
void	check_enemy_path(t_game *game, char *filename);
void	flood_fill(char **map, int x, int y);
void	initialize_enemy(t_game *game);
int		handle_enemy_move(t_game *game);

#endif

void	read_map(char *filename, t_game *game, char **map)
{
	int		fd;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		print_error("Error\nfile cannot be opened!\n", game);
	game->i = 0;
	line = get_next_line(fd);
	while (line)
	{
		if ((ft_strncmp(line, "\n", 1)) == 0 || ft_strlen(line) == 0)
		{
			free(line);
			close (fd);
			print_error("Error\nline is empty!", game);
		}
		map[game->i] = ft_strdup(line);
		free(line);
		if (map[game->i][ft_strlen(map[game->i]) - 1] == '\n')
			map[game->i][ft_strlen(map[game->i]) - 1] = '\0';
		game->i++;
		line = get_next_line(fd);
	}
	map[game->i] = NULL;
	close (fd);
}

int	count_lines(char *filename, t_game *game)
{
	int		fd;
	int		count;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		print_error("Error\nfile cannot be opened!\n", game);
	count = 0;
	line = get_next_line(fd);
	if (!line)
	{
		close(fd);
		print_error("Error\nEmpty file or read error!\n", game);
	}
	while (line)
	{
		count++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (count);
}

int	main(int argc, char **argv)
{
	t_game	*game;
	int		lines;

	if (argc == 2)
	{
		if (ft_strchr(argv[1], '.')
			&& (ft_strncmp(ft_strchr(argv[1], '.'), ".ber", 6)) == 0)
		{
			game = malloc(sizeof(t_game));
			if (!game)
				print_error("Error\nMemory allocation failed!\n", NULL);
			lines = count_lines(argv[1], game);
			game->map = malloc((lines + 1) * sizeof(char *));
			if (!game->map)
				print_error("Error\nMemory allocation failed for map!\n", game);
			read_map(argv[1], game, game->map);
			check_map_validity(game, argv[1]);
			free_game(game->map);
			free(game);
		}
		else
			print_error("Error\nThe map name must be .ber!\n", NULL);
	}
	else
		print_error("Error\nThe number of arguments must be 2!\n", NULL);
}

void	player_up(t_game *game)
{
	count_collected(game);
	position(game, 'P');
	if (game->map[game->player_x - 1][game->player_y] == '0'
		|| game->map[game->player_x - 1][game->player_y] == 'C')
	{
		if (game->map[game->player_x - 1][game->player_y] == 'C')
			game->collected--;
		game->map[game->player_x - 1][game->player_y] = 'P';
		game->map[game->player_x][game->player_y] = '0';
	}
	if (game->map[game->player_x - 1][game->player_y] == 'E'
		&& game->collected == 0)
		(write(1, "Victory! You did it!\n", 22), close_game(game));
	game->pikachu = mlx_xpm_file_to_image(game->mlx,
			"textures/player_back.xpm", &game->img_width, &game->img_height);
	draw_map(game);
}

void	player_down(t_game *game)
{
	count_collected(game);
	position(game, 'P');
	if (game->map[game->player_x + 1][game->player_y] == '0'
		|| game->map[game->player_x + 1][game->player_y] == 'C')
	{
		if (game->map[game->player_x + 1][game->player_y] == 'C')
			game->collected--;
		game->map[game->player_x + 1][game->player_y] = 'P';
		game->map[game->player_x][game->player_y] = '0';
	}
	if (game->map[game->player_x + 1][game->player_y] == 'E'
		&& game->collected == 0)
		(write(1, "Victory! You did it!\n", 22), close_game(game));
	game->pikachu = mlx_xpm_file_to_image(game->mlx,
			"textures/player.xpm", &game->img_width, &game->img_height);
	draw_map(game);
}

void	player_right(t_game *game)
{
	count_collected(game);
	position(game, 'P');
	if (game->map[game->player_x][game->player_y + 1] == '0'
		|| game->map[game->player_x][game->player_y + 1] == 'C')
	{
		if (game->map[game->player_x][game->player_y + 1] == 'C')
			game->collected--;
		game->map[game->player_x][game->player_y + 1] = 'P';
		game->map[game->player_x][game->player_y] = '0';
	}
	if (game->map[game->player_x][game->player_y + 1] == 'E'
		&& game->collected == 0)
		(write(1, "Victory! You did it!\n", 22), close_game(game));
	game->pikachu = mlx_xpm_file_to_image(game->mlx,
			"textures/player_right.xpm", &game->img_width, &game->img_height);
	draw_map(game);
}

void	player_left(t_game *game)
{
	count_collected(game);
	position(game, 'P');
	if (game->map[game->player_x][game->player_y - 1] == '0'
		|| game->map[game->player_x][game->player_y - 1] == 'C')
	{
		if (game->map[game->player_x][game->player_y - 1] == 'C')
			game->collected--;
		game->map[game->player_x][game->player_y - 1] = 'P';
		game->map[game->player_x][game->player_y] = '0';
	}
	if (game->map[game->player_x][game->player_y - 1] == 'E'
		&& game->collected == 0)
		(write(1, "Victory! You did it!\n", 22), close_game(game));
	game->pikachu = mlx_xpm_file_to_image(game->mlx,
			"textures/player_left.xpm", &game->img_width, &game->img_height);
	draw_map(game);
}

int	handle_keypress(int keycode, t_game *game)
{
	count_collected(game);
	if (game->collected == 0)
	{
		game->door = mlx_xpm_file_to_image(game->mlx,
				"textures/door.xpm", &game->img_width, &game->img_height);
		draw_map(game);
	}
	if (keycode == 126)
		player_up(game);
	if (keycode == 125)
		player_down(game);
	if (keycode == 124)
		player_right(game);
	if (keycode == 123)
		player_left(game);
	else if (keycode == 53)
		close_game(game);
	return (0);
}

void	print_error(char *message, t_game *game)
{
	if (game)
	{
		if (game->map)
			free_game(game->map);
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

void	check(t_game *game, int *s)
{
	game->enemy_y = game->i;
	game->enemy_x1 = game->j;
	while (game->map[game->i][game->j] == '0')
	{
		(*s)++;
		game->j++;
	}
}

void	initialize_enemy(t_game *game)
{
	int	s;

	game->i = 1;
	while(game->i < game->map_height - 1)
	{
		game->j = 1;
		s = 0;
		while(game->j < game->map_width - 1)
		{
			if (game->map[game->i][game->j] == '0')
			{
				check(game, &s);
				game->enemy_x2 = game->j - 1;
				break ;
			}
			game->j++;
		}
		if (s > 2)
			break ;
		game->i++;
	}
}

void	game_over(t_game *game)
{
	if (game->player_x == game->enemy_y
	&& game->player_y == game->enemy_pos)
		print_error("Game Over! You lost this time!", game);
}
int	handle_enemy_move(t_game *game)
{
	static int	counter = 0;
	static int	direction = 1;

	if (counter < 6000)
		counter++;
	else
		counter = 0;
	if (counter == 0)
	{
		mlx_put_image_to_window(game->mlx, game->window, game->floor,
			64 * game->enemy_pos, 64 * game->enemy_y);
		if (game->enemy_pos == game->enemy_x2)
			direction = -1;
		else if (game->enemy_pos == game->enemy_x1)
			direction = 1;
		if (direction > 0 && game->enemy_pos < game->enemy_x2)
			game->enemy_pos++;
		else if (direction < 0 && game->enemy_pos > game->enemy_x1)
			game->enemy_pos--;
	}
	if (counter == 3000)
		mlx_put_image_to_window(game->mlx, game->window, game->enemy,
			64 * game->enemy_pos, 64 * game->enemy_y);
	game_over(game);
	return (0);
}
void	put_image(char c, t_game *game)
{
	if (c == 'E')
		mlx_put_image_to_window(game->mlx, game->window,
			game->door, game->j * 64, game->i * 64);
	if (c == 'P')
		mlx_put_image_to_window(game->mlx, game->window,
			game->pikachu, game->j * 64, game->i * 64);
	if (c == '1')
		mlx_put_image_to_window(game->mlx, game->window,
			game->wall, game->j * 64, game->i * 64);
	if (c == '0')
		mlx_put_image_to_window(game->mlx, game->window,
			game->floor, game->j * 64, game->i * 64);
	if (c == 'C')
		mlx_put_image_to_window(game->mlx, game->window,
			game->coin, game->j * 64, game->i * 64);
}
void	draw_map(t_game *game)
{
	game->i = 0;
	while (game->map[game->i])
	{
		game->j = 0;
		while (game->map[game->i][game->j])
		{
			put_image(game->map[game->i][game->j], game);
			game->j++;
		}
		game->i++;
	}
	char *moves_str;
	moves_str = ft_itoa(game->moves);
	mlx_string_put(game->mlx, game->window, 10, 10, 0xFFFFFF, moves_str);
	free(moves_str);
}

void	xpm_to_img(t_game *game)
{
	game->pikachu = mlx_xpm_file_to_image(game->mlx,
			"textures/player.xpm", &game->img_width, &game->img_height);
	game->door = mlx_xpm_file_to_image(game->mlx,
			"textures/door.xpm", &game->img_width, &game->img_height);
	game->wall = mlx_xpm_file_to_image(game->mlx,
			"textures/wall.xpm", &game->img_width, &game->img_height);
	game->coin = mlx_xpm_file_to_image(game->mlx,
			"textures/pokeball.xpm", &game->img_width, &game->img_height);
	game->floor = mlx_xpm_file_to_image(game->mlx,
			"textures/floor.xpm", &game->img_width, &game->img_height);
	game->enemy = mlx_xpm_file_to_image(game->mlx,
			"textures/enemy.xpm", &game->img_width, &game->img_height);
	if (!game->pikachu || !game->door || !game->wall
		|| !game->coin || !game->floor || !game->enemy)
		print_error("Error\nimage name is not compatible!\n", game);
}

void	count_collected(t_game	*game)
{
	game->i = 0;
	game->collected = 0;
	while (game->map[game->i])
	{
		game->j = 0;
		while (game->map[game->i][game->j])
		{
			if (game->map[game->i][game->j] == 'C')
				game->collected++;
			game->j++;
		}
		game->i++;
	}
}

void	render_map(t_game *game)
{
	game->moves = 0;
	game->mlx = mlx_init();
	if (!game->mlx)
		(print_error("Error\nUnable to initialize MLX!\n", game));
	game->window = mlx_new_window(game->mlx,
			game->map_width * 64, game->map_height * 64,
			"Welcome to Pikachu's game! Let the adventure begin!");
	if (!game->window)
		print_error("Error\nfailed to create MLX window!\n", game);
	xpm_to_img(game);
	draw_map(game);
	mlx_hook(game->window, 2, 1L << 0, handle_keypress, game);
	if (game->enemy_y != 0 && game->enemy_x1 != 0 && game->enemy_x2 != 0)
	{
		game->enemy_pos = game->enemy_x1;
		mlx_loop_hook(game->mlx, handle_enemy_move, game);
	}
	else
		print_error("Error\nno valid space for enemy!\n", game);
	mlx_hook(game->window, 17, 1L << 0, close_game, game);
	mlx_loop(game->mlx);
}

void	flood_fill(char **map, int x, int y)
{
	if (map[x][y] == '1' || map[x][y] == 'A'
		|| map[x][y] == 'E' || map[x][y] == 'N')
		return ;
	if (map[x][y] == '0' || map[x][y] == 'C')
		map[x][y] = 'A';
	flood_fill(map, x + 1, y);
	flood_fill(map, x - 1, y);
	flood_fill(map, x, y + 1);
	flood_fill(map, x, y - 1);
}

void	position(t_game *game, char c)
{
	game->i = 0;
	while (game->map[game->i])
	{
		game->j = 0;
		while (game->map[game->i][game->j])
		{
			if (game->map[game->i][game->j] == c)
			{
				game->player_x = game->i;
				game->player_y = game->j;
			}
			game->j++;
		}
		game->i++;
	}
}

int	check_exit(t_game *game)
{
	position(game, 'E');
	if (game->map2[game->player_x + 1][game->player_y] == 'A'
	|| game->map2[game->player_x - 1][game->player_y] == 'A'
	|| game->map2[game->player_x][game->player_y + 1] == 'A'
	|| game->map2[game->player_x][game->player_y - 1] == 'A')
		return (0);
	return (1);
}

int	check_path(t_game *game, char *filename)
{
	int		lines;

	game->enemy_y = 0;
	game->enemy_x1 = 0;
	game->enemy_x2 = 0;
	lines = count_lines(filename, game);
	position(game, 'P');
	game->map2 = malloc((lines + 1) * sizeof(char *));
	if (!game->map2)
		print_error("Error\nMemory allocation failed for map!\n", game);
	read_map(filename, game, game->map2);
	flood_fill(game->map2, game->player_x, game->player_y);
	if (check_content(game, game->map2, "01PAE") || check_exit(game))
		return (free_game(game->map2), 1);
	initialize_enemy(game);
	check_enemy_path(game, filename);
	return (free_game(game->map2), 0);
}

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
	if (game->player != 1 || !game->collectibles
		|| game->exit != 1)
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
	if (check_valid(game) || check_content(game, game->map, "01PCEN"))
		print_error("Error\nthe map is not valid!\n", game);
	if (check_path(game, filename))
		print_error("Error\nthe path is not valid!\n", game);
	render_map(game);
	return (0);
}
