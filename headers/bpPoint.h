#ifndef __BP_POINT_H__
#define __BP_POINT_H__

#include <iostream>
#include <cmath>

class bpPoint
{
public:
  bpPoint();
  bpPoint(
    const int& aId,
    const int& aX,
    const int& aY);

  bpPoint(
    const int& aX,
    const int& aY):
     mX(aX), mY(aY) {};

  const int& GetId() const;
  const int& GetX() const;
  const int& GetY() const;
  const float DistanceTo(const bpPoint& aPoint);

private:
  int mId = 0;
  int mX = 0;
  int mY = 0;
};


std::ostream& operator << (
  std::ostream& aOut,
  const bpPoint& aPoint);

std::istream& operator >> (
  std::istream& aIn,
  bpPoint& aPoint);

#endif