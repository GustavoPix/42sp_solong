# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: glima-de <glima-de@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/27 20:26:23 by glima-de          #+#    #+#              #
#    Updated: 2021/11/01 19:58:43 by glima-de         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



SRCS_MANDATORY = ./main.c \

OBJS 		= ${SRCS:.c=.o}
OBJS_M		= ${SRCS_MANDATORY:.c=.o}

LIBFT 		= ./libft/ft_atoi.c \
			  ./libft/ft_bzero.c \
			  ./libft/ft_calloc.c \
			  ./libft/ft_isalnum.c \
			  ./libft/ft_isalpha.c \
			  ./libft/ft_isascii.c \
			  ./libft/ft_isdigit.c \
			  ./libft/ft_isprint.c \
			  ./libft/ft_itoa.c \
			  ./libft/ft_memchr.c \
			  ./libft/ft_memcpy.c \
			  ./libft/ft_memmove.c \
			  ./libft/ft_memset.c \
			  ./libft/ft_putchar_fd.c \
			  ./libft/ft_putendl_fd.c \
			  ./libft/ft_putnbr_fd.c \
			  ./libft/ft_putunbr_fd.c \
			  ./libft/ft_putstr_fd.c \
			  ./libft/ft_split.c \
			  ./libft/ft_strchr.c \
			  ./libft/ft_strdup.c \
			  ./libft/ft_striteri.c \
			  ./libft/ft_strjoin.c \
			  ./libft/ft_strlcat.c \
			  ./libft/ft_strlcpy.c \
			  ./libft/ft_strlen.c \
			  ./libft/ft_strmapi.c \
			  ./libft/ft_strncmp.c \
			  ./libft/ft_strnstr.c \
			  ./libft/ft_strrchr.c \
			  ./libft/ft_strtrim.c \
			  ./libft/ft_substr.c \
			  ./libft/ft_tolower.c \
			  ./libft/ft_toupper.c \
			  ./libft/ft_memcmp.c

GNL			= ./gnl/get_next_line.c

SLG_UTL		= ./utils/map.c \
			  ./utils/clear.c \
			  ./utils/loads.c \
			  ./utils/updates.c \
			  ./utils/draws.c \
			  ./utils/read_map.c

OBJS_GNL	= ${GNL:.c=.o}
OBJS_LIBFT	= ${LIBFT:.c=.o}
OBJS_SLG	= ${SLG_UTL:.c=.o}

UNAME		:= $(shell uname)

PATH_MLX	= mlx
CC 			= clang
CFLAGS		= -Wall -Wextra -Werror
RM			= rm -f
NAME		= so_long
FLAGS		= -ldl -Imlx -Lmlx -lmlx -lm -lbsd -lXext -lX11 -Wl,-rpath=./bass/,-rpath=./mlx/,-rpath=./delay/

all: 		${NAME}

.c.o:
			${CC} -g ${CFLAGS} -Imlx -Ibass -c $< -o ${<:.c=.o}

$(NAME): 	$(OBJS) ${OBJS_M} ${OBJS_LIBFT} ${OBJS_GNL} ${OBJS_SLG}
			make -C $(PATH_MLX)
			${CC} -g $(CFLAGS) -o $(NAME) $(OBJS) ${OBJS_M} ${OBJS_LIBFT} ${OBJS_GNL} ${OBJS_SLG} $(FLAGS)

clean:
			make -C $(PATH_MLX) clean
			${RM} ${OBJS} ${OBJS_M} ${OBJS_GNL} ${OBJS_SLG} ${OBJS_LIBFT}

fclean: 	clean
			make -C $(PATH_MLX) clean
			${RM} ${NAME}

re: 		fclean all

test:		all
			./so_long

val:		all
			valgrind --leak-check=full ./so_long

.PHONY:		bonus all clean fclean re test val
