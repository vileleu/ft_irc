/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inviteCommand.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vico <vico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 02:55:25 by vico              #+#    #+#             */
/*   Updated: 2022/07/08 12:53:08 by vico             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

int		Command::inviteCommand(std::string cmd)
{
	std::vector<std::string>	arg(split(cmd, ' '));

	if (arg.size() < 3)
	{
		_to_send[_who->getSocket()] += ERR_NEEDMOREPARAMS(_who->getHost(), _who->getNickname(), arg[0]);
		return 0;
	}
	bool	isclient(false);
	bool	ischan(false);
	bool	isin(false);

	for (std::vector<Client *>::iterator client(_clients->begin()); client != _clients->end(); client++)
	{
		if ((*client)->getNickname() == arg[1])
		{
			ischan = false;
			isclient = true;
			for (std::vector<Channel *>::iterator chan(_channels.begin()); chan != _channels.end(); chan++)
			{
				if ((*chan)->getName() == arg[2])
				{
					isin = false;
					ischan = true;
					for (std::vector<Client *>::iterator cl((*chan)->_users.begin()); cl != (*chan)->_users.end(); cl++)
					{
						if (*cl == _who)
						{
							isin = true;
							for (cl = (*chan)->_users.begin(); cl != (*chan)->_users.end(); cl++)
							{
								if ((*cl)->getNickname() == arg[1])
								{
									_to_send[_who->getSocket()] += ERR_USERONCHANNEL(_who->getHost(), _who->getNickname(), arg[1], arg[2]);
									return 0;
								}
							}
							if ((*chan)->getInvite() == true && (*chan)->isOp(_who) == false)
							{
								_to_send[_who->getSocket()] += ERR_CHANOPRIVSNEEDED(_who->getHost(), _who->getNickname(), arg[2]);
								return 0;
							}
							_to_send[_who->getSocket()] += RPL_INVITING(_who->getHost(), _who->getNickname(), arg[1], arg[2]);
							_to_send[(*client)->getSocket()] += ":" + _who->getHost() + " INVITE " + arg[1] + " " + arg[2] + "\n";
							(*client)->_invite.first = true;
							(*client)->_invite.second = (*chan)->getName();
							break ;
						}
					}
					if (isin == false)
					{
						_to_send[_who->getSocket()] += ERR_NOTONCHANNEL(_who->getHost(), _who->getNickname(), arg[2]);
						return 0;
					}
					break ;
				}
			}
			if (ischan == false)
			{
				_to_send[_who->getSocket()] += ERR_NOSUCHNICK(_who->getHost(), _who->getNickname(), arg[2]);
				return 0;
			}
			break ;
		}
	}
	if (isclient == false)
	{
		_to_send[_who->getSocket()] += ERR_NOSUCHNICK(_who->getHost(), _who->getNickname(), arg[1]);
		return 0;
	}
	return 0;
}