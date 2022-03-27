#include "bpPoint.h"


bpPoint::bpPoint()
  : mId(0),
    mX(0),
    mY(0)
{
}

bpPoint::bpPoint(
  const int& aId,
  const int& aX,
  const int& aY)
  : mId(aId),
    mX(aX),
    mY(aY)
{
}

const int& bpPoint::GetId() const
{
  return mId;
}

const int& bpPoint::GetX() const
{
  return mX;
}

const int& bpPoint::GetY() const
{
  return mY;
}

const float bpPoint::DistanceTo(const bpPoint& aPoint){
  return sqrt(pow(mX - aPoint.GetX(), 2) + pow(mY - aPoint.GetY(), 2));
}


std::ostream& operator << (
  std::ostream& aOut,
  const bpPoint& aPoint)
{
  aOut << aPoint.GetId() << "\t" << aPoint.GetX() << "\t" << aPoint.GetY();
  return aOut;
}

std::istream& operator >> (
  std::istream& aIn,
  bpPoint& aPoint)
{
  int vId = 0;
  int vX = 0;
  int vY = 0;
  aIn >> vId >> vX >> vY;
  aPoint = bpPoint(vId, vX, vY);
  return aIn;
}
