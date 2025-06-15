/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzeybek <vzeybek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 11:30:14 by vzeybek           #+#    #+#             */
/*   Updated: 2025/06/15 19:02:19 by vzeybek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>
#include <fcntl.h>

int	find_next_line(char *buffer)
{
	int	i;

	i = 0;
	if (!buffer)
		return (-1);
	while (buffer[i])
	{
		if (buffer[i] == '\n')
			return (i + 1);
		i++;
	}
	return (-1);
}

int	read_and_join(int fd, char **buffer)
{
	int		read_byte;
	char	*old_buffer;
	char	*temp;

	temp = malloc(BUFFER_SIZE + 1);
	if (!temp)
		return (0);
	read_byte = read(fd, temp, BUFFER_SIZE);
	if (read_byte <= 0)
	{
		free(temp);
		return (0);
	}
	temp[read_byte] = '\0';
	old_buffer = *buffer;
	*buffer = ft_strjoin(old_buffer, temp);
	free(old_buffer);
	free(temp);
	if (!(*buffer))
		return (0);
	return (1);
}

char	*read_until_next_line(int fd, char *buffer)
{
	int		i;

	i = find_next_line(buffer);
	while (i <= 0)
	{
		if (!read_and_join(fd, &buffer))
			break ;
		if (!buffer || *buffer == '\0')
			return (NULL);
		i = find_next_line(buffer);
	}
	return (buffer);
}

char	*substr_and_update(char **buffer)
{
	char	*line;
	char	*new_buffer;
	int		i;

	if (*buffer[0] == '\0')
	{
		free(*buffer);
		*buffer = NULL;
		return (NULL);
	}
	i = find_next_line(*buffer);
	if (i <= 0)
		i = ft_strlen(*buffer);
	line = ft_substr(*buffer, 0, i);
	new_buffer = ft_substr(*buffer, i, ft_strlen(*buffer) - i);
	free(*buffer);
	*buffer = new_buffer;
	if (*buffer && *buffer[0] == '\0')
	{
		free(*buffer);
		*buffer = NULL;
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	int			i;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE > 2147483647)
		return (NULL);
	if (!buffer)
	{
		buffer = malloc(BUFFER_SIZE + 1);
		if (!buffer)
		{
			return (NULL);
		}
		buffer[0] = '\0';
	}
	i = find_next_line(buffer);
	if (i <= 0)
	{
		buffer = read_until_next_line(fd, buffer);
		if (buffer == NULL)
		{
			return (NULL);
		}
	}
	return (substr_and_update(&buffer));
}

#include <stdio.h>

int main()
{
	int fd = open("text.txt", O_CREAT | O_RDWR, 0644);
	//int fd2 = open("text.txt2", O_CREAT | O_RDWR, 0644);
	//int fd3= open("text.txt2", O_CREAT | O_RDWR, 0644);
	char *a= get_next_line(fd);
	char *b= get_next_line(fd);
	char *c= get_next_line(fd);
	char *d= get_next_line(fd);
	char *e= get_next_line(fd);
	char *f= get_next_line(fd);
	char *g= get_next_line(fd);
	char *h= get_next_line(fd);
	char *j= get_next_line(fd);

	printf("%s",a);
	printf("%s",b);	
	printf("%s",c);	
	printf("%s",d);
	printf("%s",e);
	printf("%s",f);
	printf("%s",g);
	printf("%s",h);
	printf("%s",j);
	
	free(a);
	free(b);
	free(c);
	free(d);
	free(e);
	free(f);
	printf("%p", h);

	close(fd);
}
