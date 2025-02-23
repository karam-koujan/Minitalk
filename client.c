/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkoujan <kkoujan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 17:53:15 by kkoujan           #+#    #+#             */
/*   Updated: 2025/02/23 15:26:14 by kkoujan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	send_char(int pid, char characeter)
{
	int		i;
	char	bit;

	i = 8;
	while (--i >= 0)
	{
		bit = characeter >> i & 1;
		if (bit == 1)
			kill(pid, SIGUSR1);
		else if (bit == 0)
			kill(pid, SIGUSR2);
		usleep(400);
	}
}

void	send(int pid, char *message)
{
	int	i;

	i = -1;
	while (message[++i])
		send_char(pid, message[i]);
}

int	is_number(char	*nbr)
{
	while (*nbr)
	{
		if (!(*nbr >= '0' && *nbr <= '9'))
			return (0);
		nbr++;
	}
	return (1);
}

int	main(int ac, char **av)
{
	char	*str;
	int		pid;

	if (ac != 3)
		return (1);
	str = av[2];
	if (!is_number(av[1]))
		return (1);
	pid = ft_atoi(av[1]);
	if (pid <= 0)
		return (1);
	send(pid, str);
}
