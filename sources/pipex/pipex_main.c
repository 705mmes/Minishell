/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 15:12:11 by sammeuss          #+#    #+#             */
/*   Updated: 2023/09/22 13:50:56 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_slash(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == '/')
			return (1);
	return (0);
}

int	get_cmd_path(t_data *big_data, t_content *content)
{
	int	i;

	i = -1;
	if (is_slash(content->word) && opendir(content->word))
		return (msg_e("minishell: ", content->word, ": is a directory\n"),
			exit(126), 1);
	if (is_slash(content->word) && access(content->word, F_OK) != 0)
		return (msg_e("minishell: ", content->word,
				": No such file or directory\n"), exit(127), 1);
	if (is_slash(content->word) && access(content->word, X_OK) != 0)
		return (msg_e("minishell: ", content->word,
				": Permission denied\n"), exit(126), 1);
	while (big_data->path && big_data->path[++i])
	{
		content->pathed = ft_strjoin(ft_strdup(big_data->path[i]), "/");
		content->pathed = ft_strjoin(content->pathed, content->cmd[0]);
		if (access(content->pathed, F_OK | X_OK) == 0)
			return (0);
		else
			free(content->pathed);
	}
	if (access(content->word, F_OK | X_OK) == 0 && !opendir(content->word))
		return (content->pathed = ft_strdup(content->word), 0);
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
