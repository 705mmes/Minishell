/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 15:04:10 by ljerinec          #+#    #+#             */
/*   Updated: 2023/09/14 00:48:30 by ljerinec         ###   ########.fr       */
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
