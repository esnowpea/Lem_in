/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablane <ablane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 15:11:27 by ablane            #+#    #+#             */
/*   Updated: 2020/10/27 14:36:24 by esnowpea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		ft_ants(int fd)
{
	int		i;
	int		ants;
	char	*line;

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

int		ft_search_coordin(int i, char *line)
{
	while (line[i] != ' ' && line[i] != '\t' && line[i] != '\0')
		i++;
	while ((line[i] == ' ' || line[i] == '\t') && line[i] != '\0')
		i++;
	return (i);
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
	int		i;
	int		fd;
	int		gnl;
	char	*line;

	i = 0;
	line = NULL;
	fd = open(FILE_NAME, O_RDONLY, 0777);
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
