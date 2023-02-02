#include "../Includes/main.h"

void	export_error_log(char *command)
{
	ft_putstr_fd(get_val_value("PS1"), 2);
	ft_putstr_fd(": export: `", 2);
	ft_putstr_fd(command, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

int	command_parsing(char *command)
{
	int	i;

	i = 0;
	while (command[i])
	{
		if (i == 0)
		{
			if ((ft_isalpha(command[i]) == 1) || command[i] == '_')
				i++;
			else
				return (0);
			if (!command[i])
				return (1);
		}
		if (command[i] == '+' && command[i + 1] == '=')
			return (1);
		if (command [i] == '=')
			return (1);
		if ((ft_isalpha(command[i]) == 1) || (command[i] == ' ')
			|| (ft_isdigit(command[i]) == 1) || (command[i] == '_'))
			i++;
		else
			return (0);
	}
	return (1);
}

void	print_exported_env(t_env *env)
{
	t_env	*ptr;

	ptr = env;
	while (ptr)
	{
		if (ptr->hidden != 1)
		{
			if (ptr->val_value != NULL)
				printf("declare -x %s=\"%s\"\n", ptr->val_name, ptr->val_value);
			else
				printf("declare -x %s\n", ptr->val_name);
		}
		ptr = ptr->next;
	}
}

void	ft_lstadd_back_env(t_env **lst, t_env *new)
{
	t_env	*iter;

	if (lst == NULL || new == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	iter = *lst;
	while (iter -> next != NULL)
		iter = iter -> next;
	iter -> next = new;
}

t_env	*ft_lstnew_env(char *val_name, char *val_value, int hidden)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->val_name = val_name;
	new->val_value = val_value;
	new->hidden = hidden;
	new->next = NULL;
	return (new);
}
