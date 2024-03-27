/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johmarti <johmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 12:20:36 by johmarti          #+#    #+#             */
/*   Updated: 2024/03/27 15:10:04 by johmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	free_game(t_game *game, int type)
{
	if (game->map != NULL)
		free_map(&game->map);
	if (type == 1)
	{
		mlx_destroy_image(game->mlx, game->img.wall);
		mlx_destroy_image(game->mlx, game->img.empty);
		mlx_destroy_image(game->mlx, game->img.exit);
		mlx_destroy_image(game->mlx, game->img.characters);
		mlx_destroy_image(game->mlx, game->img.coin);
		mlx_destroy_window(game->mlx, game->win);
	}
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	exit(0);
}

void	free_map(t_list **map)
{
	t_list *current_node = *map;
	t_list *next_node;

	while (current_node != NULL)
	{
		next_node = current_node->next;
		free(current_node);
		current_node = next_node;
		}
	*map = NULL;
}

void	game_launch(t_game *game)
{
	set_img(game);
	game->win = mlx_new_window(game->mlx, (game->x_max + 1) * game->img_width,
			(game->y_max + 1) * game->img_height, "So_long");
	if (game->win == NULL)
	{
		free(game->mlx);
		return ;
	}
	mlx_loop_hook(game->mlx, &pop_window, game);
	mlx_hook(game->win, KeyRelease, KeyReleaseMask, &handle_keypress, game);
	mlx_loop(game->mlx);
}

void	game_init(t_game *game)
{
	game->mlx = mlx_init();
	game->map = NULL;
	game->img_height = 64;
	game->img_width = 64;
	game->count_C = 0;
	game->count_P = 0;
	game->count_E = 0;
	game->count_mooves = 0;
}

int	main(int argc, char **argv)
{
	t_game	game;

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
	game_init(&game);
	game.map = get_map(&game, argv[1]);
	if (game.map != NULL && check_map(&game, argv[1]) == 1)
	{
		game_launch(&game);
	}
	else
		free_game(&game, 0);
	return (1);
}
