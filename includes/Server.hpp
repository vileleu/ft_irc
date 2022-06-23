/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vico <vico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 00:08:36 by vico              #+#    #+#             */
/*   Updated: 2022/06/23 22:29:58 by vico             ###   ########.fr       */
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
	std::vector<int>		_not_register;

	void			checkFds();
	void			addClient();
	void			deleteClient(std::vector<Client *>::iterator it);
	int				fillClient(std::vector<Client *>::iterator to_fill, std::string text);
	void			registration(std::vector<int>::iterator it, std::string text);
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