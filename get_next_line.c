/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnass-pe <hnass-pe@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 19:32:26 by hnass-pe          #+#    #+#             */
/*   Updated: 2021/10/21 07:53:51 by hnass-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
*	This function checks if the string in the buffer contains a line.
*	A line is defined by the '\n' character.
*/

int	is_line(char	*buffer)
{
	while (*buffer)
	{
		if (*(buffer++) == '\n')
			return (1);
	}
	return (0);
}

/*	
*	This function updates the static_buffer with the buffer.
*/

void	upd_buffer(char	**static_buffer, char	**buffer)
{
	char	*temp;

	temp = *static_buffer;
	*static_buffer = ft_strjoin(temp, *buffer);
	free(temp);
}

/*
*	This function takes the line that contains in static_buffer, and checks
*	if it has more content after the line, if it does, the function updates the
*	static_buffer with that content.
*	A line is defined by the '\n' character.
*/

char	*get_line(char	**static_buffer, char	**line)
{
	size_t	line_len;
	char	*new_buffer;

	line_len = 0;
	new_buffer = NULL;
	while ((*static_buffer)[line_len] != '\n' \
			&& (*static_buffer)[line_len] != '\0')
		++line_len;
	if ((*static_buffer)[line_len] == '\n')
	{
		*line = ft_substr(*static_buffer, 0, (line_len + 1));
		new_buffer = ft_strdup(&(*static_buffer)[line_len + 1]); //o & pega o endereço da variavel
	}
	else
		*line = ft_strdup(*static_buffer);
	free(*static_buffer);
	*static_buffer = new_buffer;
	if (**line == '\0')
	{
		free(*line);
		*line = NULL;
	}
	return (*line);
}

/*
*	This function reads a file descriptor with read(2) and checks if the read
*	buffer has a line, if it doesn't have a line, the static_buffer is updated
*	with the contents of the buffer.
*/

char	*read_file(int	fd, char	**buffer)
{
	static char	*static_buffer = NULL;
	char		*line;
	ssize_t		n; //ssize_t = signed size_t / size_t = unsigned

	n = 1;
	if (!static_buffer)
		static_buffer = ft_strdup("");
	while (!is_line(static_buffer) && n)
	{
		n = read(fd, *buffer, BUFFER_SIZE);
		(*buffer)[n] = '\0';
		upd_buffer(&static_buffer, buffer);
	}
	free(*buffer);
	*buffer = NULL;
	return (get_line(&static_buffer, &line));
}

/*
*	Write a function which returns a line read from a
*	file descriptor.
*/

char	*get_next_line(int	fd)
{
	char		*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(*buffer));
	if (!buffer)
		return (NULL);
	if (read(fd, buffer, 0) < 0)
	{
		free(buffer);
		return (NULL);
	}
	return (read_file(fd, &buffer));
}
