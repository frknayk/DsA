#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <unordered_map>
#include <iomanip>

using namespace std;

/************************* DEFINE DATA STRUCTURES *************************/
struct TimeIntervals {
    int start;
    int finish;
};

struct Priority {
    string floorName;
    string roomNo;
    int priority;
};

struct Item {
    string name;
    int price;
    float value;
};

// Define a structure for a single room schedule
struct RoomSchedule {
    string roomName;
    int start;
    int finish;
    int priority;
};

// Define a structure for floor data including priority gain
struct FloorData {
    vector<RoomSchedule> optimalSchedule;
    float priorityGain;
};

// Define a data structure for schedules using a hash-map between floor and rooms
class Schedule {
    public:
        unordered_map<string, unordered_map<string, vector<RoomSchedule>>> floorRoomMap;
        unordered_map<string, FloorData> floorDataMap; // Added floor data map

        // Function to add a schedule for a room in a floor
        void addSchedule(string floorName, string roomNo, int start, int finish, int priority) {
            RoomSchedule roomSchedule = {roomNo, start, finish, priority};
            floorRoomMap[floorName][roomNo].push_back(roomSchedule);
        }

        // Function to get all schedules for a room in a floor
        vector<RoomSchedule> getSchedules(string floorName, string roomNo) {
            return floorRoomMap[floorName][roomNo];
        }

        // Function to check if schedules exist for a room in a floor
        bool hasSchedules(string floorName, string roomNo) {
            return floorRoomMap.count(floorName) && floorRoomMap[floorName].count(roomNo);
        }

        // Function to get all schedules for a floor
        vector<RoomSchedule> getAllSchedules(string floorName) {
            vector<RoomSchedule> allSchedules;
            for (const auto& room : floorRoomMap[floorName]) {
                allSchedules.insert(allSchedules.end(), room.second.begin(), room.second.end());
            }
            return allSchedules;
        }

        // Function to set optimal schedule for a floor
        void setOptimalSchedule(string floorName, vector<RoomSchedule> optimalSchedule) {
            floorDataMap[floorName].optimalSchedule = optimalSchedule;
        }

        // Function to get optimal schedule for a floor
        const vector<RoomSchedule> getOptimalSchedule(string floorName) {
            return floorDataMap[floorName].optimalSchedule;
        }

        // Function to set priority gain for a floor
        void setPriorityGain(string floorName, float priorityGain) {
            floorDataMap[floorName].priorityGain = priorityGain;
        }

        // Function to get priority gain for a floor
        const float getPriorityGain(string floorName) {
            return floorDataMap[floorName].priorityGain;
        }

        const int getSize(){
            return floorRoomMap.size();
        }

};


/************************* DEFINE HELPER FUNCTIONS *************************/
int time_to_minutes(string time_str) {
    int hours, minutes;
    char colon;
    stringstream ss(time_str);
    ss >> hours >> colon >> minutes;
    return hours * 60 + minutes;
}

vector<Priority> readFromFilePrioritis(const string path){
    // Reading priorities
    vector<Priority> priorities;
    ifstream priority_file(path);
    if (priority_file.is_open()) {
        string line;
        getline(priority_file, line); // skipping header
        while (getline(priority_file, line)) {
            stringstream ss(line);
            Priority p;
            ss >> p.floorName >> p.roomNo >> p.priority;
            priorities.push_back(p);
        }
        priority_file.close();
    } else {
        cerr << "Unable to open priority file" << endl;
    }
    return priorities;
}

