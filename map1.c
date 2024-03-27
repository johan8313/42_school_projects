/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johmarti <johmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 09:43:43 by johmarti          #+#    #+#             */
/*   Updated: 2024/03/27 15:25:40 by johmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_map(t_game *game, char *map_path)
{
	if (check_if_map_is_rectangle(game, game->map) == 0)
	{
		ft_printf("Error\nMap is not a rectangle\n");
		return (0);
	}
	else if (check_map_data(game->map) == 0
		|| check_map_elements(game, game->map) == 0)
	{
		ft_printf("Error\nChar rules not followed in .ber\n");
		return (0);
	}
	else if (check_if_map_walled(game, game->map) == 0)
	{
		ft_printf("Error\nMap is not fully walled\n");
		return (0);
	}
	else if (valid_path(map_path) == 0)
	{
		ft_printf("Error\nMap not solvable\n");
		return (0);
	}
	return (1);
}

int	check_if_map_is_rectangle(t_game *game, t_list *map)
{
	int	i;

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

int	check_map_data(t_list *map)
{
	while (map != NULL)
	{
		if (map->data != '1' && map->data != 'P'
			&& map->data != 'C' && map->data != '0'
			&& map->data != 'E')
			return (0);
		map = map->next;
	}
	return (1);
}

int	check_map_elements(t_game *game, t_list *map)
{
	while (map->next != NULL)
	{
		if (map->data == 'C')
			game->count_C++;
		if (map->data == 'E')
			game->count_E++;
		if (map->data == 'P')
			game->count_P++;
		map = map->next;
	}
	if (game->count_C == 0 || game->count_E != 1 || game->count_P != 1)
		return (0);
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
