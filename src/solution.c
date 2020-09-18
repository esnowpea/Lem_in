/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solution.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esnowpea <esnowpea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 15:12:00 by esnowpea          #+#    #+#             */
/*   Updated: 2020/09/18 16:33:46 by esnowpea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		restore_links(t_room *room1, t_room *room2)
{
	t_bilist *tmp;

	tmp = room1->removed_links;
	while (tmp)
	{
		if (tmp->content == room2)
		{
			if (tmp->prev)
				tmp->prev->next = tmp->next;
			if (tmp->next)
				tmp->next->prev = tmp->prev;
			ft_bilstadd(&room1->links, tmp);
			room1->removed_links = tmp->next;
			restore_links(room2, room1);
			return ;
		}
		tmp = tmp->next;
	}
}

void		removed_links(t_room *room1, t_room *room2)
{
	t_bilist *tmp;

	tmp = room1->links;
	while (tmp)
	{
		if (tmp->content == room2)
		{
			if (tmp->prev)
				tmp->prev->next = tmp->next;
			if (tmp->next)
				tmp->next->prev = tmp->prev;
			ft_bilstadd(&room1->removed_links, tmp);
			room1->links = tmp->next;
			removed_links(room2, room1);
			return ;
		}
		tmp = tmp->next;
	}
}

void 		restore_links_all(t_bilist *rooms)
{
	t_bilist	*tmp;

	tmp = rooms;
	while (tmp)
	{
		while (((t_room*)tmp->content)->removed_links)
			restore_links(tmp->content,
				 ((t_room*)tmp->content)->removed_links->content);
		tmp = tmp->next;
	}
}

int			find_room(t_room *room, t_bilist *rooms)
{
	t_bilist	*tmp;

	tmp = rooms;
	while (tmp)
	{
		if (room == (t_room*)tmp->content)
		{
			if (room->is_end || room->is_start)
				return (-1);
			else
				return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

void		null_parant(t_bilist *rooms)
{
	t_bilist *room;

	room = rooms;
	while (room)
	{
		((t_room*)room->content)->parent = NULL;
		room = room->next;
	}
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
			if (!find_room((t_room*)links->content, visit) &&
				!find_room((t_room*)links->content, queue) &&
				find_room((t_room*)links->content, dont_visit) <= 0)
			{
				((t_room*)links->content)->parent = (t_room*)queue->content;
				ft_bilstadd_back(&queue, ft_bilstnew(links->content, 0));
			}
			if (((t_room*)links->content)->is_end)
			{
				ft_bilstdel(&visit, del_node);
				ft_bilstdel(&queue, del_node);
				return ;
			}
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

void		find_solution(int n, t_lem_in *lem_in)
{
//	t_bilist	*corridor;

	if (n == 1)
	{
		find_parant(lem_in->start_room, 0);
		ft_bilstadd(&lem_in->solutions,
			  ft_bilstnew(
			  		ft_bilstnew(find_short_corridor(lem_in->end_room), 0), 0));
	}
//	print_corridor(corridor);
//	removed_links(lem_in->end_room, lem_in->end_room->parent);
//	null_parant(lem_in->rooms);
//	find_parant(lem_in->start_room, 0);
//	corridor = find_short_corridor(lem_in->end_room);
//	print_corridor(corridor);
//	restore_links_all(lem_in->rooms);
//	null_parant(lem_in->rooms);
//	find_parant(lem_in->start_room, corridor);
//	corridor = find_short_corridor(lem_in->end_room);
//	print_corridor(corridor);
}