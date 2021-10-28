/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima-de <glima-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 18:56:51 by glima-de          #+#    #+#             */
/*   Updated: 2021/10/27 21:03:59 by glima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./mlx/mlx.h"
#include "./so_long.h"
#include "./gnl/get_next_line.h"
#include "./libft/ft_printf.h"

static void readMap()
{
	int 	fd;
	char	*aux;

	fd = open("./maps/level0.ber",O_RDONLY);
	aux = get_next_line(fd);

	ft_printf("%s",aux);
}

int	main(void)
{
	readMap();
	t_game	game;

	game.mlx = mlx_init();
	game.spr_size.x = 32;
	game.spr_size.y = 32;
	game.size.x = game.spr_size.x * 10;
	game.size.y = game.spr_size.x * 10;

	//t_data	img;

	game.player.spr.path = "./img/char1.xpm";
	game.player.pos.x = 1;
	game.player.pos.y = 5;

	game.win = mlx_new_window(game.mlx, game.size.x, game.size.y, "so_long");
	game.player.spr.img = mlx_xpm_file_to_image(game.mlx, game.player.spr.path, &game.size.x, &game.size.y);
	mlx_put_image_to_window(game.mlx, game.win, game.player.spr.img, game.player.pos.x, game.player.pos.y);
	mlx_loop(game.mlx);
}
