#include <iostream>
#include <string>
#include <random>
using namespace std;

struct Node {
	string name;
	int cost;
	string owner;
	Node* next;

	Node(string n, int c)
		: name(n), cost(c), owner(""), next(nullptr) {}
};

class LinkedList {
	Node* head = nullptr;
	Node* tail = nullptr;
	int sz = 0;

public:
	~LinkedList() {
		Node* current = head;

		for (int i = 0; i < sz; i++) {
			Node* next = current->next;
			delete current;
			current = next;
		}
	}

	void add(string name, int cost) {
		Node* newNode = new Node(name, cost);

		if (head == nullptr) {
			head = newNode;
			tail = newNode;
			newNode->next = head;
		} else {
			newNode->next = head;
			tail->next = newNode;
			tail = newNode;
		}

		sz++;
	}

	Node* search(string name) {
		Node* current = head;

		for (int i = 0; i < sz; i++) {
			if (current->name == name)
				return current;

			current = current->next;
		}

		return nullptr;
	}

	bool remove(string name) {
		if (head == nullptr)
			return false;

		Node* current = head;
		Node* previous = tail;

		for (int i = 0; i < sz; i++) {
			if (current->name == name) {
				if (sz == 1) {
					head = nullptr;
					tail = nullptr;
				} else {
					previous->next = current->next;

					if (current == head)
						head = current->next;

					if (current == tail)
						tail = previous;

					tail->next = head;
				}

				delete current;
				sz--;
				return true;
			}

			previous = current;
			current = current->next;
		}

		return false;
	}

	void print() {
		Node* current = head;

		for (int i = 0; i < sz; i++) {
			cout << current->name
			     << " - $" << current->cost
			     << " - Owner: "
			     << (current->owner.empty() ? "None" : current->owner)
			     << "\n";

			current = current->next;
		}
	}

	Node* getHead() {
		return head;
	}

	int size() {
		return sz;
	}
};

struct Player {
	string name;
	int money = 1500;
	Node* position = nullptr;
};

void takeTurn(Player& player, LinkedList& board, int roll) {
	if (player.position == nullptr)
		player.position = board.getHead();

	for (int i = 0; i < roll; i++)
		player.position = player.position->next;

	Node* property = player.position;

	cout << player.name << " rolled " << roll
	     << " and landed on " << property->name << ".\n";

	if (property->owner.empty()) {
		if (player.money >= property->cost) {
			player.money -= property->cost;
			property->owner = player.name;

			cout << player.name << " bought it for $"
			     << property->cost << ".\n";
		}
	} else {
		cout << "Already owned by "
		     << property->owner << ".\n";
	}

	cout << player.name << " has $"
	     << player.money << " left.\n\n";
}

int main() {
	// Part 1: linked list test
	cout << "=== Linked List Test ===\n";

	LinkedList test;

	test.add("Test A", 100);
	test.add("Test B", 200);
	test.add("Test C", 300);

	cout << "After adding:\n";
	test.print();

	Node* found = test.search("Test B");

	cout << "\nSearch for Test B: "
	     << (found != nullptr ? "Found" : "Not found")
	     << "\n";

	test.remove("Test B");

	cout << "\nAfter removing Test B:\n";
	test.print();


	// Part 2: Monopoly board
	cout << "\n=== Monopoly Game ===\n";

	LinkedList board;

	board.add("Ivano-Frankivsk", 60);
	board.add("Chernivtsi", 80);
	board.add("Uzhhorod", 100);
	board.add("Lviv", 120);
	board.add("Bukovel", 140);
	board.add("Kamianets-Podilskyi", 160);
	board.add("Odesa", 180);
	board.add("Dnipro", 200);
	board.add("Kharkiv", 220);
	board.add("Kyiv", 250);

	Player p1;
	Player p2;

	cout << "Player 1 name: ";
	cin >> p1.name;

	cout << "Player 2 name: ";
	cin >> p2.name;

	mt19937 generator(62);
	uniform_int_distribution<int> die(1, 6);

	for (int turn = 1; turn <= 12; turn++) {
		cout << "Turn " << turn << "\n";

		if (turn % 2 == 1)
			takeTurn(p1, board, die(generator));
		else
			takeTurn(p2, board, die(generator));
	}

	cout << "=== Final Board ===\n";
	board.print();

	return 0;
}