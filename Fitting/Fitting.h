/*********************************************************************
 * Author : BorisVandermeer
 * 
 * Discription ：
 *      A Simple implement of Linear Fitting
 * 
*********************************************************************/

#pragma once

#include<Points/PointsType.h>
#include<Geometry/Line2D.h>

namespace Fitting{

    Geometry::Line LinearFitting(Points::PosPoint2Ds Points);
    
}// namespace Fitting

