/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima-de <glima-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 16:43:44 by glima-de          #+#    #+#             */
/*   Updated: 2021/11/01 20:19:05 by glima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <fcntl.h>
# include <stdio.h>
# include "libft.h"
# include "./mlx/mlx.h"

typedef struct s_vector2d {
	int		x;
	int		y;
}				t_vector2d;
typedef struct s_image {
	void		*img;
}				t_image;

typedef struct s_player
{
	t_image		spr;
	t_vector2d	pos;
	int			steps;
}				t_player;

typedef struct s_game
{
	char		**map;
	void		*mlx;
	void		*win;
	t_vector2d	spr_size;
	t_vector2d	size;
	t_player	player;
	t_image		spr_wall;
	t_image		spr_floor;
	t_image		spr_eclose;
	t_image		spr_eopen;
	t_image		spr_coin;
}				t_game;

int		load_game(t_game *game);
void	set_start_pos_char(t_game *game);
void	draw_map(t_game game);
int		update_game(t_game *game);
int		count_coins(t_game game);
void	collect_coin(t_vector2d pos, t_game game);
int		catch_input(int keycode, t_game *game);
int		check_valid_map(t_game game);
int		close_game(t_game *game);
int		read_map(t_game *game, char *path);
void	clear_map(t_game *game);
char	who_in_map(t_vector2d pos, t_game game);
int		move_char(t_game *game, t_vector2d mov);

#endif