Schedule readFromFileIntervals(const string path, const vector<Priority> &priorities){
    Schedule schedule;
    ifstream interval_file(path);
    if (interval_file.is_open()) {
        string line;
        getline(interval_file, line); // skipping header
        while (getline(interval_file, line)) {
            stringstream ss(line);
            string floorName;
            string roomNo;
            int start;
            int finish;
            int priority;
            ss >> floorName >> roomNo;
            // Read and convert time string to minutes since midnight
            string start_time_str, end_time_str;
            ss >> start_time_str >> end_time_str;
            start = time_to_minutes(start_time_str);
            finish = time_to_minutes(end_time_str);
            for (const auto& p : priorities) {
                if (p.floorName == floorName && p.roomNo == roomNo) {
                    priority = p.priority;
                    break;
                }
            }
            schedule.addSchedule(floorName, roomNo, start, finish, priority);
        }
        interval_file.close();
    } else {
        cerr << "Unable to open intervals file" << endl;
    }
    return schedule;
}

vector<Item> readFromFileItems(const string path){
    vector<Item> items;
    ifstream item_file(path);
    if (item_file.is_open()) {
        string line;
        getline(item_file, line); // skipping header
        while (getline(item_file, line)) {
            stringstream ss(line);
            Item item;
            ss >> item.name >> item.price >> item.value;
            items.push_back(item);
        }
        item_file.close();
    } else {
        cerr << "Unable to open item file" << endl;
    }
    return items;
}

std::string padStartTime(int startTime) {
    std::ostringstream oss;
    oss << startTime;
    std::string startTimeStr = oss.str();
    if (startTimeStr.size() == 1) {
        return "0" + startTimeStr;
    }
    // remove(startTimeStr.begin(), startTimeStr.end(), ' ');
    startTimeStr.erase( remove( startTimeStr.begin(), startTimeStr.end(), ' ' ), startTimeStr.end() );
    return startTimeStr;
}

std::string minutes_to_hours(int minutes) {
    int hours = minutes / 60;
    int mins = minutes % 60;
    string mins_str = padStartTime(mins);
    string hours_str = padStartTime(hours);
    return hours_str + ":" + mins_str;
}

void printSchedule(Schedule& optimal_schedule) {
    // Collect floor names and sort them based on their numerical order
    vector<string> floor_names;
    for (const auto& floor : optimal_schedule.floorDataMap) {
        floor_names.push_back(floor.first);
    }
    sort(floor_names.begin(), floor_names.end(), [](const string& a, const string& b) {
        return stoi(a.substr(6)) < stoi(b.substr(6));
    });

    // Print priority gain for each floor
    cout<<"Best Schedule for Each Floor\n";
    for (const auto& floor_name : floor_names) {
        cout << floor_name << " --> Priority Gain: " << optimal_schedule.getPriorityGain(floor_name) << "\n";
        // Print schedules for each room in the floor
        for (const auto& room : optimal_schedule.getOptimalSchedule(floor_name)){
            string startTime = minutes_to_hours(room.start);
            string finishTime = minutes_to_hours(room.finish);
            cout << floor_name << "\t" << room.roomName << "\t" << startTime << "\t" << finishTime << "\n";
        }
    }
}

void printItems(vector<Item>& selected_items) {
    // Sort items based on value
    double total_value_items = 0;
    for(const auto& selected_item: selected_items){
        total_value_items += selected_item.value;
    }
    // Selecting items using knapsack algorithm
    cout << "Best Use of Budget"<<"\n";
    const double rounded_total_val = static_cast<int>(total_value_items * 10 + 0.51) / 10.0;
    cout<< "Total Value --> "<< std::fixed << std::setprecision(1) << rounded_total_val<<"\n";
    for (const auto& item : selected_items) {
        cout << item.name << "\n";
    }
}

