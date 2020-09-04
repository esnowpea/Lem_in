/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_solutions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esnowpea <esnowpea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/04 16:39:11 by esnowpea          #+#    #+#             */
/*   Updated: 2020/09/04 21:19:27 by esnowpea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		add_solution(t_bilist *solution, t_bilist **solutions)
{
	t_bilist	*corridors;

	ft_bilstadd(solutions, ft_bilstnew(0, sizeof(t_bilist)));
	corridors = solution;
	while (corridors)
	{
		add_corridor(corridors->content,
			(t_bilist**)(&((*solutions)->content)));
		corridors = corridors->next;
	}
}

int			check_corridor(t_bilist *ptr, t_bilist *solution)
{
	t_bilist	*tmp1;
	t_bilist	*tmp2;
	t_bilist	*tmp3;

	tmp1 = solution;
	while (tmp1)
	{
		tmp2 = (t_bilist*)solution->content;
		while (tmp2)
		{
			tmp3 = (t_bilist*)ptr->content;
			while (tmp3)
			{
				if (!(((t_room*)tmp3->content)->is_start) &&
					!(((t_room*)tmp3->content)->is_end) &&
					(t_room*)tmp2->content == (t_room*)tmp3->content)
					return (0);
				tmp3 = tmp3->next;
			}
			tmp2 = tmp2->next;
		}
		tmp1 = tmp1->next;
	}
	return (1);
}

void		find_solution(t_lem_in *lem_in)
{
	t_bilist	*corridors;
	t_bilist	*ptr;
	t_bilist	*solution;
	int			i;

	corridors = lem_in->corridors;
	solution = 0;
	while (corridors)
	{
		ft_bilstadd(&solution,
			ft_bilstnew(corridors->content, sizeof(t_bilist)));
		ptr = corridors->next;
		while (ptr)
		{
			if (check_corridor(ptr, solution))
				ft_bilstadd(&solution,
							ft_bilstnew(ptr->content, sizeof(t_bilist)));
			ptr = ptr->next;
		}
		add_solution(solution, &lem_in->solutions);
		i = ft_bilstlength(solution);
		ft_bilstdel(&solution, del_node);
		while (i-- && corridors)
			corridors = corridors->next;
	}
}
