#include <boost/asio.hpp>
#include <iostream>
#include <string>
#include <thread>
#include <memory>
#include <atomic>
#include <vector>

using boost::asio::ip::tcp;

std::string make_daytime_string() {
    using namespace std; // For time_t, time and ctime;
    time_t now = time(0);
    return ctime(&now);
}

class WebServer {
public:
    WebServer(unsigned short port)
        : io_context_(), acceptor_(io_context_, tcp::endpoint(tcp::v4(), port)), is_running_(true) {}

    void start() {
        server_thread_ = std::thread([this]() { this->run(); });
    }

    void stop() {
        is_running_ = false;
        io_context_.stop();
        if (server_thread_.joinable()) {
            server_thread_.join();
        }
    }

private:
    void run() {
        try {
            while (is_running_) {
                tcp::socket socket(io_context_);
                acceptor_.accept(socket);

                std::string message = make_daytime_string();
                boost::system::error_code ignored_error;
                boost::asio::write(socket, boost::asio::buffer(message), ignored_error);
            }
        } catch (std::exception& e) {
            std::cerr << "Server error: " << e.what() << std::endl;
        }
    }

    boost::asio::io_context io_context_;
    tcp::acceptor acceptor_;
    std::thread server_thread_;
    std::atomic<bool> is_running_;
};

int main() {
    std::vector<std::shared_ptr<WebServer>> servers;

    auto server1 = std::make_shared<WebServer>(8080);
    servers.push_back(server1);
    server1->start();

    auto server2 = std::make_shared<WebServer>(8081);
    servers.push_back(server2);
    server2->start();

    std::cout << "Servers are running. Enter 1 to stop...\n";
    int stop = std::cin.get();
    if(stop == 1)
    {
        for (auto& server : servers) 
        {
            server->stop(); 
        }
    }

    std::cout << "Servers stopped.\n";
    return 0;
}
