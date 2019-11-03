/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_hooks.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merras <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 18:32:25 by merras            #+#    #+#             */
/*   Updated: 2019/11/03 18:45:52 by merras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	render_handler(t_game *w)
{
	if (!(w->world = read_world(w->fd)))
		exit_cleanup(w);
	render_scene(w)
}

void	render_scene(t_game *w)
{
	mlx_clear_window(w->mlx_ptr, w->win_ptr)
}
