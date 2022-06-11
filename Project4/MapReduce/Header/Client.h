#ifndef __CLIENT_H_INCLUDED__
#define __CLIENT_H_INCLUDED__

///////////////////////////////////////////////////////////////////
//  Client.h    -  header file for Client class  //
//                                                               //
//  Language:     Visual C++ 2022, ver 17.1.3                    //
//  Application:  MapReduce Project 3                            //
//  Course:		  CSE687 SP22 - Object Oriented Design           //
//  Authors:      Stephanie Eordanidis                           //
//                JT Washington                                  //
//                Syracuse University                            //
//                {sleordan,jwashi05}@syr.edu                    //
///////////////////////////////////////////////////////////////////

#pragma once

#include <winsock2.h>

class Client {
public:
	int SendNewMessage(const char*);
	void ShutDownServer();

private:
	WSADATA wsaData;
	SOCKET ConnectSocket = INVALID_SOCKET;
};

#endif