#include "webserver.hpp"

int main() {
    int socket;
    int address;

    socket = socket(AF_INET, SOCK_STREAM, 0);
    address = bind(socket, struct sockaddr_in *addr, 4);
    std::cout << socket << std::endl;
    std::cout << address << std::endl;

    return 0;
}