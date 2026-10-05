/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argvalidation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hho-jia- <hho-jia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 11:59:17 by hho-jia-          #+#    #+#             */
/*   Updated: 2025/12/09 12:47:32 by hho-jia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static int	is_valid_number(char *str)
{
	int	i;

	i = 0;
	if (!str[0])
		return (0);
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (0);
		i++;
	}
	if (i > 10 || ft_atol(str) > 2147483647)
		return (0);
	return (1);
}

int	validate_arg(int ac, char **av)
{
	int	i;

	i = 1;
	if (!(ac == 5 || ac == 6))
	{
		printf ("./philo philo_num time_die time_eat time_sleep [nbr_meals]\n");
		return (1);
	}
	while (i < ac)
	{
		if (!is_valid_number(av[i]))
			return (printf("Enter Integer Only\n"), 1);
		i++;
	}
	if (ft_atol(av[1]) == 0 || (ac == 6 && ft_atol(av[5]) == 0))
		return (printf("Need at least 1 philosopher and 1 meal\n"), 1);
	return (0);
}

int	create_mutex(t_data *data)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (i < data->nophilo)
	{
		if (pthread_mutex_init (&data->fork_flag[i], NULL) != 0)
		{
			while (j < i)
			{
				pthread_mutex_destroy (&data->fork_flag[j]);
				j++;
			}
			free (data->philo_list);
			free (data->fork_flag);
			return (1);
		}
		i++;
	}
	if (pthread_mutex_init(&data->print_flag, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&data->end_mutex, NULL) != 0)
		return (1);
	return (0);
}

void	initargv(t_data *data, char **av)
{
	data->nophilo = (int)ft_atol(av[1]);
	data->ttd = (int)ft_atol(av[2]);
	data->tte = (int)ft_atol(av[3]);
	data->tts = (int)ft_atol(av[4]);
	if (av[5] != NULL)
		data->nme = (int)ft_atol(av[5]);
	else
		data->nme = 0;
	data->end_stimulation = 0;
	data->programtime = cal_time();
}

int	initdata(t_data *data, char **av)
{
	initargv(data, av);
	data ->philo_list = (t_philo *)malloc(sizeof(t_philo) * data->nophilo);
	if (!data -> philo_list)
	{
		perror ("Error");
		return (1);
	}
	data->fork_flag
		= (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * data->nophilo);
	if (!data -> fork_flag)
	{
		free (data->philo_list);
		perror("Error");
		return (1);
	}
	if (create_mutex(data))
	{
		perror ("Error creating mutex");
		return (1);
	}
	return (0);
}
