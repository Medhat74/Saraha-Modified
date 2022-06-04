#pragma once
#include<iostream>
using namespace std;
class Message
{
private:
	int ID , sent_id , recived_id;
	string body;
	bool fav_message;
	

public:
	void set_id(int);
	void set_body(string);
	void set_fav_message(bool);
	void set_recived_id(int);
	void set_sent_id(int);
	Message();

	int get_id();
	string get_body();
	bool get_fav_message();
	int get_recived_id();
	int get_sent_id();

	

};



