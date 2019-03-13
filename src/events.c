/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 08:58:10 by aben-azz          #+#    #+#             */
/*   Updated: 2019/03/13 12:00:18 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		evt_live_mouse_move(int x, int y, t_mlx *m)
{
	(void)x;
	(void)y;
	(void)m;
	if (m->is_pressed)
	{
		put_rainbow(m, x, y, m->is_ok);
		process(m);
	}
	return (0);
}

int		evt_live_key_clicked(int key, t_mlx *m)
{
	(void)m;
	if (53 == key)
		exit(0);
	else if (49 == key)
	{
		m->zoom = 100;
		m->xoffset = 500;
		m->yoffset = 400;
		m->altitude = 1;
	}
	return (0);
}

int		evt_live_key_pressed(int key, t_mlx *m)
{
	(void)m;
	if (key == ESC_KEY)
		exit(0);
	else if (key == RIGHT_KEY || key == D_KEY)
		m->xoffset += 5;
	else if (key == LEFT_KEY || key == A_KEY)
		m->xoffset -= 5;
	else if (key == UP_KEY || key == W_KEY)
		m->yoffset -= 5;
	else if (key == DOWN_KEY || key == S_KEY)
		m->yoffset += 5;
	else if (key == LSFT_KEY || key == RSFT_KEY)
		m->is_shift = 1;
	else if (49 == key)
	{
		m->zoom = 100;
		m->xoffset = 500;
		m->yoffset = 400;
		m->altitude = 1;
	}
	process(m);
	return (0);
}

unsigned long	rgb2dec(int r, int g, int b)
{
	return ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
}

int		evt_live_key_released(int key, t_mlx *m)
{
	if (key == LSFT_KEY)
		m->is_shift = 0;
	process(m);
	return (0);
}

void		put_rainbow(t_mlx *fdf, int x, int y, int focus)
{
	int i;
	int color[3];

	i = 0;
	color[0] = 255;
	color[1] = 0;
	color[2] = 0;
	while (i++ < 499)
	{
		(color[1] == 0 && color[0] == 255) && (color[2] += 5);
		(color[1] == 255 && color[0] == 0) && (color[2] -= 5);
		(color[1] == 0 && color[2] == 255) && (color[0] -= 5);
		(color[1] == 255 && color[2] == 0) && (color[0] += 5);
		(color[0] == 0 && color[2] == 255) && (color[1] += 5);
		(color[0] == 255 && color[2] == 0) && (color[1] -= 5);
		if (i == WIN_W - x && ((y >= WIN_H - 20 && y <= WIN_H - 5) || !focus))
			fdf->color = rgb2dec(color[0], color[2], color[1]);
		fdf->is_border = 1;
		put_line(fdf, (t_points){(t_point){DRAW_W + i, WIN_H - 25}, (t_point){
			DRAW_W + i, WIN_H - 5}}, 0, rgb2dec(color[0], color[2], color[1]));
		fdf->is_border = 0;
	}
}

int		evt_live_mouse_clicked(int x, int y, int z, t_mlx *m)
{
	if (m->is_shift)
	{
		if (x == 6)
			m->altitude++;
		else if (x == 7)
			m->altitude--;
	}
	else
	{
		if (x == WHEELUP)
			m->zoom += 5;
		else if (x == WHEELDOWN)
			m->zoom -= 5;
		else if (x == BUT1_KEY)
			m->is_pressed = 1;
		else if (x == BUT1_KEY && (y >= WIN_H - 25 && y <= WIN_H - 5))
			m->is_ok = 1;
		else if (x == BUT3_KEY)
			m->iso = !m->iso;
	}
	put_rainbow(m, y, z, 0);
	process(m);
	return (0);
}

int		evt_live_mouse_pressed(int x, int y, int z, t_mlx *m)
{
	(void)y;
	(void)z;
	(void)m;
	if (x == WHEELUP)
		m->zoom++;
	else if (x == WHEELDOWN)
		m->zoom--;
	else if (x == BUT1_KEY && !(m->is_ok = 0))
		m->is_pressed = 0;
	put_rainbow(m, y, z, 0);
	process(m);
	return (0);
}
