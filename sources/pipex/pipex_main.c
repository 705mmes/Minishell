/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 15:12:11 by sammeuss          #+#    #+#             */
/*   Updated: 2023/09/21 18:56:37 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_cmd_path(t_data *big_data, t_content *content)
{
	int	i;

	i = -1;
	if (content->word && access(content->word, X_OK) == 0)
	{
		content->pathed = ft_strdup(content->word);
		return (0);
	}
	if (!big_data->path)
	{
		msg_e("minishell: ", content->cmd[0], ": No such file or directory\n");
		exit(126);
	}
	while (big_data->path[++i])
	{
		content->pathed = ft_strjoin(ft_strdup(big_data->path[i]), "/");
		content->pathed = ft_strjoin(content->pathed, content->cmd[0]);
		if (access(content->pathed, X_OK) == 0)
			return (0);
		else
			free(content->pathed);
	}
	msg_e("minishell: ", content->cmd[0], ": command not found\n");
	return (1);
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
}
