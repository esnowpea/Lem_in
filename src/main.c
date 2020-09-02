/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esnowpea <esnowpea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 15:20:14 by esnowpea          #+#    #+#             */
/*   Updated: 2020/09/02 14:47:28 by esnowpea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	print_rooms(t_lem_in *lem_in)
{
	t_room		*room;
	t_bilist	*tmp;

	tmp = lem_in->rooms;
	while (tmp)
	{
		room = (t_room*)(tmp->content);
		ft_printf("%s %d %d", room->name, room->coord_x, room->coord_y);
		if (room->is_start)
			ft_printf(" start room");
		if (room->is_end)
			ft_printf(" end room");
		ft_printf("\n");
		tmp = tmp->next;
	}
}

void	print_links(t_lem_in *lem_in)
{
	t_room		*room;
	t_bilist	*tmp;
	t_bilist	*tmp0;

	tmp = lem_in->rooms;
	while (tmp)
	{
		room = (t_room*)(tmp->content);
		tmp0 = room->links;
		while (tmp0)
		{
			ft_printf("%s---%s", room->name, ((t_room*)tmp0->content)->name);
			if (room->is_start)
				ft_printf(" start room");
			if (room->is_end)
				ft_printf(" end room");
			ft_printf("\n");
			tmp0 = tmp0->next;
		}
		tmp = tmp->next;
	}
}

void	print_corridors(t_lem_in *lem_in)
{
	t_bilist	*tmp;
	t_bilist	*tmp0;

	tmp = lem_in->corridors;
	while (tmp)
	{
		tmp0 = (t_bilist*)tmp->content;
		while (tmp0)
		{
			ft_printf("[%s]->", ((t_room*)tmp0->content)->name);
			tmp0 = tmp0->next;
		}
		write(1, "\n", 1);
		tmp = tmp->next;
	}
}

int		main(void)
{
	t_lem_in	*lem_in;

	lem_in = init_lem_in();
	parsing_input(lem_in);
	ft_printf("ants = %d\n", lem_in->ants);
	print_rooms(lem_in);
	print_links(lem_in);
	print_corridors(lem_in);
	return (0);
}
