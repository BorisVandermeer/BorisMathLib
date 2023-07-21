/*********************************************************************
 * Author : BorisVandermeer
 * 
 * Discription ：
 *      A Simple implement of 2D Line
 * 
*********************************************************************/

#include<cmath>

#include<Geometry/Line2D.h>
#define A_PRIVATE_VALUE (0.001)

namespace Geometry {

    Points::PosPoint2D GetIntersection(Line l1, Line l2){
        /*
        * x = x1 + k1*dx1      \                                 
        * x = x2 + k2*dx2   ----\    x1 - x2 = k2*dx2 - k1*dx1  
        * y = y1 + k1*dy1   ----/    y1 - y2 = k2*dy2 - k1*dy1
        * y = y2 + k2*dy2      /
        */
        double x1 = l1.point.x; double y1 = l1.point.y; double dx1 = l1.direction.x; double dy1 = l1.direction.y;
        double x2 = l2.point.x; double y2 = l2.point.y; double dx2 = l2.direction.x; double dy2 = l2.direction.y;
        double tmp = dy1*dx2-dx1*dy2;
        if(std::fabs(tmp)<A_PRIVATE_VALUE) return Points::PosPoint2D(NAN,NAN);
        double k2 = (dx1*(y1-y2)-dy1*(x1-x2))/tmp;
        // double k2 = (dx2*(y2-y1)-dy2*(x2-x1));
        return Points::PosPoint2D(x2 + k2*dx2,y2 + k2*dy2);
    }
} //namespace Geometry
