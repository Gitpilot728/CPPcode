#include <iostream>
#include <vector>
#include <deque>
#include <list>
#include <algorithm>
#include <string>

class Smart_Home {
private:
    std::vector<std::string> evtArc;
    std::deque<std::string> cmdQue;
    std::list<std::string> alertList;
public:
    void logEvt(const std::string& evt) {
        evtArc.push_back(evt);
    }
    void showEvts() const {
        std::cout << "\n--- Security Camera Data Archive ---\n";
        if (evtArc.empty()) {
            std::cout << "No events logged.\n";
        } else {
            for (const auto& evt : evtArc) {
                std::cout << " " << evt << "\n";
            }
        }
    }
    void addHiPriorityCmd(const std::string& cmd) {
        cmdQue.push_front("[HP] " + cmd);
    }
    void addRegCmd(const std::string& cmd) {
        cmdQue.push_back("[RP] " + cmd);
    }
    void procCmd() {
        if (cmdQue.empty()) {
            std::cout << "No commands in queue.\n";
            return;
        }
        std::string cmd = cmdQue.front();
        cmdQue.pop_front();
        std::cout << "Processing: " << cmd << "\n";
    }
    void showCmdQue() const {
        std::cout << "\n Command List ---\n";
        if (cmdQue.empty()) {
            std::cout << "No commands in queue.\n";
        } else {
            for (const auto& cmd : cmdQue) {
                std::cout << " " << cmd << "\n";
            }
        }
    }
    void addAlert(const std::string& alert) {
        if (std::find(alertList.begin(), alertList.end(), alert) == alertList.end()) {
            alertList.push_back(alert);
            std::cout << "Alert added: " << alert << "\n";
        } else {
            std::cout << "Alert already exists: " << alert << "\n";
        }
    }
    void resolveAlert(const std::string& alert) {
        auto it = std::find(alertList.begin(), alertList.end(), alert);
        if (it != alertList.end()) {
            alertList.erase(it);
            std::cout << "Alert resolved: " << alert << "\n";
        } else {
            std::cout << "Alert not found: " << alert << "\n";
        }
    }
    void reorderAlerts(const std::string& priorityAlert) {
        auto it = std::find(alertList.begin(), alertList.end(), priorityAlert);
        if (it != alertList.end()) {
            alertList.splice(alertList.begin(), alertList, it);
            std::cout << "Prioritized alert: " << priorityAlert << "\n";
        } else {
            std::cout << "Alert not found for prioritization: " << priorityAlert << "\n";
        }
    }
    void showAlerts() const {
        std::cout << "\n Active Alerts ---\n";
        if (alertList.empty()) {
            std::cout << "No active alerts.\n";
        } else {
            for (const auto& alert : alertList) {
                std::cout << "--> " << alert << "\n";
            }
        }
    }
};

int main() {
    Smart_Home mngr;
    mngr.logEvt("Camera Motion Detected - Front Door");
    mngr.logEvt("Door Forced Open - Garage");
    mngr.logEvt("System Armed");
    mngr.addRegCmd("Switch Camera View to Kitchen");
    mngr.addHiPriorityCmd("Lock All Doors");
    mngr.addRegCmd("Night Mode Start");
    mngr.addAlert("Window Open Alert - Room");
    mngr.addAlert("Intruder Detected - Backyard");
    mngr.addAlert("Window Open Alert - Room");
    mngr.showEvts();
    mngr.showCmdQue();
    mngr.showAlerts();
    std::cout << "\nProcessing Commands:\n";
    mngr.procCmd();
    mngr.procCmd();
    mngr.reorderAlerts("Intruder Detected");
    std::cout << "\nAfter reordering alerts:\n";
    mngr.showAlerts();
    mngr.resolveAlert("Window Open Alert - room");
    std::cout << "\nAfter resolving window alert:\n";
    mngr.showAlerts();
    mngr.resolveAlert("Non-existent Alert");
    return 0;
}
