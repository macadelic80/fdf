/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/03 09:25:27 by aben-azz          #+#    #+#             */
/*   Updated: 2019/05/22 15:02:29 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "mlx/mlx.h"
# include "custom.h"
# include "libft/includes/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <fcntl.h>
# define WIN_W 2000
# define WIN_H  1000
# define DRAW_W WIN_W - 500
# define KPRESS 2
# define KCLICK	3
# define MCLICK	4
# define MPRESS 5
# define MMOVE 	6
# define DROITE 124
# define GAUCHE 123
# define HAUT 126
# define BAS 125
# define ESC 53
# define WHEELUP 5
# define WHEELDOWN 4
# define WHEELCLICK 3
# define RIGHTCLICK 2
# define LEFTCLICK 2

# define SHOW_LIVE_MOUSE 0
# define SHOW_LIVE_KEY 0

typedef struct	s_map
{
	int				**board;
	int				x;
	int				y;
}				t_map;

typedef struct	s_image
{
	void		*ptr;
	char		*data;
	int			bpp;
	int			sizeline;
	int			endian;
}				t_image;

typedef struct	s_point
{
	int				x;
	int				y;
	int				color;
}				t_point;
typedef struct	s_points
{
	t_point			p1;
	t_point			p2;
}				t_points;
typedef struct	s_mlx
{
	void			*mlx;
	void			*win;
	t_image			*img;
	t_map			*map;
	int				zoom;
	int				xo;
	int				yo;
	int				is_border;
	int				is_shift;
	int				altitude;
	int				iso;
	int				clr;
	int				is_pressed;
	int				is_ok;
	float			angle_x;
	float			angle_y;
	float			angle_z;
	t_point			rotation_offset;
}				t_mlx;
t_map			*create_map(int fd);
int				evt_live_mouse_clicked(int x, int y, int z, t_mlx *m);
int				evt_live_key_pressed(int key, t_mlx *m);
int				evt_live_key_clicked(int key, t_mlx *m);
int				evt_live_mouse_move(int x, int y, t_mlx *m);
int				evt_live_mouse_pressed(int x, int y, int z, t_mlx *m);
int				evt_live_key_released(int key, t_mlx *m);
int				fdf(void);
void			draw(t_mlx *m);
void			process(t_mlx *fdf);
void			put_line(t_mlx *fdf, t_point p1, t_point p2, int offset);
void			put_rainbow(t_mlx *fdf, int x, int y, int focus);
void			rotate(t_mlx *fdf, t_point *point);
#endif
