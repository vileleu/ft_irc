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

Command::Command() : _host(""), _password(""), _is_init(false), _who(NULL)
{
	// all commands we handle
	// if command not here send ERR_UNKNOWNCOMMAND
	_check_cmd.push_back("PASS");
	_check_cmd.push_back("NICK");
	_check_cmd.push_back("USER");
}

Command::~Command()
{
}

/*
** ↓ PRIVATE ↓
*/

std::vector<std::string>	Command::split(std::string to_split, char c) const
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

/*int							Command::passCommand(std::string cmd)
{
	std::vector<std::string>	arg(split(cmd, ' '));

	if (arg.size() < 2)
	{
		_to_send.insert(std::make_pair(_who->getSocket(), ERR_NEEDMOREPARAMS(_who->getHost(), _who->getNickname(), arg[0])));
		return -1;
	}
	else if (arg[1] != _password)
	{
		_to_send.insert(std::make_pair(_who->getSocket(), ERR_PASSWDMISMATCH(_who->getHost(), _who->getNickname())));
		return -1;
	}
	else if (_who->isRegister() == true)
	{
		_to_send.insert(std::make_pair(_who->getSocket(), ERR_ALREADYREGISTRED(_who->getHost(), _who->getNickname())));
		return -1;		
	}
	return 0;
}

int							Command::nickCommand(std::string cmd)
{
	std::vector<std::string>	arg(split(cmd, ' '));

	_who->setNickname(arg[1]);
	_check_send.insert(std::make_pair(_who->getSocket(), ": NICK :" + _who->getNickname() + "\n" + RPL_WELCOME(_who->getHost(), _who->getNickname())));
}

int							Command::userCommand(std::string cmd)
{
}*/

int							Command::registration()
{
	std::vector<std::string>	tmp;

	for (std::vector<std::string>::iterator it(_cmd.begin()); it != _cmd.end(); it++)
	{
		tmp = split(*it, ' ');
		if (it->find("PASS") == 0)
		{
			_who->setPass(tmp[1]);
		}
		if (it->find("NICK") == 0)
		{
			_who->setNickname(tmp[1]);
		}
		if (it->find("USER") == 0)
		{
			_who->setUsername(tmp[1]);
			_who->setHost(_who->getNickname() + "!" + _who->getUsername() + "@" + _host);
			_who->setRealname(tmp[4]);
			_who->setRegister(true);
		}
	}
	if (_who->isRegister() == true)
	{
		if (_who->getPass() == "")
		{
			_to_send.insert(std::make_pair(_who->getSocket(), ERR_NOTREGISTERED(_who->getHost(), _who->getNickname())));
			return -1;
		}
		else if (_who->getPass() != _password)
		{
			_to_send.insert(std::make_pair(_who->getSocket(), ERR_PASSWDMISMATCH(_who->getHost(), _who->getNickname())));
			return -1;
		}
		_check_send.insert(std::make_pair(_who->getSocket(), ": NICK :" + _who->getNickname() + "\n" + RPL_WELCOME(_who->getHost(), _who->getNickname())));
	}
	return 0;
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
	_is_init = true;
}

void						Command::parsing()
{
	if (_who->isRegister() == false)
	{
		if (registration())
			return ;
		_to_send = _check_send;
		return ;
	}
	for (std::vector<std::string>::iterator it(_cmd.begin()); it != _cmd.end(); it++)
	{
		/*if ((*it).find("PASS") == 0) // PASS
		{
			if (passCommand(*it))
			{
				return ;
			}
		}
		else if ((*it).find("NICK") == 0) // NICK
		{
			if (nickCommand(*it))
			{
				return ;
			}
		}
		else if ((*it).find("USER") == 0) // USER
		{
			if (userCommand(*it))
			{
				return ;
			}
		}
		else
		{
			_to_send.insert(std::make_pair(_who->getSocket(), ERR_UNKNOWNCOMMAND(_who->getHost(), _who->getNickname(), (*it).substr(0, (*it).find(' ')))));
			return ;
		}*/
	}
	_to_send = _check_send;
}

void						Command::clean()
{
	_who = NULL;
	_cmd.clear();
	_to_send.clear();
	_check_send.clear();
	_is_init = false;
}

void						Command::setCommand(std::string password, std::string host)
{
	_password = password;
	_host = host;
}

std::map<int, std::string>	Command::getTosend() const
{
	return _to_send;
}
