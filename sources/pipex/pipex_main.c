/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 15:12:11 by sammeuss          #+#    #+#             */
/*   Updated: 2023/09/18 15:04:14 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_cmd_path(t_data *big_data, t_content *content)
{
	int	i;

	i = -1;
	if (access(content->word, X_OK) == 0)
	{
		content->pathed = content->word;
		return ;
	}
	while (big_data->path[++i])
	{
		content->pathed = ft_strjoin(big_data->path[i], "/");
		content->pathed = ft_strjoin(content->pathed, content->cmd[0]);
		if (access(content->pathed, X_OK) == 0)
			return ;
	}
	write(2, "minishell: ", ft_strlen("minishell: "));
	write(2, content->cmd[0], ft_strlen(content->cmd[0]));
	ft_putstr_fd(": command not found", 2);
}

int	ft_count_cmds(t_data *big_data)
{
	t_list		*lst;
	int			r;

	r = 0;
	lst = big_data->lst_parsing->first;
	while (lst)
	{
		if (((t_content *)lst->content)->type == CMD)
			r++;
		lst = lst->next;
	}
	return (r);
}

void	exec(t_data *big_data)
{
	if (ft_count_cmds(big_data) > 0)
		create_childs(big_data);
	else
		return ;
	// print_lst_parsing(big_data->lst_parsing->first);
}
