/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solution.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esnowpea <esnowpea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 15:12:00 by esnowpea          #+#    #+#             */
/*   Updated: 2020/10/27 16:52:24 by ablane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_bilist	*find_solution_part1(t_bilist *tmp_corridor, t_lem_in *lem_in)
{
	if (tmp_corridor->next && tmp_corridor->next->next)
	{
		restore_links_all(lem_in->rooms);
		removed_links((t_room*)tmp_corridor->content,
					(t_room*)tmp_corridor->next->content);
		return (tmp_corridor->next);
	}
	else
		return (0);
}

int			find_solution_part2(t_find_solution *var, t_lem_in *lem_in)
{
	if (var->corridor)
		ft_bilstadd_back(&var->solution, ft_bilstnew(var->corridor, 0));
	else if (var->tmp_corridor)
		var->tmp_corridor = find_solution_part1(var->tmp_corridor, lem_in);
	else if (var->solution && (var->corridor = var->solution->content) &&
			ft_bilstlength(var->corridor) >= 4)
	{
		ft_bilstadd(&var->dont_visit, ft_bilstnew(var->corridor, 0));
		var->tmp_corridor = var->corridor->next;
		ft_bilstdelone(&var->solution, del_node);
	}
	else
	{
		del_solution(&var->solution);
		del_solution(&var->dont_visit);
		return (0);
	}
	return (1);
}

t_bilist	*find_solution_part(int n, t_lem_in *lem_in)
{
	t_find_solution		var;

	var = init_find_solution();
	restore_links_all(lem_in->rooms);
	while (ft_bilstlength(var.solution) < n)
	{
		null_parant(lem_in->rooms);
		find_parant(lem_in->start_room, var.solution);
		var.corridor = find_short_corridor(lem_in->end_room);
		if (var.corridor && find_corridor(var.corridor, var.dont_visit))
			ft_bilstdel(&var.corridor, del_node);
		if (!find_solution_part2(&var, lem_in))
			return (0);
	}
	del_solution(&var.dont_visit);
	return (var.solution);
}

void		find_solution(t_lem_in *lem_in)
{
	t_bilist	*solution;
	int			max_sol;
	int			len;
	int			n;

	max_sol = min(ft_bilstlength(lem_in->start_room->links),
					ft_bilstlength(lem_in->end_room->links));
	n = 2;
	len = 0;
	while (n <= max_sol && (solution = find_solution_part(n, lem_in)))
	{
		if (len > find_length_corridor_with_ants(lem_in->ants, solution) ||
		len == 0)
		{
			len = find_length_corridor_with_ants(lem_in->ants, solution);
			ft_bilstadd(&lem_in->solutions, ft_bilstnew(solution, 0));
			n++;
		}
		else
		{
			del_solution(&solution);
			return ;
		}
	}
}
