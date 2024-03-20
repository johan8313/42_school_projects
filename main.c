/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johmarti <johmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 12:20:36 by johmarti          #+#    #+#             */
/*   Updated: 2024/03/20 17:04:36 by johmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	handle_keypress(int keysym, t_game *data)
{
	if (keysym == XK_Escape)
	{
		mlx_destroy_image(data->mlx_ptr, data->wall);
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
		exit(0);
	}

	printf("Keypress: %d\n", keysym);
	return (0);
}

int	handle_keyrelease(int keysym)
{
	printf("Keyrelease: %d\n", keysym);
	return (0);
}

void	fill_list(t_list **map, char c, int x, int y)
{
	t_list	*mp = malloc(sizeof(*mp));
	t_list	*temp = *map;

	mp->data = c;
	mp->x = x;
	mp->y = y;
	mp->next = NULL;
	if (!(*map))
	{
		mp->prev = NULL;
		*map = mp;
	}
	else
	{
		while (temp->next != NULL)
		{
			temp = temp->next;
		}
		mp->prev = temp;
		temp->next = mp;
	}
}
t_list	*get_map(t_game *game, char *map_path)
{
	int		fd;
	char	*line;
	int		x;
	int		y;

	fd = open(map_path, O_RDONLY);
	if (fd == -1)
	{
		ft_printf("Error\nFile not found or empty\n");
		return (0);
	}
	x = 0;
	y = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		while (line[x] != '\n')
		{
			fill_list(&game->map, line[x], x, y);
			x++;
		}
		x = 0;
		line = get_next_line(fd);
		y++;
	}
	close(fd);
	return (game->map);
}

int	check_file_format(char *map_path)
{
	int	end;

	end = ft_strlen(map_path);
	if (map_path[end - 4] != '.' || map_path[end - 3] != 'b'
		|| map_path[end - 2] != 'e' || map_path[end - 1] != 'r')
		return (0);
	return (1);
}

int	check_map_elements(t_list *map)
{
	int	count_C;
	int	count_E;
	int	count_P;

	count_C = 0;
	count_E = 0;
	count_P = 0;
	while (map->next != NULL)
	{
		if (map->data == 'C')
			count_C++;
		if (map->data == 'E')
			count_E++;
		if (map->data == 'P')
			count_P++;
		map = map->next;
	}
	if (count_C == 0 || count_E != 1 || count_P != 1)
		return (0);
	return (1);
}

int	check_if_map_is_rectangle(t_game *game, t_list *map)
{
	int i;

	i = 0;
	while (map->next->y != 1)
		map = map->next;
	game->x_max = map->x;
	while (map->next != NULL)
	{
		map = map ->next;
		while (i < game->x_max)
		{
			map = map->next;
			i++;
		}
		i = 0;
		if (map->x != game->x_max)
			return (0);
	}
	game->y_max = map->y;
	if (game->y_max == game->x_max)
		return (0);
	return (1);
}

t_list *moove_up(t_game *game, t_list *map)
{
	printf("entering > moove_up\n");
	int	i;

	i = game->x_max;
	while (i > 0)
	{
		map = map->prev;
		i--;
	}
	return (map);
}
t_list *moove_down(t_game *game, t_list *map)
{
	printf("entering > moove_down\n");
	int	i;

	i = 0;
	while (i < game->x_max)
	{
		map = map->next;
		i++;
	}
	return (map);
}

int	check_path(t_game *game, t_list *map)
{
	printf("entering > check_path\n");
	if (map->data == '1')
	{
		printf("entering > map->data == 1\n");
		printf("x : %d\n", map->x);
		printf("y : %d\n", map->y);
		printf("data : %c\n", map->data);
		return (0);
	}
	if (map->data == 'P')
	{
		printf("entering > map->data == P\n");
		printf("x : %d\n", map->x);
		printf("y : %d\n", map->y);
		printf("data : %c\n", map->data);
		return (1);
	}
	printf("before: map->data = 1\n");
	printf("x : %d\n", map->x);
	printf("y : %d\n", map->y);
	printf("data : %c\n", map->data);
	map->data = '1';
	printf("After: map->data = 1\n");
	printf("x : %d\n", map->x);
	printf("y : %d\n", map->y);
	printf("data : %c\n", map->data);
	printf("next\n");
	if (check_path(game, map->next) == 1)
	{
		printf("entering > check_path x + 1\n");
		printf("x : %d\n", map->x);
		printf("y : %d\n", map->y);
		printf("data : %c\n", map->data);
		return (1);
	}
	printf("up\n");
	if (check_path(game, moove_up(game, game->map)) == 1)
	{
		printf("entering > check_path y + 1\n");
		printf("x : %d\n", map->x);
		printf("y : %d\n", map->y);
		printf("data : %c\n", map->data);
	}
	return (1);
	printf("prev\n");
	if (check_path(game, map->prev) == 1)
	{
		printf("entering > check_path x - 1\n");
		printf("x : %d\n", map->x);
		printf("y : %d\n", map->y);
		printf("data : %c\n", map->data);
		return (1);
	}
	printf("down\n");
	if (check_path(game, moove_down(game, game->map)) == 1)
	{
		printf("entering > check_path y + 1\n");
		printf("x : %d\n", map->x);
		printf("y : %d\n", map->y);
		printf("data : %c\n", map->data);
		return (1);
	}
	printf("before return (0)\n");
	return (0);
}

int	check_map_path(char *map_path)
{
	printf("entering > check_map_path\n");
	t_game game_new;

	game_new.map = get_map(&game_new, map_path);
	check_if_map_is_rectangle(&game_new, game_new.map);
	while (game_new.map != NULL)
	{
		printf("boucle while\n");
		printf("x : %d\n", game_new.map->x);
		printf("y : %d\n", game_new.map->y);
		printf("data : %c\n", game_new.map->data);
		if ((game_new.map->data == 'C' || game_new.map->data == 'E')
			&& (check_path(&game_new, game_new.map) == 0))
			return (0);
		game_new.map = game_new.map->next;
	}
	return (1);
}

int	check_if_map_walled(t_game *game, t_list *map)
{
	while (map != NULL)
	{
		if (map->y == 0 && map->data != '1')
			return (0);
		else if (map->x == 0 && map->data != '1')
			return (0);
		else if (map->x == game->x_max && map->data != '1')
			return (0);
		else if (map->y == game->y_max && map->data != '1')
			return (0);
		map = map->next;
	}
	return (1);
}
int	check_map_data(t_list *map)
{
	while (map != NULL)
	{
		if (map->data != '1' || map->data != 'P'
			|| map->data != 'C' || map->data != '0'
				|| map->data != 'E')
				return (0);
		map = map->next;
	}

	return (1);
}

int	check_map(t_game *game, char *map_path)
{
	if (check_if_map_is_rectangle(game, game->map) == 0)
		ft_printf("Error\nMap is not a rectangle");
	else if (check_map_elements(game->map) == 0)
		ft_printf("Error\nMap elements (Missing Collectibles or too many Exits/Players)");
	else if (check_if_map_walled(game, game->map) == 0)
		ft_printf("Error\nMap is not fully walled");
	else if (check_map_path(map_path) == 0)
		ft_printf("Error\nMap not solvable");
	//else if (check_map_data(map) == 0)
		//ft_printf("Error\nMap not comformed (expected 1 0 P C E char)");
	return (1);
}

int	main(int argc, char **argv)
{
	t_game	game;

	char	*wall_path = "./texture/wall.xpm";
	char	*character_path = "./texture/characters.xpm";
	char	*coin_path = "./texture/coin.xpm";
	char	*exit_path = "./texture/exit.xpm";

	if (argc != 2)
	{
		ft_printf("Error\n2 parameters only accepted\n");
		return (0);
	}
	if (check_file_format(argv[1]) == 0)
	{
		ft_printf("Error\nWrong file format (expected: .ber)\n");
		return (0);
	}
	game.mlx_ptr = mlx_init();
	game.map = NULL;
	game.img_height = 64;
	game.img_width = 64;
	game.map = get_map(&game, argv[1]);
	check_map(&game, argv[1]);

	game.win_ptr = mlx_new_window(game.mlx_ptr, (game.x_max + 1)*game.img_width, (game.y_max + 1)*game.img_height, "So_long");
	game.wall = mlx_xpm_file_to_image(game.mlx_ptr, wall_path, &game.img_width, &game.img_height);
	game.characters = mlx_xpm_file_to_image(game.mlx_ptr, character_path, &game.img_width, &game.img_height);
	game.coin = mlx_xpm_file_to_image(game.mlx_ptr, coin_path, &game.img_width, &game.img_height);
	game.exit = mlx_xpm_file_to_image(game.mlx_ptr, exit_path, &game.img_width, &game.img_height);

while (game.map != NULL)
{
		if(game.map->data == '1')
			mlx_put_image_to_window(game.mlx_ptr, game.win_ptr, game.wall,game.map->x * game.img_width, game.map->y * game.img_height);
		else if(game.map->data == 'P')
			mlx_put_image_to_window(game.mlx_ptr, game.win_ptr, game.characters,game.map->x * game.img_width, game.map->y * game.img_height);
		else if (game.map->data == 'C')
			mlx_put_image_to_window(game.mlx_ptr, game.win_ptr, game.coin,game.map->x * game.img_width, game.map->y * game.img_height);
		else if (game.map->data == 'E')
			mlx_put_image_to_window(game.mlx_ptr, game.win_ptr, game.exit,game.map->x * game.img_width, game.map->y * game.img_height);
	game.map = game.map->next;
}
mlx_loop(game.mlx_ptr);
}
/*
	//ft_printf("x = %d\n", map.x);
	//ft_printf("y = %d\n", map.y);
	//game.wall = mlx_xpm_file_to_image(game.mlx_ptr, relative_path, &img_width, &img_height);
	//printf("width : %d , height : %d\n", img_width, img_height);
	//game.win_ptr = mlx_new_window(game.mlx_ptr, 10*img_width, 5*img_height, "So_long");
	//mlx_put_image_to_window(game.mlx_ptr, game.win_ptr, game.img, 0, 0);

line  = 0;
while (line < 10)
{
	mlx_put_image_to_window(game.mlx_ptr, game.win_ptr, game.img, line*img_width, 0);
	line++;
}
colum = 0;
while (colum < 5)
{
	mlx_put_image_to_window(game.mlx_ptr, game.win_ptr, game.img, 0, colum*img_height);
	colum++;
}
	mlx_hook(game.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &game);
	mlx_hook(game.win_ptr, KeyRelease, KeyReleaseMask, &handle_keyrelease, &game);

	//mlx_loop(game.mlx_ptr);
}
*/
