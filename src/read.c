/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 04:12:09 by midrissi          #+#    #+#             */
/*   Updated: 2019/06/12 05:57:55 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fdf.h"

static int		check_line(char *str, int fd)
{
	char	**words;
	int		i;
	int		j;

	if (!(words = ft_strsplit(str, ' ')))
	{
		close(fd);
		exit(1);
	}
	j = -1;
	while (words[++j])
	{
		if (!(i = 0) && words[j][i] == '-')
			i++;
		while (ft_isdigit(words[j][i]))
			i++;
		if (words[j][i])
			return (0);
	}
	i = 0;
	while (words[i])
		free(words[i++]);
	free(words[i]);
	free(words);
	return (j);
}

static int		create_list(int fd, t_list **begin)
{
	char		*str;
	int			ret;
	t_list		*lst;
	int			words;
	int			lines;

	words = -1;
	lines = 0;
	while ((ret = get_next_line(fd, &str, '\n')) > 0)
	{
		if (words == -1)
			words = check_line(str, fd);
		if (words != check_line(str, fd))
			return (ft_lstdestroy(begin));
		if (!(lst = ft_lstnew((void *)str, ft_strlen(str) + 1)))
			return (ft_lstdestroy(begin));
		ft_lstadd(begin, lst);
		ft_strdel(&str);
		lines++;
	}
	if (ret)
		return (ft_lstdestroy(begin));
	ft_lstrev(begin);
	return (lines);
}

static int		*create_row(char *str, int fd)
{
	char	**words;
	int		*row;
	int		j;

	row = (int *)malloc(sizeof(int) * (ft_count_words(str, ' ')));
	if (!(words = ft_strsplit(str, ' ')) || !row)
	{
		close(fd);
		exit(1);
	}
	j = 0;
	while (words[j])
	{
		row[j] = ft_atoi(words[j]);
		j++;
	}
	j = 0;
	while (words[j])
		free(words[j++]);
	free(words[j]);
	free(words);
	return (row);
}

static void		end(char *str, int fd)
{
	ft_putendl_fd(str, 2);
	close(fd);
	exit(1);
}

t_map			*create_map(int fd)
{
	t_list		*list;
	t_list		*begin;
	char		*str;
	int			lines;
	t_map		*map;

	begin = NULL;
	lines = create_list(fd, &begin);
	map = (t_map *)malloc(sizeof(t_map));
	map ? map->board = (int **)malloc(sizeof(int *) * lines) : 0;
	if (!(list = begin) || !lines || !map || !(map->board))
		end("map error", fd);
	map->x = ft_count_words((char *)list->content, ' ');
	map->y = 0;
	while (map->y < lines)
	{
		str = (char *)list->content;
		map->board[(map->y)++] = create_row(str, fd);
		list = list->next;
	}
	ft_lstdestroy(&begin);
	return (map);
}
