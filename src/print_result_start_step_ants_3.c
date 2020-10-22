/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_result_start_step_ants_3.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablane <ablane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 16:22:31 by ablane            #+#    #+#             */
/*   Updated: 2020/10/22 16:36:43 by ablane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

size_t	ft_one_solution_add_ants(t_bilist *sol, size_t an)
{
	sol->content_size = sol->content_size + an;
	an = 0;
	return (an);
}

int		ft_count_data(size_t *cont, size_t *an, int i)
{
	size_t	content;
	size_t	ant;

	content = *cont + 1;
	ant = *an - 1;
	*cont = content;
	*an = ant;
	return (i);
}

