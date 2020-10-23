/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_result_step_ants_room.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablane <ablane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 16:24:25 by ablane            #+#    #+#             */
/*   Updated: 2020/10/22 16:24:25 by ablane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		ft_chek_solution_room_for_ants(t_bilist *solution, size_t an, int ants)
{
	t_bilist	*tmp;
	t_bilist	*cor;

	if (an <= (size_t)ants)
		return (1);
	tmp = solution;
	while (tmp)
	{
		if (tmp->content_size)
			return (1);
		cor = (t_bilist*)tmp->content;
		while (cor)
		{
			if (cor->content_size)
				return (1);
			cor = cor->next;
		}
		tmp = tmp->next;
	}
	return (0);
}

void	ft_step_ants_corridor(t_bilist *cor, size_t *num_ant, int ants)
{
	t_bilist	*tmp;

	tmp = (t_bilist*)cor->content;
	while (tmp->next)
		tmp = tmp->next;
	while (tmp->prev)
	{
		tmp->content_size = tmp->prev->content_size;
		tmp->prev->content_size = 0;
		tmp = tmp->prev;
	}
	if (cor->content_size > 0 && *num_ant <= (size_t)ants)
	{
		tmp->content_size = *num_ant;
		*num_ant = *num_ant + 1;
		cor->content_size--;
	}
}

int		ft_step_ants_room(t_bilist *solution, int *ant, int ants)
{
	size_t		an;
	t_bilist	*tmp;

	an = *ant;
	tmp = solution;
	while (tmp)
	{
		ft_step_ants_corridor(tmp, &an, ants);
		tmp = tmp->next;
	}
	*ant = an;
	return (ft_chek_solution_room_for_ants(solution, an, ants));
}
