#include "../Includes/main.h"

void	export_without_equal(char *name, t_env *new_node)
{
	new_node->val_name = get_val_name(name);
	new_node->val_value = NULL;
	new_node->hidden = 2;
	new_node->next = NULL;
	ft_lstadd_back_env(&g_lobal->env, new_node);
}

int	export_with_arg(char *command)
{
	t_env	*node;
	t_env	*new_node;
	char	*name;

	name = get_val_name(command);
	if (name[ft_strlen(name) - 1] == '+')
		name[ft_strlen(name) - 1] = '\0';
	node = env_exist(g_lobal->env, name);
	new_node = malloc(sizeof(t_env));
	if (command_parsing(command) == 0)
	{
		export_error_log(command);
		return (1);
	}
	if (ft_strchr(command, '=') != NULL)
	{
		if (!export_with_equal(name, command, new_node, node))
			return (1);
	}
	else
	{
		if (!node)
			export_without_equal(name, new_node);
	}
	return (0);
}

int	do_export(char **command, t_env	*head)
{
	int		i;
	t_env	*tmp;

	i = 0;
	tmp = NULL;
	if (!command[1])
	{
		sort_env(&head);
		tmp = head;
		print_exported_env(tmp);
	}
	else
	{
		while (command[++i])
		{
			if (export_with_arg(command[i]) == 1)
			{
				return (set_status(1));
			}
		}
	}
	return (set_status(0));
}

void	built_in_export(t_element *elem)
{
	char	**command;
	t_env	*head;
	t_env	*node;
	t_env	*tmp;

	tmp = g_lobal->env;
	head = ft_lstnew_env(tmp->val_name, tmp->val_value, tmp->hidden);
	tmp = tmp->next;
	while (tmp)
	{
		node = ft_lstnew_env(tmp->val_name, tmp->val_value, tmp->hidden);
		ft_lstadd_back_env(&head, node);
		tmp = tmp->next;
	}
	node->next = NULL;
	command = elem->command->args;
	if (do_export(command, head) == 1)
		return ;
}
