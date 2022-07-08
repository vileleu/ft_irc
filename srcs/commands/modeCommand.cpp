/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modeCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vico <vico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 02:55:25 by vico              #+#    #+#             */
/*   Updated: 2022/07/08 12:51:55 by vico             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

int			Command::execmode(char c, char mode, std::string it, Channel *chan)
{
	int	ret(1);

	std::cout << "mode = " << mode << ", pref = " << c << ", param = " << it << std::endl;
	if (mode == 'o') // give/take channel operator privilege
	{
		bool	usin(false);
		
		if (it == "")
			it = "*";
		for (std::vector<Client *>::iterator client(chan->_users.begin()); client != chan->_users.end(); client++)
		{
			if ((*client)->getNickname() == it)
			{
				usin = true;
				if (c == '-')
				{
					if (chan->isOp(*client) == true)
					{
						chan->removeOp(*client);
						for (client = chan->_users.begin(); client != chan->_users.end(); client++)
						{
							_to_send[(*client)->getSocket()] += ":" + _who->getHost() + " MODE " + chan->getName() + " -o " + it + "\n";
						}
					}
				}
				else
				{
					if (chan->isOp(*client) == false)
					{
						chan->_ops.push_back(*client);
						for (client = chan->_users.begin(); client != chan->_users.end(); client++)
						{
							_to_send[(*client)->getSocket()] += ":" + _who->getHost() + " MODE " + chan->getName() + " +o " + it + "\n";
						}
					}
				}
				break ;
			}
		}
		if (usin == false)
			_to_send[_who->getSocket()] += ERR_USERNOTINCHANNEL(_who->getHost(), _who->getNickname(), it, chan->getName());
	}
	else if (mode == 'k') // set/remove the channel key (password)
	{
		if (c == '-')
		{
			ret = 0;
			if (chan->getKey() != "")
			{
				chan->setKey("");
				chan->removeMode(mode);
			}
		}
		else
		{
			if (it != "")
			{
				chan->setKey(it);
				chan->addMode(mode, it);
			}
		}
	}
	else if (mode == 'l') // set/remove the user limit to channel
	{
		if (c == '-')
		{
			ret = 0;
			if (chan->getLimit())
			{
				chan->setLimit(0);
				chan->removeMode(mode);
			}
		}
		else
		{
			if (it != "")
			{
				chan->setLimit(std::atoi(it.c_str()));
				chan->addMode(mode, it);
			}
		}
	}
	else if (mode == 'i') // toggle the invite-only channel flag
	{
		ret = 0;
		if (c == '-')
		{
			if (chan->getInvite() == true)
			{
				chan->setInvite(false);
				chan->removeMode(mode);
			}
		}
		else
		{
			chan->setInvite(true);
			chan->addMode(mode, "");
		}
	}
	else if (mode == 'm') // toggle the moderated channel
	{
		ret = 0;
		if (c == '-')
		{
			if (chan->getModerated() == true)
			{
				chan->setModerated(false);
				chan->removeMode(mode);
			}
		}
		else
		{
			chan->setModerated(true);
			chan->addMode(mode, "");
		}
	}
	return ret;
}

int			Command::modeCommand(std::string cmd)
{
	std::vector<std::string>	arg(split(cmd, ' '));

	if (arg.size() < 2)
	{
		_to_send[_who->getSocket()] += ERR_NEEDMOREPARAMS(_who->getHost(), _who->getNickname(), arg[0]);
		return 0;
	}
	bool	exist(false);
	bool	isin(false);
	bool	isop(false);

	for (std::vector<Channel *>::iterator chan(_channels.begin()); chan != _channels.end(); chan++)
	{
		if ((*chan)->getName() == arg[1])
		{
			isin = false;
			exist = true;
			for (std::vector<Client *>::iterator client((*chan)->_users.begin()); client != (*chan)->_users.end(); client++)
			{
				if (*client == _who)
				{
					isop = false;
					isin = true;
					if (arg.size() < 3)
					{
						_to_send[_who->getSocket()] += RPL_CHANNELMODEIS(_who->getHost(), _who->getNickname(), arg[1], (*chan)->getMode(), (*chan)->getModeparams());
						return 0;
					}
					else if (arg[2] == "b")
						return 0;
					for (std::vector<Client *>::iterator op((*chan)->_ops.begin()); op != (*chan)->_ops.end(); op++)
					{
						if (*op == _who)
						{
							isop = true;
							std::vector<std::string>::iterator	it(arg.begin() + 3);
							std::string							send(":" + _who->getHost() + " MODE " + arg[1] + " ");
							bool								ismode(false);
							char								c(0);

							for (size_t i(0); i < arg[2].size(); i++)
							{
								ismode = false;
								if (arg[2][i] == '+' || arg[2][i] == '-')
									c = arg[2][i++];
								for (size_t j(0); arg[2][i] && j < _check_mode.size(); j++)
								{
									if (arg[2][i] == _check_mode[j])
									{
										ismode = true;
										if (it == arg.end())
											execmode(c, arg[2][i], "", *chan);
										else
										{
											if (execmode(c, arg[2][i], *it, *chan))
												it++;
										}
										break ;
									}
								}
								if (ismode == false && arg[2][i])
								{
									_to_send[_who->getSocket()] += ERR_UNKNOWNMODE(_who->getHost(), _who->getNickname(), arg[1], arg[2][i]);
								}
								if (i == arg[2].size())
									break ;
							}
							send += (*chan)->getMode() + "\n";
							for (std::vector<Client *>::iterator cl((*chan)->_users.begin()); cl != (*chan)->_users.end(); cl++)
							{
								_to_send[(*cl)->getSocket()] += send;
							}
							break ;
						}
					}
					if (isop == false)
					{
						_to_send[_who->getSocket()] += ERR_CHANOPRIVSNEEDED(_who->getHost(), _who->getNickname(), arg[1]);
						return 0;
					}
					break ;
				}
			}
			if (isin == false)
			{
				_to_send[_who->getSocket()] += ERR_NOTONCHANNEL(_who->getHost(), _who->getNickname(), arg[1]);
				return 0;
			}
			break;
		}
	}
	if (exist == false)
	{
		for (std::vector<Client *>::iterator client(_clients->begin()); client != _clients->end(); client++)
		{
			if ((*client)->getNickname() == arg[1])
				return 0;
		}
		_to_send[_who->getSocket()] += ERR_NOSUCHCHANNEL(_who->getHost(), _who->getNickname(), arg[1]);
		return 0;
	}
	return 0;
}