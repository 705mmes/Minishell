/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_parsing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sammeuss <sammeuss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 14:55:17 by sammeuss          #+#    #+#             */
/*   Updated: 2023/09/05 15:17:18 by sammeuss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	array_len(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return (0);
	while (array[i])
		i++;
	return (i);
}

char	*get_flags(char **cmd)
{
	char	*r;
	int		i;

	i = 1;
	while (cmd[i])
	{
		r = ft_strjoin(r, cmd[i]);
		i++;
	}
	return (r);
}

t_p_data	*quick_setup(char **av, char **env)
{
	t_p_data	*data;

	data = malloc(sizeof(t_p_data));
	if (!data)
		return (perror("Malloc error"), NULL);
	data->infile = open(av[1], O_RDONLY);
	data->outfile = open(av[4], O_CREAT | O_RDWR);
	if (data->infile < 0 || data->outfile < 0)
		return (perror("Failed to open in/outfile"), NULL);
	data->cmd1 = ft_split(av[2], ' ');
	data->cmd2 = ft_split(av[3], ' ');
	data->path = ft_split(getenv("PATH"), ':');
	data->exec_args = malloc(sizeof(t_cmdve));
	if (!data->exec_args)
		return (perror("Malloc error"), NULL);
	data->env = env;
	return (data);
}
