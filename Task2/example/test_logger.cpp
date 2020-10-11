#include "log.hpp"

int main(void) {
    Task2::Logger::get_instance().set_global_logger(Task2::init_with_stdout_logger(Task2::Level::INFO));
    Task2::debug("DEBUG: Stdout");
    Task2::info("INFO: Stdout");
    Task2::warn("WARN: Stdout");
    Task2::error("ERROR: Stdout");
    std::cout << std::endl;
    
    Task2::Logger::get_instance().set_global_logger(Task2::init_with_stderr_logger(Task2::Level::ERROR));
    Task2::debug("DEBUG: Stderr");
    Task2::info("INFO: Stderr");
    Task2::warn("WARN: Stderr");
    Task2::error("ERROR: Stderr");
    
    Task2::Logger::get_instance().set_global_logger(Task2::init_with_file_logger("log.txt", Task2::Level::DEBUG));
    Task2::debug("DEBUG: File");
    Task2::info("INFO: File");
    Task2::warn("WARN: File");
    Task2::error("ERROR: File");

    return 0;
}