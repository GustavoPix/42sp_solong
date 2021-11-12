/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draws.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima-de <glima-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 15:03:16 by glima-de          #+#    #+#             */
/*   Updated: 2021/10/31 15:59:37 by glima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static void	mlx_put_img(t_game game, void *spr, t_vector2d p)
{
	int	sprx;
	int	spry;

	sprx = game.spr_size.x;
	spry = game.spr_size.y;
	mlx_put_image_to_window(game.mlx, game.win, spr, p.x * sprx, p.y * spry);
}

static void	draw_exit(t_game game, t_vector2d pos)
{
	if (count_coins(game))
		mlx_put_img(game, game.spr_eclose.img, pos);
	else
		mlx_put_img(game, game.spr_eopen.img, pos);
}

void	draw_map(t_game game)
{
	t_vector2d	pos;

	pos.y = 0;
	while (pos.y < game.size.y)
	{
		pos.x = 0;
		while (pos.x < game.size.x)
		{
			if (game.player.pos.x == pos.x && game.player.pos.y == pos.y)
				mlx_put_img(game, game.player.spr.img, game.player.pos);
			else if (game.map[pos.y][pos.x] == '1')
				mlx_put_img(game, game.spr_wall.img, pos);
			else if (game.map[pos.y][pos.x] == 'E')
				draw_exit(game, pos);
			else if (game.map[pos.y][pos.x] == 'C')
				mlx_put_img(game, game.spr_coin.img, pos);
			else
				mlx_put_img(game, game.spr_floor.img, pos);
			pos.x++;
		}
		pos.y++;
	}
}
