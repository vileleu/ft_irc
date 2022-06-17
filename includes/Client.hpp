/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vico <vico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 11:49:32 by vico              #+#    #+#             */
/*   Updated: 2022/06/15 17:04:18 by vico             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "utils.hpp"

class Client
{
	private:

	public:

	Client();
	~Client();

	std::string			_name;
	int					_socket;

	struct sockaddr_in	_infos_client;
	socklen_t			_infos_client_size;
};

#endif
