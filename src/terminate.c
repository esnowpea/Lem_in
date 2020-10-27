/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esnowpea <esnowpea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 16:12:26 by esnowpea          #+#    #+#             */
/*   Updated: 2020/10/27 16:27:01 by esnowpea         ###   ########.fr       */
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

void	del_solution(t_bilist **solution)
{
	t_bilist	*tmp;

	tmp = *solution;
	while (tmp)
	{
		ft_bilstdel((t_bilist**)(&tmp->content), del_node);
		tmp = tmp->next;
	}
	ft_bilstdel(solution, del_node);
}
