#include "../Includes/main.h"

void	print_cd_err(char *path)
{
	ft_putstr_fd("Say - Hello myalmo > cd: ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
}

int	save_old_pwd(char *old_pwd)
{
	int		i;
	char	new_pwd[PATH_MAX];

	i = 0;
	getcwd(new_pwd, sizeof(new_pwd));
	add_env_value("OLD_PWD", old_pwd, 0, &(g_lobal)->env);
	add_env_value("PWD", new_pwd, 0, &(g_lobal)->env);
	return (0);
}

void	cd_relative(char *relative, char *old_path)
{
	int		i;
	char	*path;
	char	*tmp;

	i = 0;
	path = get_env_value(g_lobal->env, "$PWD", &i);
	tmp = ft_strdup(path);
	free (path);
	path = ft_strjoin(tmp, "/");
	free(tmp);
	path = ft_strjoin(path, relative);
	if (path[ft_strlen(path) - 1] == '/')
		path[ft_strlen(path) - 1] = '\0';
	if (chdir(path) != 0)
		print_cd_err(relative);
	else
		save_old_pwd(old_path);
	free (path);
}

void	cd_no_arg(char *old_pwd)
{
	char	*path;
	int		i;

	i = 0;
	path = get_env_value(g_lobal->env, "$HOME", &i);
	if (path)
	{
		chdir(path);
		save_old_pwd(old_pwd);
		free (path);
	}
	else
		ft_putstr_fd(" cd: HOME not set", 2);
}

void	built_in_cd(t_element *elem)
{
	char	**command;
	int		i;
	int		n;
	char	*old_pwd;

	i = 0;
	command = elem->command->args;
	old_pwd = get_env_value(g_lobal->env, "$PWD", &i);
	if (!(command[1]) || (command[1][0] == '~' && !(command[1][1])))
		cd_no_arg(old_pwd);
	else
	{
		if (command[1][0] == '/')
		{
			if (ft_strlen(command[1]) > 2
				&& command[1][ft_strlen(command[1]) - 1] == '/')
				command[1][ft_strlen(command[1]) - 1] = '\0';
			if (chdir(command[1]) != 0)
				print_cd_err(command[1]);
			else
				save_old_pwd(old_pwd);
		}
		else
			cd_relative (command[1], old_pwd);
	}
}
