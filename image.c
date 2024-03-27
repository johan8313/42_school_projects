/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johmarti <johmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 15:08:39 by johmarti          #+#    #+#             */
/*   Updated: 2024/03/27 14:39:58 by johmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	set_img(t_game *game)
{
	image_path(game);
	xpm_to_image1(game);
}

void	image_path(t_game *game)
{
	game->img.path.wall = "./texture/wall.xpm";
	game->img.path.characters = "./texture/characters.xpm";
	game->img.path.coin = "./texture/coin.xpm";
	game->img.path.empty = "./texture/empty.xpm";
	game->img.path.exit = "./texture/exit.xpm";
}

void	xpm_to_image1(t_game *game)
{
	game->img.wall = mlx_xpm_file_to_image(game->mlx,
			game->img.path.wall, &(game->img_width), &(game->img_height));
	game->img.characters = mlx_xpm_file_to_image(game->mlx,
			game->img.path.characters, &(game->img_width), &(game->img_height));
	game->img.coin = mlx_xpm_file_to_image(game->mlx, game->img.path.coin,
			&(game->img_width), &(game->img_height));
	game->img.empty = mlx_xpm_file_to_image(game->mlx, game->img.path.empty,
			&(game->img_width), &(game->img_height));
	game->img.exit = mlx_xpm_file_to_image(game->mlx, game->img.path.exit,
			&(game->img_width), &(game->img_height));
}

int	pop_window(t_game *game)
{
	t_list	*current;

	current = game->map;
	while (current != NULL)
	{
		if (current->data == '1')
			mlx_put_image_to_window(game->mlx, game->win, game->img.wall,
				current->x * game->img_width, current->y * game->img_height);
		else if (current->data == 'P')
			mlx_put_image_to_window(game->mlx, game->win, game->img.characters,
				current->x * game->img_width, current->y * game->img_height);
		else if (current->data == 'C')
			mlx_put_image_to_window(game->mlx, game->win, game->img.coin,
				current->x * game->img_width, current->y * game->img_height);
		else if (current->data == 'E')
			mlx_put_image_to_window(game->mlx, game->win, game->img.exit,
				current->x * game->img_width, current->y * game->img_height);
		else if (current->data == '0')
			mlx_put_image_to_window(game->mlx, game->win, game->img.empty,
				current->x * game->img_width, current->y * game->img_height);
		current = current->next;
	}
	return (0);
}
