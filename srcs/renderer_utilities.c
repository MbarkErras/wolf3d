/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer_utilities.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merras <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 21:45:45 by merras            #+#    #+#             */
/*   Updated: 2019/11/02 01:58:52 by merras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

char	**read_world(int fd)
{
	char	buffer[4096];
	char	*world_raw;

	world_raw = NULL;
	while (read(fd, buffer, 4096))
		world_raw = ft_strjoin_free(world_raw, buffer, 1);
	return (ft_strsplit(world_raw, '\n'));
}
