#include<iostream>
//#include<vector>
using namespace std;

struct Data {
	int value;
	Data* next;
	Data* pre;
};

class Hash_table{
public:
	Hash_table(int m) {
		mod = m;
	}
	void add(int num) {
		Data* new_Data = new Data;
		new_Data->value = num;
		Data* carrent = Head[num % mod];
		if (Head[num % mod] == NULL) {
			Head[num % mod] = new_Data;
			Tail[num % mod] = new_Data;
			new_Data->next = NULL;
			new_Data->pre = NULL;
		}
		else if (num < Head[num % mod]->value) {
			Head[num % mod] = new_Data;
			new_Data->next = carrent;
			new_Data->pre = NULL;
			carrent->pre = new_Data;
		}
		else {
			for (; (num < carrent->value) && (carrent->next != NULL); carrent = carrent->next) {}
			new_Data->next = carrent->next;
			new_Data->pre = carrent;
			carrent->next = new_Data;
			Tail[num % mod] = new_Data;
			if (new_Data->next == NULL);
			else 
				new_Data->next->pre = new_Data;
		}
	}
	void pop(int num) {
		Data* carrent = Head[num % mod];
		for (; carrent->value == num; carrent = carrent->next){}
		if (carrent->next == NULL && carrent->pre == NULL) {
			Head[num % mod] = NULL;
			Tail[num % mod] = NULL;
		}
		else if (carrent->next == NULL) {
			carrent->pre->next = carrent->next;
			Tail[num % mod] = carrent->pre;
		}
		else if (carrent->pre == NULL) {
			carrent->next->pre = carrent->pre;
			Head[num % mod] = carrent->next;
		}
		else {
			carrent->pre->next = carrent->next;
			carrent->next->pre = carrent->pre;
		}
		delete carrent;
		carrent = NULL;
	}
	void output() {
		Data* carrent;
		cout << "===== s =====" << endl;
		for (int i = 0; i < mod; i++) {
			if (mod < 10) {
				cout << "[00" << i << "]:";
			}
			else if (mod < 100) {
				cout << "[0" << i << "]:";
			}
			else{
				cout << "[" << i << "]:";
			}
			carrent = Head[i];
			while (carrent != NULL) {
				cout << carrent->value << " -> ";
				carrent = carrent->next;
			}
			cout << "NULL" << endl;
		}
		cout << "===== e =====" << endl;
	}
private:
	int mod;
	Data* Head[200] = { NULL };
	Data* Tail[200] = { NULL };
};

int main() {
	int num, number, time, mod;
	cin >> time >> mod;
	Hash_table hash(mod);
	for (int i = 0; i < time; i++) {
		cin >> num;
		if (num == 1) {
			cin >> number;
			hash.add(number);
		}
		else if (num == 2) {
			cin >> number;
			hash.pop(number);
		}
		else if (num == 3) {
			hash.output();
		}
	}
	return 0;
}