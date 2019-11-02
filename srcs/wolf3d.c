/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merras <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 19:19:29 by merras            #+#    #+#             */
/*   Updated: 2019/11/02 16:39:50 by event            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int			exit_cleanup(void *w)
{
	mlx_clear_window(((t_game *)w)->mlx_ptr, ((t_game *)w)->win_ptr);
	mlx_destroy_image(((t_game *)w)->mlx_ptr, ((t_game *)w)->img_ptr);
	//cleanup;
	exit(0);
}

static void	init_game(t_game *w)
{
	int		width;
	int		height;
	void	*xpm;

	w->mlx_ptr = mlx_init();
	w->win_ptr = mlx_new_window(w->mlx_ptr, WIDTH, HEIGHT, EXEC_NAME);
	w->img_ptr = mlx_new_image(w->mlx_ptr, WIDTH, HEIGHT);
	//arrow hooks
	//esc hook
	//mouse hook
	//enter hook
	xpm = mlx_xpm_file_to_image (w->mlx_ptr, "./ressources/main.xpm", &width, &height);
	mlx_put_image_to_window(w->mlx_ptr, w->win_ptr,	xpm, 0, 0);
	xpm = mlx_xpm_file_to_image (w->mlx_ptr, "./ressources/level.xpm", &width, &height);
	mlx_put_image_to_window(w->mlx_ptr, w->win_ptr, xpm, 90, 330);
	xpm = mlx_xpm_file_to_image (w->mlx_ptr, "./ressources/level.xpm", &width, &height);
	mlx_put_image_to_window(w->mlx_ptr, w->win_ptr, xpm, width + 90 + 10, 330);
	xpm = mlx_xpm_file_to_image (w->mlx_ptr, "./ressources/level.xpm", &width, &height);
	mlx_put_image_to_window(w->mlx_ptr, w->win_ptr, xpm, (width * 2) + 90 + 20, 330);
	mlx_hook(w->win_ptr, 17, 1, exit_cleanup, w);
}

int			main(void)
{
	t_game	wolf3d;

	init_game(&wolf3d);
	//load_home(&wolf3d);

	// DEV
	int fd = open("worlds/world0.map", O_RDONLY);
	load_gameplay(fd, &wolf3d);
	//
	mlx_loop(wolf3d.mlx_ptr);
}
