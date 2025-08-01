#include <iostream>
#include <vector>
#include <deque>
#include <list>
#include <string>
#include <algorithm>

class AudioTracker
{
public:
    std::vector<int> volPs;
    void initVolPs()
    {
        volPs = {5, 10, 15, 20, 25};
        std::cout << "Starting for volume presets: ";
        dispVolPs();
    }
    void addVolP(int p)
    {
        if (std::find(volPs.begin(), volPs.end(), p) == volPs.end())
        {
            volPs.push_back(p);
            std::sort(volPs.begin(), volPs.end());
            std::cout << "Added volume to preset: " << p << std::endl;
        }
        else
        {
            std::cout << "Volume preset data" << p << " already exists." << std::endl;
        }
    }
    void dispVolPs() const
    {
        std::cout << "Available Volume Presets: [";
        for (size_t i = 0; i < volPs.size(); ++i)
        {
            std::cout << volPs[i];
            if (i < volPs.size() - 1)
            {
                std::cout << ", ";
            }
        }
        std::cout << "]" << std::endl;
    }
    std::deque<std::string> eventQ;
    void addRegEvt(const std::string &evt)
    {
        eventQ.push_back(evt);
        std::cout << "Add regular input value to front: " << evt << std::endl;
    }
    void addPriEvt(const std::string &evt)
    {
        eventQ.push_front(evt);
        std::cout << "Added PRIORITY input event to front: " << evt << std::endl;
    }
    void procNextEvt()
    {
        if (!eventQ.empty())
        {
            std::string evt = eventQ.front();
            eventQ.pop_front();
            std::cout << "Processing event: " << evt << std::endl;
        }
        else
        {
            std::cout << "User input event queue is empty." << std::endl;
        }
    }
    void dispEventQ() const
    {
        if (eventQ.empty())
        {
            std::cout << "User Input Event Queue: [Empty]" << std::endl;
            return;
        }
        std::cout << "User Input Event Queue: [";
        for (size_t i = 0; i < eventQ.size(); ++i)
        {
            auto it = eventQ.begin();
            std::advance(it, i);
            std::cout << *it;
            if (i < eventQ.size() - 1)
            {
                std::cout << ", ";
            }
        }
        std::cout << "]" << std::endl;
    }
    std::list<std::string> actHist;
    void addAct(const std::string &act)
    {
        actHist.push_back(act);
        std::cout << "Added action history List: " << act << std::endl;
    }
    void undoLastAct()
    {
        if (!actHist.empty())
        {
            std::string lastAct = actHist.back();
            actHist.pop_back();
            std::cout << "Undid last action: " << lastAct << std::endl;
        }
        else
        {
            std::cout << "Action history is empty, nothing to undo." << std::endl;
        }
    }
    void dispActHist() const
    {
        if (actHist.empty())
        {
            std::cout << "Audio Control Action History: [Empty]" << std::endl;
            return;
        }
        std::cout << "Audio Control Action History: {";
        bool first = true;
        for (const std::string &act : actHist)
        {
            if (!first)
            {
                std::cout << " == ";
            }
            std::cout << act;
            first = false;
        }
        std::cout << " }" << std::endl;
    }
}; 

int main()
{
    AudioTracker tracker;
    std::cout << "\nVolume Preset List  " << std::endl;
    tracker.initVolPs();
    tracker.addVolP(30);
    tracker.addVolP(15);
    tracker.dispVolPs();
    std::cout << "\nUser Input Event List " << std::endl;
    tracker.addRegEvt("VolumeUp");
    tracker.addRegEvt("ChangeSource");
    tracker.addRegEvt("Mute");
    tracker.addPriEvt("PhoneCallAudio");
    tracker.addRegEvt("VolumeDown");
    tracker.addPriEvt("NavigationPrompt");
    tracker.dispEventQ();
    tracker.procNextEvt();
    tracker.procNextEvt();
    tracker.dispEventQ();
    tracker.procNextEvt();
    tracker.dispEventQ();
    tracker.procNextEvt();
    tracker.procNextEvt();
    tracker.procNextEvt();
    tracker.procNextEvt();
    std::cout << "\nAudio Control Action History list" << std::endl;
    tracker.addAct("Audio == Set Volume 15");
    tracker.addAct("ChangeSource == Bluetooth");
    tracker.addAct("Mute");
    tracker.dispActHist();
    tracker.undoLastAct();
    tracker.dispActHist();
    tracker.undoLastAct();
    tracker.dispActHist();
    tracker.undoLastAct();
    tracker.dispActHist();
    tracker.undoLastAct();
    return 0;
}
