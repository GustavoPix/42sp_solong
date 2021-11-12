# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: glima-de <glima-de@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/27 20:26:23 by glima-de          #+#    #+#              #
#    Updated: 2021/11/01 20:03:09 by glima-de         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS_MANDATORY = ./main.c \

OBJS 		= ${SRCS:.c=.o}
OBJS_M		= ${SRCS_MANDATORY:.c=.o}

LIBFT 		= libft

GNL			= ./gnl/get_next_line.c

SLG_UTL		= ./utils/map.c \
			  ./utils/clear.c \
			  ./utils/loads.c \
			  ./utils/updates.c \
			  ./utils/draws.c \
			  ./utils/read_map.c

OBJS_GNL	= ${GNL:.c=.o}
OBJS_SLG	= ${SLG_UTL:.c=.o}

UNAME		:= $(shell uname)

PATH_MLX	= mlx
CC 			= clang
CFLAGS		= -Wall -Wextra -Werror
RM			= rm -f
NAME		= so_long
FLAGS		= -ldl -Imlx -Lmlx -lmlx -lm -lbsd -lXext -lX11 

all: 		${NAME}

.c.o:
			${CC} -g ${CFLAGS} -I libft -Imlx -c $< -o ${<:.c=.o}

$(NAME): 	gclone $(OBJS) ${OBJS_M} ${OBJS_GNL} ${OBJS_SLG}
			make -C $(LIBFT)
			make -C $(PATH_MLX)
			${CC} -g $(CFLAGS) -o $(NAME) $(OBJS) ${OBJS_M} ${OBJS_GNL} ${OBJS_SLG} $(FLAGS) -L $(LIBFT) -lft

gclone:		
			if [ ! -d "./mlx" ] ; then git clone https://github.com/42Paris/minilibx-linux.git mlx ; fi

clean:
			make -C $(LIBFT) clean
			make -C $(PATH_MLX) clean
			${RM} ${OBJS} ${OBJS_M} ${OBJS_GNL} ${OBJS_SLG} 

fclean: 	clean
			make -C $(LIBFT) fclean
			make -C $(PATH_MLX) clean
			rm -rf mlx
			${RM} ${NAME}

re: 		fclean all

test:		all
			./so_long ./maps/pdf2.ber

val:		all
			valgrind --leak-check=full ./so_long ./maps/test_leak.ber

.PHONY:		all gclone clean fclean re test val
