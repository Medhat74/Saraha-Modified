#include "Message.h"

Message::Message() {
	ID = sent_id = recived_id = 0;
	body = "null";

}

void Message::set_id(int id) {
	ID = id;
}
void Message::set_body(string body) {
	this->body = body;
}
void Message::set_fav_message(bool fav_msg) {
	fav_message = fav_msg;
}
void Message::set_recived_id(int con_id) {
	recived_id = con_id;
}
void Message::set_sent_id(int sent_id) {
	this->sent_id = sent_id;
}

int Message::get_id() {
	return ID;
}
string Message::get_body() {
	return body;
}
bool Message::get_fav_message() {
	return fav_message;
}
int Message::get_recived_id() {
	return recived_id;
}
int Message::get_sent_id() {
	return sent_id;
}