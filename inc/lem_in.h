/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esnowpea <esnowpea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 15:22:04 by esnowpea          #+#    #+#             */
/*   Updated: 2020/08/31 17:42:09 by esnowpea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"
# include "ft_printf.h"
# include "error_message.h"

typedef struct			s_room
{
	char				*name;
	int					coord_x;
	int					coord_y;
	int					is_start;
	int					is_end;
}						t_room;

typedef struct			s_link
{
	char				*name1;
	char				*name2;
}						t_link;

typedef struct			s_lem_in
{
	int					ants;
	t_bilist			*rooms;
	t_bilist			*links;
}						t_lem_in;

void					terminate(char *s);
t_lem_in				*init_lem_in();
void					parsing_input(t_lem_in *lem_in);
t_room					*new_room(char *name, int x, int y);
t_link					*new_link(char *name1, char *name2);

#endif
