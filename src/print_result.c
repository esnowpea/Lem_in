/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_result.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablane <ablane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 13:27:11 by ablane            #+#    #+#             */
/*   Updated: 2020/10/22 14:08:27 by ablane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

size_t	ft_count_len_corridor(t_bilist *cor)
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

size_t	ft_add_ant_corr(t_bilist *cor, size_t an)
{
	t_bilist *tmp;
	int i;

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
		{
			return(an);
		}
		if (!tmp->next && tmp->prev && tmp->content_size <
									   tmp->prev->content_size && an)
			ft_count_data(&tmp->content_size, &an, 0);
		tmp = tmp->next;
	}
	return (an);
}

void	ft_add_ants_solution(t_bilist *solution, int ants)
{
	t_bilist *tmp;
	size_t	an;

	an = (size_t)ants;
	while (an)
	{
		tmp = solution;
		an = ft_add_ant_corr(tmp, an);
	}
}

void	ft_subtract_len_corridor_content_size(t_bilist *solution)
{
	t_bilist *tmp;

	tmp = solution;
	while (tmp)
	{
		tmp->content_size -= ft_count_len_corridor((t_bilist*)tmp->content);
		tmp = tmp->next;
	}
}

void	ft_bilstsort_content_size(t_bilist **alst, int (*cmp)(size_t , size_t))
{
	t_bilist	*tmp;

	if (alst && *alst)
	{
		tmp = *alst;
		while (tmp->prev)
			tmp = tmp->prev;
		while (tmp->next)
		{
			if (cmp(tmp->content_size, tmp->next->content_size))
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

int		ft_more_less_content_size(size_t a, size_t b)
{
	if (a > b)
		return (1);
	return (0);
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
	ft_bilstsort_content_size(&solution, ft_more_less_content_size);
	ft_add_ants_solution(solution, ants);
	ft_subtract_len_corridor_content_size(solution);
	ft_bilstsort_content_size(&solution, ft_more_less_content_size);
	return (solution);
}

void	ft_step_ants_corridor(t_bilist *cor, size_t *num_ant, int ants)
{
	t_bilist *tmp;

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

int		ft_chek_solution_room_for_ants(t_bilist *solution, size_t an, int ants)
{
	t_bilist *tmp;
	t_bilist *cor;

	if (an <= (size_t) ants)
		return (1);
	tmp = solution;
	while (tmp)
	{
		if(tmp->content_size)
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

int		ft_step_ants_room(t_bilist *solution, int *ant, int ants)
{
	t_bilist	*tmp;
	size_t		an;

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

int		ft_search_max_len_corridors(t_bilist *solution)
{
	int len;
	int len_max;
	t_bilist *tmp;

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

int		ft_next_cor(t_bilist **tmp_cor, int i)
{
	t_bilist* tmp;

	tmp = *tmp_cor;
	tmp = tmp->next;
	*tmp_cor = tmp;
	i--;
	return (i);
}

int		ft_search_for_next_print(t_bilist *tmp_solution, size_t ant, int i)
{
	t_bilist *tmp_cor;
	int n;

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
	char *name;
	t_room *tmp;
	int n;

	n = 0;
	while (cor && n <= i)
	{
		if(cor->prev && cor->content_size && n == i)
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

void	print_current_position_ants(t_bilist *solution)
{
	t_bilist *tmp;
	t_bilist *cor;
	t_bilist *tmp_solution;
	int i;
	int max_len;

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

t_bilist	*select_solution(t_lem_in *lem_in)
{
	t_bilist	*corridors;
	t_bilist	*solution;
	int			k;
	int			len;

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


void	print_result(int ants, t_lem_in *lem_in)
{
	int j;
	int i;
	int	ant;
	t_bilist *solution;

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
