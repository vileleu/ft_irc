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

Command::Command() : _host(""), _password(""), _check_mode("OovaimnqpsrtklbeI"), _who(NULL)
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
	_check_cmd.push_back("INVITE");
	_check_cmd.push_back("MODE");
	_check_cmd.push_back("NOTICE");
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

void						Command::registration()
{
	std::vector<std::string>	tmp;

	for (std::vector<std::string>::iterator it(_cmd.begin()); it != _cmd.end(); it++)
	{
		if (it->find("PASS") != 0 && it->find("NICK") != 0 && it->find("USER") != 0)
		{
			_to_send.insert(std::make_pair(_who->getSocket(), ERR_NOTREGISTERED(std::string(""), std::string("*"))));
			return ;
		}
		tmp = split(*it, ' ');
		if (it->find("PASS") == 0 && _password != "")
		{
			if (tmp[1] != _password)
			{
				_to_send.insert(std::make_pair(_who->getSocket(), ERR_PASSWDMISMATCH(std::string(""), std::string("*"))));
				return ;
			}
			_who->setPass(tmp[1]);
		}
		else if (it->find("NICK") == 0)
		{
			if (_who->getPass() != _password && _password != "")
			{
				_to_send.insert(std::make_pair(_who->getSocket(), ERR_NOTREGISTERED(std::string(""), std::string("*"))));
				return ;
			}
			if (tmp.size() < 2 || nickCheck(tmp[1]))
			{
				_to_send.insert(std::make_pair(_who->getSocket(), ERR_ERRONEUSNICKNAME(_who->getHost(), _who->getNickname(), tmp[1])));
				return ;
			}
			for (size_t i(0); i < tmp[1].size(); i ++)
			{
				tmp[1][i] = std::tolower(tmp[1][i]);
			}
			if (alreadyUse(tmp[1]))
				_to_send.insert(std::make_pair(_who->getSocket(), ERR_NICKNAMEINUSE(std::string(""), std::string("*"), tmp[1])));			
			else
				_who->setNickname(tmp[1]);
		}
		else if (it->find("USER") == 0)
		{
			if (_who->getPass() != _password && _password != "")
			{
				_to_send.insert(std::make_pair(_who->getSocket(), ERR_NOTREGISTERED(std::string(""), std::string("*"))));
				return ;
			}
			if (tmp.size() < 5)
			{
				_to_send.insert(std::make_pair(_who->getSocket(), ERR_NEEDMOREPARAMS(std::string(""), std::string("*"), tmp[0])));
				return ;
			}
			_who->setUsername(tmp[1]);
			_who->setRealname(tmp[4]);
		}
		if (_who->getNickname() != "" && _who->getUsername() != "")
		{
			_who->setHost(_who->getNickname() + "!" + _who->getUsername() + "@" + _who->getIp());
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
	std::string					print("");

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
	for (std::vector<std::string>::iterator it(_cmd.begin()); it != _cmd.end() ; it++)
	{
		if (print == "")
			print = *it + "\n";
		else
			print += " " + *it + "\n";
	}
	if (print != "")
		std::cout << "recv socket " << _who->getSocket() << " message --> \033[1;35m" << print << "\033[0m" << std::endl;
}

void						Command::parsing()
{
	if (_who->isRegister() == false)
		return registration();
	for (std::vector<std::string>::iterator it(_cmd.begin()); it != _cmd.end(); it++)
	{
		if ((*it).find("PING") == 0)
		{
			if (pongCommand(*it))
				return ;
		}
		else if ((*it).find("PRIVMSG") == 0)
		{
			if (privmsgCommand(*it))
				return ;
		}
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
		else if ((*it).find("INVITE") == 0)
		{
			if (inviteCommand(*it))
				return ;
		}
		else if ((*it).find("NOTICE") == 0)
		{
			if (noticeCommand(*it))
				return ;
		}
		else if ((*it).find("QUIT") == 0)
			return quitCommand(*it);
	}
}

void						Command::clean()
{
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
