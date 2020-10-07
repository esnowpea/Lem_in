/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esnowpea <esnowpea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 15:22:04 by esnowpea          #+#    #+#             */
/*   Updated: 2020/09/30 16:09:02 by esnowpea         ###   ########.fr       */
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
	t_bilist			*links;
	t_bilist			*removed_links;
	struct s_room		*parent;
	int					is_start;
	int					is_end;
}						t_room;

typedef struct			s_lem_in
{
	int					ants;
	t_room				*start_room;
	t_room				*end_room;
	t_bilist			*rooms;
	t_bilist			*corridors;
	t_bilist			*solutions;
}						t_lem_in;

void					terminate(char *s);
t_lem_in				*init_lem_in();
void					parsing_input(t_lem_in *lem_in);
t_room					*new_room(char *name, int x, int y);
void					del_node(void *content, size_t content_size);
int						bilst_length_cmp(void *a, void *b);
int						find_room(t_room *room, t_bilist *rooms);
void					find_solutions(t_bilist *solution, t_lem_in *lem_in);
void					add_corridor(t_bilist *corridor, t_bilist **corridors);
void					find_parant(t_room *start, t_bilist *dont_visit);
t_bilist				*find_short_corridor(t_room *end_room);
void					find_solution(t_lem_in *lem_in);
void	print_corridor(t_bilist *rooms);
void	print_corridors(t_bilist *corridors);
void	print_solutions(t_bilist *solutions);
void	print_links(t_bilist *rooms);

#endif
