#include <Client.hpp>
#include <fstream>
#include <iostream>
#include <unistd.h>
#include <cstring>
#include <netdb.h>

Client::Client(const char *hostname, int port) {
    portno = port;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        throw "ERROR opening socket";
    // TODO Modifier plus tard pour co a distance
    server = gethostbyname(hostname);
    if (server == NULL) {
        throw "ERROR, no such host\n";
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr,
          (char *)&serv_addr.sin_addr.s_addr,
          server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
        throw "ERROR connecting";
    std::cout << "Client Connected" << std::endl;
}

void Client::send_file(const char * filename) {
    std::ifstream infile(filename);
    // get length of file:
    infile.seekg (0, infile.end);
    int file_size = infile.tellg();
    infile.seekg (0, infile.beg);

    std::cout << file_size << std::endl;
    char buffer[file_size];
    long n;
    infile.read(buffer, file_size);
    n = send(sockfd, &file_size, sizeof(file_size), 0);
    if (n < 0)
        throw "ERROR writing to socket";
    n = send(sockfd, buffer, file_size, 0);
    if (n < 0)
        throw "ERROR writing to socket";
    std::cout << "file sent" << std::endl;

}

void Client::read_string() {
    char buffer[2048];
    long n;
    n = recv(sockfd,buffer,2047, 0);
    if (n < 0)
        throw "ERROR reading from socket";
    std::cout << buffer << std::endl;
}

Client::~Client() {
    close(sockfd);
}
