#include <iostream>
#include <cmath>
#include <vector>
#include <list>
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

        void insert(bpPoint aPoint);
        bool isIn(bpPoint aPoint);
};


QuadTree::QuadTree(bpPoint aTopLeft, bpPoint aBottomRight, int aMaxPoints) : mTopLeft(aTopLeft), mBottomRight(aBottomRight), mMaxPoints(aMaxPoints)
{

    mTopLeftChild = nullptr;
    mTopRightChild = nullptr;
    mBottomLeftChild = nullptr;
    mBottomRightChild = nullptr;

    mPoints = std::list<bpPoint>();

}

QuadTree::insert(bpPoint aPoint)
{

    if (!isIn(aPoint))
    {
        return;
    }

    if(isIn(aPoint) && mPoints.size() < mMaxPoints)
    {
        mPoints.push_back(aPoint);
        return;
    }
    else
    {
        if(mTopLeftChild == nullptr)
        {
            mTopLeftChild = new QuadTree(mTopLeft, bpPoint(mTopLeft.GetX() + (mBottomRight.GetX() - mTopLeft.GetX())/2, mTopLeft.GetY() + (mBottomRight.GetY() - mTopLeft.GetY())/2));
            mTopRightChild = new QuadTree(bpPoint(mTopLeft.GetX() + (mBottomRight.GetX() - mTopLeft.GetX())/2, mTopLeft.GetY()), bpPoint(mBottomRight.GetX(), mTopLeft.GetY() + (mBottomRight.GetY() - mTopLeft.GetY())/2));
            mBottomLeftChild = new QuadTree(bpPoint(mTopLeft.GetX(), mTopLeft.GetY() + (mBottomRight.GetY() - mTopLeft.GetY())/2), bpPoint(mTopLeft.GetX() + (mBottomRight.GetX() - mTopLeft.GetX())/2, mBottomRight.GetY()));
            mBottomRightChild = new QuadTree(bpPoint(mTopLeft.GetX() + (mBottomRight.GetX() - mTopLeft.GetX())/2, mTopLeft.GetY() + (mBottomRight.GetY() - mTopLeft.GetY())/2), mBottomRight);
        }

        if(mTopLeftChild->isIn(aPoint))
        {
            mTopLeftChild->insert(aPoint);
        }
        else if(mTopRightChild->isIn(aPoint))
        {
            mTopRightChild->insert(aPoint);
        }
        else if(mBottomLeftChild->isIn(aPoint))
        {
            mBottomLeftChild->insert(aPoint);
        }
        else if(mBottomRightChild->isIn(aPoint))
        {
*/
bool QuadTree::isIn(bpPoint aPoint)
{
    if (aPoint.GetX() >= mTopLeft.GetX() && aPoint.GetX() <= mBottomRight.GetX() &&
        aPoint.GetY() >= mTopLeft.GetY() && aPoint.GetY() <= mBottomRight.GetY())
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
    /*std::list<bpPoint> vPointListImageB;
    bpReadPoints("data/PointsToFind.txt", vPointListImageB);*/


    // Reading radius defining neighbors in range.
    int vRadius = 20;
    int maxPoints = 100;

    // Creating QuadTree for image A.
    QuadTree vQuadTreeImage(bpPoint(0, 0), bpPoint(100, 100), maxPoints);

    std::map<int, std::list<int> > vSolutionIds;
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