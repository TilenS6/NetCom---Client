#define WIN32_LEAN_AND_MEAN

#include <iostream>

#include <conio.h>
#include <thread> // std::thread

#include "netagent/netagent.h"

// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib

NetClient *cl = nullptr;
void recv_f() {
    while (true) {

        int res = cl->recieveData();
        if (res != recieveData_NO_NEW_DATA) {
            if (res != recieveData_OK)
                return;

            std::cout << "\t" << cl->recvbuf << std::endl;
        }

        Sleep(100);
    }
}

int main(int argc, char *argv[]) {
    std::cout << "Server: ";
    std::string srvrName;
    std::cin >> srvrName;

    NetClient client(srvrName);

    cl = &client;

    std::thread recieving(recv_f);

    std::cout << "connected to server.\n";
    std::string str = "";
    do {
        // std::cout << "send: ";
        std::getline(std::cin, str);
        if (str != "") {
            client.sendData(str.c_str(), str.length() + 1);
        }
    } while (str != "bye");

    client.closeConnection();
    recieving.join();
    return 0;
}