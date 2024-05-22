/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinda-si <dinda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 12:57:03 by dinda-si          #+#    #+#             */
/*   Updated: 2024/04/26 18:21:27 by dinda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

char	*get_next_line(int fd);
char	*ft_joinfree(char *str, char *buffer);
void	*ft_callocgetnextline(size_t mem, size_t size);
char	*ft_strjoingetnextline(char *str1, char *str2);
size_t	ft_strlengetnextline(const char *str, size_t sn);
void	bufferclean(char *buffer);

#endif