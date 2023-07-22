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
        typedef Vectors::Vector2D Vector2D;
      
        Line(){};
        Line(Vector2D & _point, Vector2D & _direction):point(_point),direction(_direction){}
        Line(Vector2D const & _point, Vector2D const & _direction):point(_point),direction(_direction){}
        Vectors::Vector2D direction;
        Vectors::Vector2D point;
    };

    Points::PosPoint2D GetIntersection(Line const &  l1, Line const &  l2);

    bool isParallel(Line const & l1, Line const & l2);

} // namespace Geometry 
