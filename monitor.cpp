#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>
#include <string>
#include <sys/sysinfo.h>
#include <unistd.h>

void logResourceUsage(const std::string& filename) {
    std::ofstream logFile(filename, std::ios::app);
    if (!logFile.is_open()) {
        std::cerr << "Failed to open log file: " << filename << std::endl;
        return;
    }

    while (true) {
        struct sysinfo info;
        sysinfo(&info);

        double totalRam = info.totalram;
        double freeRam = info.freeram;
        double usedRam = totalRam - freeRam;
        double usedCpu = (info.uptime / 60.0); // Using uptime as a proxy for CPU load

        logFile << "CPU Load (approx): " << usedCpu << " minutes, "
                << "Memory Usage: " << (usedRam / 1024 / 1024) << " MB used / "
                << (totalRam / 1024 / 1024) << " MB total" << std::endl;

        logFile.flush();
        std::this_thread::sleep_for(std::chrono::seconds(5)); // Log every 5 seconds
    }

    logFile.close();
}

int main() {
    std::string logFilename = "resource_usage.log";
    logResourceUsage(logFilename);
    return 0;
}
