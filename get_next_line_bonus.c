/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malfarah <malfarah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 12:46:39 by malfarah          #+#    #+#             */
/*   Updated: 2025/09/22 12:16:59 by malfarah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
	static char	*rem[1023];
	char		*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	rem[fd] = ft_reader(rem[fd], buffer, fd);
	free(buffer);
	if (!rem[fd] || *rem[fd] == '\0')
	{
		free(rem[fd]);
		rem[fd] = NULL;
		return (NULL);
	}
	line = get_line(rem[fd]);
	rem[fd] = upd_rem(rem[fd]);
	return (line);
}

// int main(void)
// {
//     int     fd1;
//     int     fd2;
//     int     fd3;
//     char    *line;

//     fd1 = open("file1.txt", O_RDONLY);
//     fd2 = open("file2.txt", O_RDONLY);
//     fd3 = open("file3.txt", O_RDONLY);

//     if (fd1 < 0 || fd2 < 0 || fd3 < 0)
//     {
//         perror("Error opening files");
//         return (1);
//     }

//     printf("=== Reading from file1 and file2 alternately ===\n");
//     line = get_next_line(fd1);
//     printf("file1: %s", line);
//     free(line);

//     line = get_next_line(fd2);
//     printf("file2: %s", line);
//     free(line);

//     line = get_next_line(fd1);
//     printf("file1: %s", line);
//     free(line);

//     line = get_next_line(fd2);
//     printf("file2: %s", line);
//     free(line);

//     printf("\n=== Reading full file3 ===\n");
//     while ((line = get_next_line(fd3)) != NULL)
//     {
//         printf("file3: %s", line);
//         free(line);
//     }

//     close(fd1);
//     close(fd2);
//     close(fd3);

//     return (0);
// }