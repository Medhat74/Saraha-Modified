#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <list>
#include "Message.h"
//#include "File.h"

using namespace std;
class User
{
public:

	

	public:
	User();
	User(int id, string name, string pass);
	~User();
	void read_messages(vector<Message> all_msg);
	void add_contact(int user_id);
	bool search(int contact_id);
	void add_Fav(Message msg , vector<Message> &all_msg);
	void undo_message(vector<Message>& all_msg);
	void remove_message();
	void view_all_contacts();
	void view_all_fav_message(vector<Message> all_msg);
	void send_message(int con_id, string msg_body, vector<Message>& all_msg);
	void view_all_recieved_message(vector<Message> all_msg);
	void view_recieved_message_from_contact(int con_id , vector<Message> all_msg);
	void view_all_sent_message(vector<Message> all_msg);
	void set_contacts(int cont_id);
	void remove_oldest_fav_message(vector<Message>& all_msg);
	void set_user_name(string name);
	void set_password(string pass);
	void set_id(int id);
	
	string get_user_name();
	string get_password();
	int get_id();



	Message get_message(int num , vector<Message>all_msg);
	int get_size_of_recived_msg(vector<Message>all_msg);



	/*
	void set_recived_message(Message msg);
	void set_sent_message(Message msg);
	void set_recived_message(Message msg);
	*/
	

private :

	string user_name , password;
	int ID;
	vector<int> contacts;
	stack<Message> recived_messages , sent_message;
	queue<Message> fav_msg;


	void clear_messages();
	



	

};

