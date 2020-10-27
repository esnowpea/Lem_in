/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esnowpea <esnowpea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 15:22:04 by esnowpea          #+#    #+#             */
/*   Updated: 2020/10/27 15:35:56 by esnowpea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"
# include "ft_printf.h"
# include "error_message.h"
# include <fcntl.h>

# define FILE_NAME "/Users/esnowpea/CLionProjects/Lem_in/input_data.txt" //todo

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

typedef struct			s_find_solution
{
	t_bilist			*corridor;
	t_bilist			*solution;
	t_bilist			*dont_visit;
	t_bilist			*tmp_corridor;
}						t_find_solution;

t_lem_in				*init_lem_in();

t_bilist				*select_solution(t_lem_in *lem_in);
t_bilist				*find_short_corridor(t_room *end_room);
t_bilist				*ft_start_ants_first_room(t_bilist *solution, int ants);

t_room					*new_room(char *name, int x, int y);

size_t					ft_count_len_corridor(t_bilist *cor);
size_t					ft_one_solution_add_ants(t_bilist *sol, size_t an);

void					terminate(char *s);
void					find_solution(t_lem_in *lem_in);
void					parsing_input(t_lem_in *lem_in);
void					ft_last_chek(int gnl, t_lem_in *lem_in);
void					print_result(int ants, t_lem_in *lem_in);
void					del_node(void *content, size_t content_size);
void					print_current_position_ants(t_bilist *solution);
void					find_parant(t_room *start, t_bilist *dont_visit);
void					ft_add_vertex(t_lem_in *lem_in, char **line, int fd);
void					ft_bilstsort_content_size(t_bilist **alst);

int						ft_search_coordin(int i, char *line);
int						find_room(t_room *room, t_bilist *rooms);
int						ft_add_edge(t_lem_in *lem_in, char *line);
int						ft_count_data(size_t *cont, size_t *an, int i);
int						ft_step_ants_room(t_bilist *sol, int *ant, int ants);
int						find_length_corridor_with_ants(int ants, t_bilist *sol);

char					*ft_free_line(char *line);
char					*ft_next_gnl(char *line, int fd);

#endif
