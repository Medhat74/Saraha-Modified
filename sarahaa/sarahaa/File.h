#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <list>
#include <fstream>
#include "User.h"
using namespace std;

class File
{
public:
	File();
	bool read_user_file(User &user);
	void read_messages(vector<Message>& all_msg);
	void read_contacts(User &user);
	User check_user(string user_name, string pass); 
	void add_users(User user);
	void write_messages(vector<Message>& all_msg);
	void add_contact(int id_user,int id_contact);
	int last_id();
	
};


