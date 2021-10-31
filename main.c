/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima-de <glima-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 18:56:51 by glima-de          #+#    #+#             */
/*   Updated: 2021/10/31 15:12:03 by glima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./mlx/mlx.h"
#include "./so_long.h"
#include "./libft/libft.h"

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
			mlx_hook(game.win, 2, 1L<<0, move_char, &game);
			mlx_hook(game.win, 17, 0L, close_game, &game);
			mlx_loop(game.mlx);
		}
	}
	else
		clear_map(&game);
	return (0);
}
