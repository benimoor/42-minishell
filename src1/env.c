#include "../Includes/main.h"

int get_env_var_count(t_env *l_env)
{
    int l;

    l = 0;
    while (l_env->next)
    {
        l++;
        l_env = l_env->next;
    }
    return l + 1;
}


char *get_line_env(t_env *l_env)
{
    char *line;
    int i;
    int j;
    int name;
    int value;

    name = ft_strlen(l_env->val_name);
    value = ft_strlen(l_env->val_value);
    i = 0;
    line = malloc(name + value + 2);
    if (!line)
        return NULL;
    while (i < name)
    {
        line[i] = l_env->val_name[i];
        i++;
    }
    line[i] = '=';
    i++;
    j = 0;
    while (j < value)
    {
        
        line[i] = l_env->val_value[j];
        i++;
        j++;
    }
    line[i] = '\0';
    return line;
}

// get the char ** from linked list 
char **get_arr_env(t_env *l_env)
{
    char **env;
    int l;
    int i;

    l = get_env_var_count(l_env);
    env = (char **)malloc((1 + l) * sizeof(char *));
    i = 0;
    while (i < l)
    {
        env[i] = get_line_env(l_env);
        l_env = l_env->next;
        i++;
    }
    env[i] = NULL;
    return env;
}