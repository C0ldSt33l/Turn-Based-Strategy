#include "Message.h"

Message::Message() {}

void Message::set_create(Unit* new_unit) {
	this->type = Message::Type::CREATE;
	this->create.new_unit = new_unit;
}

void Message::set_kill(Unit* killer, Unit* who_to_kill) {
	this->type = Message::Type::KILL;
	this->kill.killer = killer;
	this->kill.who_to_kill = who_to_kill;
}

void Message::set_move(Cell* from, Cell* destination) {
	this->type = Message::Type::MOVE;
	this->move.from = from;
	this->move.destination = destination;
}

void Message::set_attack(Unit* attacker, Unit* who_to_attack) {
	this->type = Message::Type::ATTACK;
	this->attack.attacker = attacker;
	this->attack.who_to_attack = who_to_attack;
}

void Message::set_heal(Unit* healer, Unit* who_to_heal) {
	this->type = Message::Type::HEAL;
	this->heal.healer = healer;
	this->heal.who_to_heal = who_to_heal;
}

void Message::set_buff(Unit* buffer, Unit* who_to_buff) {
	this->type = Message::Type::BUFF;
	this->buff.buffer = buffer;
	this->buff.who_to_buff = who_to_buff;
}

void Message::set_select(Unit* who_to_select) {
	this->type = Message::Type::SELECT;
	this->select.who_select = who_to_select;
}
