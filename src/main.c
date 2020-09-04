/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esnowpea <esnowpea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 15:20:14 by esnowpea          #+#    #+#             */
/*   Updated: 2020/09/04 18:55:26 by esnowpea         ###   ########.fr       */
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

void	print_corridors(t_bilist *corridors)
{
	t_bilist	*corridor;
	t_bilist	*room;

	corridor = corridors;
	while (corridor->prev)
		corridor = corridor->prev;
	while (corridor)
	{
		room = (t_bilist*)corridor->content;
		ft_printf("len = %d: ", ft_bilstlength(room));
		while (room)
		{
			ft_printf("[%s]%s", ((t_room*)room->content)->name,
			room->next ? "->" : "\n");
			room = room->next;
		}
		corridor = corridor->next;
	}
}

void	print_solutions(t_bilist *solutions)
{
	t_bilist	*solution;
	int			i;

	solution = solutions;
	i = 1;
	while (solution)
	{
		ft_printf("\nSolution %d:\n", i++);
		print_corridors((t_bilist*)(solution->content));
		solution = solution->next;
	}
}

int		main(void)
{
	t_lem_in	*lem_in;

	lem_in = init_lem_in();
	parsing_input(lem_in);
	ft_printf("ants = %d\n", lem_in->ants);
//	print_rooms(lem_in);
//	print_links(lem_in);
	find_solution(lem_in);
	print_corridors(lem_in->corridors);
	print_solutions(lem_in->solutions);
	return (0);
}
