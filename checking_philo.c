/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking_philo.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hho-jia- <hho-jia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 16:07:30 by hho-jia-          #+#    #+#             */
/*   Updated: 2025/12/10 15:07:14 by hho-jia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	checkphilodeath(t_data *data)
{
	long long	time;
	int			i;

	i = 0;
	while (i < data->nophilo)
	{
		pthread_mutex_lock(&data->philo_list[i].meal_mutex);
		time = cal_time() - data->philo_list[i].tle;
		pthread_mutex_unlock(&data->philo_list[i].meal_mutex);
		if (time > data->ttd)
		{
			print_death(&data->philo_list[i]);
			return (1);
		}
		i++;
	}
	return (0);
}

// prints "died" and ends the simulation atomically, so it is printed
// exactly once and nothing can be printed after it
void	print_death(t_philo *philo)
{
	t_data	*data;

	data = philo->alldata;
	pthread_mutex_lock(&data->print_flag);
	pthread_mutex_lock(&data->end_mutex);
	if (data->end_stimulation == 0)
	{
		printf("%lld %d died\n",
			cal_time() - data->programtime, philo->id + 1);
		data->end_stimulation = 1;
	}
	pthread_mutex_unlock(&data->end_mutex);
	pthread_mutex_unlock(&data->print_flag);
}

void	*one_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	print_item(philo, "has taken a fork\n");
	usleep(philo->alldata->ttd * 1000);
	print_death(philo);
	return (NULL);
}

void	check_eat(t_data *data, int i, int *alleat)
{
	pthread_mutex_lock(&data->philo_list[i].meal_mutex);
	if (data->philo_list[i].meal_eaten < data->nme)
		*alleat = 0;
	pthread_mutex_unlock(&data->philo_list[i].meal_mutex);
}

void	checkphilo(t_data *data)
{
	int	i;
	int	alleat;

	while (1)
	{
		i = 0;
		alleat = 1;
		if (checkphilodeath(data))
			return ;
		if (data->nme != 0)
		{
			while (i < data->nophilo)
			{
				check_eat(data, i, &alleat);
				i++;
			}
			if (alleat == 1)
				return (set_data_end_simulation(data));
		}
		usleep(1000);
	}
}
