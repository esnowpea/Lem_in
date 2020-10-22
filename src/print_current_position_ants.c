/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_current_position_ants.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablane <ablane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 16:26:52 by ablane            #+#    #+#             */
/*   Updated: 2020/10/22 16:26:52 by ablane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		ft_next_cor(t_bilist **tmp_cor, int i)
{
	t_bilist	*tmp;

	tmp = *tmp_cor;
	tmp = tmp->next;
	*tmp_cor = tmp;
	i--;
	return (i);
}

int		ft_search_for_next_print(t_bilist *tmp_solution, size_t ant, int i)
{
	int			n;
	t_bilist	*tmp_cor;

	i++;
	if (!tmp_solution)
		return (0);
	while (tmp_solution)
	{
		n = 0;
		tmp_cor = (t_bilist *)tmp_solution->content;
		while (tmp_cor)
		{
			if (tmp_cor->prev && tmp_cor->content_size == ant)
				i = ft_next_cor(&tmp_cor, i);
			if (tmp_cor && tmp_cor->prev && tmp_cor->content_size > 0 && n >= i)
				return (1);
			if (tmp_cor)
				tmp_cor = tmp_cor->next;
			n++;
		}
		tmp_solution = tmp_solution->next;
	}
	return (0);
}

void	ft_print_room(t_bilist *cor, int i, t_bilist *start)
{
	int		n;
	char	*name;
	t_room	*tmp;

	n = 0;
	while (cor && n <= i)
	{
		if (cor->prev && cor->content_size && n == i)
		{
			tmp = (t_room*)cor->content;
			name = tmp->name;
			ft_printf("L%d-%s", cor->content_size, name);
			if (ft_search_for_next_print(start, cor->content_size, i))
				ft_printf(" ");
		}
		n++;
		cor = cor->next;
	}
}

int		ft_search_max_len_corridors(t_bilist *solution)
{
	int			len;
	int			len_max;
	t_bilist	*tmp;

	len_max = 0;
	tmp = solution;
	while (tmp)
	{
		len = ft_count_len_corridor((t_bilist*)tmp->content);
		if (len > len_max)
			len_max = len;
		tmp = tmp->next;
	}
	return (len_max);
}

void	print_current_position_ants(t_bilist *solution)
{
	int			i;
	int			max_len;
	t_bilist	*tmp;
	t_bilist	*cor;
	t_bilist	*tmp_solution;

	i = 0;
	tmp_solution = solution;
	max_len = ft_search_max_len_corridors(solution);
	tmp = solution;
	while (tmp && i <= max_len)
	{
		cor = (t_bilist*)tmp->content;
		ft_print_room(cor, i, tmp_solution);
		tmp = tmp->next;
		if (i <= max_len && !tmp)
		{
			tmp = solution;
			i++;
		}
	}
}

