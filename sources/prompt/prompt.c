/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 12:37:12 by ljerinec          #+#    #+#             */
/*   Updated: 2023/09/28 14:50:27 by ljerinec         ###   ########.fr       */
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

void	reset_big_data(t_data *big_data)
{
	char	*get_env;

	if (big_data->lst_parsing)
		free_lst_content(big_data->lst_parsing);
	if (big_data->path)
		ft_free_array(big_data->path);
	get_env = ft_getenv(big_data, ft_strdup("PATH"));
	big_data->path = ft_split(get_env, ':');
	free(get_env);
	free(big_data->root_path);
	big_data->root_path = ft_getenv(big_data, ft_strdup("HOME"));
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
		reset_big_data(big_data);
		big_data->input = NULL;
		if (big_data->syntax_error)
			big_data->syntax_error = 0;
		free(input);
	}
	else
	{
		add_history(input);
		printf("minishell: syntax error `quote unclosed'\n");
	}
}
