#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"
#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;

Process::Process(int pid) : PID(pid), cpuUtil(Process::CpuUtilization()) {}

// TODO: Return this process's ID
int Process::Pid() { return PID; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() { return LinuxParser::CpuUtilization(PID); }

// TODO: Return the command that generated this process
string Process::Command() { return LinuxParser::Command(PID); }

// TODO: Return this process's memory utilization
string Process::Ram() { return LinuxParser::Ram(PID); }

// TODO: Return the user (name) that generated this process
string Process::User() { return LinuxParser::User(PID); }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { return LinuxParser::UpTime(PID); }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a) const {
	return cpuUtil > a.cpuUtil;
}

