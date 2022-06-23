/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vico <vico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 02:56:08 by vico              #+#    #+#             */
/*   Updated: 2022/06/24 00:58:47 by vico             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.hpp"

std::string	deleteLinefeed(std::string modif)
{
	size_t	i(0);
	
	while ((i = modif.find('\r')) != std::string::npos)
	{
		modif.erase(i, 1);
	}
	return modif;
}
