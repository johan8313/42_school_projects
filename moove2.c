/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moove2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johmarti <johmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 10:26:26 by johmarti          #+#    #+#             */
/*   Updated: 2024/03/27 13:38:14 by johmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	moove_up(t_game *game)
{
	t_list	*map;
	int		i;

	map = game->map;
	while (map->data != 'P')
		map = map->next;
	i = game->x_max;
	if (data_up_p(game, map) != '1' && data_up_p(game, map) != 'E')
	{
		map->data = '0';
		while (i >= 0)
		{
			map = map->prev;
			i--;
		}
		game->count_mooves += 1;
		ft_printf("Nbr of mooves : %d\n", game->count_mooves);
		if (map->data == 'C')
			game->count_C -= 1;
		map->data = 'P';
	}
}

void	moove_down(t_game *game)
{
	t_list	*map;
	int		i;

	map = game->map;
	while (map->data != 'P')
		map = map->next;
	i = 0;
	if (data_down_p(game, map) != '1' && data_down_p(game, map) != 'E')
	{
		map->data = '0';
		while (i <= game->x_max)
		{
			map = map->next;
			i++;
		}
		game->count_mooves += 1;
		ft_printf("Nbr of mooves : %d\n", game->count_mooves);
		if (map->data == 'C')
			game->count_C -= 1;
		map->data = 'P';
	}
}

void	moove_right(t_game *game)
{
	t_list	*map;

	map = game->map;
	while (map->data != 'P')
		map = map->next;
	if (data_next_p(map) != '1' && data_next_p(map) != 'E')
	{
		map->data = '0';
		map = map->next;
		game->count_mooves += 1;
		ft_printf("Nbr of mooves : %d\n", game->count_mooves);
		if (map->data == 'C')
			game->count_C -= 1;
		map->data = 'P';
	}
}

void	moove_left(t_game *game)
{
	t_list	*map;

	map = game->map;
	while (map->data != 'P')
		map = map->next;
	if (data_prev_p(map) != '1' && data_prev_p(map) != 'E')
	{
		map->data = '0';
		map = map->prev;
		game->count_mooves += 1;
		ft_printf("Nbr of mooves : %d\n", game->count_mooves);
		if (map->data == 'C')
			game->count_C -= 1;
		map->data = 'P';
	}
}
