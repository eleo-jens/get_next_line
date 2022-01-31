/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estultje <estultje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 12:10:13 by estultje          #+#    #+#             */
/*   Updated: 2022/01/31 15:09:22 by nemish           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_cut(char *buffer)
{
	char		*cut;
	int			i;
	int			j;

	i = 0;
	j = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	cut = ft_calloc((ft_strlen(buffer) - i + 1), 1);
	if (!cut)
	{
		free(buffer);
		return (NULL);
	}
	i++;
	while (buffer[i])
		cut[j++] = buffer[i++];
	free(buffer);
	return (cut);
}

char	*get_line(char *buffer)
{
	char	*line;
	int		i;

	i = 0;
	if (!buffer[i])
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	line = ft_calloc((i + 2), 1);
	if (!line)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
		line[i] = '\n';
	return (line);
}

char	*ft_join_free(char *buffer, char *newstr)
{
	char	*temp;

	temp = ft_strjoin(buffer, newstr);
	free(buffer);
	return (temp);
}

char	*get_buffer(int fd, char *buffer)
{
	char	*new;
	int		count;

	if (!buffer)
		buffer = ft_calloc(1, 1);
	new = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	count = 1;
	while (count > 0 && !(ft_strchr(new, '\n')))
	{
		count = read(fd, new, BUFFER_SIZE);
		if (count == -1)
		{
			free(new);
			return (NULL);
		}
		new[count] = '\0';
		buffer = ft_join_free(buffer, new);
	}
	free(new);
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (BUFFER_SIZE < 1 || fd < 0 || (read(fd, NULL, 0) < 0))
		return (0);
	buffer = get_buffer(fd, buffer);
	if (!buffer)
		return (NULL);
	line = get_line(buffer);
	buffer = get_cut(buffer);
	return (line);
}
