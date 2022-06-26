/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vico <vico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 00:26:45 by vico              #+#    #+#             */
/*   Updated: 2022/06/26 01:47:11 by vico             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef Command_HPP
#define Command_HPP

#include "utils.hpp"
#include "Client.hpp"

class Command
{
	private:

	std::string					_host;
	std::string					_password;
	std::vector<std::string>	_check_cmd;
	std::vector<std::string>	_cmd;
	bool						_is_init;
	std::map<int, std::string>	_check_send;
	std::map<int, std::string>	_to_send;

	Client						*_who;

	int							passCommand(std::string cmd);
	int							nickCommand(std::string cmd);
	int							userCommand(std::string cmd);
	std::vector<std::string>	split(std::string to_split, char c) const;

	int							registration();


	public:

	Command();
	~Command();

	void						init(std::string to_parse, Client *who);
	void						parsing();
	std::map<int, std::string>	getTosend() const;
	void						setCommand(std::string password, std::string host);
	void						clean();
};

#endif
