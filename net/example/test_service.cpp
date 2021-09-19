#include "net.hpp"
#include <sstream>

int is_prime(long long a) {
    if(a == 2) {
        return true;
    }
    if(a < 2 || a % 2 == 0) {
        return false;
    }
    for(long long i = 3; i * i <= a; i += 2) {
        if(a % i == 0) {
            return false;
        }
    }
    return true;
}

class PrimeService : public Project::net::IServiceListener {
private:
    int result;
public:
    void onNewConnection(Project::net::BufConnection *buf_con) override {
        std::cout << "New client connecting to Service" << std::endl;
        buf_con->subscribe(Project::net::EVENT_FLAG::READ);
    }

    void onClose(Project::net::BufConnection *buf_con) override {
        std::cout << "Client disconnected from Service" << std::endl;
    }

    void onWriteDone(Project::net::BufConnection *buf_con) override {
        if (result) {
            std::cout << "Client's num is prime" << std::endl;
        } else {
            std::cout << "Client's num is not prime" << std::endl;
        }
        buf_con->unsubscribe(Project::net::EVENT_FLAG::WRITE);
    }

    void onReadAvailable(Project::net::BufConnection *buf_con) override {
        int num;
        std::string &read_buf = buf_con->get_read_buf();
        if (read_buf.size() >= sizeof(num)) {
            num = std::stoi(read_buf);
            buf_con->unsubscribe(Project::net::EVENT_FLAG::READ);
            std::cout << "Get number " << num << std::endl;
            result = is_prime(num);
            std::cout << "Result is " << result << std::endl;
            std::string &write_buf = buf_con->get_write_buf();
            if (result) {
                write_buf += std::string("Your number is prime!");
            } else {
                write_buf += std::string("Your number is not prime!");
            }
            buf_con->subscribe(Project::net::EVENT_FLAG::WRITE);
        }
    }

    void onError(Project::net::BufConnection *buf_con) override {
        std::cout << "Error occured!" << std::endl;
    }
    
};

int main() {
    PrimeService prime_serv;
    Project::net::Service service(&prime_serv);
    service.open("127.0.0.1", 8000);
    service.run();
}