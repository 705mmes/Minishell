/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_atribute.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 15:56:15 by ljerinec          #+#    #+#             */
/*   Updated: 2023/08/01 14:57:53 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Verifie si le mot est une commande
	Change son attribution is_cmd a 1 si c'est une commande
*/
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
		if (!strncmp(word, "|", ft_strlen(word))
			|| !strncmp(word, "||", ft_strlen(word))
			|| !strncmp(word, "&&", ft_strlen(word)))
			content->is_separator = 1;
		else if (!strncmp(word, "<", ft_strlen(word))
			|| !strncmp(word, ">", ft_strlen(word))
			|| !strncmp(word, ">>", ft_strlen(word))
			|| !strncmp(word, "<<", ft_strlen(word)))
			content->is_redir = 1;
		lst_parsing = lst_parsing->next;
	}
}

/*
	Verifie si il y a le dollars dans la string
	Param : 1. contenu d'un maillon
	Return : 1 = true, 0 = false
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

int	char_in_squotes(t_content *content, int goal)
{
	int	i;
	int	flags;

	i = 0;
	flags = 0;
	while (i < goal)
	{
		if (content->word[i] == 39 && flags == 1)
			flags = 0;
		else if (content->word[i] == 39)
			flags = 1;
		i++;
	}
	if (flags == 1)
		return (TRUE);
	return (FALSE);
}

/*
	Expand les varaible d'environnement 
	Enleve le $NAME_OF_VARIABLE et le remplace par sa valeur.
	Si la variable n'existe pas enleve juste le $NAME_OF_VARIABLE
	Param : 1. contenu d'un maillon
	Return : 
*/
void	env_to_string(t_content *content)
{
	int		i;
	int		start;
	char	*p1;
	char	*p2;
	char	*env;
	char	*word;

	while (is_env_var(content))
	{
		i = 0;
		while (content->word[i] != '$' && content->word[i] && !char_in_squotes(content, i))
			i++;
		p1 = ft_substr(content->word, 0, i);
		start = i;
		i++;
		while (content->word[i] && content->word[i] != ' ' && content->word[i] != '$' && content->word[i + 1] != '\0')
			i++;
		start++;
		env = getenv(ft_substr(content->word, start, i - start));
		p2 = ft_substr(content->word, i, ft_strlen(content->word) - i);
		word = ft_strjoin(p1, env);
		content->word = ft_strjoin(word, p2);
	}
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
		if (is_env_var(content) && !content->is_squote)
			env_to_string(content);
		lst_parsing = lst_parsing->next;
	}
}

void	set_if_quoted(t_list *lst_parsing)
{
	t_content	*content;
	int			len;

	len = 0;
	while (lst_parsing)
	{
		content = (t_content *)lst_parsing->content;
		len = ft_strlen(content->word);
		if (content->word && content->word[0] == '"' && content->word[len] == '"')
			content->is_squote = 1;
		else if (content->word && content->word[0] == 39 && content->word[len] == 39)
			content->is_dquote = 1;
		lst_parsing = lst_parsing->next;
	}
}

void	define_word(t_list *lst_parsing)
{
	t_content	*content;

	while (lst_parsing)
	{
		content = (t_content *)lst_parsing->content;
		if (!is_cmds(content, lst_parsing->prev))
			if (!is_flag(content))
				content->is_arg = 1;
		lst_parsing = lst_parsing->next;
	}
}

void	link_settings(t_data *big_data)
{
	t_list		*lst_parsing;

	lst_parsing = big_data->lst_parsing->first;
	find_separator(lst_parsing);
	change_env_var(lst_parsing);
	define_word(lst_parsing);
}

/*
	Verifie si le mot est un flag
	Return : 1 = true, 2 = false
*/
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
