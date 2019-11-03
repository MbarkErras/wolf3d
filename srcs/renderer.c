/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merras <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 01:40:46 by merras            #+#    #+#             */
/*   Updated: 2019/11/03 04:03:47 by merras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	verticalline(int x, int start, int end, char c, t_game *w)
{
	while (++start < end)
		mlx_pixel_put(w->mlx_ptr, w->win_ptr, x, start, c == '1' ? 0xff0000 : 0x00ff00);
		

}

void	load_gameplay(int fd, t_game *w)
{
	double position[2] = {22, 12};
	double direction[2] = {-1, 0};
	double plane[2] = {0, 0.66};

	if (!(w->world = read_world(fd)))
		exit_cleanup(w);

	for (int x = 0; x < WIDTH; x++)
	{
		double cameraX = 2 * x / (double)WIDTH - 1;
		double ray[2] = {direction[0] + cameraX * plane[0],
			direction[1] + cameraX * plane[1]};
		int	map[2] = {(int)position[0], (int)position[1]};
		double sidedist[2];
		double deltadist[2] = {fabs(1/ray[0]), fabs(1/ray[1])};
		double perpwalldist;
		double step[2];
		int hit = 1;
		int side;
		if (ray[0] < 0)
		{
			step[0] = -1;
			sidedist[0] = (position[0] - map[0])  * deltadist[0];
		}
		else
		{
			step[0] = 1;
			sidedist[0] = (position[0] - map[0] + 1.0)  * deltadist[0];
		}
		if (ray[1] < 0)
		{
			step[1] = -1;
			sidedist[1] = (position[1] - map[1])  * deltadist[1];
		}
		else
		{
			step[1] = 1;
			sidedist[1] = (position[1] - map[1] + 1.0)  * deltadist[1];
		}
		while (hit)
		{
			if (sidedist[0] < sidedist[1])
			{
				sidedist[0] += deltadist[0];
				map[0] += step[0];
				side = 0;
			}
			else
			{
				sidedist[1] += deltadist[1];
				map[1] += step[1];
				side = 1;
			}
			if (w->world[map[0]][map[1]] > '0')
				hit = 0;
		}
		if (side == 0) 
			perpwalldist = (map[0] - position[0] + (1 - step[0]) / 2) / ray[0];
		else
			perpwalldist = (map[1] - position[1] + (1 - step[1]) / 2) / ray[1];
		int lineheight = (int)(HEIGHT / perpwalldist);
		int drawstart = -1 * lineheight / 2 + HEIGHT / 2;
		if(drawstart < 0)drawstart = 0;
		int drawend = lineheight / 2 + HEIGHT / 2;
		if(drawend >= HEIGHT)drawend = HEIGHT - 1;
		verticalline(x, drawstart, drawend, w->world[map[0]][map[1]], w);
	}

}
