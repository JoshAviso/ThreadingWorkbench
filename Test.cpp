
#include <iostream>
#include <mutex>
#include "src/IETThread.h"

#include <semaphore>

bool hasFood = false;
bool orderMade = false;
float data = 0.f;
std::mutex dataGuard;

int turn = 0;
bool flag[3] = { false, false, false };

std::counting_semaphore<1> mtxA(1);
std::counting_semaphore<1> mtxB(0);
std::counting_semaphore<1> mtxC(0);

class ThreadA : public IETThread {
private:
	void run() override {
		while (true) {

			mtxA.acquire();

			IETThread::sleep(500);
			data = data + 100;
			std::cout << data << std::endl;

			mtxB.release();
		}
	}
};

class ThreadB : public IETThread {
private:
	void run() override {
		while (true) {
			mtxB.acquire();

			IETThread::sleep(500);
			data = data - 100;
			std::cout << data << std::endl;

			mtxC.release();
		}
	}
};

class ThreadC : public IETThread {
private:
	void run() override {
		while (true) {

			mtxC.acquire();

			IETThread::sleep(500);
			std::cout << "Third thread" << std::endl;

			mtxA.release();
		}
	}
};

class Chef : public IETThread {
private:
	void Cook() {
		std::cout << "Chef cooks\n";
		hasFood = true;
	}
	void Enter() {
		std::cout << "Chef enters\n";
	}
	void WaitForOrder() {
		while (!orderMade) {
			std::cout << "Cook is waiting for order\n";
			IETThread::sleep(50);
		}
	}
	void run() override {
		Enter();
		WaitForOrder();
		Cook();
	}
};

class Customer : public IETThread {
private:
	void Eat() {
		
		hasFood = false;
		std::cout << "Customer eats\n";
	}
	void Enter() {
		std::cout << "Customer enters\n";
	}
	void Order() {
		std::cout << "Customer orders\n";
		orderMade = true;
	}
	void WaitForFood() {
		while (!hasFood) {
			std::cout << "Customer is waiting for food\n";
			IETThread::sleep(50);
		}
	}
	void run() override {
		Enter();
		Order();
		WaitForFood();
		Eat();
	}
};

std::counting_semaphore<5> my_semaphore(1); // Max permits = 5, initial permits = 1, ie. 1/5 permits available

class SemaphoreThread1 : public IETThread {
private:
	void run() override {
		std::cout << "1: Trying to acquire Semaphore\n";
		my_semaphore.acquire(); // Note, C++ limits this to only 1
		std::cout << "1: At Critical Section\n";
		IETThread::sleep(5000);
		std::cout << "1: Released Semaphore\n";
		my_semaphore.release();
	}
};

class SemaphoreThread2 : public IETThread {
private:
	void run() override {
		std::cout << "2: Trying to acquire Semaphore\n";
		IETThread::sleep(5000);
		my_semaphore.acquire(); // Note, C++ limits this to only 1
		std::cout << "2: At Critical Section\n";
		std::cout << "2: Released Semaphore\n";
		my_semaphore.release();
	}
};

int gold = 0;
int user_gold = 0;
std::binary_semaphore gold_key(1);
std::counting_semaphore<500> mine_key(0);

class Mine : public IETThread {
private:
	void run() override {
		while (true) {

			gold_key.acquire();
			gold++;
			Print();
			gold_key.release();

			mine_key.release();
			IETThread::sleep(100);
		}
	}

	void Print() {
		std::cout << "Mine " << _id << " added 1 gold! " << gold << " in mine!\n";
	}

	int _id;

public:
	Mine(int id) : _id(id){};

};

class Miner : public IETThread {
private:
	void run() override {
		while (true) {
			mine_key.acquire();
			gold_key.acquire();
			gold--;
			user_gold++;
			Print();
			gold_key.release();	
			IETThread::sleep(800);
		}
	}

	void Print() {
		std::cout << "Miner " << _id << " took 1 gold!" << user_gold << " in bag! " << gold << " left in mine!\n";
	}

	int _id;

public:
	Miner(int id) : _id(id) {};

};

#include <vector>

int main() {
	std::vector<Mine*> mines;
	std::vector<Miner*> miners;

	int mine_count = 4;
	int miner_count = 28;

	for (int i = 0; i < mine_count; i++) {
		Mine* mine = new Mine(i);
		mine->start();
		mines.push_back(mine);
	}
	for (int i = 0; i < miner_count; i++) {
		Miner* miner = new Miner(i);
		miner->start();
		miners.push_back(miner);
	}

	/*SemaphoreThread1 t1;
	SemaphoreThread2 t2;
	t1.start();
	t2.start();*/

	IETThread::sleep(15000);

	return 0;
}