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
#include "Channel.hpp"

class Command
{
	private:

	bool						_nickuse;
	std::string					_host;
	std::string					_password;
	std::vector<std::string>	_check_cmd;
	std::vector<std::string>	_cmd;
	std::map<int, std::string>	_check_send;
	std::map<int, std::string>	_to_send;

	Client						*_who;
	std::vector<Channel *>		_channels;

	std::vector<Client *>		*_clients;

	std::vector<std::string>	split(const std::string &to_split, char c) const;

	int							alreadyUse(std::string nick);
	int							registration();

	int							nickCheck(const std::string &check);

	int							nickCommand(std::string cmd); // change de nickname
	int							joinCommand(std::string cmd); // rejoins un canal de disscussion, le créé si il n'existe pas (le créateur est un opérateur)
	int							partCommand(std::string cmd); // quitte un ou plusieurs canal(canaux)
	int							modeCommand(std::string cmd); 
	int							topicCommand(std::string cmd); // créer un topic pour un channel, il faut être dans le channel
	int							namesCommand(std::string cmd); // affiche les nicknames des utilisateurs sur un canal, il faut être dans le canal
	int							listCommand(std::string cmd);
	int							inviteCommand(std::string cmd);
	int							kickCommand(std::string cmd);
	int							pongCommand(std::string cmd); // answer to PING
	int							privmsgCommand(std::string cmd); // gère les messages des canaux

	public:

	Command();
	~Command();

	void						init(std::string to_parse, Client *who);
	void						parsing();
	void						clean();

	std::map<int, std::string>	getTosend() const;
	void						setCommand(std::string password, std::string host, std::vector<Client *> *clients);
};

#endif
