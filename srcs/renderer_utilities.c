/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer_utilities.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merras <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 21:45:45 by merras            #+#    #+#             */
/*   Updated: 2019/11/03 04:03:55 by merras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

// char	**read_world(int fd)
// {
// 	char	buffer[4096];
// 	char	*world_raw;
//
// 	world_raw = NULL;
// 	while (read(fd, buffer, 4095))
// 		world_raw = ft_strjoin_free(world_raw, buffer, 1);
// 		printf("the original string\n");
// 	printf("%s\n", world_raw );
// 	printf("end of original string\n");
// 	return (ft_strsplit(world_raw, '\n'));
// }


char	**read_world(int fd)
{
	int		rd;
	char	buf[BUF_SIZE + 1];
	char	*str_file;
	char	*tmp;

	// if (fd < 0 || read(fd, buf, 0) < 0)
	// 	return (NULL);
	str_file = ft_strnew(0);
	while ((rd = read(fd, buf, BUF_SIZE)))
	{
		tmp = str_file;
		buf[rd] = '\0';
		str_file = ft_strjoin(str_file, buf);
		free(tmp);
	}
	return (ft_strsplit(str_file, '\n'));
}
