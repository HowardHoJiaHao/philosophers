/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timeprocess.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hho-jia- <hho-jia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 11:58:43 by hho-jia-          #+#    #+#             */
/*   Updated: 2025/12/10 14:42:40 by hho-jia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	print_error(void)
{
	printf("Error:\n Insufficient input parameter");
}

long long	cal_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((long long)tv.tv_sec * 1000LL + tv.tv_usec / 1000LL);
}
