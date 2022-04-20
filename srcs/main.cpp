/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vico <vico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 12:12:55 by vico              #+#    #+#             */
/*   Updated: 2022/03/10 13:49:47 by vico             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <sys/socket.h> // socket()
#include <netinet/in.h> // struct sockaddr_in
#include <arpa/inet.h> // inet_addr() htons()
#include <unistd.h> // close()

int		main(void)
{
	int	socketServer;

	socketServer = socket(AF_INET, SOCK_STREAM, 0);
	
	struct sockaddr_in	addrServer;

	addrServer.sin_addr.s_addr = inet_addr("127.0.0.1");
	addrServer.sin_family = AF_INET;
	addrServer.sin_port = htons(15000);

	bind(socketServer, (const sockaddr *)&addrServer, sizeof(addrServer));
	std::cout << "bind success : " << socketServer << std::endl;

	listen(socketServer, 1);
	std::cout << "waiting for clients..." << std::endl;

	int	socketClient;
	struct sockaddr_in	addrClient;
	socklen_t	addrClient_size;

	addrClient_size = sizeof(addrClient);
	socketClient = accept(socketServer, (struct sockaddr *)&addrClient, &addrClient_size);
	std::cout << "client accept" << std::endl;

	close(socketClient);
	close(socketServer);
	return 0;
}