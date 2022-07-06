/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vico <vico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 19:39:18 by vico              #+#    #+#             */
/*   Updated: 2022/07/06 02:44:50 by vico             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_HPP
#define DEFINE_HPP

/*
**  ↓ COMMANDS REPLIES ↓
*/

#define RPL_WELCOME(host, nick) ":" + host + " 001 " + nick + " :Bienvenue chakal " + host + "\n"

#define RPL_CHANNELMODEIS(host, nick, channel, mode, modeparams) ":" + host + " 324 " + nick + " " + channel + " " + mode + " " + modeparams + "\n"

#define RPL_NOTOPIC(host, nick, channel) ":" + host + " 331 " + nick + " " + channel + " :No topic is set\n"

#define RPL_TOPIC(host, nick, channel, topic) ":" + host + " 332 " + nick + " " + channel + " :" + topic + "\n"

#define RPL_NAMREPLY(host, nick, channel) ":" + host + " 353 " + nick + " = " + channel + " :"
/*
"@" is used for secret channels, "*" for private channels, and "=" for others (public channels).
*/
#define RPL_ENDOFNAMES(host, nick, channel) ":" + host + " 366 " + nick + " " + channel + " :End of NAMES list\n"
/*
To reply to a NAMES message, a reply pair consisting
of RPL_NAMREPLY and RPL_ENDOFNAMES is sent by the
server back to the client.  If there is no channel
found as in the query, then only RPL_ENDOFNAMES is
returned.  The exception to this is when a NAMES
message is sent with no parameters and all visible
channels and contents are sent back in a series of
RPL_NAMEREPLY messages with a RPL_ENDOFNAMES to mark
the end.
*/

/*
**  ↓ ERRORS REPLIES ↓
*/

#define ERR_NOSUCHNICK(host, nick, n) ":" + host + " 401 " + nick + " " + n + " :No such nick/channel\n"
/*
 Used to indicate the nickname parameter supplied to a
            command is currently unused.
*/
#define ERR_NOSUCHSERVER(host, nick, server) ":" + host + " 402 " + nick + " " + server + " :No such server\n"
/*
Used to indicate the server name given currently
           does not exist.
*/
#define ERR_NOSUCHCHANNEL(host, nick, channel) ":" + host + " 403 " + nick + " " + channel + " :No such channel\n"
/*
Used to indicate the given channel name is invalid.
*/
#define ERR_CANNOTSENDTOCHAN(host, nick, channel) ":" + host + " 404 " + nick + " " + channel + " :Cannot send to channel\n"
/*
Sent to a user who is either (a) not on a channel
           which is mode +n or (b) not a chanop (or mode +v) on
           a channel which has mode +m set or where the user is
           banned and is trying to send a PRIVMSG message to
           that channel.
*/
#define ERR_TOOMANYCHANNELS(host, nick, channel) ":" + host + " 405 " + nick + " " + channel + " :You have joined too many channels\n"
/*
Sent to a user when they have joined the maximum
           number of allowed channels and they try to join
           another channel.
*/
#define ERR_WASNOSUCHNICK(host, nick, n) ":" + host + " 406 " + nick + " " + n + " :There was no such nickname\n"
/*
Returned by WHOWAS to indicate there is no history
           information for that nickname.
*/

/*
407 ERR_TOOMANYTARGETS "<target> :<error code> recipients. <abort message>"
*/

/*
Returned to a client which is attempting to send a
           PRIVMSG/NOTICE using the user@host destination format
           and for a user@host which has several occurrences.
*/

/*
Returned to a client which trying to send a
           PRIVMSG/NOTICE to too many recipients.
*/

/*
Returned to a client which is attempting to JOIN a safe
           channel using the shortname when there are more than one
           such channel.
*/
#define ERR_NOSUCHSERVICE(host, nick, service) ":" + host + " 408 " + nick + " " + service + " :No such service\n"
/*
Returned to a client which is attempting to send a SQUERY
           to a service which does not exist.
*/
#define ERR_NOORIGIN(host, nick) ":" + host + " 409 " + nick + " :No origin specified\n"
/*
PING or PONG message missing the originator parameter.
*/

/*
411 ERR_NORECIPIENT ":No recipient given (<command>)"
412 ERR_NOTEXTTOSEND ":No text to send"
413 ERR_NOTOPLEVEL "<mask> :No toplevel domain specified"
414 ERR_WILDTOPLEVEL "<mask> :Wildcard in toplevel domain"
415 ERR_BADMASK "<mask> :Bad Server/host mask"
*/

