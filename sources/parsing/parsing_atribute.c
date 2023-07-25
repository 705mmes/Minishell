/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_atribute.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 15:56:15 by ljerinec          #+#    #+#             */
/*   Updated: 2023/07/25 19:03:22 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_cmds(t_content *content, t_list *prev)
{
	t_content	*cont_prev;

	if (prev)
		cont_prev = (t_content *)prev->content;
	if (content->index == 0)
		content->is_cmd = 1;
	else if (prev != NULL && cont_prev->is_separator)
		content->is_cmd = 1;
	if (content->is_cmd)
		return (TRUE);
	return (FALSE);
}

void	find_separator(t_list *lst_parsing)
{
	t_content	*content;
	char		*word;

	while (lst_parsing)
	{
		content = (t_content *)lst_parsing->content;
		word = content->word;
		if (!strncmp(word, "|", ft_strlen(word)))
			content->is_separator = 1;
		else if (!strncmp(word, "<", ft_strlen(word))
			|| !strncmp(word, ">", ft_strlen(word))
			|| !strncmp(word, ">>", ft_strlen(word))
			|| !strncmp(word, "<<", ft_strlen(word))
			|| !strncmp(word, "||", ft_strlen(word))
			|| !strncmp(word, "&&", ft_strlen(word)))
			content->is_redir = 1;
		lst_parsing = lst_parsing->next;
	}
}

/*
	Verifie si il y a une variable d'environnement
*/
int	is_env_var(t_content *content)
{
	int	i;

	i = 0;
	while (content->word[i])
	{
		if (content->word[i] == '$')
			return (TRUE);
		i++;
	}
	return (FALSE);
}

void	env_to_string(t_content *content)
{
	int		i;
	int		start;
	char	*p1;
	char	*p2;
	char	*env;
	char	*word;

	i = 0;
	while (is_env_var(content))
	{
		while (content->word[i] != '$' && content->word[i])
			i++;
		p1 = ft_substr(content->word, 0, i);
		start = i;
		i++;
		while (content->word[i] && content->word[i] != ' ' && content->word[i] != '$')
			i++;
		printf("%d\n", i);
		start++;
		env = ft_substr(content->word, start, i - start);
		printf("Env sub %s\n", env);
		env = getenv(env);
		p2 = ft_substr(content->word, i, ft_strlen(content->word));
		printf("P1 %s\n", p1);
		printf("Env get %s\n", env);
		printf("P2 %s\n", p2);
		word = ft_strjoin(p1, env);
		content->word = ft_strjoin(word, p2);
		i = 0;
	}
	ft_printf("%s\n", content->word);
}

/* 
	Parcours la liste chaine 
	Si on trouve un dollars suivi d'une chaine '$...'
	la fonction env_to_string() est appeler
	pour remplacer le nom de la variable d'env par sa valeur !
*/
void	change_env_var(t_list *lst_parsing)
{
	t_content	*content;

	while (lst_parsing)
	{
		content = (t_content *)lst_parsing->content;
		if (is_env_var(content))
			env_to_string(content);
		lst_parsing = lst_parsing->next;
	}
}

void	link_settings(t_data *big_data)
{
	t_list		*lst_parsing;
	t_content	*content;

	lst_parsing = big_data->lst_parsing->first;
	find_separator(lst_parsing);
	change_env_var(lst_parsing);
	while (lst_parsing)
	{
		content = (t_content *)lst_parsing->content;
		if (!is_cmds(content, lst_parsing->prev))
			if (!is_flag(content))
				content->is_arg = 1;
		lst_parsing = lst_parsing->next;
	}
}

int	is_flag(t_content *content)
{
	char	*word;

	word = content->word;
	if (word[0] == '-' && ft_strlen(word) > 1)
		return (content->is_flag = TRUE);
	else
		return (FALSE);
}

int	is_quotes_open(char *input)
{
	int	i;
	int	state;

	i = 0;
	state = 0;
	while (input[i] && input)
	{
		if (state == 0 && (input[i] == 39 || input[i] == 34))
			state = input[i++];
		if (input[i] == state)
			state = 0;
		i++;
	}
	if (state > 0)
		return (TRUE);
	return (FALSE);
}
