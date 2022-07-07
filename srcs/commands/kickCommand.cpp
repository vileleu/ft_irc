/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kickCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vico <vico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 02:55:25 by vico              #+#    #+#             */
/*   Updated: 2022/07/07 12:33:33 by vico             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

int		Command::kickCommand(std::string cmd)
{
	std::vector<std::string>	arg(split(cmd, ' '));

	if (arg.size() < 3)
	{
		_to_send[_who->getSocket()] += ERR_NEEDMOREPARAMS(_who->getHost(), _who->getNickname(), arg[0]);
		return -1;
	}
	std::vector<std::string>	name(split(arg[1], ','));
	bool						exist(false);
	bool						isin(false);
	bool						isop(false);
	bool						usin(false);

	for (std::vector<std::string>::iterator it(name.begin()); it != name.end(); it++)
	{
		exist = false;
		for (std::vector<Channel *>::iterator chan(_channels.begin()); chan != _channels.end(); chan++)
		{
			if ((*chan)->getName() == *it)
			{
				isin = false;
				exist = true;
				for (std::vector<Client *>::iterator client((*chan)->_users.begin()); client != (*chan)->_users.end(); client++)
				{
					if (*client == _who)
					{
						isop = false;
						isin = true;
						for (client = (*chan)->_ops.begin(); client != (*chan)->_ops.end(); client++)
						{
							if (*client == _who)
							{
								usin = false;
								isop = true;
								for (client = (*chan)->_users.begin(); client != (*chan)->_users.end(); client++)
								{
									if ((*client)->getNickname() == arg[2])
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
								{
									_to_send[_who->getSocket()] += ERR_USERNOTINCHANNEL(_who->getHost(), _who->getNickname(), arg[2], *it);
									return -1;
								}
								break ;
							}
						}
						if (isop == false)
						{
							_to_send[_who->getSocket()] += ERR_CHANOPRIVSNEEDED(_who->getHost(), _who->getNickname(), *it);
							return -1;
						}
						break ;
					}
				}
				if (isin == false)
				{
					_to_send[_who->getSocket()] += ERR_NOTONCHANNEL(_who->getHost(), _who->getNickname(), *it);
					return -1;
				}
				break ;
			}
		}
		if (exist == false)
		{
			_to_send[_who->getSocket()] += ERR_NOSUCHCHANNEL(_who->getHost(), _who->getNickname(), *it);
			return -1;
		}
	}
	return 0;
}
