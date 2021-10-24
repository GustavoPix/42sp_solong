SRCS_MANDATORY = ./main.c \

OBJS 		= ${SRCS:.c=.o}
OBJS_B		= ${SRCS_BONUS:.c=.o}
OBJS_M		= ${SRCS_MANDATORY:.c=.o}

UNAME		:= $(shell uname)

PATH_MLX	= mlx
CC 			= gcc
CFLAGS		= -Wall -Wextra -Werror
RM			= rm -f
NAME		= so_long
FLAGS		= -ldl -Imlx -Lmlx -lmlx -lm -lbsd -lXext -lX11 -Wl,-rpath=./bass/,-rpath=./mlx/,-rpath=./delay/

all: 		${NAME}

.c.o:
			${CC} ${CFLAGS} -Imlx -Ibass -c $< -o ${<:.c=.o}

$(NAME): 	$(OBJS) ${OBJS_M}
			make -C $(PATH_MLX)
			${CC} $(CFLAGS) -o $(NAME) $(OBJS) ${OBJS_M} $(FLAGS)

bonus:		${OBJS} ${OBJS_B}
			make -C $(PATH_MLX)
			${CC} ${CFLAGS} -o ${NAME} ${OBJS} ${OBJS_B} $(FLAGS)

clean:
			make -C $(PATH_MLX) clean
			${RM} ${OBJS} ${OBJS_M} ${OBJS_B}

fclean: 	clean
			make -C $(PATH_MLX) clean
			${RM} ${NAME}

re: 		fclean all

.PHONY:		bonus all clean fclean re
