/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vico <vico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 02:56:08 by vico              #+#    #+#             */
/*   Updated: 2022/06/24 03:32:03 by vico             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.hpp"

std::string	deleteChar(std::string modif, char c)
{
	size_t	i(0);
	
	while ((i = modif.find(c)) != std::string::npos)
	{
		modif.erase(i, 1);
	}
	return modif;
}

std::string	replaceChar(std::string modif, char origin, char replace)
{
	size_t	i(0);
	char	s[2];
	
	s[0] = replace;
	s[1] = '\0';
	while ((i = modif.find(origin)) != std::string::npos)
	{
		modif.replace(i, 1, s);
	}
	return modif;
}
