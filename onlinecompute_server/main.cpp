#include <iostream>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <stack>
#include <string>
#include "compute.h"

#define BUFSIZE 1024

using std::cin;
using std::cout;
using std::endl;
using namespace boost::asio;

typedef boost::shared_ptr<ip::tcp::socket> socket_ptr;

int main(void)
{
    io_service service;
    ip::tcp::endpoint ep(ip::tcp::v4(),2001);
    ip::tcp::acceptor acc(service,ep);

    cout << "This is sever for computing the express from the client." << endl;

    while(true){
        socket_ptr sock(new ip::tcp::socket(service));
        acc.accept(*sock);
        cout << sock->remote_endpoint().address() << " has connected." << endl;
        char notice[512] = {"Success lined the sever!"};
        sock->write_some(buffer(notice));
        boost::thread(boost::bind(client_session,sock));
    }
}

