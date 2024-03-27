NAME		= so_long

CC			= gcc
RM			= rm -rf
CFLAGS		= -Wall -Wextra -Werror -g3

SRC			= main image map1 map2 moove1 moove2 moove3 utils
SRCS		= $(addsuffix .c, ${SRC})

OBJ_DIR		= obj
OBJS		= ${SRCS:%.c=$(OBJ_DIR)/%.o}

MLX_PATH	= ./minilibx-linux
MLX_LIB		= $(MLX_PATH)/libmlx.a

LIBFT_PATH	= ./libft
LIBFT		= $(LIBFT_PATH)/libft.a

$(OBJ_DIR)/%.o:		%.c
						${CC} ${CFLAGS} -c $< -o $@

all:		$(NAME)

$(NAME):	$(MLX_LIB) $(LIBFT) $(OBJ_DIR) $(OBJS)
				cp	$(MLX_LIB) $(NAME)
				cp	$(LIBFT) $(NAME)
					$(CC) $(OBJS) $(MLX_LIB) $(LIBFT) -lXext -lX11 -o $(NAME)

$(MLX_LIB):
					make -C $(MLX_PATH) all

$(LIBFT):
					make -C $(LIBFT_PATH) all

$(OBJ_DIR):
					mkdir -p $(OBJ_DIR)

clean:
			make -C $(MLX_PATH) clean
			${RM} ${OBJ_DIR}

fclean:		clean
			make -C $(LIBFT_PATH) fclean
			${RM} $(NAME)

re:			fclean all

.PHONY:		all clean fclean re mlx_lib
