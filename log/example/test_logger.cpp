#include "log.hpp"

int main(void) {
    Project::log::init_with_stdout_logger();
    Project::log::debug("DEBUG: Stdout");
    Project::log::info("INFO: Stdout");
    Project::log::warn("WARN: Stdout");
    Project::log::error("ERROR: Stdout");
    std::cout << std::endl;
    
    Project::log::init_with_stderr_logger();
    Project::log::debug("DEBUG: Stderr");
    Project::log::info("INFO: Stderr");
    Project::log::warn("WARN: Stderr");
    Project::log::error("ERROR: Stderr");
    
    Project::log::init_with_file_logger("log.txt");
    Project::log::debug("DEBUG: File");
    Project::log::info("INFO: File");
    Project::log::warn("WARN: File");
    Project::log::error("ERROR: File");

    return 0;
}