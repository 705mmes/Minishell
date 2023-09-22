/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 11:24:32 by ljerinec          #+#    #+#             */
/*   Updated: 2023/09/22 15:38:42 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(t_content *cont, t_data *big_data)
{
	char	*pwd;

	pwd = ft_getenv(big_data, ft_strdup("PWD"));
	if (pwd == NULL)
		perror("minishell: pwd: command failed");
	else
	{
		write(cont->outfile, pwd, ft_strlen(pwd));
		write(cont->outfile, "\n", 1);
	}
}
