/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vico <vico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 00:08:36 by vico              #+#    #+#             */
/*   Updated: 2022/06/20 15:41:21 by vico             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include "utils.hpp"
#include "Client.hpp"

class Server
{
	private:

	int						_port;
	int						_socket;
	std::string				_password;
	struct sockaddr_in		_infos;
	bool					_loop;

	std::vector<Client *>	_list_client;
	int						_max_client;
	fd_set					_read_fds;

	int						_select;

	void			checkFds();
	void			addClient();
	void			deleteClient(std::vector<Client *>::iterator it);
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