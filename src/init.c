/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esnowpea <esnowpea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 15:59:26 by esnowpea          #+#    #+#             */
/*   Updated: 2020/08/31 16:14:26 by esnowpea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_room			*new_room(char *name, int x, int y)
{
	t_room		*room;

	if (!(room = (t_room*)ft_memalloc(sizeof(t_room))))
		terminate(ERR_MALC_INIT);
	room->name = name;
	room->coord_x = x;
	room->coord_y = y;
	return (room);
}

t_lem_in		*init_lem_in(void)
{
	t_lem_in	*lem_in;

	if (!(lem_in = (t_lem_in*)ft_memalloc(sizeof(t_lem_in))))
		terminate(ERR_MALC_INIT);
	return (lem_in);
}
