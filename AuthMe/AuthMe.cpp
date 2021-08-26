#include "AuthMe.h"

AuthMe::AuthMe() {
	//init
	connection = ldap_sslinit(NULL, LDAP_SSL_PORT, 1);

	if (connection == NULL) {
		printf("we can inint because -> 0x%x.\n", LdapGetLastError());
		ldap_unbind(connection);
		return;
	}



	//set version 
	 returnStatus = ldap_set_option(connection, LDAP_OPT_PROTOCOL_VERSION, (void*)LDAP_VERSION3);
	if (returnStatus == LDAP_SUCCESS) {
		std::cout << "version set successfully" << std::endl;
	}
	else {
		printf("we have err in option:%0lX\n", returnStatus);
		ldap_unbind(connection);
		return;
	}


	//lets connect to the server
	connectMe();


}


void AuthMe::connectMe() {

	returnStatus = ldap_connect(connection, NULL);
	if ( returnStatus == LDAP_SUCCESS) {

		std::cout << "we have connected to the server" << std::endl;
	}
	else {
		printf("We have err in with connect to server 0x%lx.\n", returnStatus);
		ldap_unbind(connection);
		return;
	}

	

	//lets figure out if we are in AD
	bindMe();


}


void AuthMe::bindMe() {
	
	if (ldap_bind_s(connection, NULL, NULL, LDAP_AUTH_NEGOTIATE) == LDAP_SUCCESS) {
		std::cout << "We are in DB"<<std::endl;
	}
	else {
	
		std::cout << "We are not in the DB"<<std::endl;
	
	}


	sayMyName();
	
	
}



void AuthMe::sayMyName() {
	char username[UNLEN + 1];
	DWORD username_len = UNLEN + 1;
	GetUserName(LPWSTR(username), &username_len);
	int a = 0;
	std::cout << "Acount name is ->";
	while (username[a] != '\0') {
	
		std::cout << username[a];
		a+=2;
	
	}
}


AuthMe::~AuthMe() {
	//free up resources
	ldap_unbind(connection);

}
