/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vico <vico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 03:07:45 by vico              #+#    #+#             */
/*   Updated: 2022/07/03 03:04:07 by vico             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server() : _port(0), _socket(0), _password(""), _host("localhost"), _loop(true), _max_client(FD_SETSIZE), _select(0)
{
}

Server::~Server()
{
	std::cout << "close Server ..." << std::endl;
	for (size_t i(0); i < _list_client.size(); i++)
	{
		std::cout << "delete client " << _list_client[i]->getSocket() << std::endl;
		FD_CLR(_list_client[i]->getSocket(), &_read_fds);
		close(_list_client[i]->getSocket());
		delete _list_client[i];
	}
	close(_socket);
}

/*
** ↓ PRIVATE ↓
*/

void			Server::addClient()
{
	_list_client.push_back(new Client);
	_list_client[_list_client.size() - 1]->setSocket(accept(_socket, reinterpret_cast<struct sockaddr *>(&(_list_client[_list_client.size() - 1]->getInfos())), &(_list_client[_list_client.size() - 1]->getInfosSize())));
	if (_list_client[_list_client.size() - 1]->getSocket() == -1)
	{
		errorServer("accept");
		return ;	
	}
	FD_SET(_list_client[_list_client.size() - 1]->getSocket(), &_read_fds);
	std::cout << "Client connected: " << _list_client[_list_client.size() - 1]->getSocket() << " from " << _list_client[_list_client.size() - 1]->getIp() << ":" << _list_client[_list_client.size() - 1]->getPort() << "\n" << std::endl;
}

void			Server::receiveText(const int i)
{
	char	buf[4096];

	memset(buf, 0, 4096);
	int bytes = recv(i, buf, 4096, 0);

	if (bytes > 0)
	{
		std::cout << "recv socket " << i << " message --> \033[1;35m" << std::string(deleteChar(buf, '\r')) << "\033[0m" << std::endl;
		for (std::vector<Client *>::iterator it(_list_client.begin()); it != _list_client.end(); it++)
		{
			if ((*it)->getSocket() == i)
			{
				_command.init(deleteChar(buf, '\r'), *it);
				break ;
			}
		}
		_command.parsing();
		std::map<int, std::string>	to_send(_command.getTosend());

		for (std::map<int, std::string>::iterator it(to_send.begin()); it != to_send.end(); it++)
		{
			std::cout << "send socket " << (*it).first << " message --> \033[1;35m" << (*it).second << "\033[0m";
			send((*it).first, (*it).second.c_str(), (*it).second.size(), 0);
		}
		std::cout << std::endl;
		_command.clean();
	}
}

void			Server::checkFds()
{
	fd_set	copy = _read_fds;

	_select = select(_max_client, &copy, NULL, NULL, NULL);
	for (int i(0); i < (_max_client) && (_select); i++)
	{
		if (FD_ISSET(i, &copy))
		{
			if (i == _socket)
			{
				addClient();
				_select--;
			}
			else
			{
				receiveText(i);
				_select--;
			}
		}
	}
}

/*
** ↓ PUBLIC ↓
*/

void			Server::init(int ac, char **av)
{
	if (ac == 3)
	{
		_port = std::atoi(av[1]);
		_password = av[2];
		_socket = socket(AF_INET, SOCK_STREAM, 0);
		if (_socket == -1)
		{
			errorServer("socket");
			return ;
		}
		_infos.sin_addr.s_addr = INADDR_ANY;
		_infos.sin_family = AF_INET;
		_infos.sin_port = htons(_port);
		if (bind(_socket, (const sockaddr *)&_infos, sizeof(_infos)) == -1)
		{
			errorServer("bind");
			return ;
		}
		if (listen(_socket, SOMAXCONN) == -1)
		{
			errorServer("listen");
			return ;
		}
		std::cout << "IRC Server is running on port " << getPort() << std::endl;
		FD_ZERO(&_read_fds);
		FD_SET(_socket, &_read_fds);
		_command.setCommand(_password, _host, &_list_client, &_read_fds);
	}
	else
	{
		std::cout << "Need arguments: " << av[0] << " [port] [password]" << std::endl;
		_loop = false;
	}
}

void			Server::run()
{
	while (_loop)
	{
		checkFds();
	}
}

/*
** ↓ UTILS ↓
*/

int				Server::nbClient() const
{
	return _list_client.size();
}

std::string		Server::getIp() const
{
	return (inet_ntoa(_infos.sin_addr));
}

std::string		Server::getHostIp() const
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

int				Server::getPort() const
{
	return _port;
}

int				Server::errorServer(std::string msg)
{
	_loop = false;
	_select = 0;
	std::cout << "ERROR: " << msg << std::endl;
	return -1;
}
