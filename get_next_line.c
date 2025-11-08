/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malfarah <malfarah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 16:53:15 by malfarah          #+#    #+#             */
/*   Updated: 2025/09/22 12:18:24 by malfarah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*get_line(char *rem)
{
	int		i;
	char	*line;

	i = 0;
	if (!*rem || !rem)
		return (NULL);
	while (rem[i] && rem[i] != '\n')
		i++;
	if (rem[i] == '\n')
		i++;
	line = malloc(i + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (rem[i] && rem[i] != '\n')
	{
		line[i] = rem[i];
		i++;
	}
	if (rem[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

static char	*upd_rem(char *rem)
{
	int		i;
	int		j;
	char	*new_rem;

	i = 0;
	j = 0;
	while (rem[i] && rem[i] != '\n')
		i++;
	if (!rem[i])
	{
		free(rem);
		return (NULL);
	}
	i++;
	new_rem = malloc(ft_strlen(rem + i) + 1);
	if (!new_rem)
		return (NULL);
	while (rem[i])
		new_rem[j++] = rem[i++];
	new_rem[j] = '\0';
	free(rem);
	return (new_rem);
}

static char	*ft_reader(char *rem, char *buffer, int fd)
{
	char	*tmp;
	int		b;

	b = 1;
	if (!rem)
		rem = ft_strdup("");
	if (!rem)
		return (NULL);
	while (!ft_strchr(rem, '\n') && b > 0)
	{
		b = read(fd, buffer, BUFFER_SIZE);
		if (b < 0)
		{
			free(rem);
			rem = NULL;
			return (NULL);
		}
		buffer[b] = '\0';
		tmp = rem;
		rem = ft_strjoin(rem, buffer);
		free(tmp);
	}
	return (rem);
}

char	*get_next_line(int fd)
{
	static char	*rem;
	char		*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	rem = ft_reader(rem, buffer, fd);
	free(buffer);
	if (!rem || *rem == '\0')
	{
		free(rem);
		rem = NULL;
		return (NULL);
	}
	line = get_line(rem);
	rem = upd_rem(rem);
	return (line);
}

// int	main(void)
// {
// 	int fd = open("mutaz.txt", O_RDONLY);
// 	char *line;

// 	if (fd < 0)
// 		return (1);
// 	while ((line = get_next_line(fd)))
// 	{
// 		printf("%s", line);
// 		free(line);
// 	}
// 	close(fd);
// 	return (0);
// }
