/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruthann <pruth@student.21-school.ru>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 15:59:59 by pruthann          #+#    #+#             */
/*   Updated: 2021/01/25 12:37:39 by pruthann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# include <unistd.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif

int		join_checker(char **buf, char **rem, char **line, int i);
int		main_checks(char **buf, char **rem, char **line);
int		quantity_checker(char **buf, char **rem, int quantity);
size_t	ft_strlen(const char *s);
int		ft_strjoin_free(char **s1, char *s2);
void	ft_strcpy(char **dst, char *src, int a);
int		check_endl(char *buf);
int		get_next_line(int fd, char **line);

#endif
