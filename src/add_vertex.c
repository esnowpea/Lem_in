/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_vertex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablane <ablane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 14:59:24 by ablane            #+#    #+#             */
/*   Updated: 2020/10/22 15:23:24 by esnowpea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	ft_add_coordinate(t_room *room, char *line, int i)
{
	if (!room->name)
		return ;
	while (line[i] != ' ' && line[i] != '\0')
		i++;
	if (line[i] == '\0')
		terminate(ERR_BAD_COORD);
	i = ft_search_coordin(i, line);
	room->coord_x = ft_atoi(&line[i]);
	i = ft_search_coordin(i, line);
	if (line[i] == '\0')
		terminate(ERR_BAD_COORD);
	room->coord_y = ft_atoi(&line[i]);
}

void	ft_start_end(t_room *room, int start)
{
	if (!start)
		return ;
	if (start == 1)
		room->is_start = 1;
	if (start == 2)
		room->is_end = 1;
}

char	*ft_add_this_name(char *line)
{
	int i;
	char *name;

	i = 0;
	while (line[i] != ' ' && line[i] != '\0')
		i++;
	if (line[i] == '\0' || (!(name = (char *)malloc(sizeof(char) * i + 1))))
		return (NULL);
	name[i--] = '\0';
	while (i != -1)
	{
		name[i] = line [i];
		if (name[i] == '-')
		{
			name = ft_free_line(name);
			i = 0;
		}
		i--;
	}
	return (name);
}

char	*ft_search_name_for_start_end(char *line , int fd)
{
	int i;

	i = 0;
	if (ft_strequ(line, "##start") || ft_strequ(line, "##end"))
		i = 1;
	while (line && ft_strlen(line) > 0 && line[0] == '#')
	{
		line = ft_next_gnl(line, fd);
		if ((ft_strequ(line, "##start") || ft_strequ(line, "##end")) && i == 1)
			return (ft_free_line(line));
	}
	return (line);
}

void	ft_add_vertex(t_lem_in *lem_in, char **line, int fd)
{
	int len;
	int start;
	t_room *room;

	start = 0;
	len = ft_strlen(*line);
	if (*line && len > 1 && *line[0] == '#')
	{
		if (ft_strequ(*line, "##start"))
			start = 1;
		else if (ft_strequ(*line, "##end"))
			start = 2;
		else
			return ;
		*line = ft_search_name_for_start_end(*line, fd);
	}
	if (!*line)
		return ;
	if (*line && *line[0] == 'L')
		terminate(ERR_BAD_BIG_L);
	room = new_room(ft_add_this_name(*line), 0 , 0);
	ft_start_end(room, start);
	ft_add_coordinate(room, *line, 0);
	ft_bilstadd(&(lem_in->rooms), ft_bilstnew(room, sizeof(t_room)));
}