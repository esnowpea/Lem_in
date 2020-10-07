/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esnowpea <esnowpea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/18 16:18:20 by esnowpea          #+#    #+#             */
/*   Updated: 2020/10/07 18:25:40 by esnowpea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	print_corridor(t_bilist *rooms)
{
	t_bilist	*room;

	room = rooms;
	while (room)
	{
		if (room->content)
			ft_printf("[%s]%s", ((t_room *) room->content)->name,
					  room->next ? "->" : "\n");
		room = room->next;
	}
}

void	print_corridors(t_bilist *corridors)
{
	t_bilist	*corridor;

	corridor = corridors;
	while (corridor)
	{
		print_corridor(corridor->content);
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

void	print_links(t_bilist *rooms)
{
	t_bilist *tmp;
	t_bilist *room;

	tmp = rooms;
	while (tmp)
	{
		ft_printf("[%s links]:", ((t_room*)tmp->content)->name);
		room = ((t_room*)tmp->content)->links;
		print_corridor(room);
		ft_printf("[%s rmlinks]:", ((t_room*)tmp->content)->name);
		room = ((t_room*)tmp->content)->removed_links;
		print_corridor(room);
		ft_putchar('\n');
		tmp = tmp->next;
	}
}