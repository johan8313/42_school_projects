/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johmarti <johmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 12:22:37 by johmarti          #+#    #+#             */
/*   Updated: 2024/03/20 16:02:11 by johmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "minilibx-linux/mlx.h"
# include "minilibx-linux/mlx_int.h"
# include "libft/libft.h"
# include "libft/get_next_line_bonus.h"
# include "libft/ft_printf.h"

typedef struct		s_list_s
{
	struct s_list_s	*next;
	struct s_list_s	*prev;
	char			data;
	int				x;
	int				y;
}					t_list;

typedef struct	s_path
{
	char		*path_wall;
	char		*path_characters;
}				t_path;

typedef struct	s_image
{
	t_path		img_path;
	void		*wall;
	void		*characters;
}				t_image;

typedef struct	s_game
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*wall;
	void		*characters;
	void		*coin;
	void		*exit;
	int			img_width;
	int			img_height;
	int			x_max;
	int			y_max;
	t_list		*map;
	t_img		game_img;
}				t_game;

#endif
