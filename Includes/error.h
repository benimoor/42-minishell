/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ergrigor < ergrigor@student.42yerevan.am > +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 21:40:08 by ergrigor          #+#    #+#             */
/*   Updated: 2022/10/09 14:39:08 by ergrigor         ###   ########.fr       */
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