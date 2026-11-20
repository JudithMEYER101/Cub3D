/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_closure_check_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armeyer <armeyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 13:23:51 by sgoldenb          #+#    #+#             */
/*   Updated: 2025/01/28 17:27:18 by armeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
static int get_max_line_len(char *file, t_gm *gm)
{
	static int max_len;
	int i;
	int fd;
	char *buff;

	if (!file)
		return (-1);
	i = -1;
	buff = NULL;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (-2);
	while (get_next_line(fd, &buff, gm) > 0)
	{
		if (ft_strlen(buff) > max_len)
			max_len = ft_strlen(buff);
		free(buff);
		buff = NULL;
	}
	if (buff)
		free(buff);
	close(fd);
	return (max_len);
}

static void copy_line(char *buff, char *line)
{
	int i;
	int len;

	if (!buff || !line)
		return ;
	i = -1;
	len = ft_strlen(line);
	while (++i < len)
	{
		buff[i] = line[i];
	}
	buff[i] = 0;
}

static void erase_buff(char *buff, int max_len)
{
	int i;
	
	if (!buff)
		return ;
	i = -1;
	while (++i < max_len)
	{
		buff[i] = 0;
		// printf("\t\t%d - %d\n", i, max_len);
	}
}

void check_routine(char *str_save, char *str, int **ret_fd_len, t_gm *gm)
{
	str = NULL;
	*ret_fd_len[0] = get_next_line(*ret_fd_len[1], &str, gm);
	if (str)
	{
		copy_line(str_save, str);
		// printf("%s\n", str_save);
		free(str);
		if (*ret_fd_len[0] > 0)
			erase_buff(str_save, *ret_fd_len[2]);
	}
}

void	check_last_data(t_gm *gm, char *file)
{
	int		fd;
	int		ret;
	int		max_len;
	char	*str;
	char	*str_save;

	max_len = get_max_line_len(file, gm);
	str_save = (char *)malloc(sizeof(char) * (max_len + 1));
	if (!str_save)
		return ;
	erase_buff(str_save, max_len);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return ;
	ret = 1;
	str = NULL;
	while (ret > 0)
		check_routine(str_save, str, (int *[]){&ret, &fd, &max_len}, gm);
	if (*str_save && !ft_is_map(str_save, gm))
	{
		free(str_save);
		close(fd);
		ft_error(gm, "Map isn't the last element of the file.");
	}
	close(fd);
	free(str_save);
}
