#include <iostream>
#include <vector>
#include "Client.h"

using namespace std;
using namespace client;
using namespace hairstylist;

int main() {
    setlocale(LC_ALL, "RUS");

    HairStylist hairStylist;
    int numClients = 10;
    //2100
    int delay = 1000; 

    thread stylistThread(&HairStylist::hairstylistWork, &hairStylist);
    vector<thread> clientThreads;

    for (int i = 1; i < numClients + 1; i++) {
        clientThreads.emplace_back(Client(i, hairStylist));
        this_thread::sleep_for(chrono::milliseconds(delay));
    }

    stylistThread.join();
    for (auto& thread : clientThreads) {
        thread.join();
    }

    return 0;
}
