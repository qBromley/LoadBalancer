#include "webserver.cpp"
#include "webserver.h"
#include "request.h"
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