/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsgCommand.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vico <vico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 02:55:25 by vico              #+#    #+#             */
/*   Updated: 2022/07/07 11:42:57 by vico             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

int		Command::privmsgCommand(std::string cmd)
{
	std::vector<std::string>	arg(split(cmd, ' '));
	
	if (arg.size() < 2)
	{
		_to_send[_who->getSocket()] += ERR_NEEDMOREPARAMS(_who->getHost(), _who->getNickname(), arg[0]);
		return -1;
	}
	bool	exist(false);
	bool	isin(false);

	for (std::vector<Channel *>::iterator chan(_channels.begin()); chan != _channels.end(); chan++)
	{
		if ((*chan)->getName() == arg[1])
		{
			isin = false;
			exist = true;
			if ((*chan)->getModerated() == true && (*chan)->isOp(_who) == false)
			{
				_to_send[_who->getSocket()] += ERR_CANNOTSENDTOCHAN(_who->getHost(), _who->getNickname(), arg[1]);
				return -1;
			}
			for (std::vector<Client *>::iterator client((*chan)->_users.begin()); client != (*chan)->_users.end(); client++)
			{
				if (*client == _who)
				{
					isin = true;
					if (arg.size() < 3 || (arg.size() < 4 && arg[2] == ":"))
					{
						_to_send[_who->getSocket()] += ERR_NOTEXTTOSEND(_who->getHost(), _who->getNickname());
						return -1;
					}
					for (client = (*chan)->_users.begin(); client != (*chan)->_users.end(); client++)
					{
						if (*client != _who)
							_to_send[(*client)->getSocket()] += ":" + _who->getHost() + " " + cmd + "\n";
					}
					break ;
				}
			}
			if (isin == false)
			{
				_to_send[_who->getSocket()] += ERR_NOTONCHANNEL(_who->getHost(), _who->getNickname(), arg[1]);
				return -1;				
			}
		}
	}
	if (exist == false)
	{
		_to_send[_who->getSocket()] += ERR_NOSUCHCHANNEL(_who->getHost(), _who->getNickname(), arg[1]);
		return -1;
	}
	return 0;
}