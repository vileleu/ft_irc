/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vico <vico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 03:07:45 by vico              #+#    #+#             */
/*   Updated: 2022/06/18 01:54:15 by vico             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server() : _port(0), _socket(0), _password(""), _loop(true), _nb_client(0), _max_client(FD_SETSIZE), _ret_select(0)
{
}

Server::~Server()
{
	for (unsigned int i(0); i < _list_client.size(); i++)
	{
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

	_ret_select = select(_max_client, &copy, NULL, NULL, NULL);
	for (int i(0); i < _max_client; i++)
	{
		if (FD_ISSET(i, &copy))
		{
			if (i == _socket)
			{
				_list_client.push_back(new Client);
				_list_client[_nb_client]->_socket = accept(_socket, reinterpret_cast<struct sockaddr *>(&(_list_client[_nb_client]->_infos_client)), &(_list_client[_nb_client]->_infos_client_size));
				FD_SET(_list_client[_nb_client]->_socket, &_read_fds);
				std::cout << "Client connected: " << _list_client[_nb_client]->_socket << std::endl;
				_nb_client++;
			}
			else
			{
				char	buf[4096];

				memset(buf, 0, 4096);
				int bytesReceived = recv(i, buf, 4096, 0);
				std::string	command(buf);

				if (bytesReceived == 0)
				{
					for (int j(0); j < _nb_client; j++)
					{
						if (i == _list_client[j]->_socket)
						{
							std::cout << "Client disconnected: " << _list_client[j]->_socket << std::endl;
							FD_CLR(_list_client[j]->_socket, &_read_fds);
							Client	*c = _list_client[j];
							_list_client.pop_back();
							delete c;
							_nb_client--;
							break ;
						}
					}
				}
				else if (command == "exit")
				{
					std::cout << "Server disconnected: " << i << " use exit command" << std::endl;
					_loop = false;
					return ;
				}
				else
				{
					std::cout << "new message from " << i << ": " << command << std::endl;
				}
			}
		}
	}
}
