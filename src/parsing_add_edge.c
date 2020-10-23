/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_add_edge.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablane <ablane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 16:10:55 by ablane            #+#    #+#             */
/*   Updated: 2020/10/22 16:42:53 by ablane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_room	*ft_search_name_struct(t_bilist *room, char *name)
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

char	*ft_search_name(char *line)
{
	int		i;
	char	*name;

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

int		ft_add_edge(t_lem_in *lem_in, char *line)
{
	int		i;
	char	*name1;
	char	*name2;
	t_room	*tmp1;
	t_room	*tmp2;

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
