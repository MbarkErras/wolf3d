/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_hooks.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merras <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 18:32:25 by merras            #+#    #+#             */
/*   Updated: 2019/11/04 00:31:16 by merras           ###   ########.fr       */
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
	r->step[X] = r->ray[X] < 0 ? -1 : 1;
	r->sidedist[X] = fabs((g.position[X] - r->map[X] + (r->ray[X] >= 0)) *
			r->deltadist[X]);
	r->step[Y] = r->ray[Y] < 0 ? -1 : 1;
	r->sidedist[Y] = fabs((g.position[Y] - r->map[Y] + (r->ray[Y] >= 0)) *
			r->deltadist[Y]);
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
	while (++start < end)
	{
		mlx_pixel_put(w->config.mlx_ptr, w->config.win_ptr, x, start,
		c == '1' ? 0xff0000 : 0x00ff00);
	}
}

void	render_scene(t_game *w)
{
	int	x;
	double	perpwalldist;

	mlx_clear_window(w->config.mlx_ptr, w->config.win_ptr);
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
		if(drawstart < 0)drawstart = 0;
		int drawend = lineheight / 2 + HEIGHT / 2;
		if(drawend >= HEIGHT)drawend = HEIGHT - 1;
		verticalline(x, drawstart, drawend, w->gameplay.world[w->raycaster.map[0]][w->raycaster.map[1]], w);
	}
}

void	render_handler(t_game *w)
{
	if (!(w->gameplay.world = read_world(w->gameplay.fd)))
		exit_cleanup(w);
	init_gameplay(&w->gameplay);
	render_scene(w);
}
