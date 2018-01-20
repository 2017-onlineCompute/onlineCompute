#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/bind.hpp>

#define BUFSIZE 1024

using std::cin;
using std::cout;
using std::endl;
using std::string;
using namespace boost::asio;

int main(void){
    io_service service;
    ip::tcp::endpoint ep(ip::address::from_string("127.0.0.1"),2001);
    ip::tcp::socket sock(service);

    sock.connect(ep);
    char buf[BUFSIZE];
    cout << "This is the client." << endl;
    cout << "please enter the express like a+b*c: " ;
    cin >> buf;
    sock.write_some(buffer(buf));

    char result[100];
    sock.read_some(buffer(result));
    cout << buf << " = " << atof(result) << endl;
    return 0;
}
