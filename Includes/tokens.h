/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ergrigor < ergrigor@student.42yerevan.am > +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 19:44:48 by ergrigor          #+#    #+#             */
/*   Updated: 2023/01/27 23:35:56 by ergrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENS_H
# define TOKENS_H

# define DOUBLE_QUOTES				0 // ""
# define SINGLE_QUOTES				1 // ''
# define L_SCOPE 					2 // (
# define R_SCOPE 					3 // )
# define RED_INPUT 					4 // <
# define RED_OUTPUT 				5 // >
# define RED_OUTPUT_APP 			6 // >>
# define HERE_DOC					7 // <<
# define PIPE 						8 // |
# define AND_OR 					9 // &&
# define OR_IF 						10 // ||
# define DOT_COMMA 					11 // ;
# define DB_DOT_COMMA 				12 // ;;
# define SPACE_TK					13 // ' '
# define WORD						14 // {a..Z}
# define ASTERIX					15 // *
# define VARIABLE_TK				16 // $...
# define PS1						"[KARGIN-Shell] $."
#endif