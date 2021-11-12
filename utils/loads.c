/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loads.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima-de <glima-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 14:55:58 by glima-de          #+#    #+#             */
/*   Updated: 2021/10/31 15:40:09 by glima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static void	*mlx_put_img(void *mlx, char *path, int x, int y)
{
	return (mlx_xpm_file_to_image(mlx, path, &x, &y));
}

static int	success_load_images(t_game *game)
{
	if (!game->player.spr.img)
		return (0);
	if (!game->spr_wall.img)
		return (0);
	if (!game->spr_floor.img)
		return (0);
	if (!game->spr_eclose.img)
		return (0);
	if (!game->spr_eopen.img)
		return (0);
	if (!game->spr_coin.img)
		return (0);
	return (1);
}

static int	load_assets(t_game *game)
{
	void	*mlx;
	int		sprx;
	int		spry;

	mlx = game->mlx;
	sprx = game->spr_size.x;
	spry = game->spr_size.y;
	game->player.spr.img = mlx_put_img(mlx, "./img/character.xpm", sprx, spry);
	game->spr_wall.img = mlx_put_img(mlx, "./img/rock.xpm", sprx, spry);
	game->spr_floor.img = mlx_put_img(mlx, "./img/grass.xpm", sprx, spry);
	game->spr_eclose.img = mlx_put_img(mlx, "./img/exitclose.xpm", sprx, spry);
	game->spr_eopen.img = mlx_put_img(mlx, "./img/exit.xpm", sprx, spry);
	game->spr_coin.img = mlx_put_img(mlx, "./img/coin.xpm", sprx, spry);
	return (success_load_images(game));
}

int	load_game(t_game *game)
{
	int		sprx;
	int		spry;
	int		gsx;
	int		gsy;
	void	*mlx;

	game->spr_size.x = 32;
	game->spr_size.y = 32;
	sprx = game->spr_size.x;
	spry = game->spr_size.y;
	gsx = game->size.x;
	gsy = game->size.y;
	mlx = game->mlx;
	game->player.steps = 0;
	game->win = mlx_new_window(mlx, gsx * sprx, gsy * spry, "so_long");
	if (load_assets(game))
		return (1);
	printf("Failed to load assets\n");
	close_game(game);
	return (0);
}

void	set_start_pos_char(t_game *game)
{
	int	x;
	int	y;
	int	finded;

	y = 0;
	finded = 0;
	while (y < game->size.y && !finded)
	{
		x = 0;
		while (x < game->size.x && !finded)
		{
			if (game->map[y][x] == 'P')
			{
				game->player.pos.x = x;
				game->player.pos.y = y;
				finded = 1;
			}
			x++;
		}
		y++;
	}
}
