/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bilst_length_cmp.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esnowpea <esnowpea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 13:42:09 by esnowpea          #+#    #+#             */
/*   Updated: 2020/09/05 13:51:26 by esnowpea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			bilst_length_cmp(void *a, void *b)
{
	t_bilist *ptr1;
	t_bilist *ptr2;

	ptr1 = (t_bilist*)a;
	ptr2 = (t_bilist*)b;
	if (ft_bilstlength(&ptr1) < ft_bilstlength(&ptr2))
		return (1);
	return (0);
}