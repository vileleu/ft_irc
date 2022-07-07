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

	bool						_fail;
	std::string					_host;
	std::string					_password;
	std::vector<std::string>	_check_cmd;
	std::string					_check_mode;
	std::vector<std::string>	_cmd;

	std::map<int, std::string>	_to_send;

	Client						*_who;

	std::vector<Client *>		*_clients;
	fd_set						*_read_fds;

	std::vector<std::string>	split(const std::string &to_split, char c) const;

	void						failedRegister();
	int							alreadyUse(std::string nick);
	void						registration();

	int							nickCheck(const std::string &check);
	int							execmode(char c, char mode, std::string it, Channel *chan);

	int							joinCommand(std::string cmd);    // rejoins un canal de disscussion, le créé si il n'existe pas (le créateur est un opérateur)
	int							nickCommand(std::string cmd);    // change de nickname
	int							partCommand(std::string cmd);    // quitte un ou plusieurs canal(canaux)
	int							pongCommand(std::string cmd);    // réponse à PING
	int							privmsgCommand(std::string cmd); // gère les messages des canaux
	void						quitCommand(std::string cmd);    // quitte le serveur et tout les channels rejoints
	int							topicCommand(std::string cmd);   // créer un topic pour un channel, il faut être dans le channel
	int							kickCommand(std::string cmd);    // exclu un/des user/users d'un/des canal/canaux
	int							modeCommand(std::string cmd);    // gère les canaux (il faut être operateur)
	int							inviteCommand(std::string cmd);  // invite un user dans un canal

	public:

	std::vector<Channel *>		_channels;

	Command();
	~Command();

	void						init(std::string to_parse, Client *who);
	void						parsing();
	void						clean();

	std::map<int, std::string>	getTosend() const;
	void						setCommand(std::string password, std::string host, std::vector<Client *> *clients, fd_set *read_fds);
};

#endif
