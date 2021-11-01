/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima-de <glima-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 18:56:51 by glima-de          #+#    #+#             */
/*   Updated: 2021/11/01 20:06:41 by glima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./mlx/mlx.h"
#include "./so_long.h"

int	catch_input(int keycode, t_game *game)
{
	t_vector2d	pos_mov;

	pos_mov.x = 0;
	pos_mov.y = 0;
	if (keycode == 65307)
	{
		close_game(game);
		return (0);
	}
	else if (keycode == 119)
		pos_mov.y--;
	else if (keycode == 97)
		pos_mov.x--;
	else if (keycode == 115)
		pos_mov.y++;
	else if (keycode == 100)
		pos_mov.x++;
	if (pos_mov.x != 0 || pos_mov.y != 0)
		move_char(game, pos_mov);
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
		game.mlx = mlx_init();
		if (load_game(&game))
		{
			set_start_pos_char(&game);
			mlx_loop_hook(game.mlx, update_game, &game);
			mlx_hook(game.win, 2, 1L << 0, catch_input, &game);
			mlx_hook(game.win, 17, 0L, close_game, &game);
			mlx_loop(game.mlx);
		}
	}
	else
		clear_map(&game);
	return (0);
}
