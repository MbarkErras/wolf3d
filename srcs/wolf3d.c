/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merras <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 19:19:29 by merras            #+#    #+#             */
/*   Updated: 2019/11/03 23:38:52 by merras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void mini_clear(t_game *w)
{
	mlx_clear_window(w->config.mlx_ptr, w->config.win_ptr);
	mlx_destroy_image(w->config.mlx_ptr, w->config.img_ptr);
}

int			exit_cleanup(void *w)
{
	mini_clear((t_game *)w);
	// mlx_clear_window(((t_game *)w)->config.mlx_ptr, ((t_game *)w)->config.win_ptr);
	//mlx_destroy_image(((t_game *)w)->mlx_ptr, ((t_game *)w)->img_ptr);
	//cleanup;
	exit(0);
}

int		mouse_press(int mouse, int x, int y, t_game *w)
{
	if (mouse == 1)
	{
		if (y >= 800 && y <= 900)
		{
			if (x >= 330 && x <= 430)
			{
				w->config.level = 0;
				F_SET(w->flags, GAMEPLAY);
				set_params(w);
			}
			if (x >= 440 && x <= 540)
			{
				w->config.level = 1;
				F_SET(w->flags, GAMEPLAY);
				set_params(w);
			}
			if (x >= 550 && x <= 650)
			{
				w->config.level = 2;
				F_SET(w->flags, GAMEPLAY);
				set_params(w);
			}
		}
	}
	return (0);
}

int		mouse_move(int x, int y, t_game *w)
{
	int		width;
	int		height;
	void	*xpm;
	if (!F_GET(w->flags, GAMEPLAY))
	{
		if (x <= WIDTH && x >=0 &&  y <= HEIGHT && y >=0)
		{
			if (y >= 800 && y <= 900)
			{
				if (x >= 330 && x <= 430)
					w->config.level = 0;
				if (x >= 440 && x <= 540)
					w->config.level = 1;
				if (x >= 550 && x <= 650)
					w->config.level = 2;
			}
			w->config.mx = x;
			w->config.my = y;
			mini_clear(w);
			main_menu(w);
			xpm = mlx_xpm_file_to_image (w->config.mlx_ptr, "./ressources/curs.xpm", &width, &height);
			mlx_put_image_to_window(w->config.mlx_ptr, w->config.win_ptr, xpm, x, y);
		}
	}
	return (0);
}

void 	menu_event(int key, t_game *w)
{
	if (key == 124)
	{
		if (w->config.level < 2)
			w->config.level++;
		else
			w->config.level = 0;
		mini_clear(w);
		main_menu(w);
	}
	if (key == 123)
	{
		if (w->config.level > 0)
			w->config.level--;
		else
			w->config.level = 2;
		mini_clear(w);
		main_menu(w);
	}
}

void	vec_normalise(double *v)
{
	double	x;
	double	y;
	double	mod;

	x = v[0] * v[0];
	y = v[1] * v[1];
	mod = sqrt(x + y);
	v[0] /= mod;
	v[1] /= mod;
}

void translation(t_game *w, double factor, int key)
{
	double *tmp;
	double tanslation[2];

	tmp = w->gameplay.direction;
	vec_normalise(tmp);
	tanslation[0] = w->gameplay.position[0];
	tanslation[1] = w->gameplay.position[1];
	if (key == 126)
	{
			tanslation[0] += (factor * tmp[0]);
			tanslation[1] += (factor * tmp[1]);
	}
	if (key == 125)
	{

			tanslation[0] -= (factor * tmp[0]);
			tanslation[1] -= (factor * tmp[1]);
	}
	if (tanslation[0] >= 1 && tanslation[1] >= 1 && tanslation[0] <= 22 && tanslation[1] <= 22)
	{
		w->gameplay.position[0] = tanslation[0];
		w->gameplay.position[1] = tanslation[1];
	}
}

void	rot_x(double *ray, float angle)
{
	double	tmp;

	tmp = ray[0];
	ray[0] = ray[0] * cos(angle) - ray[1] * sin(angle);
	ray[1] = tmp * sin(angle) + ray[1] * cos(angle);
}

void set_params(t_game *w)
{
	int fd;
	if (w->config.level == 0)
		fd = open("worlds/world0.map", O_RDONLY);
	if (w->config.level == 1)
		fd = open("worlds/world0.map", O_RDONLY);
	if (w->config.level == 2)
		fd = open("worlds/world0.map", O_RDONLY);
	w->gameplay.fd = fd;
	render_handler(w);
}

void gameplay_event(int key, t_game *w)
{
	if (key == 123)
	{
		rot_x(w->gameplay.direction, ROT_ANGLE);
		rot_x(w->gameplay.plane, ROT_ANGLE);
	}
	if (key == 124)
	{
		rot_x(w->gameplay.direction, (double)ROT_ANGLE * -1);
		rot_x(w->gameplay.plane, (double)ROT_ANGLE * -1);
	}
	if (key == 126)
		translation(w, 0.2, key);
	if (key == 125)
		translation(w, 0.2, key);
	render_scene(w);
}

int		key_press(int key, t_game *w)
{
	// printf("key : %d\n", key);
	if (key == 124 || key == 123 || key == 125 || key == 126)
	{
		if (!F_GET(w->flags, GAMEPLAY))
			menu_event(key, w);
		else
			gameplay_event(key, w);
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

	if (w->config.level == 0)
		start = 329;
	else if (w->config.level == 1)
		start = 329 + 100 + 10;
	else if (w->config.level == 2)
		start = 329 + (100 + 10) * 2;
	y = -1;
	while (++y < 102)
	{
		x = 0;
		while (x < 102)
		{
			if (((x == 0 && y != 0) || (y == 0 && x != 0)) && x < 80 && y < 80)
				mlx_pixel_put(w->config.mlx_ptr, w->config.win_ptr, x + start, y + 799, 0xFFFFFF);
			x++;
		}
	}
}

void 		main_menu(t_game *w)
{
	int		width;
	int		height;
	void	*xpm;

	w->config.img_ptr = mlx_new_image(w->config.mlx_ptr, WIDTH, HEIGHT);
	xpm = mlx_xpm_file_to_image (w->config.mlx_ptr, "./ressources/background.xpm", &width, &height);
	mlx_put_image_to_window(w->config.mlx_ptr, w->config.win_ptr,	xpm, 0, 0);
	border(w);
	xpm = mlx_xpm_file_to_image (w->config.mlx_ptr, "./ressources/l1.xpm", &width, &height);
	mlx_put_image_to_window(w->config.mlx_ptr, w->config.win_ptr, xpm, 330, 800);
	xpm = mlx_xpm_file_to_image (w->config.mlx_ptr, "./ressources/l2.xpm", &width, &height);
	mlx_put_image_to_window(w->config.mlx_ptr, w->config.win_ptr, xpm, width + 330 + 10, 800);
	xpm = mlx_xpm_file_to_image (w->config.mlx_ptr, "./ressources/l3.xpm", &width, &height);
	mlx_put_image_to_window(w->config.mlx_ptr, w->config.win_ptr, xpm, (width * 2) + 330 + 20, 800);
	xpm = mlx_xpm_file_to_image (w->config.mlx_ptr, "./ressources/curs.xpm", &width, &height);
	mlx_put_image_to_window(w->config.mlx_ptr, w->config.win_ptr, xpm, w->config.mx, w->config.my);
}

static void	init_game(t_game *w)
{
	w->config.level = 0;
	w->config.mx = 0;
	w->config.my = 0;
	F_UNSET(w->flags, GAMEPLAY);
	w->config.mlx_ptr = mlx_init();
	w->config.win_ptr = mlx_new_window(w->config.mlx_ptr, WIDTH, HEIGHT, EXEC_NAME);
	//arrow hooks
	//esc hook
	//mouse hook
	//enter hook
	main_menu(w);
	mlx_hook(w->config.win_ptr, 17, 1, exit_cleanup, w);
	mlx_hook(w->config.win_ptr, 4, 1, mouse_press, w);
	mlx_hook(w->config.win_ptr, 2, 1, key_press, w);
	mlx_hook(w->config.win_ptr, 6, 1, mouse_move, w);
}

int			main(void)
{
	t_game	wolf3d;

	init_game(&wolf3d);
	//load_home(&wolf3d);

	// DEV
	//int fd = open("worlds/world0.map", O_RDONLY);
	//load_gameplay(fd, &wolf3d);
	//
	mlx_loop(wolf3d.config.mlx_ptr);
}
