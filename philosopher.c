/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hho-jia- <hho-jia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 11:59:45 by hho-jia-          #+#    #+#             */
/*   Updated: 2025/10/31 11:59:45 by hho-jia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	*philo_work(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		pthread_mutex_lock(&philo->alldata->end_mutex);
		if (philo->alldata->end_stimulation == 1)
		{
			pthread_mutex_unlock(&philo->alldata->end_mutex);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->alldata->end_mutex);
		if (eatphilo(philo))
			return (NULL);
		pthread_mutex_lock(&philo->alldata->end_mutex);
		if (philo->alldata->end_stimulation == 1)
		{
			pthread_mutex_unlock(&philo->alldata->end_mutex);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->alldata->end_mutex);
		sleepphilo(philo);
		thinkphilo(philo);
	}
	return (NULL);
}

void	initphilo_data(t_data *data, int i)
{
	data->philo_list[i].id = i;
	data->philo_list[i].fork1 = i;
	data->philo_list[i].fork2 = (i + 1) % data->nophilo;
	data->philo_list[i].meal_eaten = 0;
	data->philo_list[i].alldata = data;
}

int	initphilo(t_data *data)
{
	int	i;
	int	temp_fork_index;

	i = 0;
	while (i < data->nophilo)
	{
		initphilo_data(data, i);
		if (i % 2 == 0)
		{
			temp_fork_index = data->philo_list[i].fork1;
			data->philo_list[i].fork1 = data->philo_list[i].fork2;
			data->philo_list[i].fork2 = temp_fork_index;
		}
		if (pthread_mutex_init(&data->philo_list[i].meal_mutex, NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&data->philo_list[i].meal_mutex);
			return (1);
		}
		i++;
	}
	return (0);
}

int	create_thread(t_data *data)
{
	int	i;

	i = 0;
	data->programtime = cal_time();
	if (data->nophilo == 1)
	{
		data->philo_list[i].tle = data->programtime;
		if (pthread_create(&data->philo_list[i].tid,
				NULL, one_philo, &data->philo_list[i]) != 0)
			return (error_exit(data, i), 1);
	}
	else
	{
		while (i < data->nophilo)
		{
			data->philo_list[i].tle = data->programtime;
			if (pthread_create(&data->philo_list[i].tid,
					NULL, philo_work, &data->philo_list[i]) != 0)
				return (error_exit(data, i), 1);
			i++;
		}
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (validate_arg(ac, av))
		return (1);
	if (initdata(&data, av))
		return (1);
	if (initphilo(&data))
		return (1);
	if (create_thread(&data))
		return (1);
	checkphilo(&data);
	join_created_thread(&data, data.nophilo);
	safetly_exit(&data);
	return (0);
}
