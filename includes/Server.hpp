/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vico <vico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 00:08:36 by vico              #+#    #+#             */
/*   Updated: 2022/07/09 19:10:31 by vico             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include "utils.hpp"
#include "Client.hpp"
#include "Command.hpp"

class Server
{
	private:

	int							_port;
	int							_socket;
	std::string					_password;
	struct sockaddr_in			_infos;
	std::string					_host;
	bool						_loop;

	std::vector<Client *>		_list_client;
	int							_max_client;
	fd_set						_read_fds;
	int							_select;

	Command						_command;

	void			checkFds();
	void			addClient();
	void			receiveText(const int i);

	int				errorServer(std::string msg);

	public:

	Server();
	~Server();

	void			init(int ac, char **av);
	void			run();

	int				nbClient() const;

	std::string		getIp() const;
	std::string		getHostIp() const;
	int				getPort() const;
};

#endif