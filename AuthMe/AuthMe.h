#pragma once
#include <iostream>
#include <Windows.h>
#include "Winldap.h"
#include <Lmcons.h>
class AuthMe
{
public:
	AuthMe();
	void connectMe();
	void bindMe();
	void sayMyName();
	~AuthMe();


private:
	LDAP* connection = NULL;
	ULONG returnStatus;

};

