#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
using namespace std;

bool read = false, write = false;
int r_num = 0, w_num = 0, count_w = 1, count_r = 1;
mutex mut;

void reader();
void writer();

int main() {
	cout << "Enter the number of readers:";
	cin >> ::r_num;
	while (::r_num < 1) {
		cout << "Please, try again!";
		cin >> ::r_num;
	}
	cout << "Enter the number of writers:";
	cin >> ::w_num;
	while (::w_num < 1) {
		cout << "Please, try again!";
		cin >> ::w_num;
	}

	thread read(reader);
	thread write(writer);

	read.join();
	write.join();

	return 0;
}

void reader() {
	while (true) {
		this_thread::sleep_for(chrono::milliseconds(10));
		mut.lock();
		while (true) {
			cout << "Reading " << ::count_r << " thread id " << this_thread::get_id() << "\n";
			this_thread::sleep_for(chrono::milliseconds(300));
			::count_r = rand() % ::r_num + 1;
			if (::count_r - 1 == 0) {
				mut.unlock();
				break;
			}
		}
	}
}

void writer() {
	while (true) {
		this_thread::sleep_for(chrono::milliseconds(10));
		mut.lock();
		while (true) {
			int temp = ::count_w;
			cout << "Writing " << ::count_w << " thread id " << this_thread::get_id() << "\n";
			this_thread::sleep_for(chrono::milliseconds(300));
			::count_w = rand() % ::w_num + 1;
			if (::count_w - 1 == 0 || ::count_w == temp || ::count_r != 0) {
				mut.unlock();
				break;
			}
		}
	}
}