/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   noticeCommand.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vico <vico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 02:55:25 by vico              #+#    #+#             */
/*   Updated: 2022/07/08 12:57:05 by vico             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

int		Command::noticeCommand(std::string cmd)
{
	std::vector<std::string>	arg(split(cmd, ' '));
	
	if (arg.size() < 2)
	{
		_to_send[_who->getSocket()] += ERR_NEEDMOREPARAMS(_who->getHost(), _who->getNickname(), arg[0]);
		return 0;
	}
	else if (arg.size() < 3 || arg[2] == ":")
	{
		_to_send[_who->getSocket()] += ERR_NOTEXTTOSEND(_who->getHost(), _who->getNickname());
		return 0;
	}
	else
	{
		bool						exist(false);

		for (std::vector<Client *>::iterator client(_clients->begin()); client != _clients->end(); client++)
		{
			if ((*client)->getNickname() == arg[1])
			{
				exist = true;
				_to_send[(*client)->getSocket()] += ":" + _who->getHost() + " " + cmd + "\n";
				return 0;
			}
		}
		for (std::vector<Channel *>::iterator chan(_channels.begin()); chan != _channels.end(); chan++)
		{
			if ((*chan)->getModerated() || (*chan)->getInvite() || (*chan)->getKey() != "" || isBan(_who, *chan))
			{
				_to_send[_who->getSocket()] += ERR_CANNOTSENDTOCHAN(_who->getHost(), _who->getNickname(), (*chan)->getName());
				return 0;
			}
			else if ((*chan)->getName() == arg[1])
			{
				exist = true;
				for (std::vector<Client *>::iterator client((*chan)->_users.begin()); client != (*chan)->_users.end(); client++)
				{
					_to_send[(*client)->getSocket()] += ":" + _who->getHost() + " " + cmd + "\n";
				}
				break ;
			}
		}
		if (exist == false)
		{
			_to_send[_who->getSocket()] += ERR_NOSUCHNICK(_who->getHost(), _who->getNickname(), arg[1]);
			return 0;
		}
	}
	return 0;
}