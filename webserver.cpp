#include "webserver.h"
#include "request.h"
using boost::asio::ip::tcp;

std::ofstream outfile("output.txt");

std::string make_daytime_string() {
    using namespace std; // For time_t, time and ctime;
    time_t now = time(0);
    return ctime(&now);
}

double AI_function(double usd) {
    const double exchangeRate = 1.35; // Example exchange rate
    return usd * exchangeRate;
}

WebServer::WebServer(unsigned short port)
    : io_context_(), acceptor_(io_context_, tcp::endpoint(tcp::v4(), port)), is_running_(true), port(port) {}

void WebServer::start() {
    outfile << "Starting Server " << port << std::endl;
    server_thread_ = std::thread([this]() { this->run(); });
}

void WebServer::stop() {
    outfile << "Server Has Stopped. port:" << port << std::endl;
    is_running_ = false;
    io_context_.stop();
    if (server_thread_.joinable()) {
        server_thread_.join();
    }
}

void WebServer::run() {
    try {
        outfile << "Server Is Running..." << std::endl;
        while (is_running_) {
            tcp::socket socket(io_context_);
            acceptor_.accept(socket);

            std::string message = std::to_string(AI_function(54.00));
            boost::system::error_code ignored_error;
            boost::asio::write(socket, boost::asio::buffer(message), ignored_error);
        }
    } catch (std::exception& e) {
        std::cerr << "Server error: " << e.what() << std::endl;
    }
}
