/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vico <vico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 11:49:32 by vico              #+#    #+#             */
/*   Updated: 2022/06/20 02:19:38 by vico             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "utils.hpp"

class Client
{
	private:

	int					_socket;
	struct sockaddr_in	_infos_client;
	socklen_t			_infos_client_size;

	public:

	Client();
	~Client();

	int					getSocket() const;
	void				setSocket(int socket);
	struct sockaddr_in	&getInfos();
	socklen_t			&getInfosSize();

	std::string			getIp() const;
	int					getPort() const;
};

#endif
