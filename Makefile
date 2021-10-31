# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: glima-de <glima-de@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/27 20:26:23 by glima-de          #+#    #+#              #
#    Updated: 2021/10/31 13:59:23 by glima-de         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



SRCS_MANDATORY = ./main.c \

OBJS 		= ${SRCS:.c=.o}
OBJS_B		= ${SRCS_BONUS:.c=.o}
OBJS_M		= ${SRCS_MANDATORY:.c=.o}

LIBFT 		= ./libft/libft/ft_atoi.c \
			  ./libft/libft/ft_bzero.c \
			  ./libft/libft/ft_calloc.c \
			  ./libft/libft/ft_isalnum.c \
			  ./libft/libft/ft_isalpha.c \
			  ./libft/libft/ft_isascii.c \
			  ./libft/libft/ft_isdigit.c \
			  ./libft/libft/ft_isprint.c \
			  ./libft/libft/ft_itoa.c \
			  ./libft/libft/ft_memchr.c \
			  ./libft/libft/ft_memcpy.c \
			  ./libft/libft/ft_memmove.c \
			  ./libft/libft/ft_memset.c \
			  ./libft/libft/ft_putchar_fd.c \
			  ./libft/libft/ft_putendl_fd.c \
			  ./libft/libft/ft_putnbr_fd.c \
			  ./libft/libft/ft_putunbr_fd.c \
			  ./libft/libft/ft_putstr_fd.c \
			  ./libft/libft/ft_split.c \
			  ./libft/libft/ft_strchr.c \
			  ./libft/libft/ft_strdup.c \
			  ./libft/libft/ft_striteri.c \
			  ./libft/libft/ft_strjoin.c \
			  ./libft/libft/ft_strlcat.c \
			  ./libft/libft/ft_strlcpy.c \
			  ./libft/libft/ft_strlen.c \
			  ./libft/libft/ft_strmapi.c \
			  ./libft/libft/ft_strncmp.c \
			  ./libft/libft/ft_strnstr.c \
			  ./libft/libft/ft_strrchr.c \
			  ./libft/libft/ft_strtrim.c \
			  ./libft/libft/ft_substr.c \
			  ./libft/libft/ft_tolower.c \
			  ./libft/libft/ft_toupper.c \
			  ./libft/libft/ft_memcmp.c \
			  ./libft/utils/prf_dec_to_base.c \
			  ./libft/utils/prf_print_d.c \
			  ./libft/utils/prf_print_p.c \
			  ./libft/utils/prf_print_s.c \
			  ./libft/utils/prf_print_u.c \
			  ./libft/utils/prf_print_x.c \
			  ./libft/ft_printf.c

GNL			= ./gnl/get_next_line.c \
			  ./gnl/get_next_line_utils.c

SLG_UTL		= ./utils/map.c \
			  ./utils/clear.c

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

bonus:		${OBJS} ${OBJS_B}
			make -C $(PATH_MLX)
			${CC} ${CFLAGS} -o ${NAME} ${OBJS} ${OBJS_B} $(FLAGS)

clean:
			make -C $(PATH_MLX) clean
			${RM} ${OBJS} ${OBJS_M} ${OBJS_B} ${OBJS_GNL} ${OBJS_SLG} ${OBJS_LIBFT}

fclean: 	clean
			make -C $(PATH_MLX) clean
			${RM} ${NAME}

re: 		fclean all

test:		all
			./so_long
val:		all
			valgrind --leak-check=full ./so_long

.PHONY:		bonus all clean fclean re test val
