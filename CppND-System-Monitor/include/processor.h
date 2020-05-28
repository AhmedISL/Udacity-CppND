#ifndef PROCESSOR_H
#define PROCESSOR_H

class Processor {
 public:
  float Utilization();  // TODO: See src/processor.cpp

  // TODO: Declare any necessary private members
 private:
  float totalJiffies{0.0};
  float prevTotalJiffies{0.0};
  float idleJiffies{0.0};
  float utilJiffies{0.0};
  float prevUtilJiffies{0.0};
  float usage{0.0};
};

#endif