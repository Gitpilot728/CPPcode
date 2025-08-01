#include<iostream>
#include<vector>
#include<algorithm>
#include<iomanip>    

int main() {
    std::vector<int> speedLogs = {60, 70, -1, 85, 95, 210, 100, -1, 230, 80};
    std::cout << "Original Speed Logs:\n";
    for (size_t i = 0; i < speedLogs.size(); ++i) 
        std::cout << std::setw(4) << speedLogs[i];
    std::cout << "\n";
    std::replace(speedLogs.begin(), speedLogs.end(), -1, 0);
    std::cout << "\nAfter replacing -1 with 0:\n";
    for (auto speed : speedLogs)
        std::cout << std::setw(4) << speed;
    std::cout << "\n";
    speedLogs.erase(std::remove_if(speedLogs.begin(), speedLogs.end(), [](int speed) {
        return speed > 200;
    }), speedLogs.end());
    
    std::cout << "\nAfter removing speeds > 200 km/h:\n";
    for (auto speed : speedLogs)
        std::cout << std::setw(6) << speed;
    std::cout << "\n";
    return 0;
}
