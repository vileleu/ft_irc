/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vico <vico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 11:49:32 by vico              #+#    #+#             */
/*   Updated: 2022/07/07 13:08:10 by vico             ###   ########.fr       */
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

	std::string			_pass;
	std::string			_nickname;
	std::string			_username;
	std::string			_realname;
	std::string			_host;
	bool				_register;

	public:

	std::pair<bool, std::string>	_invite;

	Client();
	~Client();

	int					getSocket() const;
	void				setSocket(int socket);
	struct sockaddr_in	&getInfos();
	socklen_t			&getInfosSize();

	std::string			getPass() const;
	std::string			getNickname() const;
	std::string			getUsername() const;
	std::string			getRealname() const;
	std::string			getHost() const;
	bool				isRegister() const;
	void				setPass(const std::string &pass);
	void				setNickname(const std::string &nickname);
	void				setUsername(const std::string &username);
	void				setRealname(const std::string &realname);
	void				setHost(const std::string &host);
	void				setRegister(const bool &mode);

	std::string			getIp() const;
	int					getPort() const;
};

#endif
