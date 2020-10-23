/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_last_chek.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablane <ablane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 16:11:33 by ablane            #+#    #+#             */
/*   Updated: 2020/10/22 16:11:33 by ablane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		find_corridor_pars(t_lem_in *lem_in)
{
	t_bilist	*corridor;

	find_parant(lem_in->start_room, 0);
	if (!(corridor = find_short_corridor(lem_in->end_room)))
		return (0);
	ft_bilstadd(&lem_in->solutions, ft_bilstnew(ft_bilstnew(corridor, 0), 0));
	return (1);
}

void	ft_check_list_name_room(t_bilist *this, t_bilist *tmp)
{
	int x;
	int y;

	x = ((t_room*)this->content)->coord_x;
	y = ((t_room*)this->content)->coord_y;
	while (tmp)
	{
		if ((ft_strequ(((t_room*)this->content)->name,
				((t_room*)tmp->content)->name)))
			terminate(ERR_BAD_ROOMS);
		else if (((t_room*)tmp->content)->coord_y == y &&
				((t_room*)tmp->content)->coord_x == x)
			terminate(ERR_BAD_COORD);
		else
			tmp = tmp->next;
	}
}

void	ft_check_limits(t_lem_in *lem_in, t_bilist *room, int *start, int *end)
{
	int st;
	int en;

	st = *start;
	en = *end;
	if (((t_room*)room->content)->is_start == 1)
	{
		lem_in->start_room = room->content;
		st++;
	}
	if (((t_room*)room->content)->is_end == 1)
	{
		lem_in->end_room = room->content;
		en++;
	}
	*start = st;
	*end = en;
}

int		check_start_and_end(t_lem_in *lem_in)
{
	int			end;
	int			start;
	t_bilist	*tmp;
	t_bilist	*this;

	start = 0;
	end = 0;
	if (!lem_in->rooms)
		return (0);
	this = lem_in->rooms;
	tmp = this->next;
	while (this->next)
	{
		ft_check_limits(lem_in, tmp, &start, &end);
		ft_check_list_name_room(this, tmp);
		this = this->next;
		tmp = this->next;
	}
	if (start != 1 || end != 1)
		return (0);
	return (find_corridor_pars(lem_in));
}

void	ft_last_chek(int gnl, t_lem_in *lem_in)
{
	if (gnl < 0)
		terminate(ERR_GNL_READ);
	if (!check_start_and_end(lem_in))
		terminate(ERR_BAD_INPUT);
}
