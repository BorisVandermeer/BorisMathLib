/*********************************************************************
 * Author : BorisVandermeer
 * 
 * Discription ：
 *      A Simple implement of 2D Line
 * 
*********************************************************************/

#pragma once

#include <Vectors/Vector2D.h>

namespace Geometry {

    class  Line {
    public:
      
        Line(){};
        Vectors::Vector2D direction;
        Vectors::Vector2D point;
    };

    Points::PosPoint2D GetIntersection(Line const &  l1, Line const &  l2);

    bool isParallel(Line const & l1, Line const & l2);

} // namespace Geometry 
