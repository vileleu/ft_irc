/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vico <vico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 03:07:45 by vico              #+#    #+#             */
/*   Updated: 2022/06/24 00:59:44 by vico             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server() : _port(0), _socket(0), _password(""), _loop(true), _max_client(FD_SETSIZE), _select(0)
{
}

Server::~Server()
{
	for (unsigned int i(0); i < _list_client.size(); i++)
	{
		FD_CLR(_list_client[i]->getSocket(), &_read_fds);
		delete _list_client[i];
	}
	close(_socket);
}

void	Server::addClient()
{
	_list_client.push_back(new Client);
	_list_client[_list_client.size() - 1]->setSocket(accept(_socket, reinterpret_cast<struct sockaddr *>(&(_list_client[_list_client.size() - 1]->getInfos())), &(_list_client[_list_client.size() - 1]->getInfosSize())));
	if (_list_client[_list_client.size() - 1]->getSocket() == -1)
	{
		errorServer("accept");
		return ;	
	}
	FD_SET(_list_client[_list_client.size() - 1]->getSocket(), &_read_fds);
	_not_register.push_back(_list_client[_list_client.size() - 1]->getSocket());
	std::cout << "Client connected: " << _list_client[_list_client.size() - 1]->getSocket() << " from " << _list_client[_list_client.size() - 1]->getIp() << ":" << _list_client[_list_client.size() - 1]->getPort() << "\n" << std::endl;
}

void	Server::deleteClient(std::vector<Client *>::iterator it)
{
	std::cout << "Client disconnected: " << (*it)->getSocket() << "\n" << std::endl;
	for (std::vector<int>::iterator ite(_not_register.begin()); ite != _not_register.end(); ite++)
	{
		if ((*it)->getSocket() == *ite)
		{
			_not_register.erase(ite);
			break ;
		}
	}
	FD_CLR((*it)->getSocket(), &_read_fds);
	Client	*c = *it;
	_list_client.erase(it);
	delete c;
}

int		Server::fillClient(std::vector<Client *>::iterator to_fill, std::string text)
{
	if ((*to_fill)->getNickname() == "" && text.find("NICK", 0))
		(*to_fill)->setNickname(text.substr(text.find("NICK", 0) + 5, (text.find("\n", text.find("NICK", 0) + 5)) - (text.find("NICK", 0) + 5)));
	if ((*to_fill)->getUsername() == "" && text.find("USER", 0))
	{
		(*to_fill)->setUsername(text.substr(text.find("USER", 0) + 5, (text.find(" ", text.find("USER", 0) + 5)) - (text.find("USER", 0) + 5)));
		(*to_fill)->setRealname(text.substr(text.find_last_of(':') + 1));
		(*to_fill)->setHost("localhost");
	}
	if ((*to_fill)->getNickname() != "" && (*to_fill)->getUsername() != "" && (*to_fill)->getRealname() != "" && (*to_fill)->getHost() != "")
		return 0;
	return -1;
}

void	Server::registration(std::vector<int>::iterator it, std::string text)
{
	std::vector<Client *>::iterator	to_fill(_list_client.begin());
	
	while (to_fill != _list_client.end())
	{
		if ((*to_fill)->getSocket() == *it)
			break;
	}
	if (fillClient(to_fill, text))
		return ;
	std::ostringstream	register_cmd;

	register_cmd << ": NICK :" << (*to_fill)->getNickname() << "\n:" << (*to_fill)->getHost() << " 001 " << (*to_fill)->getNickname() << " :Bienvenue chakal " << *(*to_fill) << "\n";

	std::string	to_send(register_cmd.str());
	send(*it, to_send.c_str(), to_send.size(), 0);
	_not_register.erase(it);
}

void	Server::receiveText(const int i)
{
	char	buf[4096];

	memset(buf, 0, 4096);
	int bytes = recv(i, buf, 4096, 0);

	std::string	text(deleteLinefeed(buf));

	if (bytes == 0)
	{
		for (std::vector<Client *>::iterator it(_list_client.begin()); it != _list_client.end(); it++)
		{
			if (i == (*it)->getSocket())
			{
				deleteClient(it);
				break ;
			}
		}
	}
	else
	{
		for (std::vector<int>::iterator it(_not_register.begin()); it != _not_register.end(); it++)
		{
			if (i == *it)
			{
				registration(it, text);
				return ;
			}
		}
		std::cout << "new message from " << i << ": " << text << std::endl;
	}
}

void	Server::checkFds()
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

void	Server::init(int ac, char **av)
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
	}
	else
	{
		std::cout << "Need arguments: " << av[0] << " [port] [password]" << std::endl;
		_loop = false;
	}
}

void	Server::run()
{
	while (_loop)
	{
		checkFds();
	}
}

/*
// ↓ UTILS ↓
*/

int		Server::nbClient() const
{
	return _list_client.size();
}

std::string			Server::getIp() const
{
	return (inet_ntoa(_infos.sin_addr));
}

std::string			Server::getHostIp() const
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

int		Server::errorServer(std::string msg)
{
	_loop = false;
	_select = 0;
	std::cout << "ERROR: " << msg << std::endl;
	return -1;
}
