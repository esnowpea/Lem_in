/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   breadth_first_search.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esnowpea <esnowpea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 16:23:57 by esnowpea          #+#    #+#             */
/*   Updated: 2020/10/27 16:27:01 by esnowpea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			find_room_in_solution(t_room *room, t_room *p, t_bilist *dont_visit)
{
	t_bilist	*corridor;
	t_bilist	*corridors;

	if (dont_visit)
	{
		corridors = dont_visit;
		while (corridors)
		{
			corridor = corridors->content;
			if (p->is_start && room->is_end && ft_bilstlength(corridor))
				return (1);
			while (corridor)
			{
				if (find_room(room, corridor) > 0)
					return (1);
				corridor = corridor->next;
			}
			corridors = corridors->next;
		}
	}
	return (0);
}

int			find_parant_part(t_bilist *links, t_bilist *visit, t_bilist *queue,
								t_bilist *dont_visit)
{
	if (!find_room((t_room*)links->content, visit) &&
		!find_room((t_room*)links->content, queue) &&
		!find_room_in_solution((t_room*)links->content,
							(t_room*)queue->content, dont_visit))
	{
		((t_room*)links->content)->parent = (t_room*)queue->content;
		ft_bilstadd_back(&queue, ft_bilstnew(links->content, 0));
	}
	if (((t_room*)links->content)->is_end &&
		!((t_room*)queue->content)->is_start)
	{
		ft_bilstdel(&visit, del_node);
		ft_bilstdel(&queue, del_node);
		return (0);
	}
	return (1);
}

void		find_parant(t_room *start, t_bilist *dont_visit)
{
	t_bilist	*links;
	t_bilist	*visit;
	t_bilist	*queue;

	visit = NULL;
	queue = ft_bilstnew(start, sizeof(t_room));
	while (queue)
	{
		ft_bilstadd(&visit, ft_bilstnew(queue->content, sizeof(t_room)));
		links = ((t_room*)queue->content)->links;
		while (links)
		{
			if (!find_parant_part(links, visit, queue, dont_visit))
				return ;
			links = links->next;
		}
		ft_bilstdelone(&queue, del_node);
	}
	ft_bilstdel(&visit, del_node);
}

t_bilist	*find_short_corridor(t_room *end_room)
{
	t_bilist	*list;
	t_room		*tmp;

	list = 0;
	tmp = end_room;
	while (tmp)
	{
		ft_bilstadd(&list, ft_bilstnew(tmp, 0));
		tmp = tmp->parent;
	}
	if (((t_room*)list->content)->is_start)
		return (list);
	ft_bilstdel(&list, del_node);
	return (0);
}
