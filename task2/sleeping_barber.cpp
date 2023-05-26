#include <iostream>
#include <windows.h>
#include <thread>
#include <locale>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <chrono>
#include <cassert>

using namespace std;

class Barbershop {
private:
    mutex mutex_;
    condition_variable c_v;
    queue<int> line;
    int max_line;
    bool sleep;

public:
    Barbershop(int max_line_) : max_line(max_line_), sleep(false) {}

    void addClient(int client_id) {
        unique_lock<mutex> lock(mutex_);
        if (line.size() < max_line) {
            line.push(client_id);
            cout << "Клиент " << client_id << " садится в приемную.\n";
            c_v.notify_one();
        }
        else {
            cout << "Свободных кресел нет, " << client_id << " уходит.\n";
        }
        this_thread::sleep_for(chrono::seconds(2));
    }

    int getNextClient() {
        unique_lock<mutex> lock(mutex_);
        while (line.empty()) {
            sleep = true;
            c_v.wait(lock);
            sleep = false;
        }
        int client_id = line.front();
        line.pop();
        return client_id;
    }

    bool isSleeping() const {
        return sleep;
    }
};

class Barber {
private:
    int id_;
    Barbershop& barbershop;


public:
    explicit Barber(int id, Barbershop& barbershop_) : id_(id), barbershop(barbershop_) {}

    void startWorking() {
        while (true) {
            if (barbershop.isSleeping()) {
                cout << "Парикмахер " << id_ << " просыпается.\n";
            }
            int client_id = barbershop.getNextClient();
            cout << "Парикмахер " << id_ << " стрижет клиента " << client_id << ".\n";
            this_thread::sleep_for(chrono::milliseconds(2000));
            cout << "Клиент " << client_id << " после стрижки уходит.\n";
            this_thread::sleep_for(chrono::milliseconds(2000));

        }
    }
};

void ClientFunction(int id, Barbershop& barbershop_) {
    this_thread::sleep_for(chrono::seconds(2));  
    if (barbershop_.isSleeping()) {
        cout << "Клиент " << id << " пытается разбудить парикмахера.\n";
    }
    else {
        cout << "Клиент " << id << " идет в приемную.\n";
    }
    barbershop_.addClient(id);
}

void unit_test1() {
    Barbershop barbershop(3);
    Barber barber(1, barbershop);

    thread barber_thread(&Barber::startWorking, &barber);
    thread client1_thread(ClientFunction, 1, ref(barbershop));
    thread client2_thread(ClientFunction, 2, ref(barbershop));
    thread client3_thread(ClientFunction, 3, ref(barbershop));
    thread client4_thread(ClientFunction, 4, ref(barbershop));
    thread client5_thread(ClientFunction, 5, ref(barbershop));
    thread client6_thread(ClientFunction, 6, ref(barbershop));

    barber_thread.join();
    client1_thread.join();
    client2_thread.join();
    client3_thread.join();
    client4_thread.join();
    client5_thread.join();
    client6_thread.join();
    assert(barbershop.isSleeping());
}

void unit_test2() {
    Barbershop barbershop(2);
    Barber barber(1, barbershop);

    thread barber_thread(&Barber::startWorking, &barber);
    thread client1_thread(ClientFunction, 1, ref(barbershop));
    thread client2_thread(ClientFunction, 2, ref(barbershop));
    thread client3_thread(ClientFunction, 3, ref(barbershop));
    thread client4_thread(ClientFunction, 4, ref(barbershop));

    barber_thread.join();
    client1_thread.join();
    client2_thread.join();
    client3_thread.join();
    client4_thread.join();
    assert(barbershop.isSleeping());
}

int main() {
    setlocale(LC_ALL, "Russian");
    unit_test1();
}
