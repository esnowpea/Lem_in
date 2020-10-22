/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablane <ablane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 15:11:27 by ablane            #+#    #+#             */
/*   Updated: 2020/10/22 14:22:25 by ablane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

char	*ft_free_line(char *line)
{
	if (line)
	{
		free(line);
		line = NULL;
	}
	return (line);
}

char	*ft_next_gnl(char *line, int fd)
{
	line = ft_free_line(line);
	if (get_next_line(fd, &line) > 0)
		return (line);
	return (NULL);
}

int		ft_ants(int fd)
{
	char	*line;
	int		ants;
	int i;

	i = 0;
	ants = 0;
	line = NULL;
	while (get_next_line(fd, &line) > 0 && line && line[i] == '#')
		line = ft_free_line(line);
	while (line && line[i] != '\0')
	{
		if (line[i] < '0' || line[i] > '9')
			return (0);
		i++;
	}
	if (line)
	{
		ants = ft_atoi(line);
		line = ft_free_line(line);
	}
	return (ants);
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

int		ft_search_coordin(int i, char *line)
{
	while (line[i] != ' ' && line[i] != '\t' && line[i] != '\0')
		i++;
	while ((line[i] == ' ' || line[i] == '\t') && line[i] != '\0')
		i++;
	return (i);
}

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

char	*ft_search_name(char *line)
{
	char *name;
	int i;

	i = 0;
	while (line[i] != '-' && line[i] != '\0')
		i++;
	if (line[i] == '-' && (line[i + 1] == '-' || line[i + 1] == '\0'))
	{
		line = ft_free_line(line);
		terminate(ERR_BAD_LINKS);
	}
	name = ft_strnew(i);
	if (!name)
		terminate(ERR_MALC_INIT);
	name[i--] = '\0';
	while (i != -1)
	{
		name[i] = line[i];
		i--;
	}
	return (name);
}

t_room *ft_search_name_struct(t_bilist *room, char *name)
{
	t_bilist *tmp;

	tmp = room;
	if (!name)
		return (NULL);
	while (tmp && (!(ft_strequ(((t_room *)tmp->content)->name, name))))
		tmp = tmp->next;
	if (tmp)
		return ((t_room *)tmp->content);
	return (NULL);
}

int 	ft_add_edge(t_lem_in *lem_in, char *line)
{
	char *name1; //todo попробовать сделать их не молочными;
	char *name2;
	t_room *tmp1;
	t_room *tmp2;
	int i;

	i = 0;
	if (line && line[i] == '\0')
		return (1);
	if (line && ft_strlen(line) > 1 && line[0] == '#')
		return (1);
	name1 = ft_search_name(line);
	while (line[i] != '-' && line[i] != '\0')
		i++;
	name2 = ft_search_name(&line[i + 1]);
	tmp1 = ft_search_name_struct(lem_in->rooms, name1);
	tmp2 = ft_search_name_struct(lem_in->rooms, name2);
	if (!tmp1 || !tmp2 || !name1 || !name2)
		terminate(ERR_BAD_LINKS);
	name1 = ft_free_line(name1);
	name2 = ft_free_line(name2);
	ft_bilstadd(&tmp1->links, ft_bilstnew(tmp2, sizeof(t_room)));
	ft_bilstadd(&tmp2->links, ft_bilstnew(tmp1, sizeof(t_room)));
	return (1);
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

void	ft_check_list_name_room(t_bilist *this, t_bilist *tmp)
{
	int x;
	int y;

	x = ((t_room*)this->content)->coord_x;
	y = ((t_room*)this->content)->coord_y;
	while (tmp)
	{
		if ((ft_strequ(((t_room*)this->content)->name,
					   ((t_room*)tmp->content)->name)))
			terminate(ERR_BAD_ROOMS);
		else if (((t_room*)tmp->content)->coord_y == y &&
				 ((t_room*)tmp->content)->coord_x == x)
			terminate(ERR_BAD_COORD);
		else
			tmp = tmp->next;
	}
}

void	ft_check_limits(t_lem_in *lem_in, t_bilist *room, int *start, int *end)
{
	int st;
	int en;

	st = *start;
	en = *end;
	if (((t_room*)room->content)->is_start == 1)
	{
		lem_in->start_room = room->content;
		st++;
	}
	if (((t_room*)room->content)->is_end == 1)
	{
		lem_in->end_room = room->content;
		en++;
	}
	*start = st;
	*end = en;
}

int			find_corridor_pars(t_lem_in *lem_in)
{
	t_bilist	*corridor;

	find_parant(lem_in->start_room, 0);
	if (!(corridor = find_short_corridor(lem_in->end_room)))
		return (0);
	ft_bilstadd(&lem_in->solutions, ft_bilstnew(ft_bilstnew(corridor, 0), 0));
	return (1);
}

int		check_start_and_end(t_lem_in *lem_in)
{
	int start;
	int end;
	t_bilist *tmp;
	t_bilist *this;

	start = 0;
	end = 0;
	if (!lem_in->rooms)
		return (0);
	this = lem_in->rooms;
	tmp = this->next;
	while (this->next)
	{
		ft_check_limits(lem_in, tmp, &start, &end);
		ft_check_list_name_room(this, tmp);
		this = this->next;
		tmp = this->next;
	}
	if (start != 1 || end != 1)
		return (0);
	return (find_corridor_pars(lem_in));
}

void	ft_last_chek(int gnl, t_lem_in *lem_in)
{
	if (gnl < 0)
		terminate(ERR_GNL_READ);
	if (!check_start_and_end(lem_in))
		terminate(ERR_BAD_INPUT);

}

int		ft_read_edge(t_lem_in *lem_in, int gnl, int fd)
{
	char	*line;

	line = NULL;
	while (gnl > 0)
	{
		gnl = get_next_line(fd, &line);
		if (gnl < 1 || line[0] == '\0')
			break ;
		if (ft_strchr(line, '-') || (ft_strchr(line, '#')))
			ft_add_edge(lem_in, line);
		else
		{
			line = ft_free_line(line);
			terminate(ERR_BAD_LINKS);
		}
		line = ft_free_line(line);
	}
	return (gnl);
}

void	parsing_input(t_lem_in *lem_in)
{
	char	*line;
	int		gnl;
	int 	i;
	int		fd;

	i = 0;
	line = NULL;
	fd = open("../input_data.txt", O_RDONLY, 0777);
	if (fd < 0)
		terminate(ERR_BAD_FILE);
	lem_in->ants = ft_ants(fd);
	if (lem_in->ants < 1)
		terminate(ERR_ANTS_PARC);
	while (i == 0 && (gnl = get_next_line(fd, &line)) > 0)
	{
		if ((ft_strchr(line, ' ') || ft_strchr(line, '#'))
			&& !ft_strchr(line, '-'))
			ft_add_vertex(lem_in, &line, fd);
		else
			i = ft_add_edge(lem_in, line);
		line = ft_free_line(line);
	}
	if (gnl > 0)
		gnl = ft_read_edge(lem_in, gnl, fd);
	ft_last_chek(gnl, lem_in);
}
