/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 23:44:34 by ljerinec          #+#    #+#             */
/*   Updated: 2023/07/12 14:54:56 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*all_before_backslash_n(char *str)
{
	int		i;
	int		u;
	char	*result;

	i = 0;
	u = 0;
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	if (str[i] == '\n')
		i++;
	result = malloc(sizeof(char) * (i + 1));
	if (!result)
		return (freeall_gnl(&str));
	u = -1;
	while (++u < i)
		result[u] = str[u];
	result[u] = 0;
	if (result[0] == '\0')
	{
		free(str);
		return (freeall_gnl(&result));
	}
	return (result);
}

char	*all_after_backslash_n(char *str)
{
	int		i;
	int		u;
	char	*result;
	int		len_str;

	i = 0;
	u = 0;
	result = NULL;
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	if (!str[i])
		return (freeall_gnl(&str));
	i++;
	len_str = ft_strlen_gnl(str) - i;
	u = 0;
	result = malloc(sizeof(char) * len_str + 1);
	if (!result)
		return (doublefree_gnl(str, &result));
	while (u < len_str)
		result[u++] = str[i++];
	result[u] = 0;
	freeall_gnl(&str);
	return (result);
}

char	*ft_strjoin_gnl(char *str, char *buffer, int len)
{
	int		u;
	int		i;
	char	*save;

	i = 0;
	u = 0;
	save = malloc(sizeof(char) * (len + 1));
	if (!save)
		return (freeall_gnl(&str));
	if (str != NULL)
		while (str[i] != '\n' && str[i] != '\0')
			save[u++] = str[i++];
	free(str);
	i = 0;
	while (u < len)
		save[u++] = buffer[i++];
	save[u] = 0;
	return (save);
}

char	*get_next_line(int fd)
{
	char		buffer[BUFFER_SIZE];
	static char	*save;
	char		*result;
	int			u;

	u = BUFFER_SIZE;
	if (fd < 0 || BUFFER_SIZE < 1 || read(fd, buffer, 0) < 0)
		return (freeall_gnl(&save));
	if (check_backslash(save, u))
		u = 0;
	while (u > 0)
	{
		u = read(fd, buffer, BUFFER_SIZE);
		if ((save != NULL && u > 0) || (save == NULL && u > 0))
			save = ft_strjoin_gnl(save, buffer, (u + ft_strlen_gnl(save)));
		if (!save)
			return (NULL);
		if (check_backslash(save, u))
			break ;
	}
	result = all_before_backslash_n(save);
	if (result == 0)
		return (freeallspe_gnl(&save));
	save = all_after_backslash_n(save);
	return (result);
}
