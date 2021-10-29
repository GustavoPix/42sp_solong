/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima-de <glima-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 18:56:51 by glima-de          #+#    #+#             */
/*   Updated: 2021/10/29 20:48:52 by glima-de         ###   ########.fr       */
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
	game->size.x = ft_strlen(game->map[0]);
	game->size.y = lines;
}

static void load_game(struct s_game *game)
{
	game->win = mlx_new_window(game->mlx, game->size.x * game->spr_size.x, game->size.y * game->spr_size.y, "so_long");
	game->player.spr.path = "./img/character.xpm";
	game->spr_wall.path = "./img/rock.xpm";
	game->spr_floor.path = "./img/grass.xpm";
	game->spr_endclose.path = "./img/exitclose.xpm";
	game->player.spr.img = mlx_xpm_file_to_image(game->mlx, game->player.spr.path, &game->spr_size.x, &game->spr_size.y);
	game->spr_wall.img = mlx_xpm_file_to_image(game->mlx, game->spr_wall.path, &game->spr_size.x, &game->spr_size.y);
	game->spr_floor.img = mlx_xpm_file_to_image(game->mlx, game->spr_floor.path, &game->spr_size.x, &game->spr_size.y);
	game->spr_endclose.img = mlx_xpm_file_to_image(game->mlx, game->spr_endclose.path, &game->spr_size.x, &game->spr_size.y);
}

static void draw_map(t_game game)
{
	int x;
	int y;

	y = 0;
	while (y < game.size.y)
	{
		x = 0;
		while (x < game.size.x)
		{
			if(game.map[y][x] == '1')
				mlx_put_image_to_window(game.mlx, game.win, game.spr_wall.img, x * game.spr_size.x, y * game.spr_size.y);
			else if(game.map[y][x] == 'E')
				mlx_put_image_to_window(game.mlx, game.win, game.spr_endclose.img, x * game.spr_size.x, y * game.spr_size.y);
			else
				mlx_put_image_to_window(game.mlx, game.win, game.spr_floor.img, x * game.spr_size.x, y * game.spr_size.y);
			x++;
		}
		y++;
	}

	mlx_put_image_to_window(game.mlx, game.win, game.player.spr.img, game.player.pos.x * game.spr_size.x, game.player.pos.y * game.spr_size.y);

}

int	main(void)
{
	t_game	game;

	game.spr_size.x = 32;
	game.spr_size.y = 32;
	readMap(&game);


	game.mlx = mlx_init();


	//t_data	img;

	//game.player.spr.path = "./img/character.xpm";
	game.player.pos.x = 3;
	game.player.pos.y = 2;


	load_game(&game);

	//mlx_put_image_to_window(game.mlx, game.win, game.player.spr.img, game.player.pos.x, game.player.pos.y);
	draw_map(game);
	mlx_loop(game.mlx);
}
