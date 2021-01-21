/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlcat.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcappend <rcappend@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/29 15:44:57 by rcappend      #+#    #+#                 */
/*   Updated: 2021/01/19 10:03:54 by rcappend      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

size_t			ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	src_len;
	size_t	dst_len;

	src_len = ft_strlen(src);
	dst_len = ft_strnlen(dst, dstsize);
	if (dst_len == dstsize)
		return (dstsize + src_len);
	if (src_len < dstsize - dst_len)
		ft_memcpy(dst + dst_len, (char *)src, src_len + 1);
	else
	{
		ft_memcpy(dst + dst_len, (char *)src, dstsize - dst_len - 1);
		dst[dstsize - 1] = '\0';
	}
	return (src_len + dst_len);
}
