/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 12:37:12 by ljerinec          #+#    #+#             */
/*   Updated: 2023/09/21 17:48:59 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_mini_sig;

void	last_exit_code(t_list *lst)
{
	t_content	*content;

	content = NULL;
	if (!lst)
		g_mini_sig = 0;
	while (lst)
	{
		content = (t_content *)lst->content;
		if (content->type == CMD)
			g_mini_sig = content->exit_code;
		lst = lst->next;
	}
}

void	prompt(t_data *big_data)
{
	char	*input;

	input = NULL;
	ft_signal();
	while (1)
	{
		input = readline(big_data->read_name);
		if (is_ctrl_d(big_data, input))
			break ;
		else if (strncmp(input, "", ft_strlen(input)) != 0)
			use_prompt(big_data, input);
	}
	rl_clear_history();
}

void	unlink_heredocs(t_data *big_data)
{
	int	i;

	i = -1;
	if (!big_data->heredocs)
		return ;
	while (big_data->heredocs[++i])
		unlink(big_data->heredocs[i]);
	ft_free_array(big_data->heredocs);
	big_data->heredocs = NULL;
}

void	use_prompt(t_data *big_data, char *input)
{
	big_data->input = input;
	if (!is_quotes_open(input))
	{
		add_history(input);
		parsing(big_data);
		if (!big_data->syntax_error)
			exec(big_data);
		last_exit_code(big_data->lst_parsing->first);
		unlink_heredocs(big_data);
		free_lst_content(big_data->lst_parsing);
		big_data->input = NULL;
		if (big_data->syntax_error)
			big_data->syntax_error = 0;
		free(input);
	}
	else
		printf("minishell: syntax error `quote unclosed'\n");
}
