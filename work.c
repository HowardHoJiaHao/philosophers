/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hho-jia- <hho-jia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 16:07:36 by hho-jia-          #+#    #+#             */
/*   Updated: 2025/12/10 14:41:42 by hho-jia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	print_item(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->alldata->print_flag);
	pthread_mutex_lock(&philo->alldata->end_mutex);
	if (philo->alldata->end_stimulation == 0)
		printf("%lld %d %s",
			cal_time() - philo->alldata->programtime, philo->id + 1, str);
	pthread_mutex_unlock(&philo->alldata->end_mutex);
	pthread_mutex_unlock(&philo->alldata->print_flag);
}

int	eatphilo2(t_philo *philo)
{
	long	currenttime;

	currenttime = cal_time();
	pthread_mutex_lock(&philo->meal_mutex);
	if (currenttime - philo->tle > philo->alldata->ttd)
	{
		pthread_mutex_unlock(&philo->meal_mutex);
		print_death(philo);
		pthread_mutex_unlock(&philo->alldata->fork_flag[philo->fork1]);
		pthread_mutex_unlock(&philo->alldata->fork_flag[philo->fork2]);
		return (1);
	}
	pthread_mutex_unlock(&philo->meal_mutex);
	print_item(philo, "is eating\n");
	pthread_mutex_lock(&philo->meal_mutex);
	philo->tle = currenttime;
	philo->meal_eaten++;
	pthread_mutex_unlock(&philo->meal_mutex);
	usleep(philo->alldata->tte * 1000);
	pthread_mutex_unlock(&philo->alldata->fork_flag[philo->fork2]);
	pthread_mutex_unlock(&philo->alldata->fork_flag[philo->fork1]);
	return (0);
}

int	eatphilo(t_philo *philo)
{
	long	currenttime;

	currenttime = cal_time();
	pthread_mutex_lock(&philo->meal_mutex);
	if (currenttime - philo->tle > philo->alldata->ttd)
	{
		pthread_mutex_unlock(&philo->meal_mutex);
		print_death(philo);
		return (1);
	}
	pthread_mutex_unlock(&philo->meal_mutex);
	pthread_mutex_lock(&philo->alldata->fork_flag[philo->fork1]);
	print_item(philo, "has taken a fork\n");
	pthread_mutex_lock(&philo->alldata->fork_flag[philo->fork2]);
	print_item(philo, "has taken a fork\n");
	if (eatphilo2(philo))
		return (1);
	return (0);
}

void	sleepphilo(t_philo *philo)
{
	print_item(philo, "is sleeping\n");
	usleep(philo->alldata->tts * 1000);
}

void	thinkphilo(t_philo *philo)
{
	print_item(philo, "is thinking\n");
	usleep(1000);
}
