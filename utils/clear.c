/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima-de <glima-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 13:56:55 by glima-de          #+#    #+#             */
/*   Updated: 2021/10/31 13:59:43 by glima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"
#include "../libft/libft/libft.h"

void clear_map(t_game *game)
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
}
