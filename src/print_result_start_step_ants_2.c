/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_result_start_step_ants_2.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablane <ablane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 16:19:09 by ablane            #+#    #+#             */
/*   Updated: 2020/10/22 16:56:05 by ablane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			ft_content_size(size_t a, size_t b)
{
	if (a > b)
		return (1);
	return (0);
}

void		ft_bilstsort_content_size(t_bilist **alst)
{
	t_bilist	*tmp;

	if (alst && *alst)
	{
		tmp = *alst;
		while (tmp->prev)
			tmp = tmp->prev;
		while (tmp->next)
		{
			if (ft_content_size(tmp->content_size, tmp->next->content_size))
			{
				ft_bilstswap(tmp, tmp->next);
				while (tmp->prev)
					tmp = tmp->prev;
				continue;
			}
			tmp = tmp->next;
		}
		while (tmp->prev)
			tmp = tmp->prev;
		*alst = tmp;
	}
}

size_t		ft_count_len_corridor(t_bilist *cor)
{
	size_t	i;

	i = 0;
	while (cor)
	{
		cor = cor->next;
		i++;
	}
	return (i);
}

t_bilist	*select_solution(t_lem_in *lem_in)
{
	int			k;
	int			len;
	t_bilist	*corridors;
	t_bilist	*solution;

	len = 0;
	solution = NULL;
	corridors = lem_in->solutions;
	while (corridors)
	{
		k = find_length_corridor_with_ants(lem_in->ants, corridors->content);
		if (k < len || len == 0)
		{
			len = k;
			solution = corridors->content;
		}
		corridors = corridors->next;
	}
	return (solution);
}
