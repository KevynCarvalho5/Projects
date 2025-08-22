#include <iostream>
#include <vector>
#include <string>
#include <filesystem>
#include <fstream>
#include <unordered_map>
#include <thread>

using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::unordered_map;
using std::thread;
namespace fsystem = std::filesystem;

// data to be stored for each log
struct LogEntry {
    string timestamp;
    string service;
    string level;
    string message;
};


// Class to store and manage log data
class LogsData{
public:
    fsystem::path path_folder;
    vector<string> log_per_line;
    vector<LogEntry> logs;
    unordered_map<string, vector<int>> service_index;
    unordered_map<string, vector<int>> level_index;

    // load all log files into memory
    void fetch_logs(){
        for (auto& entry : fsystem::directory_iterator(path_folder)){
            if (entry.is_regular_file()){
                string filepath = entry.path().string();
                std::ifstream file(filepath);

                string line;
                while (std::getline(file, line)) log_per_line.push_back(line);

                file.close();
            }
        }
    }

    // parse log lines into LogEntry entries
    void get_log_entries(){
    int index = 1;
    for (string& s : log_per_line){
        string timestamp, service, level, message;
        
        int size = s.size();
        int iteration = 21;

        //get timestamp
        timestamp = s.substr(0, 19);

        //get service
        int to_add = 0;
        for (int i = iteration; i < size; i++){
            if (s[i] != ']'){
                service += s[i];
                to_add++;
            }
            else {
                service_index[service].push_back(index);
                break;
            }
        }
        to_add += 2;
        iteration += to_add;
        
        //get level
        to_add = 0;
        for (int i = iteration; i < size; i++){
            if (s[i] != ':'){
                level += s[i];
                to_add += 1;
            }
            else{
                level_index[level].push_back(index);
                break;
            }
        }
        iteration += to_add;

        //get message
        for (int i = iteration + 2; i < size; i++) message += s[i];

        logs.push_back({timestamp, service, level, message});
        index++;
    }
}

    // Query logs by service
    void getLogsByService(const string& service){
        //possible services 
        //"AuthService", "FileService", "SearchService", "PaymentService"
        for (auto& svc_index : service_index[service]) cout << log_per_line[svc_index-1] << endl;
    }

    // Query logs by level
    void getLogsByLevel(const string& level){
        //possible levels
        //"WARN", "INFO", "ERROR"
        for (auto& lvl_index : level_index[level]) cout << log_per_line[lvl_index-1] << endl;
    }
};

int main(){
    LogsData logsData1;
    logsData1.path_folder = fsystem::current_path() / "huge_log";

    logsData1.fetch_logs();
    logsData1.get_log_entries();

    //string level = "ERROR";
    //LogsData::getLogsByLevel(level);

    string service = "AuthService";
    logsData1.getLogsByService(service);
    
    return 0;
}
