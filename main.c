/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcappend <rcappend@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/18 18:11:34 by rcappend      #+#    #+#                 */
/*   Updated: 2021/01/19 11:32:27 by rcappend      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h> // weghalen

int			exit_error(char const *str)
{
	if (str)
		write(0, str, ft_strlen(str));
	return (EXIT_FAILURE);
}

int 		main(int argc, char **argv)
{	
	if (argc != 2)
		return (exit_error("Usage: cub3d <map>.cub\n"));
	double pos;

	return (EXIT_SUCCESS);
}