/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hho-jia- <hho-jia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 11:57:28 by hho-jia-          #+#    #+#             */
/*   Updated: 2025/12/10 14:36:48 by hho-jia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	error_exit(t_data *data, int i)
{
	set_data_end_simulation(data);
	join_created_thread(data, i);
	safetly_exit(data);
}

void	set_data_end_simulation(t_data *data)
{
	pthread_mutex_lock(&data->end_mutex);
	data->end_stimulation = 1;
	pthread_mutex_unlock(&data->end_mutex);
}

void	join_created_thread(t_data *data, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		pthread_join(data->philo_list[j].tid, NULL);
		pthread_mutex_destroy(&data->philo_list[j].meal_mutex);
		j++;
	}
}

void	safetly_exit(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nophilo)
	{
		pthread_mutex_destroy(&data->fork_flag[i]);
		i++;
	}
	pthread_mutex_destroy(&data->print_flag);
	pthread_mutex_destroy(&data->end_mutex);
	free (data->fork_flag);
	free (data->philo_list);
}
