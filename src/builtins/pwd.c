#include "../Includes/main.h"

void	built_in_pwd(t_element *elem)
{
	char	pwd[PATH_MAX];

	if (getcwd(pwd, sizeof(pwd)))
	{
		ft_putstr_fd(pwd, 1);
		ft_putstr_fd("\n", 1);
	}
	else
		ft_putstr_fd("Error when calling getcwd", 2);
}
