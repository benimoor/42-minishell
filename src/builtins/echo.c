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

int	built_in_echo(t_element *elem)
{
	char	**command;
	int		flag;
	int		i;

	i = 1;
	command = elem->command->args;
	flag = 0;
	if ((command[1]) && (ft_strcmp(command[i], "-n") == 0))
	{
		flag = 1;
		i++;
		if (!command[i])
			return (0);
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
	return (0);
}
