/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_expansion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 01:10:30 by ljerinec          #+#    #+#             */
/*   Updated: 2023/09/14 18:54:19 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_mini_sig;

char	*ft_strjoin_char(char *s1, char s2)
{
	size_t	sizetotal;
	char	*chainjoin;
	int		i;

	i = 0;
	sizetotal = ft_strlen(s1) + 1;
	chainjoin = malloc(sizeof(char) * (sizetotal + 1));
	if (!chainjoin)
		return (NULL);
	if (s1)
	{
		while (i < ft_strlen_gnl(s1))
		{
			chainjoin[i] = s1[i];
			i++;
		}
	}
	if (s2)
		chainjoin[i] = s2;
	chainjoin[i + 1] = 0;
	return (chainjoin);
}

/* 
	Parcours la liste chaine
	Si on trouve un dollars suivi d'une chaine '$...'
	la fonction env_to_string() est appeler
	pour remplacer le nom de la variable d'env par sa valeur !
*/
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
	if (c >= 48 && c <= 57)
		return (1);
	else if (c >= 65 && c <= 90)
		return (1);
	else if (c >= 97 && c <= 123)
		return (1);
	else if (c == '_')
		return (1);
	else if (c == '?')
		return (2);
	else
		return (0);
}

char	*ft_getenv(t_data *big_data, char *find_env)
{
	int		i;
	char	**env;

	i = -1;
	env = big_data->env;
	if (find_env)
		find_env = ft_strjoin(find_env, "=");
	while (big_data->env[++i])
		if (!ft_strncmp(find_env, big_data->env[i], ft_strlen(find_env)))
			return (ft_substr(env[i],
					ft_strlen(find_env),
					ft_strlen(env[i]) - ft_strlen(find_env)));
	return (NULL);
}

/*
	Expand les varaible d'environnement 
	Enleve le $NAME_OF_VARIABLE et le remplace par sa valeur.
	Si la variable n'existe pas enleve juste le $NAME_OF_VARIABLE
	Param : 1. contenu d'un maillon
	Return : 
*/
void	env_to_string(t_data *big_data, t_content *content)
{
	int		i;
	int		start;
	char	*env;
	char	*p1;

	p1 = NULL;
	start = 0;
	i = 0;
	while (content->word[i])
	{
		while (content->word[i] && content->word[i] != '$')
			p1 = ft_strjoin_char(p1, content->word[i++]);
		if (content->word[i] == '$')
			i++;
		if (ft_is_envchar(content->word[i]) == 1 && content->word[i] && is_quoted_and_who(content->word, i) != 39)
		{
			start = i;
			while (content->word[i] && ft_is_envchar(content->word[i]) == 1)
				i++;
			env = ft_substr(content->word, start, i - start);
			env = ft_getenv(big_data, env);
			p1 = ft_strjoin(p1, env);
		}
		else if (ft_is_envchar(content->word[i]) == 2 && content->word[i] && is_quoted_and_who(content->word, i) != 39)
		{
			i++;
			p1 = ft_strjoin(p1, ft_itoa(g_mini_sig));
		}
		else if (content->word[i - 1] == '$')
			p1 = ft_strjoin_char(p1, '$');
	}
	content->word = p1;
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
