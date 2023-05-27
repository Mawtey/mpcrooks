#include<iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include"Print.h"

using namespace std;
using namespace print;

namespace hairstylist {
    class HairStylist {
    private:
        queue<int> clients; 
        mutex m; 
        condition_variable c_v;
        bool all_cut; 
        bool client_came; 
        Print print;

    public:
        HairStylist() : all_cut(false), client_came(false) {} 
        void hairstylistWork();
        void addClient(int clientId);
    };

    void HairStylist::hairstylistWork() {
        unique_lock<mutex> lock(m);
        while (!all_cut) {
            while (!client_came && clients.empty()) {
                print.printRes(0x0006, "Парикмахер спит");
                c_v.wait(lock);
            }
            while (!clients.empty()) {
                int visitorId = clients.front();
                clients.pop();
                lock.unlock();
                print.printRes(0x0004, " сел на стрижку", visitorId);
                //2200
                this_thread::sleep_for(chrono::milliseconds(3000));
                lock.lock();
                print.printRes(0x0002, " теперь пострижен", visitorId);

            }
            client_came = false;
        }
    }

    void HairStylist::addClient(int clientId) {
        unique_lock<mutex> lock(m);
        clients.push(clientId);
        client_came = true;
        c_v.notify_one();
    }
}

