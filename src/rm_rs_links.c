/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm_rs_links.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esnowpea <esnowpea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 16:27:10 by esnowpea          #+#    #+#             */
/*   Updated: 2020/10/27 16:32:37 by esnowpea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		restore_links(t_room *room1, t_room *room2)
{
	t_bilist	*tmp;

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
	t_bilist	*tmp;

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

void		restore_links_all(t_bilist *rooms)
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
