/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhebert <zhebert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 19:42:40 by zhebert           #+#    #+#             */
/*   Updated: 2023/11/27 20:20:20 by zhebert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"	

static char	*read_stuff(int fd, char *buf, char *backup)
{
	int		read_bytes;
	char	*char_temp;

	read_bytes = 1;
	while (read_bytes != '\0')
	{
		read_bytes = read(fd, buf, BUFFER_SIZE);
		if (read_bytes == -1)
			return (0);
		else if (read_bytes == 0)
			break ;
		buf[read_bytes] = '\0';
		if (!backup)
			backup = ft_strdup("");
		char_temp = backup;
		backup = ft_strjoin(char_temp, buf);
		free(char_temp);
		char_temp = NULL;
		if (ft_strchr (buf, '\n'))
			break ;
	}
	return (backup);
}

static char	*extract(char *line)
{
	size_t	count;
	char	*backup;

	count = 0;
	while (line[count] != '\n' && line[count] != '\0')
		count++;
	if (line[count] == '\0' || line[1] == '\0')
		return (0);
	backup = ft_substr(line, count + 1, ft_strlen(line) - count);
	if (*backup == '\0')
	{
		free(backup);
		backup = NULL;
	}
	line[count + 1] = '\0';
	return (backup);
}

char	*get_next_line(int fd)
{
	char		*line;
	char		*buf;
	static char	*backup;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (0);
	line = read_stuff(fd, buf, backup);
	free(buf);
	buf = NULL;
	if (!line)
	{
		free(backup);
		backup = NULL;
		return (NULL);
	}
	backup = extract(line);
	return (line);
}

// int	main(void)
// {
// 	char	*line;
// 	int		fd;

// 	fd = open("simple.txt", O_RDONLY);
// 	line = get_next_line(fd);
// 	printf(">%s", line);
// 	line = get_next_line(fd);
// 	printf(">%s", line);
// 	line = get_next_line(fd);
// 	printf(">%s", line);
// 	line = get_next_line(fd);
// 	printf(">%s", line);
// 	line = get_next_line(fd);
// 	printf(">%s", line);
// 	line = get_next_line(fd);
// 	printf(">%s", line);
// 	line = get_next_line(fd);
// 	printf(">%s", line);
// 	line = get_next_line(fd);
// 	printf(">%s", line);
// 	line = get_next_line(fd);
// 	printf(">%s", line);
// 	line = get_next_line(fd);
// 	printf(">%s", line);
// 	line = get_next_line(fd);
// 	printf(">%s", line);
// 	line = get_next_line(fd);
// 	printf(">%s", line);
// 	return (0);
// }