/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vico <vico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 02:56:08 by vico              #+#    #+#             */
/*   Updated: 2022/06/19 21:33:55 by vico             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.hpp"

std::string	get_ip()
{
	char			hostname[128];
	std::string		ip;

	gethostname(hostname, 127);
	struct hostent*	host(gethostbyname(hostname));
	if (!host || host->h_addrtype != AF_INET || !host->h_addr_list[0])
		return ("");
	ip = inet_ntoa(*(reinterpret_cast<struct in_addr *>(host->h_addr_list)));
	return (ip);
}

int			error_msg(std::string msg)
{
	std::cout << "ERROR: " << msg << std::endl;
	return -1;
}
