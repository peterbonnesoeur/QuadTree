#ifndef __BP_READ_WRITE_H__
#define __BP_READ_WRITE_H__


#include <list>
#include <map>
#include <string>

class bpPoint;


void bpReadPoints(
  const std::string& aPointListPath,
  std::list<bpPoint>& aPointList);

int bpReadRadius(const std::string& aRadiusPath);

int bpReadMaxPoints(const std::string& aMaxPointsPath);

void bpWriteSolution(
  const std::string& aSolutionFilePath,
  const std::map<int, std::list<int> >& aSolutionMap);


#endif