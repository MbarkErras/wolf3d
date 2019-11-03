/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_hooks.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merras <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 18:32:25 by merras            #+#    #+#             */
/*   Updated: 2019/11/03 20:32:00 by merras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	init_gameplay(t_game *w)
{
	w->position[X] = INITIAL_POSITION_X;
	w->position[Y] = INITIAL_POSITION_Y;
	w->direction[X] = INITIAL_DIRECTION_X;
	w->direction[Y] = INITIAL_DIRECTION_Y;
	w->plane[X] = INITIAL_PLANE_X;
	w->plane[Y] = INITIAL_PLANE_Y;
}

void	render_handler(t_game *w)
{
	if (!(w->world = read_world(w->fd)))
		exit_cleanup(w);
	init_gameplay(w);
	render_scene(w)
}

void	render_scene(t_game *w)
{
	int	x;

	mlx_clear_window(w->mlx_ptr, w->win_ptr);
	x = -1;
	while (++x < WIDTH)
	{
		init_raycaster(w);
	
	}
}