/*
412 - 415 are returned by PRIVMSG to indicate that
           the message wasn't delivered for some reason.
           ERR_NOTOPLEVEL and ERR_WILDTOPLEVEL are errors that
           are returned when an invalid use of
           "PRIVMSG $<server>" or "PRIVMSG #<host>" is attempted.
*/
#define ERR_UNKNOWNCOMMAND(host, nick, command) ":" + host + " 421 " + nick + " " + nick + " :" + command + " :Unknown command\n"
/*
Returned to a registered client to indicate that the
           command sent is unknown by the server.
*/
#define ERR_NOMOTD(host, nick) ":" + host + " 422 " + nick + " " + nick + " :MOTD File is missing\n"
/*
Server's MOTD file could not be opened by the server.
*/
#define ERR_NOADMININFO(host, nick, server) ":" + host + " 423 " + nick + " " + server + " :No administrative info available\n"
/*
Returned by a server in response to an ADMIN message
           when there is an error in finding the appropriate
           information.
*/

/*
424 ERR_FILEERROR ":File error doing <file op> on <file>"
*/

/*
Generic error message used to report a failed file
           operation during the processing of a message.
*/
#define ERR_NONICKNAMEGIVEN(host, nick, n) ":" + host + " 431 " + nick + " " + n + " :No nickname given\n"
/*
Returned when a nickname parameter expected for a
           command and isn't found.
*/
#define ERR_ERRONEUSNICKNAME(host, nick, n) ":" + host + " 432 " + nick + " :" + n + " :Erroneous nickname\n"
/*
Returned after receiving a NICK message which contains
           characters which do not fall in the defined set.  See
           section 2.3.1 for details on valid nicknames.
*/
#define ERR_NICKNAMEINUSE(host, nick, n) ":" + host + " 433 " + nick + " " + n + " :Nickname is already in use\n"
/*
Returned when a NICK message is processed that results
           in an attempt to change to a currently existing
           nickname.
*/

/*
436 ERR_NICKCOLLISION "<nick> :Nickname collision KILL from <user>@<host>"
*/

/*
Returned by a server to a client when it detects a
           nickname collision (registered of a NICK that
           already exists by another server).
*/
#define ERR_UNAVAILRESOURCE(host, nick, n, channel) ":" + host + " 437 " + nick + " " + n + "/" + channel + " :Nick/channel is temporarily unavailable\n"
/*
Returned by a server to a user trying to join a channel
           currently blocked by the channel delay mechanism.
*/

/*
Returned by a server to a user trying to change nickname
           when the desired nickname is blocked by the nick delay
           mechanism.
*/
#define ERR_USERNOTINCHANNEL(host, nick, n, channel) ":" + host + " 441 " + nick + " " + n + " " + channel + " :They aren't on that channel\n"
/*
Returned by the server to indicate that the target
           user of the command is not on the given channel.
*/
#define ERR_NOTONCHANNEL(host, nick, channel) ":" + host + " 442 " + nick + " " + channel + " :You're not on that channel\n"
/*
Returned by the server whenever a client tries to
           perform a channel affecting command for which the
           client isn't a member.
*/
#define ERR_USERONCHANNEL(host, nick, user, channel) ":" + host + " 443 " + nick + " " + user + " " + channel + " :is already on channel\n"
/*
Returned when a client tries to invite a user to a
           channel they are already on.
*/
#define ERR_NOLOGIN(host, nick, user) ":" + host + " 444 " + nick + " " + user + " :User not logged in\n"
/*
Returned by the summon after a SUMMON command for a
           user was unable to be performed since they were not
           logged in.
*/
#define ERR_SUMMONDISABLED(host, nick) ":" + host + " 445 " + nick + " :SUMMON has been disabled\n"
/*
Returned as a response to the SUMMON command.  MUST be
           returned by any server which doesn't implement it.
*/
#define ERR_USERSDISABLED(host, nick) ":" + host + " 446 " + nick + " :USERS has been disabled\n"
/*
Returned as a response to the USERS command.  MUST be
           returned by any server which does not implement it.
*/
#define ERR_NOTREGISTERED(host, nick) ":" + host + " 451 " + nick + " :You have not registered\n"
/*
Returned by the server to indicate that the client
           MUST be registered before the server will allow it
           to be parsed in detail.
*/
#define ERR_NEEDMOREPARAMS(host, nick, command) ":" + host + " 461 " + nick + " " + command + " :Not enough parameters\n"
/*
Returned by the server by numerous commands to
           indicate to the client that it didn't supply enough
           parameters.
*/
#define ERR_ALREADYREGISTRED(host, nick) ":" + host + " 462 " + nick + " :Unauthorized command (already registered)\n"
/*
Returned by the server to any link which tries to
           change part of the registered details (such as
           password or user details from second USER message).
*/
#define ERR_NOPERMFORHOST(host, nick) ":" + host + " 463 " + nick + " :Your host isn't among the privileged\n"
/*
Returned to a client which attempts to register with
           a server which does not been setup to allow
           connections from the host the attempted connection
           is tried.
*/
#define ERR_PASSWDMISMATCH(host, nick) ":" + host + " 464 " + nick + " :Password incorrect\n"
/*
Returned to indicate a failed attempt at registering
           a connection for which a password was required and
           was either not given or incorrect.
*/
#define ERR_YOUREBANNEDCREEP(host, nick) ":" + host + " 465 " + nick + " :You are banned from this server\n"
/*
Returned after an attempt to connect and register
           yourself with a server which has been setup to
           explicitly deny connections to you.
*/
#define ERR_YOUWILLBEBANNED(host, nick) ":" + host + " 466 " + nick + "\n"
/*
Sent by a server to a user to inform that access to the
           server will soon be denied.
*/
#define ERR_KEYSET(host, nick, channel) ":" + host + " 467 " + nick + " " + channel + " :Channel key already set\n"

