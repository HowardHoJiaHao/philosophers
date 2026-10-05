/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hho-jia- <hho-jia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 13:34:02 by hho-jia-          #+#    #+#             */
/*   Updated: 2025/10/31 13:34:02 by hho-jia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>
# include <stdlib.h>
// #include <pthread.h>
# include <pthread.h>

struct	s_philo;

typedef struct s_data
{
	int				nophilo;
	int				ttd; // time to die
	int				tte; // time to eat 
	int				tts; // time to sleep 
	int				nme; // number must eat
	int				end_stimulation; //1 if any die
	long long		programtime;
	struct s_philo	*philo_list;// malloc  
	pthread_mutex_t	*fork_flag; // malloc mutex
	pthread_mutex_t	print_flag;//          mutex 
	pthread_mutex_t	end_mutex; //          mutex 
}	t_data;

typedef struct s_philo
{
	int				id;
	int				fork1;
	int				fork2;
	int				meal_eaten;
	pthread_mutex_t	meal_mutex; //     mutex 
	long long		tle;
	t_data			*alldata;
	pthread_t		tid;
}	t_philo;

// argvalidation.c
int			validate_arg(int ac, char **av);
int			initdata(t_data *data, char **av);

// timeprss.c
long long	cal_time(void);

// Utils.c
int			ft_isspace(char c);
long int	ft_atol(char *str);

// error_handling.c
void		safetly_exit(t_data *data);
void		set_data_end_simulation(t_data *data);
void		error_exit(t_data *data, int i);

// philosopher.c
int			create_thread(t_data *data);
int			initphilo(t_data *data);
void		*philo_work(void *arg);
void		join_created_thread(t_data *data, int i);

// work.c 
void		print_item(t_philo *philo, char *str);
int			eatphilo(t_philo *philo);
void		sleepphilo(t_philo *philo);
void		thinkphilo(t_philo *philo);

// checking_philo.c
int			checkphilodeath(t_data *data);
void		*one_philo(void *arg);
void		checkphilo(t_data *data);

#endif