/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esnowpea <esnowpea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 15:58:40 by esnowpea          #+#    #+#             */
/*   Updated: 2020/09/02 18:34:24 by esnowpea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <fcntl.h>

int		g_fd;

int			pars_ants(void)
{
	char	*line;
	char	*tmp;
	int		ants;

	if (get_next_line(g_fd, &line) <= 0)
		terminate(ERR_GNL_READ);
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

t_room		*find_room(char *name, t_bilist *rooms)
{
	t_bilist	*tmp;

	tmp = rooms;
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
	if (find_room(name, lem_in->rooms))
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
	if (!(room1 = find_room(name1, lem_in->rooms)))
		terminate(ERR_BAD_LINKS);
	if (!(room2 = find_room(name2, lem_in->rooms)))
		terminate(ERR_BAD_LINKS);
	if (find_link(name1, room2) || find_link(name2, room1))
		terminate(ERR_BAD_LINKS);
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

void		del_room(void *content, size_t content_size)
{
	(void)content;
	(void)content_size;
}

int			add_corridor(t_room *room, t_bilist *corridor, t_lem_in *lem_in)
{
	t_bilist	*tmp;

	ft_bilstadd(&(lem_in->corridors),
			ft_bilstnew(ft_bilstnew(room, sizeof(t_room)), sizeof(t_bilist)));
	tmp = corridor;
	while (tmp)
	{
		ft_bilstadd((t_bilist**)(&lem_in->corridors->content),
					ft_bilstnew(tmp->content, sizeof(t_room)));
		tmp = tmp->next;
	}
	return (1);
}

int			check_corridor(t_room *room, t_bilist *corridor, t_lem_in *lem_in)
{
	t_bilist	*tmp;
	t_bilist	*tmp0;

	if (room->is_end)
		add_corridor(room, corridor, lem_in);
	tmp = room->links;
	while (tmp)
	{
		if (!find_room(((t_room*)tmp->content)->name, corridor))
		{
			tmp0 = ft_bilstnew(room, sizeof(t_room));
			if (corridor)
			{
				tmp0->next = corridor;
				corridor->prev = tmp0;
			}
			corridor = tmp0;
			check_corridor((t_room *)tmp->content, corridor, lem_in);
			tmp0 = corridor->next;
			ft_bilstdelone(&corridor, del_room);
			corridor = tmp0;
		}
		tmp = tmp->next;
	}
	return (1);
}

int			check_start_and_end(t_lem_in *lem_in)
{
	t_bilist	*tmp;
	t_bilist	*start_room;
	int			is_start;
	int			is_end;

	tmp = lem_in->rooms;
	is_start = 0;
	is_end = 0;
	while (tmp)
	{
		if (((t_room*)tmp->content)->is_start == 1)
		{
			start_room = tmp;
			is_start++;
		}
		if (((t_room*)tmp->content)->is_end == 1)
			is_end++;
		tmp = tmp->next;
	}
	if (is_start != 1 || is_end != 1)
		terminate(ERR_BAD_ROOMS);
	check_corridor(start_room->content, 0, lem_in);
	return (lem_in->corridors != NULL);
}

void		parsing_input(t_lem_in *lem_in)
{
	char	*line;
	int		comment;
	int		gnl;

	g_fd = 0;
//	open("/Users/esnowpea/CLionProjects/Lem_in/1.map", O_RDWR);
	lem_in->ants = pars_ants();
	comment = 0;
	while ((gnl = get_next_line(g_fd, &line)) > 0)
	{
		pars_rooms_and_links(lem_in, line, comment);
		comment = check_comment(line);
		free(line);
	}
	if (gnl < 0)
		terminate(ERR_GNL_READ);
	if (!check_start_and_end(lem_in))
		terminate(ERR_BAD_INPUT);
}
