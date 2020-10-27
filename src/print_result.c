/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_result.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablane <ablane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 13:27:11 by ablane            #+#    #+#             */
/*   Updated: 2020/10/27 16:49:36 by ablane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		find_max_length_corridor(t_bilist *corridors)
{
	t_bilist	*corridor;
	int			k;
	int			len;

	len = 0;
	corridor = corridors;
	while (corridor)
	{
		k = ft_bilstlength((t_bilist*)(corridor->content));
		if (k > len)
			len = k;
		corridor = corridor->next;
	}
	return (len);
}

int		find_length_corridor_with_ants(int ants, t_bilist *solution)
{
	t_bilist	*corridor;
	int			n;
	int			max_len;

	max_len = find_max_length_corridor(solution);
	n = ft_bilstlength(solution);
	corridor = solution;
	while (corridor)
	{
		if (ants > 0)
			ants -= max_len -
					ft_bilstlength((t_bilist*)(corridor->content));
		else
			return (max_len);
		corridor = corridor->next;
	}
	return (max_len + (ants / n) + (ants % n));
}

void	print_result(int ants, t_lem_in *lem_in)
{
	int			j;
	int			i;
	int			ant;
	t_bilist	*solution;

	i = 0;
	j = 1;
	ant = 1;
	solution = select_solution(lem_in);
	solution = ft_start_ants_first_room(solution, ants);
	while (j > 0)
	{
		j = ft_step_ants_room(solution, &ant, ants);
		if (j)
			print_current_position_ants(solution);
		if (i++ && j)
			ft_printf("\n");
	}
}
