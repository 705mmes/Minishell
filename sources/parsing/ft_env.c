/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 01:10:30 by ljerinec          #+#    #+#             */
/*   Updated: 2023/09/29 15:09:16 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_mini_sig;

void	env_var_expansion(t_data *big_data, t_list *lst_parsing)
{
	t_content	*content;

	while (lst_parsing)
	{
		content = (t_content *)lst_parsing->content;
		if (is_env_var(content))
			env_to_string(big_data, content);
		lst_parsing = lst_parsing->next;
	}
}

char	*ft_getenv(t_data *big_data, char *find_env)
{
	int		i;
	int		len;
	char	**env;

	i = -1;
	env = big_data->env;
	if (find_env)
		find_env = ft_strjoin(find_env, "=");
	len = ft_strlen(find_env);
	while (big_data->env[++i])
	{
		if (!ft_strncmp(find_env, big_data->env[i], ft_strlen(find_env)))
		{
			free(find_env);
			return (ft_substr(env[i], len,
					ft_strlen(env[i]) - len));
		}
	}
	free(find_env);
	return (NULL);
}

char	*cut_to_getenv(int *i, char *p1, t_content *cont, t_data *big_data)
{
	int		start;
	char	*result;
	char	*env_1;
	char	*env_2;

	env_1 = NULL;
	env_2 = NULL;
	result = NULL;
	start = *i;
	while (cont->word[*i] && ft_is_envchar(cont->word[*i]) == 1)
		(*i)++;
	env_1 = ft_substr(cont->word, start, *i - start);
	env_2 = ft_getenv(big_data, env_1);
	result = ft_strjoin(p1, env_2);
	free(env_2);
	return (result);
}

void	env_to_string(t_data *big_data, t_content *content)
{
	int		i;
	char	*p1;

	p1 = NULL;
	i = 0;
	while (content->word[i])
	{
		while (content->word[i] && content->word[i] != '$')
			p1 = ft_strjoin_char(p1, content->word[i++]);
		if (content->word[i] == '$')
			i++;
		if (content->word[i] && ft_is_envchar(content->word[i]) == 1
			&& is_quoted_and_who(content->word, i) != 39)
			p1 = cut_to_getenv(&i, p1, content, big_data);
		else if (ft_is_envchar(content->word[i]) == 2 && content->word[i]
			&& is_quoted_and_who(content->word, i) != 39)
		{
			i++;
			p1 = ft_strjoin(p1, ft_itoa(g_mini_sig));
		}
		else if (content->word[i - 1] == '$')
			p1 = ft_strjoin_char(p1, '$');
	}
	free(content->word);
	content->word = p1;
}
