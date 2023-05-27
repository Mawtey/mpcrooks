#include<iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include"Hairstylist.h"


using namespace std;
using namespace hairstylist;

namespace client {
    class Client {
    private:
        int id;
        HairStylist& hairStylist;
        Print print;

    public:
        Client(int clientId, HairStylist& stylist) : id(clientId), hairStylist(stylist) {}
        void operator()();
    };

    void Client::operator()() {
        this_thread::sleep_for(chrono::milliseconds(1));
        print.printRes(0x0005, " пришел к барберу", id);
        hairStylist.addClient(id);
    }
}