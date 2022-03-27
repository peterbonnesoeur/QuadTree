#include <iostream>
#include <cmath>
#include <vector>
#include <list>
#include <string>
#include "bpReadWrite.h"
#include "bpPoint.h"


class QuadTree
{
  private:
    bpPoint mTopLeft;
    bpPoint mBottomRight;
    int mMaxPoints = INT_MAX;

    QuadTree* mTopLeftChild;
    QuadTree* mTopRightChild;
    QuadTree* mBottomLeftChild;
    QuadTree* mBottomRightChild;

    std::list<bpPoint> mPoints;
    bool mIsLeaf = true;

  public:
    QuadTree(){
      mTopLeftChild = nullptr;
      mTopRightChild = nullptr;
      mBottomLeftChild = nullptr;
      mBottomRightChild = nullptr;

      mTopLeft = bpPoint(0, 0);
      mBottomRight = bpPoint(0, 0);
    }

  QuadTree(bpPoint aTopLeft, bpPoint aBottomRight, int aMaxPoints);
  virtual ~QuadTree() {};

  void PrintTree(std::string aSpacing);
  void Insert(const bpPoint& aPoint);
  bool IsIn(const bpPoint& aPoint) const;
  std::list<bpPoint> FindInRadius(const bpPoint& aPoint, float& aRadius) const;

};


void QuadTree::PrintTree(std::string aSpacing = ""){
  if(mIsLeaf){
    std::cout << aSpacing << "Leaf: " << mPoints.size() << " points" << std::endl;
    std::cout << aSpacing << "TopLeft: " << mTopLeft.GetX() << " " << mTopLeft.GetY() << std::endl;
  }
  else{
    std::cout << aSpacing << "Top Left" << std::endl;
    mTopLeftChild->PrintTree( aSpacing + "  ");
    std::cout << aSpacing << "Top Right" << std::endl;
    mTopRightChild->PrintTree( aSpacing + "  ");
    std::cout << aSpacing << "Bottom Left" << std::endl;
    mBottomLeftChild->PrintTree( aSpacing + "  ");
    std::cout << aSpacing << "Bottom Right" << std::endl;
    mBottomRightChild->PrintTree( aSpacing + "  ");
  }
}

QuadTree::QuadTree(bpPoint aTopLeft, bpPoint aBottomRight, int aMaxPoints) : mTopLeft(aTopLeft), mBottomRight(aBottomRight), mMaxPoints(aMaxPoints), mIsLeaf(true)
{

  mTopLeftChild = nullptr;
  mTopRightChild = nullptr;
  mBottomLeftChild = nullptr;
  mBottomRightChild = nullptr;

  mPoints = std::list<bpPoint>();
}

void QuadTree::Insert(const bpPoint& aPoint)
{

  if (!IsIn(aPoint))
  {
    //std::cout << "Point is not in the quadtree" << std::endl;
    //std::cout << "Point: " << aPoint.GetX() << " " << aPoint.GetY() << std::endl;
    return;
  }

  if( mIsLeaf && mPoints.size() < mMaxPoints)
  {
      mPoints.push_back(aPoint);
      return;
  }
  else
  {
    mIsLeaf = false;
    if(mTopLeftChild == nullptr)
    {
      mTopLeftChild = new QuadTree(
                                    mTopLeft, bpPoint(mTopLeft.GetX() + (mBottomRight.GetX() - mTopLeft.GetX())/2,
                                    mTopLeft.GetY() + (mBottomRight.GetY() - mTopLeft.GetY())/2),
                                    mMaxPoints);
      mTopRightChild = new QuadTree(
                                    bpPoint(mTopLeft.GetX() + (mBottomRight.GetX() - mTopLeft.GetX())/2, mTopLeft.GetY()),
                                    bpPoint(mBottomRight.GetX(), mTopLeft.GetY() + (mBottomRight.GetY() - mTopLeft.GetY())/2),
                                    mMaxPoints);
      mBottomLeftChild = new QuadTree(
                                    bpPoint(mTopLeft.GetX(), mTopLeft.GetY() + (mBottomRight.GetY() - mTopLeft.GetY())/2),
                                    bpPoint(mTopLeft.GetX() + (mBottomRight.GetX() - mTopLeft.GetX())/2, mBottomRight.GetY()),
                                    mMaxPoints);
      mBottomRightChild = new QuadTree(
                                    bpPoint(mTopLeft.GetX() + (mBottomRight.GetX() - mTopLeft.GetX())/2, mTopLeft.GetY() + (mBottomRight.GetY() - mTopLeft.GetY())/2),
                                    mBottomRight,
                                    mMaxPoints);

      for (auto point : mPoints)
      {
        mTopLeftChild->Insert(point);
        mTopRightChild->Insert(point);
        mBottomLeftChild->Insert(point);
        mBottomRightChild->Insert(point);
      }
    }

    mTopLeftChild->Insert(aPoint);
    mTopRightChild->Insert(aPoint);
    mBottomLeftChild->Insert(aPoint);
    mBottomRightChild->Insert(aPoint);
  }
}

