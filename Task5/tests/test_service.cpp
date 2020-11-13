#include "net.hpp"

bool is_prime(long long a){
    if(a == 2)
        return true;
    if(a < 2 || a % 2 == 0)
        return false;
    for(long long i = 3; i * i <= a; i += 2){
        if(a % i == 0)
            return false;
    }
    return true;
}

class PrimeService : public Tasks::net::IServiceListener {
private:
    bool result;
public:
    void onNewConnection(Tasks::net::BufConnection *buf_con) override {
        std::cout << "New client connecting to Service" << std::endl;
        buf_con->subscribe(Tasks::net::EVENT_FLAG::RDW);
    }

    void onClose(Tasks::net::BufConnection *buf_con) override {
        std::cout << "Client disconnected from Service" << std::endl;
    }

    void onWriteDone(Tasks::net::BufConnection *buf_con) override {
        if (result) {
            std::cout << "Client's num is prime" << std::endl;
        } else {
            std::cout << "Client's num is not prime" << std::endl;
        }
        buf_con->unsubscribe(Tasks::net::EVENT_FLAG::WRITE);
    }

    void onReadAvailable(Tasks::net::BufConnection *buf_con) override {
        long long num;
        buf_con->read(&num, sizeof(num));
        result = is_prime(num);
        buf_con->write(&result, sizeof(result));
        buf_con->unsubscribe(Tasks::net::EVENT_FLAG::READ);
    }

    void onError(Tasks::net::BufConnection *buf_con) override {
        std::cout << "Error occured!" << std::endl;
    }
    
};

int main() {
    PrimeService prime_serv;
    Tasks::net::Service service(&prime_serv);
    service.open("127.0.0.1", 8888);
    service.run();
}