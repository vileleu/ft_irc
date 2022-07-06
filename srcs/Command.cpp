/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vico <vico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 00:26:35 by vico              #+#    #+#             */
/*   Updated: 2022/06/26 01:47:16 by vico             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

Command::Command() : _fail(false), _host(""), _password(""), _check_mode("OovaimnqpsrtklbeI"), _who(NULL)
{
	// all commands we parse
	// if command not here, ignore it
	_check_cmd.push_back("PASS");
	_check_cmd.push_back("NICK");
	_check_cmd.push_back("USER");
	_check_cmd.push_back("PING");
	_check_cmd.push_back("JOIN");
	_check_cmd.push_back("PRIVMSG");
	_check_cmd.push_back("TOPIC");
	_check_cmd.push_back("PART");
	_check_cmd.push_back("KICK");
	_check_cmd.push_back("MODE");
	_check_cmd.push_back("QUIT");
}

Command::~Command()
{
	for (size_t i(0); i < _channels.size(); i++)
	{
		delete _channels[i];
	}
}

/*
** ↓ PRIVATE ↓
*/

std::vector<std::string>	Command::split(const std::string &to_split, char c) const
{
    std::vector<std::string>	arg;
    std::istringstream			in(to_split);
    std::string 				s("");

    while (getline(in, s, c))
	{
        arg.push_back(s);
	}
	return arg;
}

int							Command::alreadyUse(std::string nick)
{
	for (std::vector<Client *>::iterator it(_clients->begin()); it != _clients->end(); it++)
	{
		if ((*it)->getNickname() == nick)
			return -1;
	}
	return 0;
}

void						Command::failedRegister()
{
	for (std::vector<Client *>::iterator client(_clients->begin()); client != _clients->end(); client++)
	{
		if (*client == _who)
		{
			FD_CLR(_who->getSocket(), _read_fds);
			close(_who->getSocket());
			delete *client;
			_clients->erase(client);
			break ;
		}
	}
}

void						Command::registration()
{
	std::vector<std::string>	tmp;

	for (std::vector<std::string>::iterator it(_cmd.begin()); it != _cmd.end(); it++)
	{
		tmp = split(*it, ' ');
		if (it->find("PASS") == 0 && _password != "")
		{
			if (tmp[1] != _password)
			{
				_to_send.insert(std::make_pair(_who->getSocket(), ERR_PASSWDMISMATCH(std::string(""), std::string("*"))));
				_fail = true;
				return ;
			}
			_who->setPass(tmp[1]);
		}
		else if (it->find("NICK") == 0)
		{
			if (_who->getPass() != _password && _password != "")
			{
				_to_send.insert(std::make_pair(_who->getSocket(), ERR_NOTREGISTERED(std::string(""), std::string("*"))));
				_fail = true;
				return ;
			}
			if (alreadyUse(tmp[1]))
				_to_send.insert(std::make_pair(_who->getSocket(), ERR_NICKNAMEINUSE(std::string(""), std::string("*"), tmp[1])));			
			else
				_who->setNickname(tmp[1]);
		}
		else if (it->find("USER") == 0)
		{
			_who->setUsername(tmp[1]);
			_who->setRealname(tmp[4]);
		}
		if (_who->getNickname() != "" && _who->getUsername() != "")
		{
			_who->setHost(_who->getNickname() + "!" + _who->getUsername() + "@" + _host);
			_who->setRegister(true);
		}
	}
	if (_who->isRegister() == true)
		_to_send.insert(std::make_pair(_who->getSocket(), ": NICK :" + _who->getNickname() + "\n" + RPL_WELCOME(_who->getHost(), _who->getNickname())));
}

/*
** ↓ PUBLIC ↓
*/

void						Command::init(std::string to_parse, Client *who)
{
    std::vector<std::string>	arg(split(to_parse, '\n'));

	for (std::vector<std::string>::iterator it(arg.begin()); it != arg.end(); it++)
	{
		for (size_t count(0); count < _check_cmd.size(); count++)
		{
			if ((*it).find(_check_cmd[count]) == 0)
			{
				_cmd.push_back(*it);
				break ;
			}
		}
	}
	_who = who;
}

void						Command::parsing()
{
	if (_who->isRegister() == false)
	{
		return registration();
	}
	for (std::vector<std::string>::iterator it(_cmd.begin()); it != _cmd.end(); it++)
	{
		if ((*it).find("PING") == 0)
			pongCommand();
		else if ((*it).find("PRIVMSG") == 0)
			privmsgCommand(*it);
		else if ((*it).find("NICK") == 0)
		{
			if (nickCommand(*it))
				return ;
		}
		else if ((*it).find("JOIN") == 0)
		{
			if (joinCommand(*it))
				return ;
		}
		else if ((*it).find("PART") == 0)
		{
			if (partCommand(*it))
				return ;
		}
		else if ((*it).find("TOPIC") == 0)
		{
			if (topicCommand(*it))
				return ;
		}
		else if ((*it).find("KICK") == 0)
		{
			if (kickCommand(*it))
				return ;
		}
		else if ((*it).find("MODE") == 0)
		{
			if (modeCommand(*it))
				return ;
		}
		else if ((*it).find("QUIT") == 0)
			return quitCommand(*it);
	}
}

void						Command::clean()
{
	if (_fail == true)
	{
		failedRegister();
		_fail = false;
	}
	_who = NULL;
	_cmd.clear();
	_to_send.clear();
}

void						Command::setCommand(std::string password, std::string host, std::vector<Client *> *clients, fd_set *read_fds)
{
	_password = password;
	_host = host;
	_clients = clients;
	_read_fds = read_fds;
}

std::map<int, std::string>	Command::getTosend() const
{
	return _to_send;
}
