#include<iostream>
template<typename T>
struct Box {
	T data;
	Box<T>* next;
	Box(const T& elem, Box<T>*_next) :data(elem), next(_next) {}
};
template<typename T>
void reverseList(Box<T>*& start) {
	Box<T>* previous = nullptr;
	Box<T>* current = start;
	Box<T>* incoming;
	while (current) {
		incoming = current->next;
		current->next = previous;
		previous = current;
		current = incoming;
	}
	start = previous;
}
int main() {

}