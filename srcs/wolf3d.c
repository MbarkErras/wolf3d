/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merras <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 19:19:29 by merras            #+#    #+#             */
/*   Updated: 2019/11/01 20:13:12 by merras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static int		red_cross(t_game *w)
{
	mlx_clear_window(w->mlx_ptr, w->win_ptr);
	mlx_destroy_image(w->mlx_ptr, w->img_ptr);
	exit(0);
	return (0);
}

static void	init_game(t_game *w)
{
	w->mlx_ptr = mlx_init();
	w->win_ptr = mlx_new_window(w->mlx_ptr, WIDTH, HEIGHT, EXEC_NAME);
	w->img_ptr = mlx_new_image(w->mlx_ptr, WIDTH, HEIGHT);
	//arrow hooks
	//esc hook
	//mouse hook
	//enter hook
	mlx_hook(w->win_ptr, 17, 1, red_cross, w);
	mlx_loop(w->mlx_ptr);
}

int			main(void)
{
	t_game	wolf3d;

	init_game(&wolf3d);
	// load_home(&wolf3d);
	return (0);
}
