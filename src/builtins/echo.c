#include "main.h"

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = -1;
	if (!fd || !s)
		return ;
	while (s[++i] != '\0')
		write(fd, &s[i], 1);
}

int	flag_checking(char *command)
{
	int	j;

	j = 1;
	while (command[j] == 'n')
		j++;
	if (command[j] == '\0')
		return (1);
	return (0);
}

int	built_in_echo(t_element *elem)
{
	char	**command;
	int		flag;
	int		i;

	i = 1;
	command = elem->command->args;
	flag = 0;
	if ((command[i]) && (command[i][0] == '-'))
	{
		while (flag_checking(command[i]) == 1)
		{
			flag = 1;
			i++;
		}
	}
	while (command[i])
	{
		ft_putstr_fd(command[i], 1);
		if (command[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (!flag)
		ft_putstr_fd("\n", 1);
	return (set_status(0));
}
