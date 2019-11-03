/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merras <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 19:19:29 by merras            #+#    #+#             */
/*   Updated: 2019/11/03 18:31:42 by merras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void 		mini_clear(t_game *w)
{
	mlx_clear_window(w->mlx_ptr, w->win_ptr);
	mlx_destroy_image(w->mlx_ptr, w->img_ptr);
}

int			exit_cleanup(void *w)
{
	mini_clear((t_game *)w);
	//cleanup;
	exit(0);
}

void 	menu_event(int key, t_game *w)
{
	if (key == 124)
	{
		if (w->level < 2)
			w->level++;
		else
			w->level = 0;
		mini_clear(w);
		main_menu(w);
	}
	if (key == 123)
	{
		if (w->level > 0)
			w->level--;
		else
			w->level = 2;
		mini_clear(w);
		main_menu(w);
	}
}

void set_params(t_game *w)
{
	int fd;
	if (w->level == 0)
		fd = open("worlds/world0.map", O_RDONLY);
	if (w->level == 0)
		fd = open("worlds/world1.map", O_RDONLY);
	if (w->level == 0)
		fd = open("worlds/world2.map", O_RDONLY);
	w->fd = fd;
	render_handler(w);
}

int		key_press(int key, t_game *w)
{
	if (key == 124 || key == 123)
	{
		if (!F_GET(w->flags, GAMEPLAY))
			menu_event(key, w);
	}
	if (key == 53)
	{
		if (!F_GET(w->flags, GAMEPLAY))
			exit_cleanup(w);
		else
		{
			mini_clear(w);
			F_UNSET(w->flags, GAMEPLAY);
			main_menu(w);
		}
	}
	if (key == 36)
		if (!F_GET(w->flags, GAMEPLAY))
		{
			F_SET(w->flags, GAMEPLAY);
			set_params(w);
		}
	return (0);
}

void 	border(t_game *w)
{
	int start;
	int x;
	int y;

	if (w->level == 0)
		start = 89;
	else if (w->level == 1)
		start = 89 + 100 + 10;
	else if (w->level == 2)
		start = 89 + (100 + 10) * 2;
	y = -1;
	while (++y < 102)
	{
		x = 0;
		while (x < 102)
		{
			if (((x == 0 && y != 0) || (y == 0 && x != 0)) && x < 80 && y < 80)
				mlx_pixel_put(w->mlx_ptr, w->win_ptr, x + start, y + 329, 0xFFFFFF);
			x++;
		}
	}
}

void 		main_menu(t_game *w)
{
	int		width;
	int		height;
	void	*xpm;

	w->img_ptr = mlx_new_image(w->mlx_ptr, WIDTH, HEIGHT);
	xpm = mlx_xpm_file_to_image (w->mlx_ptr, "./ressources/main.xpm", &width, &height);
	mlx_put_image_to_window(w->mlx_ptr, w->win_ptr,	xpm, 0, 0);
	border(w);
	xpm = mlx_xpm_file_to_image (w->mlx_ptr, "./ressources/icon.xpm", &width, &height);
	mlx_put_image_to_window(w->mlx_ptr, w->win_ptr, xpm, 90, 330);
	xpm = mlx_xpm_file_to_image (w->mlx_ptr, "./ressources/level.xpm", &width, &height);
	mlx_put_image_to_window(w->mlx_ptr, w->win_ptr, xpm, width + 90 + 10, 330);
	xpm = mlx_xpm_file_to_image (w->mlx_ptr, "./ressources/level.xpm", &width, &height);
	mlx_put_image_to_window(w->mlx_ptr, w->win_ptr, xpm, (width * 2) + 90 + 20, 330);
}

static void	init_game(t_game *w)
{
	F_UNSET(w->flags, GAMEPLAY);
	w->level = 0;
	w->mlx_ptr = mlx_init();
	w->win_ptr = mlx_new_window(w->mlx_ptr, WIDTH, HEIGHT, EXEC_NAME);
	//arrow hooks
	//esc hook
	//mouse hook
	//enter hook
	main_menu(w);
	mlx_hook(w->win_ptr, 17, 1, exit_cleanup, w);
	mlx_hook(w->win_ptr, 2, 1, key_press, w);
}

int			main(void)
{
	t_game	wolf3d;

	init_game(&wolf3d);
	//load_home(&wolf3d);

	// DEV
	int fd = open("worlds/world0.map", O_RDONLY);
	//load_gameplay(fd, &wolf3d);
	//
	mlx_loop(wolf3d.mlx_ptr);
}
