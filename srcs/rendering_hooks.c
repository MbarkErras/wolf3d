/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_hooks.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merras <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 18:32:25 by merras            #+#    #+#             */
/*   Updated: 2019/11/06 00:41:28 by merras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"


void	init_gameplay(t_gameplay *g)
{
	g->position[X] = INITIAL_POSITION_X;
	g->position[Y] = INITIAL_POSITION_Y;
	g->direction[X] = INITIAL_DIRECTION_X;
	g->direction[Y] = INITIAL_DIRECTION_Y;
	g->plane[X] = INITIAL_PLANE_X;
	g->plane[Y] = INITIAL_PLANE_Y;
}

void	init_raycaster(t_gameplay g, t_raycaster *r, int x)
{
	double screenscalar;

	screenscalar = 2 * x / (double)WIDTH - 1;
	r->ray[X] = g.direction[X] + screenscalar * g.plane[X];
	r->ray[Y] = g.direction[Y] + screenscalar * g.plane[Y];
	r->map[X] = (int)g.position[X];
	r->map[Y] = (int)g.position[Y];
	//r->deltadist[X] = sqrt(1 + (r->ray[Y] * r->ray[Y]) / (r->ray[X] * r->ray[X]));
	//r->deltadist[Y] = sqrt(1 + (r->ray[X] * r->ray[X]) / (r->ray[Y] * r->ray[Y]));
	r->deltadist[X] = fabs(1 / r->ray[X]);
	r->deltadist[Y] = fabs(1 / r->ray[Y]);
}

void	update_step_sidedist(t_gameplay g, t_raycaster *r)
{
			/*
	r->step[X] = r->ray[X] < 0 ? -1 : 1;
	r->sidedist[X] = fabs((g.position[X] - r->map[X] + (r->ray[X] >= 0)) *
			r->deltadist[X]);
	r->step[Y] = r->ray[Y] < 0 ? -1 : 1;
	r->sidedist[Y] = fabs((g.position[Y] - r->map[Y] + (r->ray[Y] >= 0)) *
			r->deltadist[Y]);
	*/
	if (r->ray[X] < 0)
	{
		r->step[X] = -1;
		r->sidedist[X] = (g.position[X] - r->map[X]) * r->deltadist[X];
	}
	else
	{
		r->step[X] = 1;
		r->sidedist[X] = (-g.position[X] + r->map[X] + 1.0) * r->deltadist[X];
	}
	if (r->ray[Y] < 0)
	{
		r->step[Y] = -1;
		r->sidedist[Y] = (g.position[Y] - r->map[Y]) * r->deltadist[Y];
	}
	else
	{
		r->step[Y] = 1;
		r->sidedist[Y] = (-g.position[Y] + r->map[Y] + 1.0) * r->deltadist[Y];
	}

}

void	raycaster_loop(char **world, t_raycaster *r)
{
	int	nothit;
	int	updown;

	nothit = 1;
	while (nothit)
	{
		updown = r->sidedist[X] < r->sidedist[Y] ? X : Y;
		r->sidedist[updown] += r->deltadist[updown];
		r->map[updown] += r->step[updown];
		r->side = updown;
		if (world[r->map[X]][r->map[Y]] > '0')
			nothit = 0;
	}
}

void	verticalline(int x, int start, int end, char c, t_game *w)
{
	int i;

	while (++start < end)
	{
		i = 1000 * start + x;
		if (w->raycaster.side == X)
			w->config.data[i] = c == '1' ? 0xff0000 : (c == '2' ? 0x00ff00 : (0x0000ff));
		else if (w->raycaster.side == Y)
			w->config.data[i] = c == '1' ? 0x990202 : (c == '2' ? 0x016e01 : (0x02026e));
	}
}

void get_texture(t_game *w)
{
	int		width;
	int		height;
	void	*xpm;

	mlx_clear_window(w->config.mlx_ptr, w->config.win_ptr);
	w->config.img_ptr = mlx_new_image(w->config.mlx_ptr, WIDTH, HEIGHT);
	xpm = mlx_xpm_file_to_image (w->config.mlx_ptr, "./ressources/sky.xpm", &width, &height);
	mlx_put_image_to_window(w->config.mlx_ptr, w->config.win_ptr,	xpm, 0, 0);
	xpm = mlx_xpm_file_to_image (w->config.mlx_ptr, "./ressources/floor.xpm", &width, &height);
	mlx_put_image_to_window(w->config.mlx_ptr, w->config.win_ptr,	xpm, 0, 500);
}
void	render_scene(t_game *w)
{
	int	x;
	double	perpwalldist;

	mlx_clear_window(w->config.mlx_ptr, w->config.win_ptr);
	mlx_destroy_image(w->config.mlx_ptr, w->config.img_ptr);
	w->config.img_ptr = mlx_new_image(w->config.mlx_ptr, 1000, 1000);
	w->config.data = (int *)mlx_get_data_addr(w->config.img_ptr, &w->config.bpp, &w->config.s_l, &w->config.endian);
	//get_texture(w);
	x = -1;
	while (++x < WIDTH)
	{
		init_raycaster(w->gameplay, &w->raycaster, x);
		update_step_sidedist(w->gameplay, &w->raycaster);
		raycaster_loop(w->gameplay.world, &w->raycaster);
		if (w->raycaster.side == X)
			perpwalldist = (w->raycaster.map[X] - w->gameplay.position[X] +
			(1 - w->raycaster.step[X]) / 2) / w->raycaster.ray[X];
		else
			perpwalldist = (w->raycaster.map[Y] - w->gameplay.position[Y] +
			(1 - w->raycaster.step[Y]) / 2) / w->raycaster.ray[Y];
		int lineheight = (int)(HEIGHT / perpwalldist);
		int drawstart = -1 * lineheight / 2 + HEIGHT / 2;
		if(drawstart < 0)
			drawstart = 0;
		int drawend = lineheight / 2 + HEIGHT / 2;
		if(drawend >= HEIGHT)
			drawend = HEIGHT - 1;
		verticalline(x, drawstart, drawend, w->gameplay.world[w->raycaster.map[0]][w->raycaster.map[1]], w);
	}
	mlx_put_image_to_window(w->config.mlx_ptr, w->config.win_ptr, w->config.img_ptr, 0, 0);
}

void	render_handler(t_game *w)
{
	if (!(w->gameplay.world = read_world(w->gameplay.fd)))
		exit_cleanup(w);
	init_gameplay(&w->gameplay);
	render_scene(w);
}
