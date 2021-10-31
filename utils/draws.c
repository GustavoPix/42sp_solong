/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draws.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima-de <glima-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 15:03:16 by glima-de          #+#    #+#             */
/*   Updated: 2021/10/31 15:04:26 by glima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"
#include "../mlx/mlx.h"

void draw_map(t_game game)
{
	int x;
	int y;

	y = 0;
	while (y < game.size.y)
	{
		x = 0;
		while (x < game.size.x)
		{
			if (game.player.pos.x == x && game.player.pos.y == y)
				mlx_put_image_to_window(game.mlx, game.win, game.player.spr.img, game.player.pos.x * game.spr_size.x, game.player.pos.y * game.spr_size.y);
			else if (game.map[y][x] == '1')
				mlx_put_image_to_window(game.mlx, game.win, game.spr_wall.img, x * game.spr_size.x, y * game.spr_size.y);
			else if(game.map[y][x] == 'E')
			{
				if (count_coins(game))
					mlx_put_image_to_window(game.mlx, game.win, game.spr_eclose.img, x * game.spr_size.x, y * game.spr_size.y);
				else
					mlx_put_image_to_window(game.mlx, game.win, game.spr_eopen.img, x * game.spr_size.x, y * game.spr_size.y);
			}
			else if(game.map[y][x] == 'C')
				mlx_put_image_to_window(game.mlx, game.win, game.spr_coin.img, x * game.spr_size.x, y * game.spr_size.y);
			else
				mlx_put_image_to_window(game.mlx, game.win, game.spr_floor.img, x * game.spr_size.x, y * game.spr_size.y);
			x++;
		}
		y++;
	}
}
