#include <iostream>  
#include <vector>    
#include <algorithm> 
int main() {
    std::vector<int> v1T = {85, 90, 95, 100, 105, 100, 85};
    std::vector<int> v2T = {85, 90, 95, 100, 105, 100, 85};
    std::cout << "      Vehicle Temperature Data Analysis       " << std::endl;
    std::cout << " Vehicle 1 Temperatures: ";
    std::for_each(v1T.begin(), v1T.end(), [](int t) {
        std::cout << t << " ";
    });
    std::cout << std::endl << std::endl;
    int spT = 90; 
    auto itF = std::find(v1T.begin(), v1T.end(), spT);
    if (itF != v1T.end()) {
        std::cout << spT << "C was recorded in Vehicle 1." << std::endl;
    } else {
        std::cout << spT << "C was NOT recorded in Vehicle 1." << std::endl;
    }
    std::cout << std::endl;
    int highLimit = 100; 
    auto itFI = std::find_if(v1T.begin(), v1T.end(), [&](int t) {
        return t > highLimit;
    });

    if (itFI != v1T.end()) {
        std::cout << "First temperature above " << highLimit << " C in Vehicle 1 is: " << *itFI << " C." << std::endl;
    } else {
        std::cout << "No temperature above " << highLimit << " C found in Vehicle 1." << std::endl;
    }
    std::cout << std::endl;
    auto itAF = std::adjacent_find(v1T.begin(), v1T.end());
    if (itAF != v1T.end()) {
        std::cout << "Two adjacent temperature values are equal in Vehicle 1: " << *itAF << " C." << std::endl;
    } else {
        std::cout << "No two adjacent temperature values are equal in Vehicle 1." << std::endl;
    }
    std::cout << std::endl;
    int targetTemp = 85; 
    long long cnt = std::count(v1T.begin(), v1T.end(), targetTemp);
    std::cout <<  targetTemp << " C was recorded " << cnt << " times in Vehicle 1." << std::endl;
    std::cout << std::endl;
    int normalLimit = 95; 
    long long cntIf = std::count_if(v1T.begin(), v1T.end(), [&](int t) {
        return t > normalLimit;
    });
    std::cout << cntIf << " readings in Vehicle 1 are above the normal limit (> " << normalLimit << " C)." << std::endl;
    std::cout << std::endl;
    bool areEq = std::equal(v1T.begin(), v1T.end(), v2T.begin());
    std::cout << "Vehicle 2 Temperatures: ";
    std::for_each(v2T.begin(), v2T.end(), [](int t) {
        std::cout << t << " ";
    });
    std::cout << std::endl;

    if (areEq) {
        std::cout << "Temperature sequences for Vehicle 1 and Vehicle 2 are identical." << std::endl;
    } else {
        std::cout << "Temperature sequences for Vehicle 1 and Vehicle 2 are different." << std::endl;
    }
    std::cout << std::endl;
    return 0;
}
