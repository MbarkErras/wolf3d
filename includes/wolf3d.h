/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merras <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 19:19:34 by merras            #+#    #+#             */
/*   Updated: 2019/11/01 21:56:31 by merras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include "centropy.h"
# include "mlx.h"

# define EXEC_NAME "wolf3d"
# define WIDTH 500
# define HEIGHT 500

# define WORLD_BUFFER 10

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
	char		**world;
	double		position[2];
	double		direction[2];
	char		flags;
}				t_game;

# define RANDON 0
# define GAMEPLAY 1

int				exit_cleanup(void *w);
char			**read_world(int fd);

# define F_GET(x, f) (x & (1 << f))
# define F_BGET(x, f) (x & f)
# define F_SET(x, f) (x |= (1 << f))
# define F_BSET(x, f) (x |= f)
# define F_UNSET(x, f) (x &= ~(1 << f))
# define F_BUNSET(x, f) (x &= ~f)

#endif
