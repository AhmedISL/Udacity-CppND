#include <string>

#include "format.h"

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) {
	long hours = seconds / 3600;
  	long remaining_seconds = seconds % 3600;
  	long minutes = remaining_seconds / 60;
  	long sec = remaining_seconds % 60;
  	string hourStr = std::to_string(hours);
  	string minuteStr = std::to_string(minutes);
  	string secondStr = std::to_string(sec);
  	string time = string(2 - hourStr.length(), '0') + hourStr + ':' + string(2 - minuteStr.length(), '0') + minuteStr + ':' + string(2 - secondStr.length(), '0') + secondStr;
  	return time;
}