/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 14:29:01 by graja             #+#    #+#             */
/*   Updated: 2021/06/19 16:58:59 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*ptr;

	i = 0;
	ptr = (char *)s;
	while (i < n)
	{
		ptr[i] = 0;
		i++;
	}
}

char	*ft_strchr(const char *s, int c)
{
	char	*bck;

	bck = (char *)s;
	while (*bck)
	{
		if (*bck == (char)c)
			return (bck);
		bck++;
	}
	if (!(*bck) && !c)
		return (bck);
	else
		return (NULL);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	ptr = malloc(size * nmemb);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, nmemb);
	return (ptr);
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	l;
	size_t	i;
	size_t	len;

	l = 0;
	i = 0;
	len = ft_strlen(dst, 0);
	if (dstsize == 0 || (len > dstsize - 1))
		return (ft_strlen(src, 0) + dstsize);
	l = len;
	while (((len + i) < (dstsize - 1)) && (src[i]))
	{
		dst[l] = src[i];
		l++;
		i++;
	}
	dst[l] = '\0';
	if (len >= dstsize)
		len = dstsize;
	return (len + ft_strlen(src, 0));
}

size_t	ft_strlen(const char *s, int flag)
{
	size_t	i;

	i = 0;
	if (flag <= 0)
	{
		while (s[i] != '\0')
			i++;
	}
	else
		while (s[i] != '\0' && s[i] != '\n')
			i++;
	return (i);
}
