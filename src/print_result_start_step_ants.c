/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_result_start_step_ants.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablane <ablane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 16:15:18 by ablane            #+#    #+#             */
/*   Updated: 2020/10/22 16:22:26 by ablane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		ft_subtract_len_corridor_content_size(t_bilist *solution)
{
	t_bilist	*tmp;

	tmp = solution;
	while (tmp)
	{
		tmp->content_size -= ft_count_len_corridor((t_bilist*)tmp->content);
		tmp = tmp->next;
	}
}

size_t		ft_add_ant_corr(t_bilist *cor, size_t an)
{
	int			i;
	t_bilist	*tmp;

	tmp = cor;
	while (tmp)
	{
		i = 0;
		if (!tmp->next && !tmp->prev)
			an = ft_one_solution_add_ants(tmp, an);
		if (tmp->next && tmp->content_size < tmp->next->content_size &&
			an)
			i = ft_count_data(&tmp->content_size, &an, 1);
		if (tmp->next && tmp->content_size == tmp->next->content_size &&
			an)
			i = ft_count_data(&tmp->content_size, &an, 0);
		if (i == 1)
			return (an);
		if (!tmp->next && tmp->prev && tmp->content_size <
			tmp->prev->content_size && an)
			ft_count_data(&tmp->content_size, &an, 0);
		tmp = tmp->next;
	}
	return (an);
}

void		ft_add_ants_solution(t_bilist *solution, int ants)
{
	size_t		an;
	t_bilist	*tmp;

	an = (size_t)ants;
	while (an)
	{
		tmp = solution;
		an = ft_add_ant_corr(tmp, an);
	}
}

t_bilist	*ft_start_ants_first_room(t_bilist *solution, int ants)
{
	t_bilist *tmp;

	tmp = solution;
	while (tmp)
	{
		tmp->content_size = ft_count_len_corridor((t_bilist*)tmp->content);
		tmp = tmp->next;
	}
	ft_bilstsort_content_size(&solution);
	ft_add_ants_solution(solution, ants);
	ft_subtract_len_corridor_content_size(solution);
	ft_bilstsort_content_size(&solution);
	return (solution);
}
