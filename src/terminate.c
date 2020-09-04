/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esnowpea <esnowpea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 16:12:26 by esnowpea          #+#    #+#             */
/*   Updated: 2020/09/04 16:34:00 by esnowpea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	terminate(char *s)
{
	ft_putendl_fd(s, 2);
	exit(0);
}

void	del_node(void *content, size_t content_size)
{
	(void)content;
	(void)content_size;
}
