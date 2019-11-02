/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merras <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 21:34:49 by merras            #+#    #+#             */
/*   Updated: 2019/11/02 01:58:44 by merras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

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

void	rot_x(double *ray, float angle)
{
	double	tmp;

	tmp = ray[0];
	ray[0] = ray[0] * cos(angle) - ray[1] * sin(angle);
	ray[1] = tmp * sin(angle) + ray[1] * cos(angle);
}

void	describe_line(double *p, double *ray, double *line)
{
	if (ray[0] < 0.000001)
		ray[0] = 0.01;

	line[0] = ray[1] / ray[0];
	line[1] = p[1] - p[0] * line[0];
}

void	load_gameplay(int fd, t_game *w)
{
	double	ray[2];
	double	line[2];

	if (!(w->world = read_world(fd)))
		exit_cleanup(w);
	w->position[0] = 1 * BLOCK_WIDTH;
	w->position[1] = 1 * BLOCK_WIDTH;
	w->direction[0] = 1;
	w->direction[1] = 1;

	ray[0] = w->direction[0];
	ray[1] = w->direction[1];

	vec_normalise(ray);
	rot_x(ray, DEG_TO_RAD(FOV / 2));

	double x;
	double y;

   	x = w->position[0] + (20 - ((int)w->position[0] % 20));
	describe_line(w->position, ray, line);
	printf("position: %f %f\n", w->position[0], w->position[1]);
	printf("direction: %f %f\n", w->direction[0], w->direction[1]);
	printf("ray: %f %f\n", ray[0], ray[1]);
	printf("line: %f %f\n", line[0], line[1]);
	printf("first block to check: %f\n", x);
	while (x < WIDTH)
	{
		y = line[0] * x + line[1] + 0.01;
		printf(">> %f %f\n", x, y);
		printf (">>>> x = %d  y = %d", (int)x / 20, (int)y / 20); 
		if (w->world[(int)y / 20][(int)x / 20] == '1')
			printf("lah\n");
		else
			printf("chitan\n");
		x += BLOCK_WIDTH;
	}
}
