#ifndef WEBSERVER_H
#define WEBSERVER_H

#include <boost/asio.hpp>
#include <iostream>
#include <string>
#include <thread>
#include <memory>
#include <atomic>
#include <vector>
#include <fstream>

std::string make_daytime_string();
double AI_function(double usd);

class WebServer {
public:
    unsigned short port;
    WebServer(unsigned short port);

    void start();
    void stop();

private:
    void run();

    boost::asio::io_context io_context_;
    boost::asio::ip::tcp::acceptor acceptor_;
    std::thread server_thread_;
    std::atomic<bool> is_running_;
};

#endif // WEBSERVER_H
