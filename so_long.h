/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima-de <glima-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 16:43:44 by glima-de          #+#    #+#             */
/*   Updated: 2021/10/30 12:26:43 by glima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef SO_LONG_H
# define SO_LONG_H

# include <unistd.h>
# include <stdlib.h>

# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

# include <stdio.h>

typedef struct	s_vector2d {
	int		x;
	int		y;
}				t_vector2d;
typedef struct	s_image {
	char		*path;
	void		*img;
}				t_image;

typedef struct	s_player
{
	t_image		spr;
	t_vector2d	pos;
	int			steps;
}				t_player;

typedef struct	s_game
{
	char		**map;
	void		*mlx;
	void		*win;
	t_vector2d	spr_size;
	t_vector2d	size;
	t_player	player;
	t_image		spr_wall;
	t_image		spr_floor;
	t_image		spr_endclose;
}				t_game;

#endif
