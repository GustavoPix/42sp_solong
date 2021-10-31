/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   updates.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima-de <glima-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 15:01:10 by glima-de          #+#    #+#             */
/*   Updated: 2021/10/31 16:50:34 by glima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	update_game(t_game *game)
{
	draw_map(*game);
	return (0);
}

int	count_coins(t_game game)
{
	int	x;
	int	y;
	int	coins;

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

void	collect_coin(t_vector2d pos, t_game game)
{
	if (game.map[pos.y][pos.x] == 'C')
		game.map[pos.y][pos.x] = '0';
	if (!count_coins(game))
		printf("No more coins\n");
}

static int	move_char(t_game *game, t_vector2d mov)
{
	mov.x += game->player.pos.x;
	mov.y += game->player.pos.y;
	if (who_in_map(mov, *game) != 'X' && who_in_map(mov, *game) != '1')
	{
		game->player.pos.x = mov.x;
		game->player.pos.y = mov.y;
		game->player.steps++;
		printf("steps: %d\n", game->player.steps);
		if (who_in_map(mov, *game) == 'C')
			collect_coin(mov, *game);
		if (who_in_map(mov, *game) == 'E' && !count_coins(*game))
		{
			printf("Finish game!\n");
			close_game(game);
		}
	}
	return (1);
}

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
