/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhit <mkhit@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 21:40:08 by ergrigor          #+#    #+#             */
/*   Updated: 2023/02/05 21:41:36 by mkhit            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# define QUOTE_ERR "minishell: unexpected EOF while looking for matching \"'\"\n"
# define DB_QUOTE_ERR "minishell: unexpected EOF while\
		looking for matching `\"`\n"
# define L_SCOPE_ERR "minishell: unexpected EOF while looking for matching \"(\"\n"
# define R_SCOPE_ERR "minishell: unexpected EOF while looking for matching \")\"\n"

#endif