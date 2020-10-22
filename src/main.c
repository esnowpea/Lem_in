/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esnowpea <esnowpea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 15:20:14 by esnowpea          #+#    #+#             */
/*   Updated: 2020/10/22 15:09:21 by esnowpea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	ft_add_line_in_input(const char *line, int fd)
{
	int i;

	i = 0;
	if (!line)
		terminate(ERR_GNL_READ);
	if (line && !line[i])
		terminate(ERR_BAD_MAP);
	ft_putstr_fd(line, fd);
	ft_putchar_fd('\n', fd);
}

void	parsing_input_for_file(void)
{
	int		gnl;
	char	*line;
	int		fd;

	fd = open("../input_data.txt", O_RDWR | O_TRUNC | O_CREAT, 0777);
	if (fd < 0)
		terminate(ERR_BAD_FILE);
	while ((gnl = get_next_line(0, &line)) > 0)
	{
		ft_add_line_in_input(line, fd);
		line = ft_free_line(line);
	}
	if (fd > 1)
		close(fd);
	if	(gnl < 0)
		terminate(ERR_GNL_READ);
}

void	print_input(void)
{
	int		fd;
	int		gnl;
	char	*line;

	fd = open("../input_data.txt", O_RDONLY, 0777);
	if (fd < 0)
		terminate(ERR_BAD_FILE);
	while ((gnl = get_next_line(fd, &line)) > 0)
	{
		ft_printf("%s\n", line);
		line = ft_free_line(line);
	}
	if	(gnl < 0)
		terminate(ERR_GNL_READ);
	close(fd);
}

int		main(void)
{
	t_lem_in	*lem_in;

	lem_in = init_lem_in();
	parsing_input_for_file();
	parsing_input(lem_in);
	find_solution(lem_in);
	print_input();
	print_result(lem_in->ants, lem_in);
	exit(0);
}
