/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_corridor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esnowpea <esnowpea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 16:28:24 by esnowpea          #+#    #+#             */
/*   Updated: 2020/10/27 16:28:50 by esnowpea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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
