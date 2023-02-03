#include "../Includes/main.h"

void	built_in_pwd(t_element *elem)
{
	char	pwd[PATH_MAX];

	getcwd(pwd, sizeof(pwd));
	ft_putstr_fd(pwd, 1);
	ft_putstr_fd("\n", 1);
	set_status(0);
}
