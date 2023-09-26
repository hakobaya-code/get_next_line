/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobaya <hakobaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 10:45:35 by hakobaya          #+#    #+#             */
/*   Updated: 2023/09/26 18:13:08 by hakobaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s1)
{
	size_t	i;

	i = 0;
	while (*s1 != '\0')
	{
		s1++;
		i++;
	}
	return (i);
}

char	*ft_strchr(const char *s, char c)
{
	char	*str;

	str = (char *)s;
	if (s == NULL)
		return (NULL);
	while (*str != '\0')
	{
		if (*str == c)
			return (str);
		str++;
	}
	return (NULL);
}

char	*ft_strdup(const char *s1)
{
	char	*dst;
	char	*save;

	if (s1 == NULL)
		return (NULL);
	dst = (char *)malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (dst == NULL)
		return (NULL);
	save = dst;
	while (*s1)
		*dst++ = *s1++;
	*dst = '\0';
	return (save);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dst;
	char	*save;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	dst = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (dst == NULL)
		return (NULL);
	save = dst;
	while (*s1)
		*dst++ = *s1++;
	while (*s2)
		*dst++ = *s2++;
	*dst = '\0';
	return (save);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*dest;
	unsigned char	*source;

	if (dst == NULL && src == NULL)
		return (NULL);
	i = 0;
	dest = (unsigned char *)dst;
	source = (unsigned char *)src;
	while (i < n)
	{
		dest[i] = source[i];
		i++;
	}
	return (dst);
}
//#include <stdio.h>

//void	test(const char *s1, const char *s2)
//{
//	char	*ret;

//	printf("\ns1[%s] s2[%s]\n", s1, s2);
//	ret = ft_strjoin(s1, s2);
//	printf("[%s]\n", ret);
//}

//void	test2(const char *s1)
//{
//	char	*ret;

//	printf("\ns1[%s]\n", s1);
//	ret = ft_strdup(s1);
//	printf("[%s]\n", ret);
//}

//int	main(void)
//{
//	test("ab", "12345");
//	test2("");
//	//test("ab", "12345");
//	//test("ab", "12345");
//}