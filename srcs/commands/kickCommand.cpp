/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kickCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vico <vico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 02:55:25 by vico              #+#    #+#             */
/*   Updated: 2022/07/08 12:49:57 by vico             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

int		Command::kickCommand(std::string cmd)
{
	std::vector<std::string>	arg(split(cmd, ' '));

	if (arg.size() < 3)
	{
		_to_send[_who->getSocket()] += ERR_NEEDMOREPARAMS(_who->getHost(), _who->getNickname(), arg[0]);
		return 0;
	}
	std::vector<std::string>	name(split(arg[1], ','));
	std::vector<std::string>	user(split(arg[2], ','));
	bool						exist(false);
	bool						isin(false);
	bool						usin(false);

	for (std::vector<std::string>::iterator it(name.begin()); it != name.end(); it++)
	{
		exist = false;
		for (std::vector<Channel *>::iterator chan(_channels.begin()); chan != _channels.end(); chan++)
		{
			if ((*chan)->getName() == *it)
			{					
				exist = true;
				for (std::vector<std::string>::iterator us(user.begin()); us != user.end(); us++)
				{
					isin = false;
					for (std::vector<Client *>::iterator client((*chan)->_users.begin()); client != (*chan)->_users.end(); client++)
					{
						if (*client == _who)
						{
							isin = true;
							if ((*chan)->isOp(_who) == true)
							{
								usin = false;
								for (client = (*chan)->_users.begin(); client != (*chan)->_users.end(); client++)
								{
									if ((*client)->getNickname() == *us)
									{
										Client		*save(*client);
										std::string	msg(":" + (*client)->getNickname());

										usin = true;
										for (size_t i(3); i < arg.size() && arg[3] != ":"; i++)
										{
											if (i == 3)
												msg = arg[i];
											else
												msg += " " + arg[i];
										}
										for (client = (*chan)->_users.begin(); client != (*chan)->_users.end(); client++)
										{
											_to_send[(*client)->getSocket()] += ":" + _who->getHost() + " KICK " + *it + " " + arg[2] + " " + msg + "\n";
										}
										if ((*chan)->removeUser(save) == false)
										{
											delete *chan;
											_channels.erase(chan);
										}
										break ;
									}
								}
								if (usin == false)
									_to_send[_who->getSocket()] += ERR_USERNOTINCHANNEL(_who->getHost(), _who->getNickname(), arg[2], *it);
							}
							else
								_to_send[_who->getSocket()] += ERR_CHANOPRIVSNEEDED(_who->getHost(), _who->getNickname(), *it);
							break ;
						}
					}
					if (isin == false)
						_to_send[_who->getSocket()] += ERR_NOTONCHANNEL(_who->getHost(), _who->getNickname(), *it);
				}
			}
			if (chan == _channels.end())
				break ;
		}
		if (exist == false)
			_to_send[_who->getSocket()] += ERR_NOSUCHCHANNEL(_who->getHost(), _who->getNickname(), *it);
	}
	return 0;
}
