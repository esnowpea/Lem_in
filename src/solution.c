/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solution.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esnowpea <esnowpea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 15:12:00 by esnowpea          #+#    #+#             */
/*   Updated: 2020/10/22 14:51:57 by esnowpea         ###   ########.fr       */
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
			ft_bilstdelone(&(tmp), del_node);
			room1->removed_links = tmp;
			ft_bilstadd(&room1->links, ft_bilstnew(room2, 0));
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
			ft_bilstdelone(&(tmp), del_node);
			room1->links = tmp;
			ft_bilstadd(&room1->removed_links, ft_bilstnew(room2, 0));
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

int			corridor_cmp(t_bilist *corridor1, t_bilist *corridor2)
{
	t_bilist	*tmp1;
	t_bilist	*tmp2;

	tmp1 = corridor1;
	tmp2 = corridor2;
	while (tmp1 && tmp2)
	{
		if (!ft_strequ(((t_room*)tmp1->content)->name,
					   ((t_room*)tmp2->content)->name))
			return (0);
		tmp1 = tmp1->next;
		tmp2 = tmp2->next;
	}
	return (1);
}

int			find_corridor(t_bilist *corridor, t_bilist *corridors)
{
	t_bilist	*tmp;

	tmp = corridors;
	while (tmp)
	{
		if (corridor_cmp(corridor, tmp->content))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

t_bilist	*find_solution_part(int n, t_lem_in *lem_in)
{
	t_bilist	*corridor;
	t_bilist	*tmp;
	t_bilist	*solution;
	t_bilist	*corridors;

	solution = 0;
	tmp = 0;
	corridors = 0;
	restore_links_all(lem_in->rooms);
	while (ft_bilstlength(solution) < n)
	{
		null_parant(lem_in->rooms);
		find_parant(lem_in->start_room, solution);
		corridor = find_short_corridor(lem_in->end_room);
		if (corridor && find_corridor(corridor, corridors))
			ft_bilstdel(&corridor, del_node);

		if (corridor)
			ft_bilstadd_back(&solution, ft_bilstnew(corridor, 0));
		else if (tmp)
		{
			if (tmp->next && tmp->next->next)
			{
				restore_links_all(lem_in->rooms);
				removed_links((t_room*)tmp->content,
				(t_room*)tmp->next->content);
				tmp = tmp->next;
			}
			else
				ft_bilstdel(&tmp, del_node);
		}
		else if (solution && (corridor = solution->content) &&
		ft_bilstlength(corridor) >= 4)
		{
			ft_bilstadd(&corridors, ft_bilstnew(corridor, 0));
			tmp = corridor->next;
			ft_bilstdelone(&solution, del_node);
		}
		else
			return (0);
	}
	return (solution);
}

void		find_solution(t_lem_in *lem_in)
{
	t_bilist	*solution;
	int			max_sol;
	int			len;
	int			n;

	max_sol = min(ft_bilstlength(lem_in->start_room->links),
				  ft_bilstlength(lem_in->end_room->links));
	n = 2;
	len = 0;
	while (n <= max_sol && (solution = find_solution_part(n, lem_in)) &&
	(len > find_length_corridor_with_ants(lem_in->ants, solution) || len == 0))
	{
		len = find_length_corridor_with_ants(lem_in->ants, solution);
		ft_bilstadd(&lem_in->solutions, ft_bilstnew(solution, 0));
		n++;
	}
}