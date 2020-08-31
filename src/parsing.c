/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esnowpea <esnowpea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 15:58:40 by esnowpea          #+#    #+#             */
/*   Updated: 2020/08/31 18:40:40 by esnowpea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <fcntl.h>

int		g_fd;

int		pars_ants()
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
				return (1);
			else if (ft_strequ(&str[i + 2], "end"))
				return (2);
			else
				return (0);
		}
	}
	return (0);
}

t_room	*check_rooms(char *str)
{
	char	*tmp;
	char	*name;
	int		x;
	int		y;

	if (!(tmp = ft_strstr(str, " ")))
		return (0);
	*tmp = '\0';
	tmp++;
	x = ft_atoi(tmp);
	if (!(tmp = ft_strstr(tmp, " ")))
		return (0);
	tmp++;
	y = ft_atoi(tmp);
	if (ft_strstr(str, "-"))
		return (0);
	if (!(name = ft_strdup(str)))
		terminate(ERR_MALC_INIT);
	return (new_room(name, x, y));
}

t_link	*check_links(char *str)
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
	return (new_link(name1, name2));
}

void	pars_rooms(t_lem_in *lem_in)
{
	char	*line;
	t_room	*room;
	t_link	*link;
	int		gnl;
	int		command;

	command = 0;
	while ((gnl = get_next_line(g_fd, &line)) > 0)
	{
		if (!lem_in->links && (room = check_rooms(line)))
		{
			room->is_end = command == 2 ? 1 : 0;
			room->is_start = command == 1 ? 1 : 0;
			ft_bilstadd_back(&(lem_in->rooms),
							 ft_bilstnew(room, sizeof(t_room)));
			command = 0;
			continue;
		}
		if (lem_in->links && check_rooms(line))
			terminate(ERR_BAD_INPUT);
		if ((link = check_links(line)))
		{
			ft_bilstadd_back(&(lem_in->links),
							 ft_bilstnew(link, sizeof(t_link)));
		}
		command = check_comment(line);
		free(line);
	}
}

void	parsing_input(t_lem_in *lem_in)
{
	g_fd = open("/Users/esnowpea/CLionProjects/Lem_in/subject/map.txt", O_RDWR);
	lem_in->ants = pars_ants();
	pars_rooms(lem_in);
}