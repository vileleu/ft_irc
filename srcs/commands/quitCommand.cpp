/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quitCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vico <vico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 02:55:25 by vico              #+#    #+#             */
/*   Updated: 2022/07/15 08:37:07 by vico             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

void	Command::quitCommand(std::string cmd)
{
	std::vector<Channel *>::iterator chan(_channels.begin());
	
	while (chan != _channels.end())
	{
		for (std::vector<Client *>::iterator client((*chan)->_users.begin()); client != (*chan)->_users.end(); client++)
		{
			if (_who == *client)
			{
				for (std::vector<Client *>::iterator cl((*chan)->_users.begin()); cl != (*chan)->_users.end(); cl++)
				{
					if (*cl != _who)
						_to_send[(*cl)->getSocket()] += ":" + _who->getHost() + " " + cmd + "\n";
				}
				for (std::vector<Client *>::iterator op((*chan)->_ops.begin()); op != (*chan)->_ops.end(); op++)
				{
					if (_who == *op)
					{
						(*chan)->_ops.erase(op);
						break ;
					}
				}
				(*chan)->_users.erase(client);
				break ;
			}
			if (client == (*chan)->_users.end())
				break ;
		}
		if ((*chan)->_users.size() == 0)
		{
			delete *chan;
			_channels.erase(chan);
			chan = _channels.begin();
		}
		else
			chan++;
	}
	for (std::vector<Client *>::iterator it(_clients->begin()); it != _clients->end(); it++)
	{
		if ((*it)->getSocket() == _who->getSocket())
		{
			FD_CLR((*it)->getSocket(), _read_fds);
			close((*it)->getSocket());
			delete *it;
			_clients->erase(it);
			break ;
		}
	}
}