/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moove1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johmarti <johmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 10:24:06 by johmarti          #+#    #+#             */
/*   Updated: 2024/03/27 13:35:32 by johmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	handle_keypress(int keysym, t_game *game)
{
	if (game->count_C != 0)
	{
		if (keysym == XK_Up || keysym == XK_w)
			moove_up(game);
		if (keysym == XK_Down || keysym == XK_s)
			moove_down(game);
		if (keysym == XK_Left || keysym == XK_a)
			moove_left(game);
		if (keysym == XK_Right || keysym == XK_d)
			moove_right(game);
	}
	else
	{
		if (keysym == XK_Up || keysym == XK_w)
			moove_up_win(game);
		if (keysym == XK_Down || keysym == XK_s)
			moove_down_win(game);
		if (keysym == XK_Left || keysym == XK_a)
			moove_left_win(game);
		if (keysym == XK_Right || keysym == XK_d)
			moove_right_win(game);
	}
	if (keysym == XK_Escape)
		free_game(game, 1);
	return (0);
}

char	data_up_p(t_game *game, t_list *map)
{
	t_list	*temp;
	int		i;

	temp = map;
	while (temp->data != 'P')
		temp = temp->next;
	i = game->x_max;
	while (i >= 0)
	{
		temp = temp->prev;
		i--;
	}
	return (temp->data);
}

char	data_down_p(t_game *game, t_list *map)
{
	t_list	*temp;
	int		i;

	temp = map;
	while (temp->data != 'P')
		temp = temp->next;
	i = 0;
	while (i <= game->x_max)
	{
		temp = temp->next;
		i++;
	}
	return (temp->data);
}

char	data_next_p(t_list *map)
{
	t_list	*temp;

	temp = map;
	while (temp->data != 'P')
		temp = temp->next;
	temp = temp->next;
	return (temp->data);
}

char	data_prev_p(t_list *map)
{
	t_list	*temp;

	temp = map;
	while (temp->data != 'P')
		temp = temp->next;
	temp = temp->prev;
	return (temp->data);
}
