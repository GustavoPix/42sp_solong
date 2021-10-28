/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima-de <glima-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 18:56:51 by glima-de          #+#    #+#             */
/*   Updated: 2021/10/28 19:02:39 by glima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./mlx/mlx.h"
#include "./so_long.h"
#include "./gnl/get_next_line.h"
#include "./libft/ft_printf.h"
#include "./libft/libft/libft.h"

static void readMap(struct s_game *game)
{
	int 	fd;
	int		lines;
	char	*aux;
	char	*map;

	fd = open("./maps/level0.ber",O_RDONLY);
	aux = get_next_line(fd);
	map = ft_strdup(aux);

	lines = 1;
	while (aux != NULL)
	{
		aux = get_next_line(fd);
		if(aux)
		{
			map = ft_strjoin(map,aux);
			lines++;
		}
	}
	game->map = ft_split(map,'\n');
	game->size.x = ft_strlen(game->map[0]) * game->spr_size.x;
	game->size.y = lines  * game->spr_size.y;
}


int	main(void)
{
	t_game	game;

	game.spr_size.x = 32;
	game.spr_size.y = 32;
	readMap(&game);

	game.mlx = mlx_init();


	//t_data	img;

	game.player.spr.path = "./img/char1.xpm";
	game.player.pos.x = 1;
	game.player.pos.y = 5;

	game.win = mlx_new_window(game.mlx, game.size.x, game.size.y, "so_long");
	game.player.spr.img = mlx_xpm_file_to_image(game.mlx, game.player.spr.path, &game.size.x, &game.size.y);
	mlx_put_image_to_window(game.mlx, game.win, game.player.spr.img, game.player.pos.x, game.player.pos.y);
	mlx_loop(game.mlx);
}
