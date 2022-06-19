/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vico <vico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 00:08:36 by vico              #+#    #+#             */
/*   Updated: 2022/06/19 21:22:39 by vico             ###   ########.fr       */
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
	int						_nb_client;
	int						_max_client;
	fd_set					_read_fds;

	int						_select;

	public:

	Server();
	~Server();

	void	init(int ac, char **av);
	void	run();

	void	check_fds();
};

#endif