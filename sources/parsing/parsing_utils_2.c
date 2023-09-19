/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smunio <smunio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 20:49:49 by ljerinec          #+#    #+#             */
/*   Updated: 2023/09/19 17:27:26 by smunio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_arraylen(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return (0);
	while (array[i])
		i++;
	return (i);
}

char	**array_dup(char **array)
{
	int		i;
	char	**new_array;

	i = 0;
	while (array[i])
		i++;
	new_array = malloc(sizeof(char *) * (i + 1));
	i = -1;
	while (array[++i])
		new_array[i] = ft_strdup(array[i]);
	new_array[i] = NULL;
	return (new_array);
}

int	is_unmanaged_operator(t_list *lst, t_data *big_data)
{
	t_content	*content;

	if (big_data->syntax_error)
		return (0);
	while (lst)
	{
		content = (t_content *)lst->content;
		if (content->type == OPERATOR)
		{
			printf("minishell: unmanaged operator: `%s'\n", content->word);
			g_mini_sig = 2;
			return (1);
		}
		lst = lst->next;
	}
	return (0);
}

t_content	*create_content(char *word, int i)
{
	t_content	*content;

	content = malloc(sizeof(t_content));
	if (!content)
		return (NULL);
	content->word = ft_strdup(word);
	content->cmd = NULL;
	content->infile = STDIN_FILENO;
	content->outfile = STDOUT_FILENO;
	content->index = i;
	content->to_delete = 0;
	content->type = NONE;
	content->pathed = NULL;
	content->error = 0;
	content->exit_code = 0;
	return (content);
}

t_data_lst	*create_data_lst(void)
{
	t_data_lst	*new_data_lst;

	new_data_lst = malloc(sizeof(t_data_lst));
	if (!new_data_lst)
		return (NULL);
	new_data_lst->first = NULL;
	new_data_lst->last = NULL;
	new_data_lst->num_link = 0;
	return (new_data_lst);
}
