/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esnowpea <esnowpea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 15:20:14 by esnowpea          #+#    #+#             */
/*   Updated: 2020/08/31 18:31:50 by esnowpea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	print_rooms(t_lem_in *lem_in)
{
	t_room *room;

	while (lem_in->rooms)
	{
		room = (t_room*)(lem_in->rooms->content);
		ft_printf("%s %d %d", room->name, room->coord_x, room->coord_y);
		if (room->is_start)
			ft_printf(" start room");
		if (room->is_end)
			ft_printf(" end room");
		ft_printf("\n");
		lem_in->rooms = lem_in->rooms->next;
	}
}

void	print_links(t_lem_in *lem_in)
{
	t_link	*link;
	while (lem_in->links)
	{
		link = (t_link*)(lem_in->links->content);
		ft_printf("%s---%s\n", link->name1, link->name2);
		lem_in->links = lem_in->links->next;
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
	return (0);
}