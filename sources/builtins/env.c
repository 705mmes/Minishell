/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smunio <smunio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 15:04:10 by ljerinec          #+#    #+#             */
/*   Updated: 2023/09/21 14:37:03 by smunio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_data *big_data, t_content *cont)
{
	int	i;

	i = -1;
	if (!big_data->env && !(*big_data->env))
		return ;
	while (big_data->env[++i])
		ft_putstr_fd(big_data->env[i], cont->outfile);
}

void	ft_export_no_args(t_data *big_data, t_content *cont)
{
	int		i;

	i = -1;
	if (!big_data->env && !(*big_data->env))
		return ;
	while (big_data->env[++i])
	{	
		write(cont->outfile, "declare -x ", 11);
		ft_putstr_fd(big_data->env[i], cont->outfile);
	}
}
