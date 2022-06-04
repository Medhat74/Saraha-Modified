#include <iostream>
#include <string>
#include "User.h"
#include "Message.h"
#include "File.h"
#include <Windows.h>
#include <conio.h>


using namespace  std;

User user;
vector<Message> all_messages;
File file;

bool log_in();
void regester();
void app();
int make_user_id();
void add_contact();
bool send_a_message();
void undo_last_sent_msg(bool b);
void search_contact();
void view_msgs_from_specific_contact();
void add_msg_to_fav_msgs();
void view_all_msgs();
bool is_valid_contact(int contact_id);
void input_pass(string &pass);

int main() {
	// after login
	



	int choice;
	bool sign_in = false;

	first : do
	{
		HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(h, 14);
		cout << endl << "***************************************************";
		SetConsoleTextAttribute(h, 6);
		cout << " Welcome to Saraha. ";
		SetConsoleTextAttribute(h, 14);
		cout << "***************************************************" << endl;
		SetConsoleTextAttribute(h, 3);
		cout<< " 1 - Log in.\n"
			<< " 2 - Register.\n"
			<< " 3 - Exit.\n"
			<< " Enter your choice : ";
		cin >> choice;

		switch (choice)
		{
		case 1:
			sign_in = log_in();
			if (!sign_in) {
				cout << "User name or password is unvalid";
			}
			break;
		case 2:
			regester();
			sign_in = true;
			break;

		case 3:
			cout << "End of Program.\n";
			break;


		default:
			cout << "Not a Valid Choice. \n"
				 << "Choose again.\n";
			break;
		}
		

	} while (choice != 3 && !sign_in);

	if (sign_in) {
		file.read_contacts(user);
		file.read_messages(all_messages);
		app();
		sign_in = false;
		goto first;
	}
	file.write_messages(all_messages);
	return 0;
}


void app() {
	int choice;
	bool is_sent = false;
	do
	{
		HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(h, 15);
		cout << endl
			<< "*************************************************************************************************************************\n";
		SetConsoleTextAttribute(h, 10);
		cout<< "Welcome to Saraha.\n"
			<< user.get_user_name() << "\nyour id is : " << user.get_id() << endl
			<< " 1 - Add user to your contact.\n"
			<< " 2 - Send a message.\n"
			<< " 3 - Undo the last sent message.\n"
			<< " 4 - Search about contact in your contacts.\n"
			<< " 5 - View all your contacts.\n"
			<< " 6 - view all recived messages. \n"
			<< " 7 - View all recieved messages from specific contact.\n"
			<< " 8 - View all favorite messages.\n"
			<< " 9 - view all sent messages. \n"
			<< " 10 - Put a meesage in favorites.\n"
			//<< " 10 - Remove the oldest message from favorites.\n"
			<< " 11 - Logout.\n"
			<< " Enter your choice : ";
		cin >> choice;
		switch (choice)
		{
		case 1:
			add_contact();

			break;
		case 2:
		
			is_sent= send_a_message();
		
		
			break;
		case 3:
			undo_last_sent_msg(is_sent);
			is_sent = false; 
			break;
		case 4:
			search_contact();
			break;
		case 5:
			user.view_all_contacts();
			break;
		case 6:
			view_all_msgs();
			break;
		case 7:
			view_msgs_from_specific_contact();
			break;
		case 8:
			user.view_all_fav_message(all_messages);
			break;

		case 9:
			user.view_all_sent_message(all_messages);
			break;

		case 10:
			add_msg_to_fav_msgs();
			break;
		case 11:
			cout << "loged out.\n";
			file.write_messages(all_messages);
			all_messages.clear();
			if (all_messages.empty())
				cout << "\n yeeeees \n";
			break;

		

		default:
			cout << "Not a Valid Choice. \n"
				 << "Choose again.\n";
			break;
		}


	} while (choice != 11);
}

bool log_in() {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, 13);
	string name, password;
	cout << "Enter your user name : " << endl;
	cin >> name ;
	cout << "Enter your password : " << endl;
	cin >> password;
	//input_pass(password);
	user.set_user_name(name);
	user.set_password(password);
	
	

	return file.read_user_file(user);

}
void regester() {
	string name, password , c_pass;
	int id;
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, 12);
	cout << "Enter your username  : " << endl;
	cin >> name;
	pass_location : 
	cout << "Enter your password : " << endl;
	cin >> password;
	cout << "Confrim your password : ";
	cin >> c_pass;
	if (password == c_pass) {
		id = make_user_id();
		cout << "your ID is:" << id << endl;
		user.set_user_name(name);
		user.set_password(password);
		user.set_id(id);
		file.add_users(user);
	}
	else {
		cout << "password and confrim password are not identical" <<endl;
		goto pass_location;
	}

}

