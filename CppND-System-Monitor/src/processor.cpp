#include "processor.h"
#include "linux_parser.h"

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() {
	std::vector<std::string> jiffies = LinuxParser::CpuUtilization();
  	for (int i = 0; i < int(jiffies.size()); i++) {
    	if (i != LinuxParser::kGuest_ and i != LinuxParser::kGuestNice_) {
      		totalJiffies += std::stof(jiffies[i]);
    	}
    	if (i == LinuxParser::kIdle_ or i == LinuxParser::kIOwait_) {
      		idleJiffies += std::stof(jiffies[i]);
    	}
  	}
  	utilJiffies = totalJiffies - idleJiffies;

  	bool cUtil = true;
  	if (cUtil) {
    	usage = (utilJiffies - prevUtilJiffies) / (totalJiffies - prevTotalJiffies);
    	prevTotalJiffies = totalJiffies;
    	prevUtilJiffies = utilJiffies;
  	} 
  	else {
    	usage = utilJiffies / totalJiffies;
  	}

  	return usage;
}