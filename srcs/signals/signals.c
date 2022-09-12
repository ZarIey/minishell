/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcauchet <jcauchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 16:37:16 by jcauchet          #+#    #+#             */
/*   Updated: 2022/08/25 17:40:23 by jcauchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/***************************************************************************
Handles CTRL C and SIGINT signal
***************************************************************************/
void	ctrl_c(int sig)
{
	(void)sig;
	if (g_glob->stty == -42)
		g_glob->code = 128 + SIGINT;
	else
		g_glob->code = 1;
	write(42, "\n", 1);
	if (g_glob->stty != -42)
		rl_replace_line("", 0);
	if (g_glob->stty != -42)
		rl_on_new_line();
	rl_redisplay();
}

/***************************************************************************
Handles CTRL \ and SIGQUIT signal
***************************************************************************/
void	ctrl_bs(int sig)
{
	(void)sig;
	g_glob->code = 128 + SIGQUIT;
	if (g_glob->stty == -42)
		printf("Quit: 3\n");
	rl_on_new_line();
	if (g_glob->stty != -42)
		rl_redisplay();
}

/***************************************************************************
Main function to give the right function to a specific signal
***************************************************************************/
void	signal_init(void)
{
	dup2(STDIN_FILENO, 42);
	signal(SIGINT, ctrl_c);
	signal(SIGQUIT, ctrl_bs);
}