void add_contact() {
	int contact_id;
	cout << endl
		 << "Enter your new contact id :\n" << " ";
	cin >> contact_id;

	if (!is_valid_contact(contact_id))
		return;
	
	user.add_contact(contact_id);
	cout << endl << ".........................................................................................................." << endl
    << " \t \t \t \t \t \t Contact added successfully. " << endl << ".........................................................................................................." << endl;
	
}

bool send_a_message() {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, 6);
	int con_id;
	string mess;
	cout << endl
		<< "Enter contact :\n";
	cin >> con_id;
	if (!is_valid_contact(con_id))
		return false;
	cout << endl
		<< "Enter your message :\n";
	getline(cin >> ws,mess);
	user.send_message(con_id, mess, all_messages);
	cout << endl << ".........................................................................................................." << endl
		<< " \t \t \t \t \t \t Message sent successfully. " << endl << ".........................................................................................................." << endl;
	return true;
}

void undo_last_sent_msg(bool can) {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, 6);
	if (!can) {
		cout << "cant undo because you didnt sent massege!";
		return;
	}
	
	user.undo_message(all_messages);
	cout << endl << ".........................................................................................................." << endl
		<< " \t \t \t \t \t \t Message unsent successfully. " << endl << ".........................................................................................................." << endl;
}

void search_contact() {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, 7);
	int con_id;
	cout << endl
		<< "Enter contact to search :\n";
	cin >> con_id;
	if (user.search(con_id)) 
		cout << "contact ( " << con_id <<" ) is Found" << endl;
	
	else
		cout << "contact ( " << con_id << " ) is Not Found" << endl;

}
void view_msgs_from_specific_contact() {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, 12);
	int con_id;
	cout << endl
		<< "Enter contact you want to receive message :\n";
	cin >> con_id;
	user.view_recieved_message_from_contact(con_id, all_messages);
}

void add_msg_to_fav_msgs() {

	int num;
	Message msg;
	cout << "\nEnter number of massege you need to make it favourite : ";
	cin >> num;
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, 12);
	if (num <0 || num > user.get_size_of_recived_msg(all_messages)) {
		cout << "invalid number .." << endl;
		return;
	}
	msg = user.get_message(num, all_messages);
	if (msg.get_fav_message()) {
		cout << "its already favourite\n";
	}
	else {
		user.add_Fav(msg, all_messages);
		cout << "successed";
	}
}
void view_all_msgs() {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, 12);
	user.view_all_recieved_message(all_messages);
	if (user.get_size_of_recived_msg(all_messages) == 0)
		return;
	cout << "\n press 10 then number of message to add it in fav \n";
}

int make_user_id() {
	int last_id, new_id;
	
	last_id = file.last_id();
	if (last_id == NULL)
		new_id = 1;
	else
		new_id = last_id + 1;
	return new_id;
}

bool is_valid_contact(int contact_id) {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, 12);
	if (contact_id > file.last_id() || contact_id <= 0) {
		cout << "This ID is not exist! " << endl;
		return false;
	}

	else if (contact_id == user.get_id()) {
		cout << "This is your id :D" << endl;
		return false;
	}

	else
		return true;
}

void input_pass(string &pass) {
	
	string password, P;
	char p;
	p = _getch();
	while (p != 13)
	{
		if (p == 8)
		{
			P.resize(P.length() - 1);
			cout << P;
			password.resize(password.length() - 1);
		}
		else {
			P = P + "*";
			cout << P;
			password.push_back(p);
		}
		p = _getch();
		system("cls");
		HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(h, 14);
		cout << endl << "***************************************************";
		SetConsoleTextAttribute(h, 6);
		cout << " Welcome to Saraha. ";
		SetConsoleTextAttribute(h, 14);
		cout << "***************************************************" << endl;
		SetConsoleTextAttribute(h, 3);
		cout << " 1 - Log in.\n"
			<< " 2 - Register.\n"
			<< " 3 - Exit.\n"
			<< " Enter your choice : " ;

	}
	//cout << endl << password << endl;
	pass = password;
}