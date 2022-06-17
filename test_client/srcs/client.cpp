/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vico <vico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 13:38:13 by vico              #+#    #+#             */
/*   Updated: 2022/06/16 13:06:22 by vico             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <sys/socket.h> // socket()
#include <netinet/in.h> // struct sockaddr_in
#include <arpa/inet.h> // inet_addr() htons()
#include <unistd.h> // close()

int		main(void)
{
	std::string	command("");
	int	socketClient;
	int	port = 10000;

	socketClient = socket(AF_INET, SOCK_STREAM, 0);
	if (socketClient == -1)
	{
		std::cerr << "ERROR: socket" << std::endl;
		return -1;
	}
	
	struct sockaddr_in	addrClient;

	addrClient.sin_addr.s_addr = INADDR_ANY;
	addrClient.sin_family = AF_INET;
	addrClient.sin_port = htons(port);
	std::cout << "port: " << port << std::endl;

	connect(socketClient, (const sockaddr *)&addrClient, sizeof(addrClient));
	std::cout << "client connecté au serveur, socket: " << socketClient << std::endl;
	
	while (command != "exit")
	{
		std::cout << ">: ";
		getline(std::cin, command);
		if (command.size() > 0)
		{
			if (send(socketClient, command.c_str(), command.size() + 1, 0) == -1)
			{
				std::cerr << "ERROR: send" << std::endl;
				return 0;
			}
			std::cout << "[" << command << "]" << std::endl;
		}
	}
	close(socketClient);
	return 0;
}