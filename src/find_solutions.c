/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_solutions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esnowpea <esnowpea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/04 16:39:11 by esnowpea          #+#    #+#             */
/*   Updated: 2020/09/18 11:31:51 by esnowpea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			corridor_cmp(t_bilist *corridor1, t_bilist *corridor2)
{
	t_bilist	*tmp1;
	t_bilist	*tmp2;

	tmp1 = ((t_bilist*)corridor1->content);
	tmp2 = ((t_bilist*)corridor2->content);
	while (tmp1 && tmp2)
	{
		if (!ft_strequ(((t_room*)tmp1->content)->name,
				((t_room*)tmp2->content)->name))
			return (0);
		tmp1 = tmp1->next;
		tmp2 = tmp2->next;
	}
	return (1);
}

int			solution_cmp(t_bilist *solution1, t_bilist *solution2)
{
	t_bilist	*tmp1;
	t_bilist	*tmp2;
	int			count;

	if (ft_bilstlength(&solution1) != ft_bilstlength(&solution2))
		return (0);
	count = 0;
	tmp1 = solution1;
	while (tmp1)
	{
		tmp2 = solution2;
		while (tmp2)
		{
			if (corridor_cmp(tmp1, tmp2))
				count++;
			tmp2 = tmp2->next;
		}
		tmp1 = tmp1->next;
	}
	if (count == ft_bilstlength(&solution1))
		return (1);
	return (0);
}

int			find_repeat_solution(t_bilist *solution, t_bilist *solutions)
{
	t_bilist	*corridors;

	corridors = solutions;
	while (corridors)
	{
		if (solution_cmp(solution, corridors->content))
			return (1);
		corridors = corridors->next;
	}
	return (0);
}

void		add_solution(t_bilist *solution, t_bilist **solutions)
{
	t_bilist	*corridor;

	ft_bilstadd(solutions, ft_bilstnew(0, sizeof(t_bilist)));
	corridor = solution;
	while (corridor)
	{
		add_corridor(corridor->content,
			(t_bilist**)(&((*solutions)->content)));
		corridor = corridor->next;
	}
}

int			check_corridor(t_bilist *ptr, t_bilist *solution)
{
	t_bilist	*tmp1;
	t_bilist	*tmp3;

	tmp1 = solution;
	while (tmp1)
	{
		tmp3 = ((t_bilist*)ptr->content)->next;
		if ((ft_bilstlength((t_bilist **) (&tmp1->content)) == 2 &&
			 ft_bilstlength((t_bilist **) (&ptr->content)) == 2))
			return (0);
		while (tmp3->next)
		{
			if (find_room((t_room*)tmp3->content, (t_bilist*)tmp1->content))
				return (0);
			tmp3 = tmp3->next;
		}
		tmp1 = tmp1->next;
	}
	return (1);
}

void		find_solutions(t_bilist *solution, t_lem_in *lem_in)
{
	t_bilist	*corridor;

	corridor = lem_in->corridors;
	while (corridor)
	{
		if (check_corridor(corridor, solution))
		{
			ft_bilstadd_back(&solution, ft_bilstnew(corridor->content,
				sizeof(t_bilist)));
			find_solutions(solution, lem_in);
			ft_bilstdelone_back(&solution, del_node);
		}
		corridor = corridor->next;
	}
	if (solution && !find_repeat_solution(solution, lem_in->solutions))
		add_solution(solution, &lem_in->solutions);
}
