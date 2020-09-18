/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esnowpea <esnowpea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 15:58:40 by esnowpea          #+#    #+#             */
/*   Updated: 2020/09/18 16:26:46 by esnowpea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			check_comment(char *str)
{
	int		i;

	if (str)
	{
		i = 0;
		if (str[i] != '#' || ft_strlen(str) < 3)
			return (0);
		else if (str[i] == '#' && str[i + 1] == '#')
		{
			if (ft_strequ(&str[i + 2], "start"))
				return (2);
			else if (ft_strequ(&str[i + 2], "end"))
				return (3);
			else
				return (1);
		}
		else if (str[i] == '#')
			return (1);
	}
	return (0);
}

int			pars_ants(void)
{
	char	*line;
	char	*tmp;
	int		ants;

	line = "#";
	while (get_next_line(0, &line) > 0 && check_comment(line))
		free(line);
	ants = ft_atoi(line);
	if (ants < 1)
		terminate(ERR_ANTS_PARC);
	tmp = ft_itoa(ants);
	if (ft_strcmp(tmp, line))
		terminate(ERR_ANTS_PARC);
	free(tmp);
	free(line);
	return (ants);
}

t_room		*find_room_name(char *name, t_bilist *rooms)
{
	t_bilist	*tmp;

	tmp = rooms;
	while (tmp && tmp->prev)
		tmp = tmp->prev;
	while (tmp)
	{
		if (ft_strequ(((t_room*)tmp->content)->name, name))
			return (tmp->content);
		tmp = tmp->next;
	}
	return (0);
}

t_room		*check_rooms(char *str, t_lem_in *lem_in)
{
	char	*tmp;
	char	*name;
	int		x;
	int		y;

	if (!(tmp = ft_strstr(str, " ")))
		return (0);
	tmp++;
	x = ft_atoi(tmp);
	if (!(tmp = ft_strstr(tmp, " ")))
		return (0);
	tmp++;
	y = ft_atoi(tmp);
	if (!(name = ft_strdup(str)))
		terminate(ERR_MALC_INIT);
	*(ft_strstr(name, " ")) = '\0';
	if (ft_strstr(name, "-"))
		terminate(ERR_BAD_ROOMS);
	if (find_room_name(name, lem_in->rooms))
		terminate(ERR_BAD_ROOMS);
	if (name && name[0] == 'L')
		terminate(ERR_BAD_ROOMS);
	return (new_room(name, x, y));
}

t_room		*find_link(char *name, t_room *room)
{
	t_bilist	*tmp;

	tmp = room->links;
	while (tmp)
	{
		if (ft_strequ(name, ((t_room*)tmp->content)->name))
			return (tmp->content);
		tmp = tmp->next;
	}
	return (0);
}

void		check_links(char *name1, t_lem_in *lem_in)
{
	char	*name2;
	t_room	*room1;
	t_room	*room2;

	if (!(name2 = ft_strstr(name1, "-")))
		return ;
	*name2 = '\0';
	name2++;
	if (ft_strstr(name1, " ") || ft_strstr(name2, " ") ||
	ft_strequ(name1, name2))
		terminate(ERR_BAD_LINKS);
	if (!(room1 = find_room_name(name1, lem_in->rooms)))
		terminate(ERR_BAD_LINKS);
	if (!(room2 = find_room_name(name2, lem_in->rooms)))
		terminate(ERR_BAD_LINKS);
	if (find_link(name1, room2) || find_link(name2, room1))
		return ;//terminate(ERR_BAD_LINKS);
	ft_bilstadd_back(&(room1->links), ft_bilstnew(room2, sizeof(t_room)));
	ft_bilstadd_back(&(room2->links), ft_bilstnew(room1, sizeof(t_room)));
}

int			exist_links(t_bilist *rooms)
{
	t_bilist	*tmp;

	tmp = rooms;
	while (tmp)
	{
		if (((t_room*)tmp->content)->links)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void		pars_rooms_and_links(t_lem_in *lem_in, char *line, int command)
{
	t_room	*room;

	if (check_comment(line))
		return ;
	else if (!exist_links(lem_in->rooms) && (room = check_rooms(line, lem_in)))
	{
		room->is_end = command == 3 ? 1 : 0;
		room->is_start = command == 2 ? 1 : 0;
		ft_bilstadd_back(&(lem_in->rooms),
				ft_bilstnew(room, sizeof(t_room)));
	}
	else if (exist_links(lem_in->rooms) && check_rooms(line, lem_in))
		terminate(ERR_BAD_ROOMS);
	else
		check_links(line, lem_in);
}

void		add_corridor(t_bilist *corridor, t_bilist **corridors)
{
	t_bilist	*room;

	ft_bilstadd(corridors, ft_bilstnew(0, sizeof(t_bilist)));
	room = corridor;
	while (room)
	{
		ft_bilstadd_back((t_bilist**)(&((*corridors)->content)),
					ft_bilstnew(room->content, sizeof(t_room)));
		room = room->next;
	}
}

void		find_corridors(t_room *room, t_bilist *corridor, t_lem_in *lem_in)
{
	t_bilist	*tmp;

	ft_bilstadd_back(&corridor, ft_bilstnew(room, sizeof(t_room)));
	if (room->is_end)
		add_corridor(corridor, &lem_in->corridors);
	else
	{
		tmp = room->links;
		while (tmp)
		{
			if (!find_room_name(((t_room *) tmp->content)->name, corridor))
				find_corridors((t_room *) tmp->content, corridor, lem_in);
			tmp = tmp->next;
		}
	}
	ft_bilstdelone_back(&corridor, del_node);
}

int			check_start_and_end(t_lem_in *lem_in)
{
	t_bilist	*tmp;
	int			is_start;
	int			is_end;

	tmp = lem_in->rooms;
	is_start = 0;
	is_end = 0;
	while (tmp)
	{
		if (((t_room*)tmp->content)->is_start == 1)
		{
			lem_in->start_room = tmp->content;
			is_start++;
		}
		if (((t_room*)tmp->content)->is_end == 1)
		{
			lem_in->end_room = tmp->content;
			is_end++;
		}
		tmp = tmp->next;
	}
	ft_printf("start: %d, end: %d\n", is_start, is_end);
	if (is_start != 1 || is_end != 1)
		terminate(ERR_BAD_ROOMS);
	ft_printf("Start find corridors\n");
	find_solution(1, lem_in);
//	exit(0);
//	find_corridors(start_room->content, 0, lem_in);
//	ft_bilstsort(&(lem_in->corridors), bilst_length_cmp);
	ft_printf("End find corridors\n");
	return (1);
}

void		parsing_input(t_lem_in *lem_in)
{
	char	*line;
	int		comment;
	int		gnl;

	lem_in->ants = pars_ants();
	comment = 0;
	while ((gnl = get_next_line(0, &line)) > 0)
	{
		pars_rooms_and_links(lem_in, line, comment);
		comment = check_comment(line);
		free(line);
	}
	if (gnl < 0)
		terminate(ERR_GNL_READ);
	ft_printf("End Parcing!\n");
	if (!check_start_and_end(lem_in))
		terminate(ERR_BAD_INPUT);
}
