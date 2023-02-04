#include "../Includes/main.h"
// if $PWD or $OLDPWD is unseted there will be hidden in env after cd

int	save_old_pwd(char *old_pwd_value)
{
	char	new_pwd[PATH_MAX];
	char	*ptr_pwd;

	getcwd(new_pwd, sizeof(new_pwd));
	ptr_pwd = ft_strdup(new_pwd);
	if (ptr_pwd != NULL)
	{
		if (old_pwd_value != NULL)
		{
			if (env_exist(g_lobal->env, "OLDPWD") != NULL)
				add_env_value("OLDPWD", old_pwd_value,
					env_exist(g_lobal->env, "OLDPWD")->hidden, &(g_lobal)->env);
			else
				add_env_value("OLDPWD", old_pwd_value, 1, &(g_lobal)->env);
		}
		if (env_exist(g_lobal->env, "PWD") != NULL)
			add_env_value("PWD", ptr_pwd,
				env_exist(g_lobal->env, "PWD")->hidden, &(g_lobal)->env);
		else
			add_env_value("PWD", ptr_pwd, 1, &(g_lobal)->env);
	}
	free(ptr_pwd);
	return (set_status(0));
}

void	cd_relative(char *relative, char *old_path)
{
	char	*path;
	char	*tmp;
	char	path_t[PATH_MAX];

	getcwd(path_t, sizeof(path_t));
	path = ft_strdup(path_t);
	if (path != NULL)
	{
		tmp = ft_strdup(path);
		free(path);
		path = ft_strjoin(tmp, "/");
		free(tmp);
		path = ft_free_strjoin(path, relative);
		if (path[ft_strlen(path) - 1] == '/')
			path[ft_strlen(path) - 1] = '\0';
		if (chdir(path) != 0)
			print_cd_err(relative);
		else
			save_old_pwd(old_path);
	}
	free (path);
}

void	cd_no_arg(char *old_pwd)
{
	t_env	*home;

	home = env_exist(g_lobal->env, "HOME");
	if (home != NULL)
	{
		if (chdir(home->val_value) != 0)
			print_cd_err(home->val_value);
		else
			save_old_pwd(old_pwd);
	}
	else
	{
		ft_putstr_fd(get_val_value("PS1"), 2);
		ft_putstr_fd("cd: HOME not set\n", 2);
		set_status (1);
	}
}

void	cd_absolute(char *command, char *old_pwd_value)
{
	if (ft_strlen(command) > 2
		&& command[ft_strlen(command) - 1] == '/')
		command[ft_strlen(command) - 1] = '\0';
	if (chdir(command) != 0)
		print_cd_err(command);
	else
		save_old_pwd(old_pwd_value);
}

void	built_in_cd(t_element *elem)
{
	char	**command;
	char	*old_pwd_value;
	char	pwd[PATH_MAX];

	command = elem->command->args;
	getcwd(pwd, sizeof(pwd));
	old_pwd_value = ft_strdup(pwd);
	if ((command[1] != NULL) && (command[2] != NULL))
		cd_many_arg_err();
	else if (!(command[1]) || (command[1][0] == '~' && !(command[1][1])))
		cd_no_arg(old_pwd_value);
	else
	{
		if (command[1][0] == '/')
			cd_absolute(command[1], old_pwd_value);
		else
			cd_relative (command[1], old_pwd_value);
	}
	free (old_pwd_value);
}
