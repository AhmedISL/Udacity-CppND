#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() { 
	float TM, FM;
  	std::ifstream stream(kProcDirectory + kMeminfoFilename);
  	string key, value, unit, line;
  
  	if(stream.is_open()){
    	while(std::getline(stream, line)){
        	std::replace(line.begin(), line.end(), ':', ' ');
          	std::istringstream lstream(line);
          	while(lstream >> key >> value >> unit){
            	if(key == "MemTotal"){
                	TM = stof(value);
                }
              	else if(key == "MemFree"){
                	FM = stof(value);
                }
            }
        }
    }
  	return ((TM - FM) / TM);
}

// TODO: Read and return the system uptime
long LinuxParser::UpTime() {
	long int upTime;
  	std::string uTStr, line, value1, value2;
  	std::ifstream stream(kProcDirectory + kUptimeFilename);
  	if(stream.is_open()){
    	while(std::getline(stream, line)){
        	std::istringstream lstream(line);
          	while(lstream >> value1 >> value2){
            	uTStr = value1;
            }
        }
    }
  
  	upTime = std::stol(uTStr);
  	return upTime;
}

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid) {
	string value, line;
  	long totalTime;
  	vector<string> stats;
  	std::ifstream stream(kProcDirectory + std::to_string(pid) + kStatFilename);
  	if (stream.is_open()) {
    	std::getline(stream, line);
    	std::istringstream lstream(line);
    	while (lstream >> value) {
      		stats.push_back(value);
    	}
  	}
  	long int uTime = stol(stats[13]);
  	long int sTime = stol(stats[14]);
  	long int cuTime = stol(stats[15]);
  	long int csTime = stol(stats[16]);
  	totalTime = (uTime + sTime + cuTime + csTime);
  	return totalTime;
}

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() {
	string value, key, line;
  	vector<string> jiffies;
  	std::ifstream stream(kProcDirectory + kStatFilename);
  	if (stream.is_open()) {
    	std::getline(stream, line);
    	std::istringstream lstream(line);
    	while (lstream >> key) {
      		if (key != "cpu") {
        		jiffies.push_back(key);
      		}
    	}
  	}
  	return jiffies;
}

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() {
	int totalProcesses;
  	string key, value, line;
  	std::ifstream stream(kProcDirectory + kStatFilename);
  	if(stream.is_open()){
    	while (std::getline(stream, line)) {
      		std::istringstream lstream(line);
      		while (lstream >> key >> value) {
        		if (key == "processes") {
          			totalProcesses = stoi(value);
        		}
      		}
    	}
  	}
  	return totalProcesses;
}

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() {
	int runningProcesses;
  	std::string key, value, line;
  	std::ifstream stream(kProcDirectory + kStatFilename);
  	if (stream.is_open()) {
    	while (std::getline(stream, line)) {
      		std::istringstream lstream(line);
      		while (lstream >> key >> value) {
        		if (key == "procs_running") {
          			runningProcesses = std::stoi(value);
        		}
      		}
    	}
  	}
  	return runningProcesses;
}

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid) {
	std::string line;
  	std::ifstream stream(kProcDirectory + std::to_string(pid) + kCmdlineFilename);

  if (stream.is_open()) {
    	std::getline(stream, line);
  }

  return line;
}

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid) {
	string key, value, unit, line;
  	string ram;
  	int vmsize;
  	std::ifstream stream(kProcDirectory + to_string(pid) + kStatusFilename);
  	if (stream.is_open()) {
    	while (std::getline(stream, line)) {
      		std::istringstream lstream(line);
      		while (lstream >> key >> value >> unit) {
        		if (key == "VmSize:") {
          			vmsize = stoi(value);
          			vmsize = vmsize / 1024;
          			ram = to_string(vmsize);
        		}
      		}
    	}
  	}
  	return ram;
}

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid) {
	string key, value, uid, line;
  	std::ifstream stream(kProcDirectory + to_string(pid) + kStatusFilename);
  	if (stream.is_open()) {
    	while (std::getline(stream, line)) {
      		std::istringstream lstream(line);
      		while (lstream >> key >> value) {
        		if (key == "Uid:") {
          			uid = value;
        		}
      		}
    	}
  	}
  	return uid;
}

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid) {
	string user, cUser, pswd, cUid, line;
  	string uid = LinuxParser::Uid(pid);
  	std::ifstream stream(kPasswordPath);
  	if (stream.is_open()) {
    	while (std::getline(stream, line)) {
      		std::replace(line.begin(), line.end(), ':', ' ');
      		std::istringstream lstream(line);
      		while (lstream >> cUser >> pswd >> cUid) {
        		if (uid == cUid) {
          			user = cUser;
        		}
      		}
    	}
  	}
  	return user;
}

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid) {
	string value, line;
  	vector<string> stats;
  	std::ifstream stream(kProcDirectory + to_string(pid) + kStatFilename);
  	if (stream.is_open()) {
    	std::getline(stream, line);
    	std::istringstream lstream(line);
    		while (lstream >> value) {
      			stats.push_back(value);
    		}
  		}
  	long int startTime = stol(stats[21]) / sysconf(_SC_CLK_TCK);
  	long int upTime = LinuxParser::UpTime() - startTime;
  	return upTime;
}


float LinuxParser::CpuUtilization(int pid) {
  	long activeTime = LinuxParser::ActiveJiffies(pid) / sysconf(_SC_CLK_TCK);
  	long upTime = LinuxParser::UpTime(pid);
  	return ((float)activeTime / upTime);
}
