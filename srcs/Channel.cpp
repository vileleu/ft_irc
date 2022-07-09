/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vico <vico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 03:06:08 by vico              #+#    #+#             */
/*   Updated: 2022/07/09 14:41:14 by vico             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

Channel::Channel(const std::string &name, Client *creator) : _name(name), _topic(""), _mode(""), _key(""), _moderated(false), _invite(false), _tops(false), _limit(0)
{
	if (_name[0] != '&' && _name[0] != '#' && _name[0] != '+' && _name[0] != '!')
		_name = '#' + _name;
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
	std::cout << "remove channel " << _name << std::endl;
}

std::string			Channel::pref(std::string name)
{
	for (std::vector<Client *>::iterator it(_ops.begin()); it != _ops.end(); it++)
	{
		if ((*it)->getNickname() == name)
			return "@" + name;
	}
	return name;
}

std::string			Channel::getName() const
{
	return _name;
}

std::string			Channel::getKey() const
{
	return _key;
}

bool				Channel::getModerated() const
{
	return _moderated;
}

bool				Channel::getInvite() const
{
	return _invite;
}

bool				Channel::getTops() const
{
	return _tops;
}

unsigned int		Channel::getLimit() const
{
	return _limit;	
}

std::string			Channel::getTopic() const
{
	return _topic;
}

std::string			Channel::getMode() const
{
	return "+" + _mode;
}

std::string			Channel::getModeparams()
{
	std::string	ret("");

	for (std::vector<std::string>::iterator it(_modeparams.begin()); it != _modeparams.end(); it++)
	{
		if (ret == "")
			ret = *it;
		else
			ret += " " + *it;
	}
	return ret;
}

void				Channel::setKey(const std::string &key)
{
	_key = key;
}

void				Channel::setModerated(const bool &mode)
{
	_moderated = mode;
}

void				Channel::setInvite(const bool &invite)
{
	_invite = invite;
}

void				Channel::setTops(const bool &tops)
{
	_tops = tops;
}

void				Channel::setLimit(const unsigned int &limit)
{
	_limit = limit;
}

void				Channel::setTopic(const std::string &topic)
{
	_topic = topic;
}

void				Channel::addUser(Client *client, bool op)
{
	_users.push_back(client);
	if (op == true)
		_ops.push_back(client);
}

bool				Channel::removeUser(Client *client)
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

bool				Channel::isOp(Client *client)
{
	for (std::vector<Client *>::iterator op(_ops.begin()); op != _ops.end(); op++)
	{
		if ((*op) == client)
		{
			return true;
		}
	}
	return false;
}

void				Channel::removeOp(Client *client)
{
	for (std::vector<Client *>::iterator op(_ops.begin()); op != _ops.end(); op++)
	{
		if ((*op) == client)
		{
			_ops.erase(op);
			return ;
		}
	}
}

void				Channel::addMode(char mode, std::string params)
{
	if (params != "")
	{
		char	tmp[3] = {'k', 'l', '\0'};
		int		count(0);
		bool	isin(false);

		for (size_t i(0); i < _mode.size(); i++)
		{
			for (size_t j(0); j < 2; j++)
			{
				if (_mode[i] == tmp[j])
					count++;
			}
			if (_mode[i] == mode)
			{
				isin = true;
				break ; 
			}
		}
		if (count && isin)
		{
			_modeparams[count- 1] = params;
		}
		else
			_modeparams.push_back(params);
	}
	if (_mode.find(mode) == std::string::npos)
		_mode.push_back(mode);
}

void				Channel::removeMode(char mode)
{
	char	tmp[3] = {'k', 'l', '\0'};
	int		count(0);

	for (size_t h(0); h < 2; h++)
	{
		if (tmp[h] == mode)
		{
			for (size_t i(0); i < _mode.size(); i++)
			{
				for (size_t j(0); j < 2; j++)
				{
					if (_mode[i] == tmp[j])
						count++;
				}
				if (_mode[i] == mode)
					break ;
			}
		}
	}
	_mode.erase(_mode.find(mode, 0), 1);
	if (count)
	{
		_modeparams.erase(_modeparams.begin() + count - 1);
	}
}
