#include "../Includes/main.h"

static int ft_strcheck(char *s1, char *s2)
{
    int i;

    i = 0;
    if (ft_strlen(s1) != ft_strlen(s2) || !s1 || !s2)
        return (-1);
    while (s1[i] && s2[i])
    {
        if (s1[i] != s2[i])
            return(-1);
        i++;
    }
    return (0);
}

void ft_unset(t_env **env, char *var_name)
{
    t_env *curr_env;
    int i;
   
    if (!var_name)
        return ;
    curr_env = *env;
    while (curr_env) 
    {
        if (ft_strcheck(curr_env->val_name, var_name) == 0)
        {
            curr_env->prev->next = curr_env->next;
            free(curr_env);
            return ;
        }
        curr_env = curr_env->next;
    }
}