/************************* DEFINE ALGORITHMS *************************/
// Function to find the best schedule for each room in each floor
Schedule weighted_interval_scheduling(Schedule schedules) {
    Schedule optimal_schedules;

    // Iterate over each floor
    for (const auto& floor : schedules.floorRoomMap) {
        // Gather all schedules for the current floor
        vector<RoomSchedule> floor_schedules = schedules.getAllSchedules(floor.first);

        // Sort schedules for the floor based on finish time
        sort(floor_schedules.begin(), floor_schedules.end(), [](const RoomSchedule& a, const RoomSchedule& b) {
            return a.finish < b.finish;
        });

        vector<int> dp(floor_schedules.size());
        vector<vector<int>> prev(floor_schedules.size(), vector<int>(floor_schedules.size(), -1));

        // Fill DP table
        dp[0] = floor_schedules[0].priority;
        // Compare each room with each other and update it's value based on priority
        // NOTE: I sort schedules first, so I can compare only predecessors. 
        for (int i = 1; i < static_cast<int>(floor_schedules.size()); ++i) {
            dp[i] = floor_schedules[i].priority;
            for (int j = i - 1; j >= 0; --j) {
                if (floor_schedules[j].finish <= floor_schedules[i].start) {
                    int included = floor_schedules[i].priority + dp[j];
                    if (included > dp[i]) {
                        dp[i] = included;
                        prev[i] = {j, i};
                    }
                }
            }
        }

        // Reconstruct optimal schedule for the floor
        vector<RoomSchedule> optimal_floor_schedule;
        int max_index = max_element(dp.begin(), dp.end()) - dp.begin();
        while (max_index != -1) {
            optimal_floor_schedule.push_back(floor_schedules[max_index]);
            if (prev[max_index][0] != -1)
                max_index = prev[max_index][0];
            else
                break;
        }
        reverse(optimal_floor_schedule.begin(), optimal_floor_schedule.end());

        // Calculate total priority of all available schedules for this floor
        int total_priority_floor = 0;
        for (const auto& schedule : optimal_floor_schedule) {
            total_priority_floor += schedule.priority;
        }

        // Store optimal schedule for the floor and calculate Priority Gain
        optimal_schedules.setOptimalSchedule(floor.first, optimal_floor_schedule);
        optimal_schedules.setPriorityGain(floor.first, total_priority_floor);
    }

    return optimal_schedules;
}


// Function to select the most valuable items that can be purchased with a certain budget
vector<Item> knapsack(const vector<Item>& Items, int budget) {
    vector<vector<float>> dp(Items.size() + 1, vector<float>(budget + 1, 0));
    vector<vector<bool>> keep(Items.size() + 1, vector<bool>(budget + 1, false));

    for (int i = 1; i <=  static_cast<int>(Items.size()); ++i) {
        for (int w = 1; w <= budget; ++w) {
            if (Items[i - 1].price <= w) {
                if (Items[i - 1].value + dp[i - 1][w - Items[i - 1].price] > dp[i - 1][w]) {
                    dp[i][w] = Items[i - 1].value + dp[i - 1][w - Items[i - 1].price];
                    keep[i][w] = true;
                } else {
                    dp[i][w] = dp[i - 1][w];
                }
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    int i = Items.size();
    int w = budget;
    vector<Item> selected_items;
    while (i > 0 && w > 0) {
        if (keep[i][w]) {
            selected_items.push_back(Items[i - 1]);
            w -= Items[i - 1].price;
        }
        --i;
    }

    // reverse(selected_items.begin(), selected_items.end());
    return selected_items;
}


/************************* START *************************/
int main(int argc, char *argv[]) {
    string case_no = argv[1];
    string case_name = "case_" + case_no;
    string path = "./inputs/" + case_name;
    int total_budget = 200000;

    // Reading priorities
    vector<Priority> priorities = readFromFilePrioritis(path + "/priority.txt");
    if (priorities.size()==0){
        return 1;
    }

    // Read time intervals for each room to create schedules
    Schedule schedules = readFromFileIntervals(path + "/room_time_intervals.txt", priorities);
    if (schedules.getSize()==0){
            return 1;
    }

    // Reading items
    vector<Item> items = readFromFileItems(path + "/items.txt");
    if (items.size()==0){
            return 1;
    }

    // Calculate optimal schedules for each floor based on priority value
    Schedule schedulesOptimal = weighted_interval_scheduling(schedules);
    printSchedule(schedulesOptimal);

    // Calculate optimal items needed
    vector<Item> selected_items = knapsack(items, total_budget);
    printItems(selected_items);


}
