/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quitCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vico <vico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 02:55:25 by vico              #+#    #+#             */
/*   Updated: 2022/07/03 03:07:51 by vico             ###   ########.fr       */
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
			if (_who->getNickname() == (*client)->getNickname())
			{
				for (std::vector<Client *>::iterator cl((*chan)->_users.begin()); cl != (*chan)->_users.end(); cl++)
				{
					if (*cl != _who)
					{
						_to_send[(*cl)->getSocket()] = ":" + _who->getHost() + " " + cmd + "\n";
					}
				}
				for (std::vector<Client *>::iterator op((*chan)->_ops.begin()); op != (*chan)->_ops.end(); op++)
				{
					if (_who->getNickname() == (*op)->getNickname())
					{
						(*chan)->_ops.erase(op);
						break ;
					}
				}
				(*chan)->_users.erase(client);
				break ;
			}
		}
		if ((*chan)->_users.size() == 0)
		{
			std::cout << "remove channel " << (*chan)->getName() << std::endl;
			delete *chan;
			_channels.erase(chan);
			chan = _channels.begin();
		}
		else
			chan++;
	}
	std::cout << "Client disconnected: " << _who->getSocket() << std::endl;
	FD_CLR(_who->getSocket(), _read_fds);
	close(_who->getSocket());
	for (std::vector<Client *>::iterator client(_clients->begin()); client != _clients->end(); client++)
	{
		if (*client == _who)
		{
			delete *client;
			_clients->erase(client);
			break ;
		}
	}
}