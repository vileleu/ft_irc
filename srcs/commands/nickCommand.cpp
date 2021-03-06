/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nickCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vico <vico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 02:55:25 by vico              #+#    #+#             */
/*   Updated: 2022/07/08 13:02:56 by vico             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

int		Command::nickCheck(const std::string &check)
{
	if (std::isdigit(check[0]) || check[0] == '_')
	{
		return -1;
	}
	for (size_t i(0); i < check.size(); i++)
	{
		if (!(std::isalnum(check[i])) && check[i] != '`' && check[i] != '|' && check[i] != '^' && check[i] != '_' && \
		check[i] != '-' && check[i] != '{' && check[i] != '}' && check[i] != '[' && check[i] != ']' && check[i] != '\\')
		{
			return -1;
		}
	}
	return 0;
}

int		Command::nickCommand(std::string cmd)
{
	std::vector<std::string>	arg(split(cmd, ' '));

	if (arg.size() < 2)
	{
		_to_send[_who->getSocket()] += ERR_NEEDMOREPARAMS(_who->getHost(), _who->getNickname(), arg[0]);
		return 0;
	}
	else if (nickCheck(arg[1]))
	{
		_to_send[_who->getSocket()] += ERR_ERRONEUSNICKNAME(_who->getHost(), _who->getNickname(), arg[1]);
		return 0;
	}
	for (size_t i(0); i < arg[1].size(); i ++)
	{
		arg[1][i] = std::tolower(arg[1][i]);
	}
	for (std::vector<Client *>::iterator it(_clients->begin()); it != _clients->end(); it++)
	{
		if (arg[1] == (*it)->getNickname())
		{
			_to_send[_who->getSocket()] += ERR_NICKNAMEINUSE(_who->getHost(), _who->getNickname(), arg[1]);
			return 0;
		}
	}
	_who->setNickname(arg[1]);
	for (std::vector<Channel *>::iterator chan(_channels.begin()); chan != _channels.end(); chan++)
	{
		for (std::vector<Client *>::iterator client((*chan)->_users.begin()); client != (*chan)->_users.end(); client++)
		{
			if (*client == _who)
			{
				for (client = (*chan)->_users.begin(); client != (*chan)->_users.end(); client++)
				{
					if (*client != _who)
						_to_send[(*client)->getSocket()] += ":" + _who->getHost() + " NICK " + _who->getNickname() + "\n";
				}
				break ;
			}
		}
	}
	_to_send[_who->getSocket()] += ":" + _who->getHost() + " NICK " + _who->getNickname() + "\n";
	_who->setHost(_who->getNickname() + "!" + _who->getUsername() + "@" + _who->getIp());
	return 0;
}
