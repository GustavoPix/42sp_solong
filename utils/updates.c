/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   updates.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima-de <glima-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 15:01:10 by glima-de          #+#    #+#             */
/*   Updated: 2021/11/01 20:18:50 by glima-de         ###   ########.fr       */
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

int	move_char(t_game *game, t_vector2d mov)
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

char	who_in_map(t_vector2d pos, t_game game)
{
	if (pos.x < 0 || pos.y < 0)
		return ('X');
	if (pos.x >= game.size.x || pos.y >= game.size.y)
		return ('X');
	if (game.map[pos.y][pos.x] == '0' || game.map[pos.y][pos.x] == 'P')
		return ('0');
	return (game.map[pos.y][pos.x]);
}
