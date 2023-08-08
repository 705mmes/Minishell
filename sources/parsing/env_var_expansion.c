/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_expansion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 01:10:30 by ljerinec          #+#    #+#             */
/*   Updated: 2023/08/07 22:01:59 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 
	Parcours la liste chaine
	Si on trouve un dollars suivi d'une chaine '$...'
	la fonction env_to_string() est appeler
	pour remplacer le nom de la variable d'env par sa valeur !
*/
void	env_var_expansion(t_list *lst_parsing)
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

int	ft_is_envchar(int c)
{
	if ((c >= 48) && (c <= 57))
		return (1);
	else if ((c >= 65) && (c <= 90))
		return (1);
	else if ((c >= 97) && (c <= 123))
		return (1);
	else if ((c == '$'))
		return (1);
	else
		return (0);
}

char	env_var(char *word, int len)
{
	int		i;
	char	*env;

	if (*word != '$')
		env_var(word++, len++);
	else
	{
		i = 1;
		while (ft_is_envchar(word[i]) && word[i])
			i++;
		env = ft_substr(word, 1, i);
	}

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

	while (is_env_var(content))
	{
		i = 0;
		while (content->word[i] != '$' && content->word[i])
			i++;
		p1 = ft_substr(content->word, 0, i);
		start = i;
		if (between_quotes(content->word, i))
			i++;
		while (content->word[i] && content->word[i] != ' '
			&& content->word[i] != '$' && content->word[i + 1] != '\0')
			i++;
		start++;
		env = getenv(ft_substr(content->word, start, i - start));
		p2 = ft_substr(content->word, i, ft_strlen(content->word) - i);
		content->word = ft_strjoin(ft_strjoin(p1, env), p2);
	}
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
