/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esnowpea <esnowpea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 16:12:26 by esnowpea          #+#    #+#             */
/*   Updated: 2020/10/22 17:09:04 by ablane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	terminate(char *s)
{
	ft_putendl_fd(s, 2);
	exit(0);
}

void	del_node(void *content, size_t content_size)
{
	(void)content;
	(void)content_size;
}

char	*ft_free_line(char *line)
{
	if (line)
	{
		free(line);
		line = NULL;
	}
	return (line);
}

char	*ft_next_gnl(char *line, int fd)
{
	line = ft_free_line(line);
	if (get_next_line(fd, &line) > 0)
		return (line);
	return (NULL);
}
