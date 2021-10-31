/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima-de <glima-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 18:56:51 by glima-de          #+#    #+#             */
/*   Updated: 2021/10/31 14:00:51 by glima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./mlx/mlx.h"
#include "./so_long.h"
#include "./libft/ft_printf.h"
#include "./libft/libft/libft.h"

static void *mlx_put_img(void *mlx, char *path, int x, int y)
{
	return (mlx_xpm_file_to_image(mlx, path, &x, &y));
}

void load_game(t_game *game)
{
	int		sprx;
	int		spry;
	int		gsx;
	int		gsy;
	void	*mlx;

	sprx = game->spr_size.x;
	spry = game->spr_size.y;
	mlx = game->mlx;
	gsx = game->size.x;
	gsy = game->size.y;
	game->win = mlx_new_window(mlx, gsx * sprx, gsy * spry, "so_long");
	game->player.spr.img = mlx_put_img(mlx, "./img/character.xpm", sprx, spry);
	game->spr_wall.img = mlx_put_img(mlx, "./img/rock.xpm", sprx, spry);
	game->spr_floor.img = mlx_put_img(mlx, "./img/grass.xpm", sprx, spry);
	game->spr_eclose.img = mlx_put_img(mlx, "./img/exitclose.xpm", sprx, spry);
	game->spr_eopen.img = mlx_put_img(mlx, "./img/exit.xpm", sprx, spry);
	game->spr_coin.img = mlx_put_img(mlx, "./img/coin.xpm", sprx, spry);
	game->player.steps = 0;
}



void set_start_pos_char(t_game *game)
{
	int x;
	int y;
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

int update_game(t_game *game)
{
	//mlx_clear_window(game->mlx, game->win);
	draw_map(*game);
	return (0);
}

static char who_in_map(t_vector2d pos, t_game game)
{
	if (pos.x < 0 || pos.y < 0)
		return ('X');
	if (pos.x >= game.size.x || pos.y >= game.size.y)
		return ('X');
	if (game.map[pos.y][pos.x] == '0' || game.map[pos.y][pos.x] == 'P')
		return ('0');
	return (game.map[pos.y][pos.x]);
}

int count_coins(t_game game)
{
	int x;
	int y;
	int coins;

	y = 0;
	coins = 0;
	while (y < game.size.y)
	{
		x = 0;
		while (x < game.size.x)
		{
			if (game.map[y][x] == 'C')
				coins++;
			x++;
		}
		y++;
	}
	return (coins);
}

void collect_coin(t_vector2d pos, t_game game)
{
	if (game.map[pos.y][pos.x] == 'C')
		game.map[pos.y][pos.x] = '0';
	if (!count_coins(game))
		ft_printf("No more coins\n");
}

int move_char(int keycode, t_game *game)
{
	t_vector2d pos_mov;
	pos_mov.x = game->player.pos.x;
	pos_mov.y = game->player.pos.y;

	if (keycode == 119)
		pos_mov.y--;
	else if (keycode == 97)
		pos_mov.x--;
	else if (keycode == 115)
		pos_mov.y++;
	else if (keycode == 100)
		pos_mov.x++;
	else if (keycode == 65307)
	{
		close_game(game);
		return (0);
	}
	else
		return (0);
	if (who_in_map(pos_mov, *game) != 'X' && who_in_map(pos_mov, *game) != '1')
	{
		game->player.pos.x = pos_mov.x;
		game->player.pos.y = pos_mov.y;
		game->player.steps++;
		ft_printf("steps: %d\n", game->player.steps);
		if (who_in_map(pos_mov, *game) == 'C')
			collect_coin(pos_mov, *game);
		if (who_in_map(pos_mov, *game) == 'E' && !count_coins(*game))
		{
			ft_printf("Finish game!\n");
			close_game(game);
		}
	}
	return (1);
}

int close_game(t_game *game)
{
	clear_map(game);
	mlx_clear_window(game->mlx,game->win);
	mlx_loop_end(game->win);
	mlx_destroy_image(game->mlx,game->spr_wall.img);
	mlx_destroy_image(game->mlx,game->spr_coin.img);
	mlx_destroy_image(game->mlx,game->spr_eclose.img);
	mlx_destroy_image(game->mlx,game->spr_eopen.img);
	mlx_destroy_image(game->mlx,game->spr_floor.img);
	mlx_destroy_image(game->mlx,game->player.spr.img);
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);

	exit(0);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_game	game;

	if (argc < 2)
		printf("Error: You need pass map in argument\n");
	else if (!read_map(&game, argv[1]))
		printf("Error: Failed to read map\n");
	else if (check_valid_map(game))
	{
		game.spr_size.x = 32;
		game.spr_size.y = 32;
		game.mlx = mlx_init();

		load_game(&game);
		set_start_pos_char(&game);

		//draw_map(game);
		mlx_loop_hook(game.mlx, update_game, &game);
		mlx_hook(game.win, 2, 1L<<0, move_char, &game);
		mlx_hook(game.win, 17, 0L, close_game, &game);
		mlx_loop(game.mlx);
	}
	else
		clear_map(&game);
	return (0);
}
