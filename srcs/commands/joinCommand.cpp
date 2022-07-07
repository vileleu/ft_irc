/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   joinCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vico <vico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 02:55:25 by vico              #+#    #+#             */
/*   Updated: 2022/07/07 13:19:50 by vico             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

int		Command::joinCommand(std::string cmd)
{
	std::vector<std::string>	arg(split(cmd, ' '));

	if (arg.size() < 2)
	{
		_to_send[_who->getSocket()] += ERR_NEEDMOREPARAMS(_who->getHost(), _who->getNickname(), arg[0]);
		return -1;
	}
	std::vector<std::string>	name(split(arg[1], ','));
	std::string					send("");
	bool						exist(false);
	
	for (std::vector<std::string>::iterator it(name.begin()); it != name.end(); it++)
	{
		send = "";
		exist = false;
		for (std::vector<Channel *>::iterator chan(_channels.begin()); chan != _channels.end(); chan++)
		{
			if ((*chan)->getName() == *it) // rejoins le canal
			{
				exist = true;
				if ((*chan)->getInvite() == true)
				{
					if (_who->_invite.first == false || _who->_invite.second != (*chan)->getName())
					{
						_to_send[_who->getSocket()] += ERR_INVITEONLYCHAN(_who->getHost(), _who->getNickname(), *it);
						break ;
					}
				}
				if ((*chan)->getKey() != "")
				{
					std::vector<std::string>	pass(split(arg[2], ','));

					if (arg.size() < 3 || pass[it - name.begin()] != (*chan)->getKey())
					{
						_to_send[_who->getSocket()] += ERR_BADCHANNELKEY(_who->getHost(), _who->getNickname(), *it);
						break ;
					}
				}
				if ((*chan)->getLimit() && (*chan)->_users.size() >= (*chan)->getLimit())
				{
					_to_send[_who->getSocket()] += ERR_CHANNELISFULL(_who->getHost(), _who->getNickname(), *it);
					break ;
				}
				_who->_invite = std::make_pair(false, "");
				(*chan)->addUser(_who, false);
				if ((*chan)->getTopic() != "")
					send.append(RPL_TOPIC(_who->getHost(), _who->getNickname(), (*chan)->getName(), (*chan)->getTopic()));
				send.append(RPL_NAMREPLY(_who->getHost(), _who->getNickname(), *it));
				for (std::vector<Client *>::iterator client((*chan)->_users.begin()); client != (*chan)->_users.end(); client++)
				{
					_to_send[(*client)->getSocket()] += ":" + _who->getHost() + " JOIN " + *it + "\n";
					send.append((*chan)->pref((*client)->getNickname()) + " ");
				}
				send.append("\n");
				send.append(RPL_ENDOFNAMES(_who->getHost(), _who->getNickname(), *it));
				_to_send[_who->getSocket()] += send;
				break ;
			}
		}
		if (exist == false) // crée le canal
		{
			_channels.push_back(new Channel(*it, _who));
			send.append(":" + _who->getHost() + " JOIN " + *it + "\n");
			send.append(RPL_NAMREPLY(_who->getHost(), _who->getNickname(), *it));
			send.append(_channels.back()->pref((_who->getNickname())) + "\n");
			send.append(RPL_ENDOFNAMES(_who->getHost(), _who->getNickname(), *it));
			_to_send[_who->getSocket()] += send;
		}
	}
	return 0;
}