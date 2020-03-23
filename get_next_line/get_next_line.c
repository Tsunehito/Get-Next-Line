/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daelee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 17:57:29 by daelee            #+#    #+#             */
/*   Updated: 2020/03/23 17:37:29 by daelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int                 split_line(char **backup, char **line, char *cut_addr)
{
	char	        *temp;
	size_t	        len;

	if ((line = malloc(cut_addr - *backup + 1)) == 0)
		return (-1);
	ft_strlcpy(*line, *backup, cut_addr - *backup + 1);
	len = ft_strlen(cut_addr + 1);
	if (len == 0)
	{
		free(*backup);
		*backup = 0;
		return (1);
	}
	if ((temp = malloc(len + 1)) == 0)
		return (-1);
	ft_strlcpy(temp, cut_addr + 1, len + 1);
	free(*backup);
	*backup = temp;
	return (1);
}

// int                 get_next_line(int fd, char **line)
// {
//     char            *buf;
//     static t_array  *backup;
//     char            *cut_addr;
//     int             eof;
//     int             ret;

// 	if (fd < 0 || line == 0 || BUFFER_SIZE <= 0)
// 		return (-1);
//     if (!(buf = (char *)malloc(sizeof(char)*BUFFER_SIZE + 1)))
//         return (0);
//     backup = ft_create_array();
//     while (cut_addr = ft_strchr(backup->str, '\n') == 0)
//     {
//         eof = read(fd, buf, BUFFER_SIZE);
//         ft_append_str(backup, buf);
//     }
//     ret = read_line(backup->str, *line, cut_addr);
//     if (eof == 0)
//         return (0);
//     return (ret);
// }

int					append_backup(char *buf, char **backup, int read_size)
{
	char			*temp;
	int 			temp_len;

	if (read_size <= 0)
		return (-1);
	if (*backup == 0)
	{
		if ((*backup = (char *)malloc(read_size + 1)) == 0)
			return (-1);
		ft_strlcpy(*backup, buf, read_size + 1);
		return (1);
	}
	temp_len = ft_strlen(*backup) + read_size + 1;
	if ((temp = (char *)malloc(temp_len)) == 0)
		return (-1);
	ft_strlcpy(temp, *backup, temp_len);
	ft_strlcat(temp, buf, temp_len);
	free(*backup);
	*backup = temp;
	free(temp);
	return (1);
}

int					get_next_line(int fd, char **line)
{
	static t_list 	list;
	char			*cut;
	int				read_size;

	if ((fd < 0) || (line == 0) || (BUFFER_SIZE <= 0))
		return (-1);
	while ((cut = ft_strchr(list.backup[fd], '\n')) == 0)
	{
		read_size = read(fd, list.buf, BUFFER_SIZE);
		info.buf[read_size] = 0; //ft_strlen을 사용하기 위해서
		if (append_backup(&list.backup[fd], list.buf, &read_size) == -1)
			return (-1);
	}
	return (split_line(&info.backup[fd], line, cut));
}

int main(void)
{
	char *line = 0;
	int ret;
	int fd;	
	
	fd = open("testfile", O_RDONLY);
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		printf("line is...%s\n", line);
		free(line);
	}
	printf("lein is...%s\n", line);
	free(line);
	return (0);
}