std::list<bpPoint> QuadTree::FindInRadius(const bpPoint& aPoint, float& aRadius) const{
  std::list<bpPoint> pointsInRadius;
  if(!IsIn(aPoint)){
    return pointsInRadius;
  }

  if(mIsLeaf){
    for(auto point : mPoints){
      if(point.DistanceTo(aPoint) <= aRadius){
        pointsInRadius.push_back(point);
      }
    }
  }
  else{
    pointsInRadius.splice(pointsInRadius.end(), mTopLeftChild->FindInRadius(aPoint, aRadius));
    pointsInRadius.splice(pointsInRadius.end(), mTopRightChild->FindInRadius(aPoint, aRadius));
    pointsInRadius.splice(pointsInRadius.end(), mBottomLeftChild->FindInRadius(aPoint, aRadius));
    pointsInRadius.splice(pointsInRadius.end(), mBottomRightChild->FindInRadius(aPoint, aRadius));
  }

  return pointsInRadius;
}

bool QuadTree::IsIn(const bpPoint& aPoint) const
{
    if (aPoint.GetX() >= mTopLeft.GetX() && aPoint.GetX() <= mBottomRight.GetX() &&
        aPoint.GetY() <= mTopLeft.GetY() && aPoint.GetY() >= mBottomRight.GetY())
    {
        return true;
    }
    else
    {
        return false;
    }
}


int main() {
    std::cout << "Hello, World!" << std::endl;

    // Reading bpPoints of image A from file.
     // Reading bpPoints of image A from file.
    std::list<bpPoint> vPointListImage;
    bpReadPoints("data/Points.txt", vPointListImage);

    // Reading bpPoints of image B from file.
    std::list<bpPoint> vPointListImageB;
    bpReadPoints("data/PointsToFind.txt", vPointListImageB);


    // Reading radius defining neighbors in range from file.

    float vRadius = bpReadRadius("data/Radius.txt");
    int maxPoints = bpReadMaxPoints("data/MaxPoints.txt");

    // Creating QuadTree for image A.
    QuadTree vQuadTreeImage(bpPoint(0, 500), bpPoint(500, 0), maxPoints);


    // Inserting bpPoints of image A to QuadTree.
    for (auto point : vPointListImage)
    {
        vQuadTreeImage.Insert(point);
    }

    vQuadTreeImage.Insert(vPointListImage.front());

    vQuadTreeImage.PrintTree();

    // Finding bpPoints of image B in range.

    std::map<int, std::list<int> > vSolutionIds;


    for (auto vPointB : vPointListImageB)
    {

      std::cout << "Point: " << vPointB.GetId() <<  vPointB.GetX() << " " << vPointB.GetY() << std::endl;
      for ( auto vPointA : vQuadTreeImage.FindInRadius(vPointB, vRadius))
      {
        vSolutionIds[vPointB.GetId()].push_back(vPointA.GetId());
      }
    }


    // Example: ID 35 has neighboring IDs 3, 5, 6.
    {
        std::list<int> vNeighbors;
        vNeighbors.push_back(3);
        vNeighbors.push_back(5);
        vNeighbors.push_back(6);
        vSolutionIds.insert(std::pair<int, std::list<int> >(35, vNeighbors));
    }

    bpWriteSolution("data/Solution.txt", vSolutionIds);
    return 0;
}