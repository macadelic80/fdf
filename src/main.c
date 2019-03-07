/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/08 08:51:22 by aben-azz          #+#    #+#             */
/*   Updated: 2019/03/07 05:22:36 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>


t_point		rasterise(t_mlx *fdf, t_point p, int z)
{
	(void)fdf;
	double cte1;
	double cte2;

	cte1 = 0.5;
	cte2 = 0.5;
	//p.x = fdf->xoffset + (p.x * fdf->zoom);
	p.x = 500 + (p.x * 100);
	p.y = 400 + (p.y * 100);
	//p.y = 400 + (p.y * fdf->zoom);
	p.x = 500 + (cte1 * p.x - cte2 * p.y);
	p.y = 400 + (-z + (cte1 / 2.0) * p.x + (cte2 / 2.0) * p.y);
	return (p);
}
void		draw(t_mlx *fdf)
{

	int		i;
	int		j;
	t_point p1;
	t_point p2;

	j = -1;

	while (++j < fdf->map->y)
	{
		i = 0;
		while (i < fdf->map->x)
		{
			p1 = (t_point){i, j};
			p2 = (t_point){i == fdf->map->x - 1 ? i : i + 1, j};
			p1 = rasterise(fdf, p1, fdf->map->board[p1.y][p1.x]);
			p2 = rasterise(fdf, p2, fdf->map->board[p2.y][p2.x]);
			put_line(fdf, p1, p2);
			p2 = (t_point){i, j == fdf->map->y - 1 ? j : j + 1};
			p2 = rasterise(fdf, p2, fdf->map->board[p2.y][p2.x]);
			put_line(fdf, p1, p2);
			i++;
		}
	}
}
void	print_map(t_map *map)
{
	int i;
	int j;

	j = 0;
	while (j < map->y)
	{
		i = 0;
		while (i < map->x)
		{
			printf("%*d", !i ? 0 : 3, map->board[j][i]);
			i++;
		}
		printf("\n");
		j++;
	}
}
t_mlx	*init(int fd)
{
	t_mlx	*fdf;

	if (!(fdf = (t_mlx *)malloc(sizeof(t_mlx))))
		exit(1);
	fdf->mlx = mlx_init();
	fdf->win = mlx_new_window(fdf->mlx, WIN_WIDTH, WIN_HEIGHT, "fdf");
	fdf->map = create_map(fd);
	if (!fdf->mlx || !fdf->win || close(fd))
		exit(1);
	// mlx_hook(fdf->win, KPRESS, 0, evt_live_key_pressed, &fdf);
	// mlx_hook(fdf->win, KCLICK, 0, evt_live_key_clicked, &fdf);
	// mlx_hook(fdf->win, MMOVE, 0, evt_live_mouse_move, &fdf);
	// mlx_hook(fdf->win, MCLICK, 0, evt_live_mouse_clicked, &fdf);
	// mlx_hook(fdf->win, MPRESS, 0, evt_live_mouse_pressed, &fdf);
	fdf->img = NULL;
	return (fdf);
}

int				main(int argc, char **argv)
{
	int		fd;
	t_mlx *m;

	if (argc != 2)
	{
		ft_dprintf(2, "usage: fdf input_file");
		return (0);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		perror("error");
	m = init(fd);
	process(m);
	mlx_loop(m->mlx);
	return (0);
}
