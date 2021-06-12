/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 08:48:09 by graja             #+#    #+#             */
/*   Updated: 2021/06/12 10:08:50 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static
int	ft_find_cr(char *ptr)
{
	int	i;

	i = 0;
	while (*ptr && (*ptr != '\n'))
	{
		ptr++;
		i++;
	}
	return (i);
}

static
int	ft_do_copy(char **line, char *ptr, int len)
{
	char	*hlp;

	if (!*line)
	{
		*line = ft_calloc(len + 1, sizeof(char));
		if (!*line)
			return (-1);
		ft_strlcat(*line, ptr, len + 1);
	}
	else
	{
		hlp = ft_calloc(len + 1, sizeof(char));
		if (!hlp)
			return (-1);
		ft_strlcat(hlp, *line, len + 1);
		ft_strlcat(hlp, ptr, len + 1);
		free(*line);
		*line = hlp;
	}
	return (1);
}

static
int	ft_handle_cr(char **line, char *ptr)
{
	int		len;
	int		i;

	len = ft_find_cr(ptr);
	if (!*line)
		i = ft_do_copy(line, ptr, len);
	else
		i = ft_do_copy(line, ptr, ft_strlen(*line) + len);
	if (i < 0)
		return (i);
	len++;
	i = 0;
	while (ptr[len + i])
	{
		ptr[i] = ptr[len + i];
		i++;
	}
	ft_bzero((ptr + i), len);
	return (1);
}

static
int	ft_copy_content(char **line, char *ptr)
{
	int	err;
	int	len;

	len = ft_strlen(ptr);
	if (!*line)
		err = ft_do_copy(line, ptr, len);
	else
		err = ft_do_copy(line, ptr, len + ft_strlen(*line));
	if (ptr && len > 0)
		ft_bzero(ptr, len);
	return (err);
}

int	get_next_line(int fd, char **line)
{
	int			err;
	static char	*buffer[MAX_FD];

	err = 1;
	if (fd < 0 || fd > MAX_FD || !line || BUFFER_SIZE < 1)
		return (-1);
	if (!buffer[fd])
		buffer[fd] = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer[fd])
		return (-1);
	if (*line)
		*line = NULL;
	if (!ft_strlen(buffer[fd]))
		err = read(fd, buffer[fd], BUFFER_SIZE);
	while (err > 0 && !(ft_strchr(buffer[fd], '\n')))
	{
		err = ft_copy_content(line, buffer[fd]);
		if (err > 0)
			err = read(fd, buffer[fd], BUFFER_SIZE);
	}
	if (err > 0)
		err = ft_handle_cr(line, buffer[fd]);
	if (!*line)
		*line = ft_calloc(1, 1);
	return (err);
}