#define ERR_CHANNELISFULL(host, nick, channel) ":" + host + " 471 " + nick + " " + channel + " :Cannot join channel (+l)\n"

#define ERR_UNKNOWNMODE(host, nick, channel, char) ":" + host + " 472 " + nick + " " + char + " :is unknown mode char to me for " + channel + "\n"

#define ERR_INVITEONLYCHAN(host, nick, channel) ":" + host + " 473 " + nick + " " + channel + " :Cannot join channel (+i)\n"

#define ERR_BANNEDFROMCHAN(host, nick, channel) ":" + host + " 474 " + nick + " " + channel + " :Cannot join channel (+b)\n"

#define ERR_BADCHANNELKEY(host, nick, channel) ":" + host + " 475 " + nick + " " + channel + " :Cannot join channel (+k)\n"

#define ERR_BADCHANMASK(host, nick, channel) ":" + host + " 476 " + nick + " " + channel + " :Bad Channel Mask\n"

#define ERR_NOCHANMODES(host, nick, channel) ":" + host + " 477 " + nick + " " + channel + " :Channel doesn't support modes\n"

#define ERR_BANLISTFULL(host, nick, channel, char) ":" + host + " 478 " + nick + " " + channel + " " + char + " :Channel list is full\n"

#define ERR_NOPRIVILEGES(host, nick, channel) ":" + host + " 481 " + nick + " :Permission Denied- You're not an IRC operator\n"
/*
Any command requiring operator privileges to operate
           MUST return this error to indicate the attempt was
           unsuccessful.
*/
#define ERR_CHANOPRIVSNEEDED(host, nick, channel) ":" + host + " 482 " + nick + " " + channel + " :You're not channel operator\n"
/*
Any command requiring 'chanop' privileges (such as
           MODE messages) MUST return this error if the client
           making the attempt is not a chanop on the specified
           channel.
*/
#define ERR_CANTKILLSERVER(host, nick) ":" + host + " 483 " + nick + " :You can't kill a server!\n"
/*
Any attempts to use the KILL command on a server
           are to be refused and this error returned directly
           to the client.
*/
#define ERR_RESTRICTED(host, nick) ":" + host + " 484 " + nick + " :Your connection is restricted!\n"
/*
Sent by the server to a user upon connection to indicate
           the restricted nature of the connection (user mode "+r").
*/
#define ERR_UNIQOPPRIVSNEEDED(host, nick) ":" + host + " 485 " + nick + " :You're not the original channel operator\n"
/*
Any MODE requiring "channel creator" privileges MUST
           return this error if the client making the attempt is not
           a chanop on the specified channel.
*/
#define ERR_NOOPERHOST(host, nick) ":" + host + " 491 " + nick + " :No O-lines for your host\n"
/*
If a client sends an OPER message and the server has
           not been configured to allow connections from the
           client's host as an operator, this error MUST be
           returned.
*/
#define ERR_UMODEUNKNOWNFLAG(host, nick) ":" + host + " 501 " + nick + " :Unknown MODE flag\n"
/*
Returned by the server to indicate that a MODE
           message was sent with a nickname parameter and that
           the a mode flag sent was not recognized.
*/
#define ERR_USERSDONTMATCH(host, nick) ":" + host + " 502 " + nick + " :Cannot change mode for other users\n"
/*
Error sent to any user trying to view or change the
           user mode for a user other than themselves.
*/

#endif
