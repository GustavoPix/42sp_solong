/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima-de <glima-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 16:22:02 by glima-de          #+#    #+#             */
/*   Updated: 2021/10/31 16:23:53 by glima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"
#include "../gnl/get_next_line.h"

static void	read_map_loop(t_game *game, char *aux, int fd)
{
	char	*map;
	char	*swap;
	int		lines;

	map = ft_strdup(aux);
	lines = 1;
	while (aux != NULL)
	{
		if (aux)
			free(aux);
		aux = get_next_line(fd);
		if (aux)
		{
			swap = map;
			map = ft_strjoin(map, aux);
			free(swap);
			lines++;
		}
	}
	swap = map;
	game->map = ft_split(map, '\n');
	free(map);
	game->size.x = ft_strlen(game->map[0]);
	game->size.y = lines;
}

int	read_map(t_game *game, char *path)
{
	int		fd;
	char	*aux;

	fd = open(path, O_RDONLY);
	if (fd < 1)
		return (0);
	aux = get_next_line(fd);
	if (aux)
	{
		read_map_loop(game, aux, fd);
		close(fd);
		return (1);
	}
	return (0);
}
