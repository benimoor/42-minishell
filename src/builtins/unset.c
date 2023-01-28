#include "../Includes/main.h"

void	unset_error_log(char *command)
{
	ft_putstr_fd("Say - Hello myalmo >: unset: `", 2);
	ft_putstr_fd(command, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

t_env	*get_prev_node(t_env *head, char *name)
{
	t_env	*ptr;
	t_env	*prev;
	int		first_flag;

	ptr = head;
	prev = NULL;
	first_flag = 1;
	while (ptr)
	{
		if (ft_strcmp(ptr->val_name, name) == 0)
			return (prev);
		prev = ptr;
		ptr = ptr->next;
	}
	return (NULL);
}

int	do_unset(char *command)
{
	t_env	*node;
	t_env	*prev;

	node = env_exist(g_lobal->env, command);
	if (!node)
		return (0);
	prev = get_prev_node(g_lobal->env, command);
	if (prev != NULL)
		prev->next = node->next;
	free(node);
	return (0);
}

int	built_in_unset(t_element *elem)
{
	char	**command;
	int		i;

	i = 0;
	command = elem->command->args;
	while (command[++i])
	{
		if (command_parsing(command[i]) == 0)
			unset_error_log(command[i]);
		else
			do_unset(command[i]);
	}
	return (0);
}
