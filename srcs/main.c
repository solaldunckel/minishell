/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/28 11:18:12 by sdunckel          #+#    #+#             */
/*   Updated: 2020/01/03 10:34:48 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_prompt(t_minishell *minishell)
{
	ft_printf("" BOLDGREEN "➜ " RESET BOLDCYAN " %s " RESET, minishell->curdir);
}

char	**free_split(char **split)
{
	int		i;

	i = 0;
	while (split[i])
	{
		ft_strdel(&split[i]);
		i++;
	}
	free(split);
	split = NULL;
	return (split);
}

void	replace_env(t_minishell *minishell, char **split)
{
	int		i;
	char 	*env;
	char	*new;
	char 	*to_free;
	char 	**tmp;

	new = ft_strdup("");
	to_free = *split;
	*split = new;
	free(to_free);
}

void	process_split(t_minishell *minishell)
{
	int		i;

	i = 1;
	while (minishell->split[i])
	{
		if (minishell->split[i][0] == '$' && minishell->split[i][1])
			replace_env(minishell, &minishell->split[i]);
		i++;
	}
}

void	env_cmd(t_minishell *minishell)
{
	int		i;
	t_list	*tmp;
	char 	**lenv;

	i = 0;
	tmp = minishell->env_list;
	while (tmp)
	{
		lenv = tmp->content;
		ft_printf("%s=%s\n", lenv[0], lenv[1]);
		tmp = tmp->next;
	}
}

void	export_cmd(t_minishell *minishell)
{
	int		i;
	t_list	*tmp;
	char 	**lenv;
	char 	**tmp_split;

	i = 0;
	tmp = minishell->env_list;
	tmp_split = ft_split(minishell->split[1], '=');
	while (tmp)
	{
		lenv = tmp->content;
		if (ft_strequ(lenv[0], tmp_split[0]))
		{
			free(tmp_split[0]);
			free(lenv[1]);
			lenv[1] = tmp_split[1];
			return;
		}
		tmp = tmp->next;
	}
	free(tmp_split[0]);
	ft_lstadd_back(&minishell->env_list, ft_lstnew(tmp_split));
}

void	exec_commands(t_minishell *minishell, char *cmd)
{
	int		i;

	i = 0;
	minishell->split = ft_ssplit(cmd, " ");
	if (!minishell->split[i])
		return ;
	process_split(minishell);
	if (ft_strequ(minishell->split[i], ECHO_CMD))
		echo_cmd(minishell);
	else if (ft_strequ(minishell->split[i], EXIT_CMD))
		exit(0);
	else if (ft_strequ(minishell->split[i], CD_CMD))
		cd_cmd(minishell);
	else if (ft_strequ(minishell->split[i], PWD_CMD))
		pwd_cmd(minishell);
	else if (ft_strequ(minishell->split[i], ENV_CMD))
		env_cmd(minishell);
	else if (ft_strequ(minishell->split[i], EXPORT_CMD))
		export_cmd(minishell);
	else
		exec_prog(minishell);
	free_split(minishell->split);
}

void	wait_for_command(t_minishell *minishell)
{
	char 	**cmds;
	int		i;

	while (1)
	{
		print_prompt(minishell);
		if (get_next_line(0, &minishell->line))
		{
			i = 0;
			cmds = ft_split(minishell->line, ';');
			while (cmds[i])
			{
				exec_commands(minishell, cmds[i]);
				free(cmds[i]);
				i++;
			}
			free(cmds);
			free(minishell->line);
		}
	}
}

void	env_init(t_minishell *minishell, char **env)
{
	int		i;
	char	**tmp_split;

	i = 0;
	while (env[i])
	{
		tmp_split = ft_split(env[i], '=');
		ft_lstadd_back(&minishell->env_list, ft_lstnew(tmp_split));
		i++;
	}
}

char	*get_env(t_minishell *minishell, char *env)
{
	int		i;
	t_list	*tmp;
	char 	**lenv;

	i = 0;
	tmp = minishell->env_list;
	while (tmp)
	{
		lenv = tmp->content;
		if (ft_strequ(env, lenv[0]))
			return (lenv[1]);
		tmp = tmp->next;
	}
	return (NULL);
}

int		main(int argc, char **argv, char **env)
{
	t_minishell 	minishell;

	(void)argv;
	ft_bzero(&minishell, sizeof(t_minishell));
	ft_printf("\nMINISHELL 42 by sdunckel & haguerni\n\n");
	minishell.name = argv[0];
	minishell.curdir = getcwd(NULL, 0);
	env_init(&minishell, env);
	wait_for_command(&minishell);
	return (0);
}
