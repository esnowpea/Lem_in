/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esnowpea <esnowpea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 15:22:04 by esnowpea          #+#    #+#             */
/*   Updated: 2020/10/22 15:14:56 by ablane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"
# include "ft_printf.h"
# include "error_message.h"
# include <fcntl.h>

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
	t_bilist			*solutions;
}						t_lem_in;

t_lem_in				*init_lem_in();

t_bilist				*select_solution(t_lem_in *lem_in);
t_bilist				*find_short_corridor(t_room *end_room);

t_room					*new_room(char *name, int x, int y);

void					terminate(char *s);
void					find_solution(t_lem_in *lem_in);
void					print_corridor(t_bilist *rooms);
void					parsing_input(t_lem_in *lem_in);
void					print_corridors(t_bilist *corridors);
void					print_solutions(t_bilist *solutions);
void					print_result(int ants, t_lem_in *lem_in);
void					del_node(void *content, size_t content_size);
void					find_parant(t_room *start, t_bilist *dont_visit);
void					ft_add_vertex(t_lem_in *lem_in, char **line, int fd);

int						ft_search_coordin(int i, char *line);
int						find_room(t_room *room, t_bilist *rooms);
int						find_length_corridor_with_ants(int ants, t_bilist *sol);

char					*ft_free_line(char *line);
char					*ft_next_gnl(char *line, int fd);

#endif
