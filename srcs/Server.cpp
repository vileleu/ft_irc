/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vico <vico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 03:07:45 by vico              #+#    #+#             */
/*   Updated: 2022/06/19 21:37:07 by vico             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server() : _port(0), _socket(0), _password(""), _loop(true), _nb_client(0), _max_client(FD_SETSIZE), _select(0)
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

void	Server::init(int ac, char **av)
{
	if (ac == 3)
	{
		_port = std::atoi(av[1]);
		_password = av[2];
		_socket = socket(AF_INET, SOCK_STREAM, 0);
		if (_socket == -1)
		{
			error_msg("Invalid socket");
			_loop = false;
			return ;
		}
		_infos.sin_addr.s_addr = INADDR_ANY;
		_infos.sin_family = AF_INET;
		_infos.sin_port = htons(_port);

		bind(_socket, (const sockaddr *)&_infos, sizeof(_infos));
		std::cout << "Server: " << get_ip() << ":" << _port << " is running" << std::endl;
		
		listen(_socket, SOMAXCONN);

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
		check_fds();
	}
}

void	Server::check_fds()
{
	fd_set	copy = _read_fds;

	_select = select(_max_client, &copy, NULL, NULL, NULL);
	for (int i(0); i < (_max_client) && (_select); i++)
	{
		if (FD_ISSET(i, &copy))
		{
			if (i == _socket)
			{
				_list_client.push_back(new Client);
				_list_client[_list_client.size() - 1]->setSocket(accept(_socket, reinterpret_cast<struct sockaddr *>(&(_list_client[_list_client.size() - 1]->getInfos())), &(_list_client[_list_client.size() - 1]->getInfosSize())));
				FD_SET(_list_client[_list_client.size() - 1]->getSocket(), &_read_fds);
				std::cout << "Client connected: " << _list_client[_list_client.size() - 1]->getSocket() << std::endl;
				_nb_client++;
				_select--;
			}
			else
			{
				char	buf[4096];

				memset(buf, 0, 4096);
				int bytesReceived = recv(i, buf, 4096, 0);
				std::string	text(buf);
				std::string	command(text.substr(0, text.find(' ')));
				
				if (bytesReceived == 0)
				{
					for (std::vector<Client *>::iterator it(_list_client.begin()); it != _list_client.end(); it++)
					{
						if (i == (*it)->getSocket())
						{
							std::cout << "Client disconnected: " << (*it)->getSocket() << std::endl;
							FD_CLR((*it)->getSocket(), &_read_fds);
							Client	*c = *it;
							_list_client.erase(it);
							delete c;
							_nb_client--;
							break ;
						}
					}
				}
				/*else if (command == "QUIT")
				{
					std::cout << "Server disconnected: " << i << " use QUIT command" << std::endl;
					_loop = false;
					return ;
				}*/
				else
				{
					std::cout << "new message from " << i << ": " << text << std::endl;
				}
				_select--;
			}
		}
	}
}
