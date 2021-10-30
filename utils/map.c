/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima-de <glima-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 14:32:30 by glima-de          #+#    #+#             */
/*   Updated: 2021/10/30 14:57:33 by glima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"
#include "../libft/ft_printf.h"

static int valid_player(t_game game)
{
	int x;
	int y;
	int	count;

	count = 0;
	y = 0;
	while (y < game.size.y)
	{
		x = 0;
		while (x < game.size.x)
		{
			if (game.map[y][x] == 'P')
			{
				if (count > 0)
					return (0);
				count++;
			}
			x++;
		}
		y++;
	}
	return (count);
}

static int valid_wall(t_game game)
{
	int x;
	int y;

	y = 0;
	while (y < game.size.y)
	{
		x = 0;
		while (x < game.size.x)
		{
			if (x == 0 || y == 0)
				if (game.map[y][x] != '1')
					return (0);
			if (x == game.size.x - 1 || y == game.size.y - 1)
				if (game.map[y][x] != '1')
					return (0);
			x++;
		}
		y++;
	}
	return (1);
}

int check_valid_map(t_game game)
{
	if (!valid_player(game))
	{
		ft_printf("Error: It's necessary only one player\n");
		return (0);
	}
	if (!valid_wall(game))
	{
		ft_printf("Error: It's necessary to have a wall surrounding the room\n");
		return (0);
	}
	return (1);
}
