/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 08:48:09 by graja             #+#    #+#             */
/*   Updated: 2021/06/12 10:30:36 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/* This function returns the length of a string until the 
 * next '\0' or '\n'
*/

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

/* This function is doing the hard copy work, it allocates the
 * right amount of memory and breaks if it fails in doing so. 
 * On success it copies and frees the old memory which is not
 * needed anymore. Using strlcat on an empty string works
 * perfectly which is proven here
*/

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

/* this function handles the case a '\n' was found. This means not the whole
 * buffer can be copied, but only a part of it. The copied part will be removed
 * from buffer and we are ready for the next turn
*/

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

/* easy work, no '\n' found, so copy in whole and set buffer to 0 */

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
	if (err > 0)
		ft_bzero(ptr, len);
	return (err);
}

/* What was asked for. The only difference between this and the bonus part
 * is the fact that here, buffer is a pointer while in bonus, it is an array of 
 * pointers. Calloc is used to make sure that every string is NULL
 * terminated. As long as no '\n' is found it will add buffer to the string
 * which will be returned, finally adding the last part until the '\n' and
 * keeping the remains in the static variable.
 * If nothing at all was put in, it will just allocate 1 Byte which can be
 * freed by main.c
*/

int	get_next_line(int fd, char **line)
{
	int			err;
	static char	*buffer;

	err = 1;
	if (fd < 0 || fd > MAX_FD || !line || BUFFER_SIZE < 1)
		return (-1);
	if (!buffer)
		buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (-1);
	if (*line)
		*line = NULL;
	if (ft_strlen(buffer) == 0)
		err = read(fd, buffer, BUFFER_SIZE);
	while (err > 0 && !(ft_strchr(buffer, '\n')))
	{
		err = ft_copy_content(line, buffer);
		if (err > 0)
			err = read(fd, buffer, BUFFER_SIZE);
	}
	if (err > 0)
		err = ft_handle_cr(line, buffer);
	if (!*line)
		*line = ft_calloc(1, 1);
	return (err);
}
