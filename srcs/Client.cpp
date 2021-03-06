/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vico <vico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 11:49:20 by vico              #+#    #+#             */
/*   Updated: 2022/07/15 08:24:11 by vico             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

Client::Client() : _socket(0), _infos_client_size(sizeof(_infos_client)), _pass(""), _nickname(""), _username(""), _realname(""), _host(""), _invite(std::make_pair(false, ""))
{
	_register = false;
}

Client::~Client()
{
	std::cout << "client " << _socket << " disconnected" << std::endl;
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

bool				Client::isRegister() const
{
	return _register;
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
	if (realname[0] == ':')
		_realname = realname.substr(1);
	else
		_realname = realname;
}

void				Client::setHost(const std::string &host)
{
	_host = host;
}

void				Client::setRegister(const bool &mode)
{
	_register = mode;
}

std::string			Client::getIp() const
{
	return (inet_ntoa(_infos_client.sin_addr));
}

int				Client::getPort() const
{
	return ntohs(_infos_client.sin_port);
}
