/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hd_utils1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ergrigor < ergrigor@student.42yerevan.am > +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 18:08:06 by ergrigor          #+#    #+#             */
/*   Updated: 2023/01/21 00:30:35 by ergrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	concate_quot(t_token **token, char *tmp, char **res)
{
	char	*tmp2;
	int		flag;
	t_token	*ptr;

	ptr = *token;
	flag = ptr->type;
	tmp2 = ft_strdup("");
	while (ptr->next->type != flag)
	{
		tmp = ft_substr(ptr->next->str, 0, ptr->next->len);
		tmp2 = ft_free_strjoin(tmp2, tmp);
		free(tmp);
		ptr = ptr->next;
	}
	ptr = ptr->next->next;
	if (flag == DOUBLE_QUOTES)
	{
		tmp = remake_var_line(tmp2, ft_strlen(tmp2));
		free(tmp2);
	}
	else
		tmp = tmp2;
	*res = ft_free_strjoin(*res, tmp);
	free(tmp);
	*token = ptr;
}

void	concate_word(t_token **token, char *tmp, char **res)
{
	t_token	*ptr;

	ptr = *token;
	tmp = remake_var_line(ptr->str, ptr->len);
	*res = ft_free_strjoin(*res, tmp);
	free(tmp);
	ptr = ptr->next;
	*token = ptr;
}

char	*concate_string(t_token **token)
{
	t_token	*ptr;
	char	*res;
	char	*tmp;

	ptr = *token;
	tmp = NULL;
	res = ft_strdup("");
	if (ptr && !(ptr->type != SPACE_TK && ptr->type != PIPE
			&& !(ptr->type == HERE_DOC || ptr->type == RED_OUTPUT_APP
				|| ptr->type == RED_OUTPUT || ptr->type == RED_INPUT)))
		return (free(res), NULL);
	while (ptr && ptr->type != SPACE_TK && ptr->type != PIPE
		&& !(ptr->type == HERE_DOC || ptr->type == RED_OUTPUT_APP
			|| ptr->type == RED_OUTPUT || ptr->type == RED_INPUT))
	{
		if (ptr->type == WORD)
			concate_word(&ptr, tmp, &res);
		else if (ptr->type == DOUBLE_QUOTES || ptr->type == SINGLE_QUOTES)
			concate_quot(&ptr, tmp, &res);
	}
	*token = ptr;
	return (res);
}

char	*get_dollar(void)
{
	t_env	*tmp;

	tmp = g_lobal->env;
	while (tmp)
	{
		if (ft_strlen(tmp->val_name) == 1
			&& ft_strncmp(tmp->val_name, "$", 1) == 0)
			return (ft_strdup(tmp->val_value));
		tmp = tmp->next;
	}
	return (NULL);
}

char	*get_doc_name(void)
{
	char	*index;
	char	*tmp;
	char	*name;

	tmp = get_dollar();
	index = ft_itoa(g_lobal->hd_count);
	name = ft_strdup("/tmp/.mini_hd_");
	name = ft_free_strjoin(name, tmp);
	name = ft_free_strjoin(name, "_");
	name = ft_free_strjoin(name, index);
	free(index);
	free(tmp);
	return (name);
}
