#include <algorithm>
#include <vector>
#include <iostream>
#include <string>

struct FirmwareVersion {
    std::string version;
    // For sorting and comparison
    bool operator<(const FirmwareVersion& other) const {
        return version < other.version;
    }
    bool operator==(const FirmwareVersion& other) const {
        return version == other.version;
    }
};
class ECUVersionManager {
public:
    // 1. Combine and sort firmware version lists from two ECUs
    void combineAndSortECUVersions(const std::vector<FirmwareVersion>& ecu1, 
                                  const std::vector<FirmwareVersion>& ecu2) {
        // Make copies since we need to modify them
        std::vector<FirmwareVersion> temp1 = ecu1;
        std::vector<FirmwareVersion> temp2 = ecu2;
        // Sort each list first
        std::sort(temp1.begin(), temp1.end());
        std::sort(temp2.begin(), temp2.end());
        // Reserve space in combinedECUVersions
        combinedECUVersions.reserve(temp1.size() + temp2.size());
        // Merge the two sorted vectors
        std::merge(temp1.begin(), temp1.end(),
                   temp2.begin(), temp2.end(),
                   std::back_inserter(combinedECUVersions));
        // Remove duplicates (optional, depending on requirements)
        auto last = std::unique(combinedECUVersions.begin(), combinedECUVersions.end());
        combinedECUVersions.erase(last, combinedECUVersions.end());
    }
    // 2. Merge available update versions with current versions for display
    void mergeAvailableUpdates(const std::vector<FirmwareVersion>& availableUpdates) {
        // Sort the available updates first
        std::vector<FirmwareVersion> sortedUpdates = availableUpdates;
        std::sort(sortedUpdates.begin(), sortedUpdates.end());
        // Sort the combined ECU versions if not already sorted
        std::sort(combinedECUVersions.begin(), combinedECUVersions.end());
        // Merge them in-place for display
        displayVersions = combinedECUVersions;
        displayVersions.insert(displayVersions.end(), sortedUpdates.begin(), sortedUpdates.end());
        std::inplace_merge(displayVersions.begin(), 
                          displayVersions.begin() + combinedECUVersions.size(),
                          displayVersions.end());
        // Remove duplicates for cleaner display
        auto last = std::unique(displayVersions.begin(), displayVersions.end());
        displayVersions.erase(last, displayVersions.end());
    }
    // 3. Identify common supported versions (intersection)
    void findCommonVersions(const std::vector<FirmwareVersion>& availableUpdates) {
        // Ensure both lists are sorted
        std::vector<FirmwareVersion> sortedUpdates = availableUpdates;
        std::sort(sortedUpdates.begin(), sortedUpdates.end());
        std::sort(combinedECUVersions.begin(), combinedECUVersions.end());
        // Find intersection
        commonVersions.clear();
        std::set_intersection(combinedECUVersions.begin(), combinedECUVersions.end(),
                             sortedUpdates.begin(), sortedUpdates.end(),
                             std::back_inserter(commonVersions));
    }
    // 4. Generate a final upgrade candidate list (set union)
    void generateUpgradeCandidates(const std::vector<FirmwareVersion>& availableUpdates) {
        // Ensure both lists are sorted
        std::vector<FirmwareVersion> sortedUpdates = availableUpdates;
        std::sort(sortedUpdates.begin(), sortedUpdates.end());
        std::sort(combinedECUVersions.begin(), combinedECUVersions.end());
        // Find union
        upgradeCandidates.clear();
        std::set_union(combinedECUVersions.begin(), combinedECUVersions.end(),
                      sortedUpdates.begin(), sortedUpdates.end(),
                      std::back_inserter(upgradeCandidates));
    }
    // 5. Show the oldest and latest versions available
    void findVersionExtremes() {
        if (!upgradeCandidates.empty()) {
            oldestVersion = *std::min_element(upgradeCandidates.begin(), upgradeCandidates.end());
            latestVersion = *std::max_element(upgradeCandidates.begin(), upgradeCandidates.end());
        }
    }
    // Helper functions to get results
    const std::vector<FirmwareVersion>& getCombinedECUVersions() const { return combinedECUVersions; }
    const std::vector<FirmwareVersion>& getDisplayVersions() const { return displayVersions; }
    const std::vector<FirmwareVersion>& getCommonVersions() const { return commonVersions; }
    const std::vector<FirmwareVersion>& getUpgradeCandidates() const { return upgradeCandidates; }
    FirmwareVersion getOldestVersion() const { return oldestVersion; }
    FirmwareVersion getLatestVersion() const { return latestVersion; }
private:
    std::vector<FirmwareVersion> combinedECUVersions;
    std::vector<FirmwareVersion> displayVersions;
    std::vector<FirmwareVersion> commonVersions;
    std::vector<FirmwareVersion> upgradeCandidates;
    FirmwareVersion oldestVersion;
    FirmwareVersion latestVersion;
};
int main() {
    // Example usage
    ECUVersionManager manager;
    // ECU 1 supported versions
    std::vector<FirmwareVersion> ecu1 = {
        {"1.2.0"}, {"1.1.5"}, {"1.3.0"}, {"1.0.0"}
    };
    // ECU 2 supported versions
    std::vector<FirmwareVersion> ecu2 = {
        {"1.2.0"}, {"1.1.0"}, {"1.3.5"}, {"1.0.5"}
    };    
    // Available updates from OTA server
    std::vector<FirmwareVersion> availableUpdates = {
        {"1.3.5"}, {"1.4.0"}, {"1.2.0"}, {"2.0.0"}
    };    
    // 1. Combine and sort ECU versions
    manager.combineAndSortECUVersions(ecu1, ecu2);

    // 2. Merge with available updates for display
    manager.mergeAvailableUpdates(availableUpdates);

    // 3. Find common versions
    manager.findCommonVersions(availableUpdates);

    // 4. Generate upgrade candidates
    manager.generateUpgradeCandidates(availableUpdates);

    // 5. Find oldest and latest versions
    manager.findVersionExtremes();
    // Display results
    std::cout << "Combined ECU Versions:\n";
    for (const auto& v : manager.getCombinedECUVersions()) {
        std::cout << v.version << " ";
    }
    std::cout << "\n\nDisplay Versions (ECU + Available):\n";
    for (const auto& v : manager.getDisplayVersions()) {
        std::cout << v.version << " ";
    }
    std::cout << "\n\nCommon Versions:\n";
    for (const auto& v : manager.getCommonVersions()) {
        std::cout << v.version << " ";
    }
    std::cout << "\n\nUpgrade Candidates:\n";
    for (const auto& v : manager.getUpgradeCandidates()) {
        std::cout << v.version << " ";
    }
    std::cout << "\n\nOldest Version: " << manager.getOldestVersion().version;
    std::cout << "\nLatest Version: " << manager.getLatestVersion().version << "\n";
    return 0;
}
