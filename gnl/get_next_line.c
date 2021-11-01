/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima-de <glima-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 12:35:40 by glima-de          #+#    #+#             */
/*   Updated: 2021/11/01 18:50:20 by glima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./get_next_line.h"
#include "../libft/libft.h"

static int	gnl_read_file(char **lastRead, int fd)
{
	char	*r;
	int		sr;
	char	*aux;

	r = ft_calloc(sizeof(char), BUFFER_SIZE + 1);
	if (!r)
		return (-1);
	sr = read(fd, (void *)r, BUFFER_SIZE);
	if (sr <= 0)
	{
		free(r);
		return (sr);
	}
	if (!*lastRead)
	{
		*lastRead = ft_calloc(sizeof(char), sr + 1);
		if (!*lastRead)
			return (-1);
	}
	aux = *lastRead;
	*lastRead = ft_strjoin(*lastRead, r);
	free(aux);
	free(r);
	return (sr);
}

static int	gnl_findreturnchar(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

static char	*gnl_split(char *left, char *right, int nPos)
{
	char	*aux_swap;

	ft_strlcpy(left, right, nPos + 2);
	if (ft_strlen(&right[nPos + 1]))
		aux_swap = ft_calloc(sizeof(char), ft_strlen(&right[nPos + 1]) + 1);
	else
		return (NULL);
	if (!left || !aux_swap)
		return (NULL);
	ft_strlcpy(aux_swap, &right[nPos + 1], ft_strlen(&right[nPos]));
	return (aux_swap);
}

char	*get_next_line(int fd)
{
	static char	*lastread;
	char		*auxr;
	char		*aux_swap;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (lastread)
	{
		aux_swap = lastread;
		if (gnl_findreturnchar(lastread) >= 0)
		{
			auxr = ft_calloc(sizeof(char), gnl_findreturnchar(lastread) + 2);
			lastread = gnl_split(auxr, lastread, gnl_findreturnchar(lastread));
			free(aux_swap);
			return (auxr);
		}
		if (gnl_read_file(&lastread, fd) <= 0)
		{
			lastread = NULL;
			return (aux_swap);
		}
	}
	else if (gnl_read_file(&lastread, fd) <= 0)
		return (NULL);
	return (get_next_line(fd));
}
