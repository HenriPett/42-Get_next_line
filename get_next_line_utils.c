/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnass-pe <hnass-pe@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 18:50:54 by hnass-pe          #+#    #+#             */
/*   Updated: 2021/10/20 21:12:36 by hnass-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
*	The strlen() function computes the length of the string str.
*/

size_t	ft_strlen(const char *s)
{
	int	n;

	n = 0;
	if (!s)
		return (0);
	while (s[n])
		n++;
	return ((size_t) n);
}

/*
*	Allocates (with malloc(3)) and returns a new string, which
*	is the result of the concatenation of ’str1’ and ’str2’.
*/

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		i;
	int		j;

	str = malloc (sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (str == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	return (str);
}

/*
*	The strlcpy() copies up to size - 1 characters from the string src
*	to dst, NUL-terminating the result if dest_size is not 0.
*/

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t		s_len;	
	char		*d;
	const char	*s;

	d = dst;
	s = src;
	s_len = ft_strlen(s);
	if (!d || !s)
		return (0);
	if (!size)
		return (s_len);
	while (size - 1 && *s)
	{
		*d = *s;
		d++;
		s++;
		size--;
	}
	*d = '\0';
	return (s_len);
}

/*
*	The strdup() function allocates sufficient memory for a copy of the
*	string str, does the copy, and returns a pointer to it.
*/

char	*ft_strdup(const char *s)
{
	int		i;
	char	*str;

	i = 0;
	str = (char *)malloc (sizeof(char) * (ft_strlen(s) + 1));
	if (str == NULL)
		return (NULL);
	while (s[i])
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

/*
*	Allocates (with malloc(3)) and returns a substring from the string ’s’.
*	The substring begins at index ’start’ and is of maximum size ’len’.
*/

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*p;
	size_t	i;

	i = ft_strlen(s);
	if (start < i)
	{
		if (i > len)
			p = (char *) malloc(sizeof(char) * len + 1);
		else
			p = (char *) malloc(sizeof(char) * i + 1);
		if (p == NULL)
			return (NULL);
		ft_strlcpy(p, &s[start], len + 1);
	}
	else
	{
		p = (char *) malloc(sizeof(char) * 1);
		if (p == NULL)
			return (NULL);
		ft_strlcpy(p, "", 1);
	}
	return (p);
}
