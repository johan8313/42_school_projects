/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johmarti <johmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 09:49:31 by johmarti          #+#    #+#             */
/*   Updated: 2024/03/27 15:24:59 by johmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	valid_path(char *arg)
{
	t_game	game;
	t_list	*map;
	int		height;

	game = map_copy(arg);
	map = game.map;
	if (map == NULL)
		return (0);
	height = 0;
	if (valid_path2(&game, map, height) == 0)
	{
		free_map(&map);
		return (0);
	}
	free_map(&map);
	return (1);
}

int	valid_path2(t_game *game, t_list *map, int height)
{
	int		width;
	t_list	*current;

	current = map;
	while (current != NULL)
	{
		width = 0;
		while (current != NULL && (current->x < game->x_max))
		{
			if ((current->data == 'C' || current->data == 'E')
				&& path(map, height, width) == 0)
			{
				return (0);
			}
			current = current->next;
			width++;
		}
		height++;
		current = current->next;
	}
	return (1);
}

int	path(t_list *map, int height, int width)
{
	t_list	*current;
	current = map;
	while (current != NULL && (current->x != width || current->y != height))
	{
		current = current->next;
	}
	if (current == NULL || current->data == '1')
		return (0);
	if (current->data == 'P')
		return (1);
	current->data = '1';
	if (path(map, height + 1, width) == 1)
		return (1);
	if (path(map, height, width + 1) == 1)
		return (1);
	if (path(map, height - 1, width) == 1)
		return (1);
	if (path(map, height, width - 1) == 1)
		return (1);
	return (0);
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
