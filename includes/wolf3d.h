/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merras <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 19:19:34 by merras            #+#    #+#             */
/*   Updated: 2019/11/03 20:10:51 by merras           ###   ########.fr       */
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
# define WIDTH 500
# define HEIGHT 500
# define X 0
# define Y 1


# define BLOCK_WIDTH 20


# define PI 3.14159265359
# define DEG_TO_RAD(x) (x / 180 * PI)

/*
** GAMEPLAY MACROS
*/

# define FOV 90
# define INITIAL_POSITION_X 0
# define INITIAL_POSITION_Y 0
# define INITIAL_DIRECTION_X 0
# define INITIAL_DIRECTION_Y 0
# define INITIAL_PLANE_X 0
# define INITIAL_PLANE_Y tan(FOV / 2)


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
	int			height;
	int			fd;
}				t_gameplay;

typedef struct	s_config
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img_ptr;
	int			*data;
	int 		level;
	int				endian;
	int				s_l;
	int				bpp;
}				t_config;

typedef struct	s_raycaster
{
	int			a;
	
}				t_raycaster;

typedef struct	s_game
{
	t_config		config;
	t_gameplay		gameplay;
	t_raycaster		raycaster;
}				t_game;

# define GAMEPLAY 1
# define FIRST_TIME 2

int				exit_cleanup(void *w);
int				key_press(int key, t_game *w);
void 			main_menu(t_game *w);
char			**read_world(int fd);

void			render_handler(t_game *w);

# define F_GET(x, f) (x & (1 << f))
# define F_BGET(x, f) (x & f)
# define F_SET(x, f) (x |= (1 << f))
# define F_BSET(x, f) (x |= f)
# define F_UNSET(x, f) (x &= ~(1 << f))
# define F_BUNSET(x, f) (x &= ~f)

#endif
