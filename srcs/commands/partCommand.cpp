/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   partCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vico <vico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 02:55:25 by vico              #+#    #+#             */
/*   Updated: 2022/07/05 22:42:14 by vico             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

int		Command::partCommand(std::string cmd)
{
	std::vector<std::string>	arg(split(cmd, ' '));

	if (arg.size() < 2)
	{
		_to_send.insert(std::make_pair(_who->getSocket(), ERR_NEEDMOREPARAMS(_who->getHost(), _who->getNickname(), arg[0])));
		return -1;
	}
	std::vector<std::string>	name(split(arg[1], ','));
	bool						exist(false);
	bool						isin(false);
	
	for (std::vector<std::string>::iterator it(name.begin()); it != name.end(); it++)
	{
		exist = false;
		for (std::vector<Channel *>::iterator chan(_channels.begin()); chan != _channels.end(); chan++)
		{
			if ((*chan)->getName() == *it)
			{
				exist = true;
				isin = false;
				for (std::vector<Client *>::iterator client((*chan)->_users.begin()); client != (*chan)->_users.end(); client++)
				{
					if (*client == _who)
					{
						std::string	msg("");

						isin = true;
						for (size_t i(2); i < arg.size(); i++)
						{
							if (i == 2)
								msg = arg[i];
							else
								msg += " " + arg[i];
						}
						for (client = (*chan)->_users.begin(); client != (*chan)->_users.end(); client++)
						{
							_to_send[(*client)->getSocket()] += ":" + _who->getHost() + " " + arg[0] + " " + *it + " " + msg + "\n";
						}
						if ((*chan)->removeUser(_who) == false)
						{
							delete *chan;
							chan = _channels.erase(chan);
							break ;
						}
						client = (*chan)->_users.begin();
					}
				}
				if (isin == false)
				{
					_to_send[_who->getSocket()] += ERR_NOTONCHANNEL(_who->getHost(), _who->getNickname(), *it);
					return -1;					
				}
			}
			if (chan == _channels.end())
				break ;
		}
		if (exist == false)
		{
			_to_send[_who->getSocket()] += ERR_NOSUCHCHANNEL(_who->getHost(), _who->getNickname(), *it);
			return -1;
		}
	}
	return 0;
}