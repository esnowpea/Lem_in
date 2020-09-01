/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esnowpea <esnowpea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 15:58:40 by esnowpea          #+#    #+#             */
/*   Updated: 2020/09/01 18:00:05 by esnowpea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <fcntl.h>

int		g_fd;

int		pars_ants(void)
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

int		check_comment(char *str)
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

int		find_rooms(char *name, t_bilist *rooms)
{
	t_bilist	*tmp;

	tmp = rooms;
	while (tmp)
	{
		if (ft_strequ(((t_room*)tmp->content)->name, name))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

t_room	*check_rooms(char *str, t_lem_in *lem_in)
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
	if (find_rooms(name, lem_in->rooms))
		terminate(ERR_BAD_ROOMS);
	if (name && name[0] == 'L')
		terminate(ERR_BAD_ROOMS);
	return (new_room(name, x, y));
}

int		find_links(char *name1, char *name2, t_bilist *links)
{
	t_bilist	*tmp;

	tmp = links;
	while (tmp)
	{
		if (ft_strequ(((t_link*)tmp->content)->name1, name1) &&
		ft_strequ(((t_link*)tmp->content)->name2, name2))
			return (1);
		else if (ft_strequ(((t_link*)tmp->content)->name1, name2) &&
		ft_strequ(((t_link*)tmp->content)->name2, name1))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

t_link	*check_links(char *str, t_lem_in *lem_in)
{
	char	*tmp;
	char	*name1;
	char	*name2;

	if (!(tmp = ft_strstr(str, "-")))
		return (0);
	*tmp = '\0';
	tmp++;
	if (!(name1 = ft_strdup(str)))
		terminate(ERR_MALC_INIT);
	if (!(name2 = ft_strdup(tmp)))
		terminate(ERR_MALC_INIT);
	if (ft_strstr(name1, " ") || ft_strstr(name2, " "))
		terminate(ERR_BAD_LINKS);
	if (!find_rooms(name1, lem_in->rooms) || !find_rooms(name2, lem_in->rooms))
		terminate(ERR_BAD_LINKS);
	if (find_links(name1, name2, lem_in->links))
		terminate(ERR_BAD_LINKS);
	return (new_link(name1, name2));
}

void	pars_rooms_and_links(t_lem_in *lem_in, char *line, int command)
{
	t_room *room;
	t_link *link;

	if (check_comment(line))
		return ;
	else if (!lem_in->links && (room = check_rooms(line, lem_in)))
	{
		room->is_end = command == 3 ? 1 : 0;
		room->is_start = command == 2 ? 1 : 0;
		ft_bilstadd_back(&(lem_in->rooms),
				ft_bilstnew(room, sizeof(t_room)));
	}
	else if (lem_in->links && check_rooms(line, lem_in))
		terminate(ERR_BAD_ROOMS);
	else if ((link = check_links(line, lem_in)))
	{
		ft_bilstadd_back(&(lem_in->links),
				ft_bilstnew(link, sizeof(t_link)));
	}
}

int		check_corridor(t_bilist *room, t_lem_in *lem_in)
{
	t_bilist *tmp;

	tmp = lem_in->links;
	while (tmp)
	{
		ft_strequ((t_link *)tmp->content)->name1, ((t_room*)room->content)
		->name);
		tmp = tmp->next;
	}
}

int		check_start_and_end(t_lem_in *lem_in)
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
	return (check_corridor(start_room, lem_in));
}

void	parsing_input(t_lem_in *lem_in)
{
	char	*line;
	int		comment;
	int		gnl;

	g_fd = 0;
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
