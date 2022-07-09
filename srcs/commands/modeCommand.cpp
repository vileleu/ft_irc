/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modeCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vico <vico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 02:55:25 by vico              #+#    #+#             */
/*   Updated: 2022/07/09 18:37:38 by vico             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

std::string	Command::verifmask(const std::string &mask) const
{
	std::string	ret(mask);

	if (ret.find('!') != std::string::npos && ret.find('@') != std::string::npos)
	{
		bool	isfirst(false);
		bool	issecond(false);
		size_t	i(0);

		while (i < ret.size())
		{
			if (ret[i] == '!' && isfirst)
				ret.erase(i, 1);
			else if (ret[i] == '!' && !isfirst)
			{
				isfirst = true;
				i++;
			}
			else if (ret[i] == '@' && !isfirst)
				ret.erase(i, 1);
			else if (ret[i] == '@' && issecond)
				ret.erase(i, 1);
			else if (ret[i] == '@' && isfirst && !issecond)
			{
				issecond = true;
				i++;
			}
			else
				i++;
		}
		if (ret.find('!') == (ret.find('@') - 1))
			ret.insert(ret.find('@'), 1, '*');
		if (ret.find('!') == 0)
			ret.insert(0, 1, '*');
		if (ret.find('@') == (ret.size() - 1))
			ret.insert(ret.size(), 1, '*');
		if (ret.find('@') == std::string::npos)
		{
			if (ret.find('!') == (ret.size() - 1))
				ret.append("*@*");
			else
				ret.append("@*");
		}
		return ret;
	}
	else if (ret.find('!') != std::string::npos && ret.find('@') == std::string::npos)
	{
		bool	isfirst(false);
		size_t	i(0);

		while (i < ret.size())
		{
			if (ret[i] == '!' && isfirst)
				ret.erase(i, 1);
			else if (ret[i] == '!' && !isfirst)
			{
				isfirst = true;
				i++;
			}
			else
				i++;
		}
		if (ret.find('!') == (ret.size() - 1))
			ret.insert(ret.size(), 1, '*');
		if (ret.find('!') == 0)
			ret.insert(0, 1, '*');
		return ret + "@*";
	}
	else if (ret.find('!') == std::string::npos && ret.find('@') != std::string::npos)
	{
		size_t	i(0);

		while (i < ret.size())
		{
			if (ret[i] == '@')
				ret.erase(i, 1);
			else
				i++;
		}
		if (!ret.size())
			ret = "*";
	}
	return ret + "!*@*";
}

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
	else if (mode == 't') // toggle the topic settable by channel operator only flag
	{
		ret = 0;
		if (c == '-')
		{
			if (chan->getTops() == true)
			{
				chan->setTops(false);
				chan->removeMode(mode);
			}
		}
		else
		{
			chan->setTops(true);
			chan->addMode(mode, "");
		}
	}
	else if (mode == 'b') // set/remove ban mask to keep users out
	{
		if (c == '-')
		{
			for (std::vector<std::string>::iterator mask(chan->_banmask.begin()); mask != chan->_banmask.end(); mask++)
			{
				if (*mask == it)
				{
					chan->_banmask.erase(mask);
					for (std::vector<Client *>::iterator client(chan->_users.begin()); client != chan->_users.end(); client++)
					{
						_to_send[(*client)->getSocket()] += ":" + _who->getHost() + " MODE " + chan->getName() + " -b " + it + "\n";
					}
					break ;
				}
			}
		}
		else
		{
			if (it != "")
			{
				bool	isin(false);
				for (std::vector<std::string>::iterator mask(chan->_banmask.begin()); mask != chan->_banmask.end(); mask++)
				{
					if (*mask == it)
						isin = true;
				}
				if (!isin)
					chan->_banmask.push_back(verifmask(it));
				for (std::vector<Client *>::iterator client(chan->_users.begin()); client != chan->_users.end(); client++)
				{
					_to_send[(*client)->getSocket()] += ":" + _who->getHost() + " MODE " + chan->getName() + " +b " + it + "\n";
				}
			}
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
					if ((arg[2] == "b" || arg[2] == "+b") && arg.size() == 3)
					{
						for (std::vector<std::string>::iterator mask((*chan)->_banmask.begin()); mask != (*chan)->_banmask.end(); mask++)
						{
							_to_send[_who->getSocket()] += RPL_BANLIST(_who->getHost(), _who->getNickname(), (*chan)->getName(), *mask);
						}
						_to_send[_who->getSocket()] += RPL_ENDOFBANLIST(_who->getHost(), _who->getNickname(), (*chan)->getName());
						return 0;
					}
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
