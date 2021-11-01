/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima-de <glima-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 14:32:30 by glima-de          #+#    #+#             */
/*   Updated: 2021/11/01 20:21:27 by glima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"
#include "../libft/libft.h"

static int	valid_only_one(t_game game, char c, char *err)
{
	int	x;
	int	y;
	int	count;

	count = 0;
	y = 0;
	while (y < game.size.y)
	{
		x = 0;
		while (x < game.size.x)
		{
			if (game.map[y][x] == c)
			{
				if (count > 0)
				{
					printf("%s\n", err);
					return (0);
				}
				count++;
			}
			x++;
		}
		y++;
	}
	return (count);
}

static int	valid_wall(t_game game)
{
	int	x;
	int	y;
	int	ok;

	y = 0;
	ok = 1;
	while (y < game.size.y && ok)
	{
		x = 0;
		while (x < game.size.x && ok)
		{
			if (x == 0 || y == 0)
				if (game.map[y][x] != '1')
					ok = 0;
			if (x == game.size.x - 1 || y == game.size.y - 1)
				if (game.map[y][x] != '1')
					ok = 0;
			x++;
		}
		y++;
	}
	if (!ok)
		printf("Error: It's necessary to have a wall surrounding the room\n");
	return (ok);
}

static int	valid_map_size(t_game game)
{
	int	y;

	y = 0;
	while (y < game.size.y)
	{
		if (ft_strlen(game.map[y]) != (unsigned int)game.size.x)
		{
			printf("Error: Length of lines is not equals\n");
			return (0);
		}
		y++;
	}
	return (1);
}

static int	valid_chars(t_game game)
{
	int		x;
	int		y;
	char	*valid;

	y = 0;
	valid = "1PCE0";
	while (y < game.size.y)
	{
		x = 0;
		while (x < game.size.x)
		{
			if (!ft_strchr(valid, game.map[y][x]))
				return (0);
			x++;
		}
		y++;
	}
	return (1);
}

int	check_valid_map(t_game game)
{
	if (!valid_map_size(game))
		return (0);
	if (!valid_chars(game))
	{
		printf("Invalid char detected in map\n");
		return (0);
	}
	if (!valid_only_one(game, 'P', "Error: It's necessary only one player"))
		return (0);
	if (!valid_wall(game))
		return (0);
	if (!valid_only_one(game, 'E', "Error: It's necessary only one exit\n"))
		return (0);
	if (!count_coins(game))
	{
		printf("Error: It's necessary one or more coins\n");
		return (0);
	}
	return (1);
}
