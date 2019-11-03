/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merras <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 19:19:34 by merras            #+#    #+#             */
/*   Updated: 2019/11/03 18:44:00 by merras           ###   ########.fr       */
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
# define MAPWIDTH 24
# define MAPHEIGHT 24

# define BLOCK_WIDTH 20
# define FOV 90.0

# define PI 3.14159265359
# define DEG_TO_RAD(x) (x / 180 * PI)

/*
** TEXTURES MACROS
** any digit from 0 to 9 represent number of stacked blocks
*/

# define TREE '*'
# define WATER 'w'
# define LAVA 'l'

typedef struct	s_game
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img_ptr;
	void		*img_menu;
	int			*data;
	int				endian;
	int				s_l;
	int				bpp;




	char		**world;
	double		position[2];
	double		direction[2];
	int 		level;
	int			height;
	char		flags;
	int			fd;



}				t_game;

# define RANDOM 0
# define GAMEPLAY 1
# define FIRST_TIME 2

int				exit_cleanup(void *w);
int				key_press(int key, t_game *w);
void 			main_menu(t_game *w);
char			**read_world(int fd);

# define INITIAL_X 5.5
# define INITIAL_Y 5.5

void			load_gameplay(int fd, t_game *w);

# define F_GET(x, f) (x & (1 << f))
# define F_BGET(x, f) (x & f)
# define F_SET(x, f) (x |= (1 << f))
# define F_BSET(x, f) (x |= f)
# define F_UNSET(x, f) (x &= ~(1 << f))
# define F_BUNSET(x, f) (x &= ~f)

#endif
