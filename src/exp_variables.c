/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_variables.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ergrigor < ergrigor@student.42yerevan.am > +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 19:40:45 by ergrigor          #+#    #+#             */
/*   Updated: 2022/11/14 15:17:09 by ergrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	is_var_cmd(char *args)
{
	int	j;

	j = 0;
	if (!args)
		return (1);
	while (args[j])
	{
		if (args[j] == '\'')
			while (args && args[++j] != '\'')
				;
		if (args[j] == '\0')
			return (1);
		if (args[j] == '$' && args[j + 1] != ' '
			&& args[j + 1] != '\0')
			return (0);
		else
			j++;
	}
	return (1);
}

int	is_var(char **args)
{
	int	i;
	int	j;

	i = 0;
	if (!args)
		return (1);
	while (args[i])
	{
		j = 0;
		while (args[i][j])
		{
			if (args[i][j] == '\'')
				while (args && args[i][++j] != '\'')
					;
			if (args[i][j] == '\0')
				break ;
			if (args[i][j] == '$' && args[i][j + 1] != ' '
					&& args[i][j + 1] != '\0')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

void	get_var_env_value(t_env *env, char **name)
{
	t_env	*ptr;

	ptr = env;
	while (ptr)
	{
		if (ft_strncmp(ptr->val_name, *name, ft_strlen(*name)) == 0)
			break ;
		else
			ptr = ptr->next;
	}
	free(*name);
	if (ptr && ft_strncmp(ptr->val_name, *name, ft_strlen(*name)) == 0)
		*name = ft_strdup(ptr->val_value);
	else
		*name = ft_strdup("");
}

void	change_var(t_env *env, char **args, int i, int *j)
{
	char	*name;
	char	*f_arg;
	char	*tmp;
	int		x;

	x = *j;
	while (args[i][x] && args[i][x] != ' '
		&& args[i][x] != '"' && args[i][x] != '\'')
		x++;
	if (*j != 0)
		f_arg = ft_substr(args[i], 0, *j);
	else
		f_arg = ft_calloc(0, sizeof(char *));
	//(*j)++;
	name = get_env_value(env, args[i], j);
	//printf("-->%s<--\n", name);
	f_arg = ft_free_strjoin(f_arg, name);
	tmp = ft_substr(args[i], x, (ft_strlen(args[i]) - x - 1));
	f_arg = ft_free_strjoin(f_arg, tmp);
	free(tmp);
	free(name);
	free(args[i]);
	args[i] = ft_strdup(f_arg);
	free(f_arg);
	// printf("%s\n",args[i]);
	// exit(0);
}

void	get_var(t_env *env, t_command *cmd)
{
	int		i;
	int		j;

	i = 0;
	while (cmd->args && cmd->args[i])
	{
		j = 0;
		while (cmd->args[i][j])
		{
			if (cmd->args[i][j] == '\'')
			{
				while (cmd->args && cmd->args[i][++j] != '\'')
					;
				j++;
			}
			if (cmd->args[i][j] != '\0' && cmd->args[i][j] == '$' && (cmd->args[i][j + 1] != ' '
					|| cmd->args[i][j + 1] != '\0'))
				change_var(env, cmd->args, i, &j);
				// printf("\ngago\n");
			if (cmd->args[i][j] == '\0')
				break ;
			j++;
		}
		i++;
	}
}

void	get_new_args(char **new, t_command *command)
{
	int		i;
	int		new_i;
	int		args_i;
	char	**new_args;

	args_i = 1;
	new_i = 0;
	i = 0;
	while (new[new_i])
		new_i++;
	while (command->args[args_i])
		args_i++;
	new_args = ft_calloc((1 + new_i + args_i), sizeof(char *));
	args_i = 1;
	new_i = 0;
	while (new[new_i])
		new_args[i++] = ft_strdup(new[new_i++]);
	//printf("GAGO\n");
	free(command->args[0]);
	while (command->args[args_i])
	{
		new_args[i++] = ft_strdup(command->args[args_i]);
		free(command->args[args_i++]);
	}
	free(command->args);
	command->args = new_args;
}

void	join_option(t_command *command)
{
	int		i;
	int		j;
	char	**new;

	i = 0;
	while (command->args[0][i])
	{
		if (command->args[0][i] == ' ')
		{
			new = ft_split(command->args[0], ' ');
			get_new_args(new, command);
			break ;
		}
		else if (command->args[0][i] == '\'')
		{
			new = ft_split(command->args[0], '\'');
			get_new_args(new, command);
			break ;
		}
		else
			i++;
	}
}

void	remove_option(t_command *command)
{
	int		i;
	char	*new_cmd;

	i = 0;
	while (command->cmd[i] && command->cmd[i] != ' ')
		i++;
	new_cmd = ft_substr(command->cmd, 0, i);
	free(command->cmd);
	command->cmd = ft_strdup(new_cmd);
	free(new_cmd);
}

char	*get_env_value(t_env *env, char *str, int *i)
{
	char	*tmp;
	t_env	*ptr;
	int		j;

	j = *i;
	ptr = env;
	while (str[j] && str[j] != ' ' && str[j] != '\0' && str[j] != '\'')
		j++;
	int a = *i + 1;
	tmp = ft_substr(str, a, (j - (*i) - 1));
	
	//printf("\n\n%s\n\n", tmp);
	*i = j;
	while (ptr)
	{
		if (ft_strcmp(ptr->val_name, tmp) == 0)
			break ;
		if (ptr->next == NULL)
		{
			ptr = NULL;
			break ;
		}
		ptr = ptr->next;
	}
	if (ptr == NULL)
		return (free(tmp), ft_strdup(""));
	return (free(tmp), ft_strdup(ptr->val_value));
}

char	*change_var_cmd(char *str, int *i, t_env *env)
{
	// char	*tmp;
	// char	*tmp2;
	// char	*tmp3;
	// int		j;
	
	// tmp3 = 0x0;
	// if (*i != 0)
	// {	
	// 	tmp3 = ft_substr(str, 0, (*i));
	// 	printf("%s\n", tmp3);
	// }
	// while (str && str[*i])
	// {
	// 	if (str[(*i)] == '$')
	// 		tmp = get_env_value(env, str, i);
	// 	if (str [*i] == '\0')
	// 	{
	// 		if(tmp3)
	// 		{
	// 			tmp3 = ft_free_strjoin(tmp3, tmp);
	// 			return ( tmp3);
	// 		}
	// 		return (tmp);
	// 	}
	// 	else
	// 	{
	// 		if(tmp3)
	// 			tmp3 = ft_free_strjoin(tmp3, tmp);
	// 		j = *i;
	// 		while (str[j])
	// 			j++;
	// 		tmp2 = ft_substr(str, (*i), (j) - (*i));
	// 		*i = j;
	// 		if(tmp3)
	// 		{
	// 			tmp3 = ft_free_strjoin(tmp3, tmp2);
	// 			return (free(tmp2), free(tmp), tmp3);
	// 		}
	// 		tmp = ft_free_strjoin(tmp, tmp2);
	// 		return (free(tmp2), tmp);
	// 	}
	// 	(*i)++;
	// }
	// return (NULL);
	char	*start;
	char	*name;
	char	*end;
	char	*tmp;
	int		j;
	
	start = 0x0;
	end = 0x0;
	if (*i != 0)
		start = ft_substr(str, 0, *i);
	name = get_env_value(env, str, i);
	printf("%s\n", name);
	if (str[*i] == '\0')
	{
		start = ft_free_strjoin(start, name);
		return(free(name), start);
	}
	else
	{
		j = *i;
		while(str[j])
			j++;
		end = ft_substr(str, *i, (j - *i));
		printf("end --> %s\n", end);
		start = ft_free_strjoin(start, name);
		tmp = ft_strjoin(start, end);
		free(start);
		if (end)
			free(end);
		free(name);
		*i = j;
		printf("-->%s<--\n", tmp);
		return(tmp);
	}
}

void	get_var_cmd(t_env *env, t_command *cmd)
{
	int		i;
	char	*command;

	command = ft_strdup(cmd->cmd);
	free(cmd->cmd);
	i = 0;
	while (command && command[i])
	{
		while (command[i] != '$' && command[i] != '\'')
			i++;
		if(command[i] == '\'')
		{
			i++;
			while(command[i++] != '\'')
				;
		}
		else if (command[i] == '$' && command[i + 1] != ' '
			&& command[i + 1] != '\0' && command[i + 1] != '\'')
			cmd->cmd = change_var_cmd(command, &i, env);
		else
			i++;
	}
}

void	get_variables(t_env *env, t_element **elem)
{
	int	i;

	i = 0;
	while (elem[i])
	{
		if (is_var_cmd(elem[i]->command->cmd) != 0 && is_var(elem[i]->command->args) != 0)
			i++;
		else
		{
			if (is_var_cmd(elem[i]->command->cmd) == 0)
			{
				get_var_cmd(env, elem[i]->command);
				//remove_option(elem[i]->command);
			}
			if (is_var(elem[i]->command->args) == 0)
			{
				// printf("Check\n");
				get_var(env, elem[i]->command);
				join_option(elem[i]->command);
			}
			i++;
		}
	}
}
