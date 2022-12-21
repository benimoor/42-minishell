#include "../Includes/main.h"

static char *get_val_name(char *env_line)
{
    int i;
    char *value;

    i = 0;
    while (env_line[i] != '=' && env_line[i] != '\0')
        i++;
    value = malloc(i + 1);
    if (!value)
        return (NULL);
    value[i] = '\0';
    i--;
    while(i >= 0)
    {
        value[i] = env_line[i];
        i--;
    }
    return value;
}

static char *get_val(char *env_line)
{
    int i;
    int tmp;
    char *value;

    i = 0;
    while (env_line[i] != '=')
        i++;
    tmp = i;
    i++;
    while (env_line[i] != '\0')
        i++;
    value = malloc(i - tmp);
    if (!value)
        return NULL;
    while (i > tmp)
    {
        value[i - tmp - 1] = env_line[i];
        i--;
    }
    return value;
}


//get the linked list from char** ENV
t_env *pars_env(char **env)
{
    t_env *list_env;
    t_env *env_start;
    int index;

    list_env = malloc(sizeof(t_env));
    env_start = list_env;
    if (!list_env)
        return NULL;
    index = 0;
    while (env[index] != NULL)
    {
        list_env->val_name = get_val_name(env[index]);
        list_env->val_value = get_val(env[index]);
        if (env[index + 1] == NULL)
        {
            list_env->next = NULL;
            break ;
        }
        list_env->next = malloc(sizeof(t_env));
        if (!list_env->next)
            return NULL;
        list_env->next->prev = list_env;
        list_env = list_env->next;
        index++;
    }
    return env_start;
}
//++++++++++++++++++++++++++++++++++++++++++++




// int main(int argc, char **argv, char **env_main)
// {
//     t_env *env;
//     char **environ;
//     if (argc != 1)
//         error_exit(0);
//     // parse the env and get the linked list
//     env = pars_env(env_main); //  # done
//     // unset env variable builtin 
//     //ft_unset(&env, "TERM"); # done
    
//     //export builtin if not 2-rd argument need to just print it writen but need to know for arguments
//     // ft_export(&env, "TERM=world"); # need to sort in priniting, for now pass, need to undersund how to sort linked arr but need it only in export



//     // parse back and get the 2 dimensional array
//     // environ = get_arr_env(env);  # done



//     // just for tests
//     // int i;

//     // i = 0;
//     // while (environ[i])
//     // {
//     //     printf("%s\n", environ[i]);
//     //     i++;
//     // }
// }
   
