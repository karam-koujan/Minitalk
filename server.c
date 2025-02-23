/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkoujan <kkoujan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 12:16:32 by kkoujan           #+#    #+#             */
/*   Updated: 2025/02/18 09:24:11 by kkoujan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	handler(int signum, siginfo_t *info, void *context)
{
	static char	buffer[9];
	static int	index;
	static int	pid;
	static int	new_pid;

	(void)context;
	(void)info;
	if (info->si_pid != 0)
		pid = info->si_pid;
	if (new_pid != 0 && new_pid != pid)
		index = 0;
	if (index < 8)
	{
		if (signum == SIGUSR1)
			buffer[index++] = '1';
		else if (signum == SIGUSR2)
			buffer[index++] = '0';
	}
	if (index == 8)
	{
		buffer[index] = '\0';
		decode_message(buffer);
		index = 0;
	}
	new_pid = info->si_pid;
}

void	decode_message(char *message)
{
	char	nb;
	int		i;

	nb = 0;
	i = -1;
	while (message[++i])
	{
		if (message[i] == '1')
			nb = nb * 2 + 1;
		else
			nb = nb * 2;
	}
	write(1, &nb, 1);
}

int	main(int ac, char **av)
{
	t_sigaction	sa;

	(void)av;
	if (ac > 1)
		return (1);
	sa.sa_sigaction = handler;
	sa.sa_flags = SA_SIGINFO;
	ft_printf("%i\n", getpid());
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGUSR1);
	sigaddset(&sa.sa_mask, SIGUSR2);
	if (sigaction(SIGUSR1, &sa, NULL) < 0)
		exit(1);
	if (sigaction(SIGUSR2, &sa, NULL) < 0)
		exit(1);
	while (1)
		pause();
}
