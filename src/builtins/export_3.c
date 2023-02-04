#include "../Includes/main.h"

void	swap_nodes_2(t_env *prev, t_env *start, t_env *last)
{
	t_env	*tmp;

	tmp = NULL;
	if (last->next)
	{
		tmp = last->next;
		prev->next = last;
		last->next = start;
		start->next = tmp;
	}
	else
	{
		prev->next = last;
		last->next = start;
		start->next = NULL;
	}
}

void	swap_nodes(t_env *prev, t_env *start, t_env *last, t_env ***head)
{
	if (!prev)
	{
		if (last->next)
		{
			start->next = last->next;
			last->next = start;
			**head = last;
		}
		else
		{
			start->next = NULL;
			last->next = start;
			**head = last;
		}
	}
	else if (prev)
	{
		swap_nodes_2(prev, start, last);
	}
}

void	sort_env(t_env	**head)
{
	t_env	*start;
	t_env	*prev;
	int		bouble;

	start = *head;
	prev = NULL;
	bouble = 0;
	while (start->next)
	{
		if (ft_strcmp(start->val_name, start->next->val_name) > 0)
		{
			swap_nodes(prev, start, start->next, &head);
			bouble = 1;
		}
		prev = start;
		if (start->next)
			start = start->next;
		if (!(start->next) && (bouble == 1))
		{
			prev = NULL;
			bouble = 0;
			start = *head;
		}
	}
}

t_env	*env_exist(t_env *head, char *name)
{
	t_env	*ptr;

	ptr = head;
	while (ptr)
	{
		if (ft_strcmp(ptr->val_name, name) == 0)
			return (ptr);
		ptr = ptr->next;
	}
	return (NULL);
}

int	export_with_equal(char *name, char *command, t_env *new_node, t_env *node)
{
	if (ft_strcmp(command, "=") == 0)
	{
		export_error_log ("=");
		return (0);
	}
	if (!node)
	{
		new_node->val_name = name;
		new_node->val_value = get_val(command);
		new_node->hidden = 0;
		new_node->next = NULL;
		ft_lstadd_back_env(&g_lobal->env, new_node);
	}
	else if ((ft_strchr(command, '=') - 1)[0] == '+')
	{
		node->val_value = ft_strjoin(node->val_value, get_val(command));
	}
	else
	{
		node->val_value = get_val(command);
	}
	if (node)
		node->hidden = 0;
	return (1);
}
