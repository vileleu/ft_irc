/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   topicCommand.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vico <vico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 02:55:25 by vico              #+#    #+#             */
/*   Updated: 2022/07/08 12:49:31 by vico             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

int		Command::topicCommand(std::string cmd)
{
	std::vector<std::string>	arg(split(cmd, ' '));

	if (arg.size() < 2)
	{
		_to_send[_who->getSocket()] += ERR_NEEDMOREPARAMS(_who->getHost(), _who->getNickname(), arg[0]);
		return 0;
	}
	bool						exist(false);
	bool						isin(false);
	
	for (std::vector<Channel *>::iterator chan(_channels.begin()); chan != _channels.end(); chan++)
	{
		if ((*chan)->getName() == arg[1])
		{
			exist = true;
			for (std::vector<Client *>::iterator client((*chan)->_users.begin()); client != (*chan)->_users.end(); client++)
			{
				if (*client == _who)
				{
					isin = true;
					if (arg.size() < 3)
					{
						if ((*chan)->getTopic() == "")
						{
							_to_send[_who->getSocket()] += RPL_NOTOPIC(_who->getHost(), _who->getNickname(), arg[1]);
							return 0;
						}
						else
						{
							_to_send[_who->getSocket()] += RPL_TOPIC(_who->getHost(), _who->getNickname(), arg[1], (*chan)->getTopic());
							return 0;
						}
					}
					std::string	topic("");
					

					for (size_t i(2); i < arg.size(); i++)
					{
						if (i == 2 && arg[i][0] == ':')
							topic = arg[i].substr(1);
						else if (i == 2)
							topic = arg[i];
						else
							topic += " " + arg[i];
					}
					for (client = (*chan)->_users.begin(); client != (*chan)->_users.end(); client++)
					{	
						_to_send[(*client)->getSocket()] += ":" + _who->getHost() + " TOPIC " + arg[1] + " :" + topic + "\n";
					}
					(*chan)->setTopic(topic);
					break ;
				}
			}
			if (isin == false)
			{
				_to_send[_who->getSocket()] += ERR_NOTONCHANNEL(_who->getHost(), _who->getNickname(), arg[1]);
				return 0;
			}
			break ;
		}
	}
	if (exist == false)
	{
		_to_send[_who->getSocket()] += ERR_NOSUCHCHANNEL(_who->getHost(), _who->getNickname(), arg[1]);
		return 0;
	}
	return 0;
}