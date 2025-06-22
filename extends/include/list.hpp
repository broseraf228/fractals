#pragma once

//circular doubly linked list
template <typename T>
struct cir_doub_elem {

	cir_doub_elem* prev { this };
	cir_doub_elem* next { this };

	T value;

	cir_doub_elem() {}
	cir_doub_elem(const T& value) : value{ value } {};
	cir_doub_elem(const T& value, cir_doub_elem* prev, cir_doub_elem* next) :
		value{ value }, prev{ prev }, next{ next } {};

	void emplace_next(cir_doub_elem<T>* element){
		element->prev = this;
		element->next = next;

		next->prev = element;
		next = element;
	}
	void emplace_prev(cir_doub_elem<T>* element) {
		element->prev = prev;
		element->next = this;

		prev->next = element;
		prev = element;
	}

	void emplace_next(const T& value) {
		cir_doub_elem<T>* el = new cir_doub_elem<T>{ value, this, next };
		next->prev = el;
		next = el;
	}
	void emplace_prev(const T& value) {
		cir_doub_elem<T>* el = new cir_doub_elem<T>{ value, prev, this };
		prev->next = el;
		prev = el;
	}
	void remove() {
		prev->next = next;
		next->prev = prev;
	}
};