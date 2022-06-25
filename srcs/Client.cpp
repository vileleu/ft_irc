/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vico <vico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 11:49:20 by vico              #+#    #+#             */
/*   Updated: 2022/06/25 03:59:16 by vico             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

Client::Client() : _socket(0), _infos_client_size(sizeof(_infos_client)), _pass(""), _nickname(""), _username(""), _realname(""), _host("")
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

std::string			Client::getPass() const
{
	return _pass;
}

std::string			Client::getNickname() const
{
	return _nickname;
}

std::string			Client::getUsername() const
{
	return _username;
}

std::string			Client::getRealname() const
{
	return _realname;
}

std::string			Client::getHost() const
{
	return _host;
}

void				Client::setPass(const std::string &pass)
{
	_pass = pass;
}

void				Client::setNickname(const std::string &nickname)
{
	_nickname = nickname;
}

void				Client::setUsername(const std::string &username)
{
	_username = username;
}

void				Client::setRealname(const std::string &realname)
{
	_realname = realname;
}

void				Client::setHost(const std::string &host)
{
	_host = host;
}

std::string			Client::getIp() const
{
	return (inet_ntoa(_infos_client.sin_addr));
}

int				Client::getPort() const
{
	return ntohs(_infos_client.sin_port);
}

std::ostream		&operator<<(std::ostream &flux, Client const& client)
{
    flux << client.getNickname() << "!" << client.getUsername() << "@" << client.getHost();
    return flux;
}
