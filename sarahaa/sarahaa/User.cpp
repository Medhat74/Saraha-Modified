#include "User.h"
#include "File.h"
#include <windows.h>

User::User(int id,string name,string pass)
{
	this->ID = id;
	this->user_name = name;
	this->password = pass;

}
User::User()
{
	this->ID = NULL;
	this->user_name = "none";
	this->password = "none";

}
void User::set_contacts(int con_id) {
	contacts.push_back(con_id);
}

void User::add_contact(int cont_id) {
	set_contacts(cont_id);
	File file;
	file.add_contact(ID , cont_id);
	
}
bool User::search(int contact_id) {
	for (int i = 0; i < contacts.size(); i++) {
		if (contact_id == contacts[i]) {
			return true;
		}
	}
	return false;
}
void User::add_Fav(Message msg , vector <Message> &all_msg ) {
	if (fav_msg.empty())
		read_messages(all_msg);
	
	if (fav_msg.size() > 4)
		remove_oldest_fav_message(all_msg);

	fav_msg.push(msg);
	for (int i = 0; i < all_msg.size(); i++) {
		if (msg.get_id() == all_msg[i].get_id()) {
			all_msg[i].set_fav_message (1);
		}
	}
}
void User::undo_message(vector<Message> &all_msg) {
	if (sent_message.empty())
		read_messages(all_msg);
	sent_message.pop();
	all_msg.pop_back();

}

void User::view_all_contacts() {
	if (contacts.empty()) {
		HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(h, 12);
		cout << "\n you dont have any contact";
		return;
	}
	for (int i = 0; i < contacts.size(); i++) {
		cout << contacts[i] << endl;
	}
}
void User::view_all_fav_message(vector<Message> all_msg) {
	if (fav_msg.empty())
		read_messages(all_msg);
	if (fav_msg.empty()) {
		HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(h, 12);
		cout << "\n you dont have any massege";
		return;
	}
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, 15);
	cout << endl << ".........................................................................................................................." << endl
		<< " \t \t \t \t \t \t Your Recieved messages " << endl << ".........................................................................................................................." << endl;
	while (!fav_msg.empty()) {
		SetConsoleTextAttribute(h, 6);
		cout << "\tFrom |=============> " << fav_msg.front().get_sent_id() << endl;
		cout << "\tThe message |====> " << " ' " << fav_msg.front().get_body() << " ' " << endl;
		fav_msg.pop();
		cout << ".........................................................................................................................." << endl;
	}

}
void User::send_message(int con_id , string msg_body,vector<Message> &all_msg) {
	Message msg;
	msg.set_recived_id(con_id);
	msg.set_body ( msg_body );
	msg.set_fav_message (0);
	msg.set_sent_id(ID);
	msg.set_id(ID * 100 + con_id * 10 + msg.get_body().size());
	all_msg.push_back(msg);

}
void User::view_all_recieved_message(vector<Message> all_msg) {
	if (recived_messages.empty())
		read_messages(all_msg);
	if (recived_messages.empty()) {
		HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(h, 12);
		cout << "\n you dont have any massege";
		return;
	}
	int counter = 1;
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, 15);
	cout << endl << ".........................................................................................................................." << endl
		<< " \t \t \t \t \t \t Your Recieved messages " << endl << ".........................................................................................................................." << endl;
	while (!recived_messages.empty()) {
		SetConsoleTextAttribute(h, 6);
		cout << endl;
		cout << "[" << counter << "] :: ";
		cout << "\tFrom |=============> " << recived_messages.top().get_sent_id() << endl;
		cout << "\tThe message |====> " << " ' " << recived_messages.top().get_body() << " ' " << endl;
		recived_messages.pop();
		cout << ".........................................................................................................................." << endl;
		counter++;
	}
}
void User::view_recieved_message_from_contact(int con_id,vector<Message> all_msg) {
	if (recived_messages.empty())
		read_messages(all_msg);
	if (recived_messages.empty()) {
		HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(h, 12);
		cout << "\n you dont have any massege";
		return;
	}
	bool found = false;
	
	
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, 15);
	cout << endl << ".........................................................................................................................." << endl
		<< " \t \t \t \t \t \t Your Recieved messages " << endl << ".........................................................................................................................." << endl;
	while (!recived_messages.empty()) {

		if (recived_messages.top().get_sent_id() == con_id) {
			SetConsoleTextAttribute(h, 6);
			cout << "\tFrom |=============> " << recived_messages.top().get_sent_id() << endl;
			cout << "\tThe message |====> " << " \" " << recived_messages.top().get_body() << " \" " << endl;
			recived_messages.pop();
			cout << ".........................................................................................................................." << endl;
			found = true;
		}
		else
			recived_messages.pop();

	}
	if (!found) {
		//HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(h, 12);
		cout << "\n you dont have any massege";
	}
}
void User::view_all_sent_message(vector<Message> all_msg) {
	if (sent_message.empty())
		read_messages(all_msg);
	if (sent_message.empty()) {
		HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(h, 12);
		cout << "\n you dont send any massege";
		return;
	}
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, 15);
	cout << endl << ".........................................................................................................................." << endl
		<< " \t \t \t \t \t \t Your sent messages " << endl << ".........................................................................................................................." << endl;
	while (!sent_message.empty()) {
		//cout << ".............................................................................................................................." << endl;
		SetConsoleTextAttribute(h, 6);
		cout << "\tTo |=============> " << sent_message.top().get_recived_id() << endl;
		cout << "\tThe message |====> " << " ' " << sent_message.top().get_body() << " ' " << endl;
		sent_message.pop();
		cout << ".........................................................................................................................." << endl;
	}
}
void User::remove_oldest_fav_message(vector<Message> &all_msg) {
	if (fav_msg.empty())
		read_messages(all_msg);
	
	for (int i = 0; i < all_msg.size(); i++) {
		if (fav_msg.front().get_id() == all_msg[i].get_id()) {
			all_msg[i].set_fav_message(0);
		}
	}
	fav_msg.pop();

}
void User::read_messages(vector<Message> all_msg) {
	clear_messages();
	for (int i = 0; i < all_msg.size(); i++) {
		if (all_msg[i].get_recived_id() == ID) {
			recived_messages.push(all_msg[i]);
			if (all_msg[i].get_fav_message() == 1) {
				fav_msg.push(all_msg[i]);
			}
			
		}
		else if (all_msg[i].get_sent_id() == ID) {
			sent_message.push(all_msg[i]);
		}
	}
}

Message User::get_message(int num , vector<Message>all_msg) {
	int counter = 1;
	
	if (recived_messages.empty())
		read_messages(all_msg);
	if (recived_messages.empty()) {
		HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(h, 12);
		cout << "\n you dont have any massege";
		Message msg = Message();
		return msg;
	}
	while (!recived_messages.empty()) {
		if (counter == num)
			return recived_messages.top();
		recived_messages.pop();
		counter++;
	}
}
void User::clear_messages() {
	while (!fav_msg.empty())
		fav_msg.pop();

	while (!recived_messages.empty())
		recived_messages.pop();

	while (!sent_message.empty())
		sent_message.pop();

}

int User::get_size_of_recived_msg(vector<Message>all_msg) {
	if (recived_messages.empty())
		read_messages(all_msg);
	
	
	return recived_messages.size();
}

string User::get_user_name() {
	return user_name;
}
string User::get_password() {
	return password;
}
int User::get_id() {
	return ID;
}

void User::set_user_name(string name) {
	user_name = name;
}
void User::set_password(string pass) {
	password = pass;
}
void User::set_id(int id) {
	ID = id;
}


User::~User()
{


}