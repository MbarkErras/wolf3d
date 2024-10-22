/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merras <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 19:19:34 by merras            #+#    #+#             */
/*   Updated: 2019/11/17 04:49:09 by merras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

// D E V
# include <stdio.h>
// ////

# include <math.h>
# include "centropy.h"
# include "mlx.h"

# define EXEC_NAME "wolf3d"
# define WIDTH 1000
# define HEIGHT 1000
# define BUF_SIZE 100
# define X 0
# define Y 1

# define PI 3.14159265359
# define DEG_TO_RAD(x) (x / 180 * PI)

/*
** GAMEPLAY MACROS
*/


// ERROR 1 : chamge the ray direction x -1 (1, 0)
// Fhad l7ala lmochkil li kain anaho fach kan9elbo ray direction kait9elbo adwaar dyal rotation f button hadi mochkil dyalha hwa map f rendering katban
// me9louba matalan f had push li pushiit dayro kaichoof f axe dyal Y -1 0 f direction donc f dekchi li kanchofo khass ikoon 3la limen 7it o enface 7it
// o 3la lisser makain walo f rendering kaikon l3ekss f lisser 7it o enface 7it o limen makain waloo, 3la mafhemt ymkne dekchi kaitrendera me3kouss

// hada machi error ms khassi itgad f parsing tani hwa hna andiro blassa par defaut mniin aybda player donc khass nb9aaw nchofo map wach dook le position
// li fiha player mafiha 7ta mur o map massgherach mndiir maps
// O gali rafael bli texture les murs darori f mandatory dayrin photo f mandatory fihom murs b textures

# define FOV 90
# define INITIAL_POSITION_X 3
# define INITIAL_POSITION_Y 3
# define INITIAL_DIRECTION_X -1
# define INITIAL_DIRECTION_Y -1
# define INITIAL_PLANE_X 0
# define INITIAL_PLANE_Y tan(FOV / 2)
# define ROT_ANGLE 0.08
# define NUM_RAYS 320
# define FOV_ANGLE DEG_TO_RAD(FOV)

/*
** TEXTURES MACROS
** any digit from 0 to 9 represent number of stacked blocks
*/

# define TREE '*'
# define WATER 'w'
# define LAVA 'l'

typedef	struct	s_gameplay
{
	char		**world;
	double		position[2];
	double		direction[2];
	double		plane[2];
	int			height;
	int			fd;
}				t_gameplay;

typedef struct	s_config
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img_ptr;
	int			*data;
	int 		mx;
	int 		my;
	int 		level;
	int				endian;
	int				s_l;
	int				bpp;
}				t_config;

typedef struct	s_raycaster
{
	double		sidedist[2];
	double		deltadist[2];
	double		step[2];
	double		ray[2];
	int			map[2];
	int			side;
}				t_raycaster;

typedef struct	s_game
{
	t_config		config;
	t_gameplay		gameplay;
	t_raycaster		raycaster;
	char					flags;
}				t_game;

# define GAMEPLAY 1
# define FIRST_TIME 2

int				exit_cleanup(void *w);
int				key_press(int key, t_game *w);
void 			main_menu(t_game *w);
void 			set_params(t_game *w);
char			**read_world(int fd);

void			render_handler(t_game *w);
void			render_scene(t_game *w);

# define F_GET(x, f) (x & (1 << f))
# define F_BGET(x, f) (x & f)
# define F_SET(x, f) (x |= (1 << f))
# define F_BSET(x, f) (x |= f)
# define F_UNSET(x, f) (x &= ~(1 << f))
# define F_BUNSET(x, f) (x &= ~f)

#endif
