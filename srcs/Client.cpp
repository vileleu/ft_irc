/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vico <vico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 11:49:20 by vico              #+#    #+#             */
/*   Updated: 2022/06/20 02:26:16 by vico             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

Client::Client() : _socket(0), _infos_client_size(sizeof(_infos_client))
{
}

Client::~Client()
{
}

int					Client::getSocket(void) const
{
	return _socket;
}

void				Client::setSocket(int socket)
{
	_socket = socket;
}

struct sockaddr_in	&Client::getInfos()
{
	return _infos_client;
}

socklen_t			&Client::getInfosSize()
{
	return _infos_client_size;
}

std::string			Client::getIp() const
{
	return (inet_ntoa(_infos_client.sin_addr));
}

int				Client::getPort() const
{
	return ntohs(_infos_client.sin_port);
}
