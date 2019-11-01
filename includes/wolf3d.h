/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merras <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 19:19:34 by merras            #+#    #+#             */
/*   Updated: 2019/11/01 20:13:01 by merras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF#D_H
# define WOLF3D_H

# include "centropy.h"
# include "mlx.h"

# define EXEC_NAME "wolf3d"
# define WIDTH 500
# define HEIGHT 500

typedef struct	s_game
{
	void		*mlx_ptr;
	void		*win_ptr;
	char		flags;
}				t_game;

typedef struct	s_walls
{
	double x[2];
	double y[2];
	double h;
}				t_walls;

# define GAMEPLAY 0

# define F_GET(x, f) (x & (1 << f))
# define F_BGET(x, f) (x & f)
# define F_SET(x, f) (x |= (1 << f))
# define F_BSET(x, f) (x |= f)
# define F_UNSET(x, f) (x &= ~(1 << f))
# define F_BUNSET(x, f) (x &= ~f)

#endif
