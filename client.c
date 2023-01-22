/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbesson <fbesson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:04:04 by fbesson           #+#    #+#             */
/*   Updated: 2023/01/22 17:54:23 by fbesson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void	exit_msg(int fd, char *str, int len, int status)
{
	write(fd, str, len);
	exit(status);
}

int	ft_atoi(const char *str)
{
	int	res;
	int	neg;
	int	i;

	res = 0;
	i = 0;
	neg = 0;
	if (str[i] == '-' && str[i++])
		neg = 1;
	while (str[i])
		if (str[i] >= '0' && str[i] <= '9')
			res = res * 10 + str[i++] - '0';
	else
		exit_msg(2, "error: invalid pid\n", 19, 1);
	if (!res)
		exit_msg(2, "error: invalid pid\n", 19, 1);
	if (!neg)
		return (-res);
	return (res);
}

void	send_char(int pid, char c)
{
	int	n;

	n = 8;
	while (n--)
	{
		if (c & 1)
		{
			if (kill(pid, SIGUSR1))
				exit_msg(2, "error: invalid pid\n", 19, 1);
		}
		else if (kill(pid, SIGUSR2))
			exit_msg(2, "error: invalid pid\n", 19, 1);
		c >>= 1;
		pause();
	}
}

void	signal_received(int sig)
{
	(void)sig;
}

int	main(int ac, char **av)
{
	int	pid;
	int	i;

	i = 0;
	if (ac != 3)
		exit_msg(1, "usage: ./client [pid] [msg]\n", 28, 0);
	signal(SIGUSR1, signal_received);
	pid = ft_atoi(av[1]);
	while (av[2][i])
		send_char(pid, av[2][i++]);
	send_char(pid, 0);
	write(1, "msg received\n", 13);
}
