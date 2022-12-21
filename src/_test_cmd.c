#include "main.h"

t_element *_cmd()
{
   


  // ===== test cmd 1  e.g. ls -l 
    t_command *cmd1;
    cmd1 = malloc(sizeof(t_command));
    char name[] = "ls";
    char *args[] = {"ls", "-l"};
    cmd1->cmd = name;
    cmd1->args = args;

    t_element *__cmd1;
    __cmd1 = malloc(sizeof(t_element));
    __cmd1->command = cmd1;
    __cmd1->type = 1;

    //=========================
    // type  1 => cmd 
    //=========================

//   // ===== test cmd 2  e.g. cat -e 
//     t_command *cmd2;
//     cmd2 = malloc(sizeof(t_command));
//     char name1[] = "cat";
//     char *args1[] = {"cat", "-e"};
//     cmd2->cmd = name1;
//     cmd2->args = args1;
    
//     t_element *__cmd2;
//     __cmd2 = malloc(sizeof(t_element));
//     __cmd2->command = cmd2;

}