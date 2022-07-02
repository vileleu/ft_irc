/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vico <vico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 03:06:08 by vico              #+#    #+#             */
/*   Updated: 2022/07/02 22:56:33 by vico             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

Channel::Channel(const std::string &name, Client *creator) : _name(name), _topic("")
{
	if (_name.size() >= 50)
	{
		std::string::iterator it(_name.begin());
		for (int i(0); i < 50; i++)
		{
			it++;
		}
		_name.erase(it, _name.end());
	}
	_users.push_back(creator);
	_ops.push_back(creator);
}

Channel::~Channel()
{
}

std::string				Channel::pref(std::string name)
{
	for (std::vector<Client *>::iterator it(_ops.begin()); it != _ops.end(); it++)
	{
		if ((*it)->getNickname() == name)
			return "@" + name;
	}
	return name;
}

std::string				Channel::getName() const
{
	return _name;
}

std::string				Channel::getTopic() const
{
	return _topic;
}

void					Channel::setTopic(const std::string &topic)
{
	_topic = topic;
}

void					Channel::addUser(Client *client, bool op)
{
	_users.push_back(client);
	if (op == true)
		_ops.push_back(client);
}

bool					Channel::removeUser(Client *client)
{
	for (std::vector<Client *>::iterator remove(_users.begin()); remove != _users.end(); remove++)
	{
		if ((*remove) == client)
		{
			_users.erase(remove);
			break ;
		}
	}
	for (std::vector<Client *>::iterator remove(_ops.begin()); remove != _ops.end(); remove++)
	{
		if ((*remove) == client)
		{
			_ops.erase(remove);
			break ;
		}
	}
	if (_users.size() == 0)
		return false;
	return true;
}
