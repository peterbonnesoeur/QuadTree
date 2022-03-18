#include "bpReadWrite.h"
#include "bpPoint.h"

#include <fstream>


void bpReadPoints(
  const std::string& aPointListPath,
  std::list<bpPoint>& aPointList)
{
  std::ifstream vPointListFileStream(aPointListPath.c_str());
  int vNumberOfPoints;
  vPointListFileStream >> vNumberOfPoints;
  for (int vIndex = 0; vIndex < vNumberOfPoints; ++vIndex) {
    bpPoint vPoint;
    vPointListFileStream >> vPoint;
    aPointList.push_back(vPoint);
  }
}


int bpReadRadius(const std::string& aRadiusPath)
{
  std::ifstream vRadiusFileStream(aRadiusPath.c_str());
  int vRadius;
  vRadiusFileStream >> vRadius;
  return vRadius;
}


static std::ostream& operator << (
  std::ostream& aStream, const std::list<int>& aList)
{
  std::list<int>::const_iterator vIt = aList.begin();
  std::list<int>::const_iterator vEnd = aList.end();
  for (; vIt != vEnd; ++vIt) {
    aStream << " " << *vIt;
  }
  return aStream;
}


void bpWriteSolution(const std::string& aSolutionFilePath,
                     const std::map<int, std::list<int> >& aSolutionMap)
{
  std::ofstream vSolutionFileStream(aSolutionFilePath.c_str());

  std::map<int, std::list<int> >::const_iterator vIt = aSolutionMap.begin();
  std::map<int, std::list<int> >::const_iterator vEnd = aSolutionMap.end();
  for (; vIt != vEnd; ++vIt) {
    // Write ID of image B bpPoint to file.
    const int& vPointId = vIt->first;
    vSolutionFileStream << "image ID: " << vPointId << ", neighbors: ";

    // Write all neighboring IDs of image A to file.
    const std::list<int>& vMappedPointIds = vIt->second;
    vSolutionFileStream << vMappedPointIds << std::endl;
  }
}


