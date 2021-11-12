/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima-de <glima-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 13:56:55 by glima-de          #+#    #+#             */
/*   Updated: 2021/11/01 19:09:50 by glima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	clear_map(t_game *game)
{
	int	y;

	y = 0;
	while (y < game->size.y)
	{
		ft_bzero(game->map[y], game->size.x);
		free(game->map[y]);
		y++;
	}
	free(game->map);
}

int	close_game(t_game *game)
{
	clear_map(game);
	mlx_clear_window(game->mlx, game->win);
	mlx_loop_end(game->win);
	if (game->spr_wall.img)
		mlx_destroy_image(game->mlx, game->spr_wall.img);
	if (game->spr_coin.img)
		mlx_destroy_image(game->mlx, game->spr_coin.img);
	if (game->spr_eclose.img)
		mlx_destroy_image(game->mlx, game->spr_eclose.img);
	if (game->spr_eopen.img)
		mlx_destroy_image(game->mlx, game->spr_eopen.img);
	if (game->spr_floor.img)
		mlx_destroy_image(game->mlx, game->spr_floor.img);
	if (game->player.spr.img)
		mlx_destroy_image(game->mlx, game->player.spr.img);
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	exit(0);
	return (0);
}
