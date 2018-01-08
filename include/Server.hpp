#ifndef DRAWSHEEP_SERVER_HPP
#define DRAWSHEEP_SERVER_HPP


#include <netinet/in.h>


class Server {
private :
    int sockfd, newsockfd, portno;
    socklen_t clilen;
    struct sockaddr_in serv_addr, cli_addr;

public:
    Server(int port);

    void start();

private:
    // Lis un entier pour savoir le type de requète
    void read_request(int sockfd) {}

    void read_file(int sockfd);

    void send_answer(int sockfd);

    void verify_draw(int sockfd) {}

};
#endif //DRAWSHEEP_SERVER_HPP
