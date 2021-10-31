/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima-de <glima-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 18:56:51 by glima-de          #+#    #+#             */
/*   Updated: 2021/10/30 23:04:39 by glima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./mlx/mlx.h"
#include "./so_long.h"
#include "./gnl/get_next_line.h"
#include "./libft/ft_printf.h"
#include "./libft/libft/libft.h"

void load_game(t_game *game)
{
	game->win = mlx_new_window(game->mlx, game->size.x * game->spr_size.x, game->size.y * game->spr_size.y, "so_long");
	game->player.spr.img = mlx_xpm_file_to_image(game->mlx, "./img/character.xpm", &game->spr_size.x, &game->spr_size.y);
	game->spr_wall.img = mlx_xpm_file_to_image(game->mlx, "./img/rock.xpm", &game->spr_size.x, &game->spr_size.y);
	game->spr_floor.img = mlx_xpm_file_to_image(game->mlx, "./img/grass.xpm", &game->spr_size.x, &game->spr_size.y);
	game->spr_endclose.img = mlx_xpm_file_to_image(game->mlx, "./img/exitclose.xpm", &game->spr_size.x, &game->spr_size.y);
	game->spr_endopen.img = mlx_xpm_file_to_image(game->mlx, "./img/exit.xpm", &game->spr_size.x, &game->spr_size.y);
	game->spr_coin.img = mlx_xpm_file_to_image(game->mlx, "./img/coin.xpm", &game->spr_size.x, &game->spr_size.y);
	game->player.steps = 0;
}

void read_map(t_game *game)
{
	int 	fd;
	int		lines;
	char	*aux;
	char	*map;
	char	*swap;

	fd = open("./maps/test_leak.ber",O_RDONLY);
	aux = get_next_line(fd);
	map = ft_strdup(aux);

	lines = 1;
	while (aux != NULL)
	{
		if (aux)
			free(aux);
		aux = get_next_line(fd);
		if(aux)
		{
			swap = map;
			map = ft_strjoin(map,aux);
			free(swap);
			lines++;
		}
	}
	close(fd);
	swap = map;
	game->map = ft_split(map,'\n');
	free(map);
	game->size.x = ft_strlen(game->map[0]);
	game->size.y = lines;
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
					mlx_put_image_to_window(game.mlx, game.win, game.spr_endclose.img, x * game.spr_size.x, y * game.spr_size.y);
				else
					mlx_put_image_to_window(game.mlx, game.win, game.spr_endopen.img, x * game.spr_size.x, y * game.spr_size.y);
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
	return (0);
}

int close_game(t_game *game)
{
	int y;

	y = 0;
	while (y < game->size.y)
	{
		ft_bzero(game->map[y],game->size.x);
		free(game->map[y]);
		y++;
	}
	free(game->map);
	mlx_destroy_window(game->mlx, game->win);
	free(game->spr_wall.img);
	free(game->spr_coin.img);
	free(game->spr_endclose.img);
	free(game->spr_endopen.img);
	free(game->spr_floor.img);
	free(game->player.spr.img);
	free(game->mlx);
	return (0);
}

int	main(void)
{
	t_game	game;

	read_map(&game);
	if (check_valid_map(game))
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
	return (0);
}
