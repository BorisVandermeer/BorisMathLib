/*********************************************************************
 * Author : BorisVandermeer
 * 
 * Discription ：
 *      Generate States Form a referance Path
 * 
*********************************************************************/
#ifndef _MATH_GENERATE_STATES_FROM_CURVES_
#define _MATH_GENERATE_STATES_FROM_CURVES_

#include<vector>
#include<Interplot/SplineCurve.h>
#include<Curves/ReedsShepp.h>
#include<Curves/Dubins.h>

namespace PointsTools{

    // Get reference points from RSCurve, save data to points;
    class PointsGenHandller{
    public:
        typedef Points::Pos2D  Pos2d;
        typedef Points::Pos2Ds RefPoses;
        typedef Points::PosPoint2D  Point2d;
        typedef Points::PosPoint2Ds RefPoints;

        class StartPos2d : public Pos2d{
        public:
            StartPos2d(){x=0,y=0,phi=0;}
            StartPos2d(double _x,double _y, double _phi){x=_x,y=_y,phi=_phi;}
            StartPos2d(Curves::RSCurveStateSpace::State state){x = state.x,y = state.y, phi = state.phi;}
        };

        class StartPoint2d : public Point2d{
        public:
            StartPoint2d(){x=0,y=0;}
            StartPoint2d(double _x,double _y, double _phi){x=_x,y=_y;}
            StartPoint2d(Curves::RSCurveStateSpace::State state){x = state.x,y = state.y;}
        };

        Interplot::SplineCurve toSplineCurve(RefPoints & points) const;

        PointsGenHandller() = default;

        Pos2d GetPose(Curves::RSCurve const RSC, double s,StartPos2d From = StartPos2d(0,0,0)) const;
        Pos2d GetPose(Curves::DubinsSpace::DubinsPath const _DBC, double s,StartPos2d From = StartPos2d(0,0,0)) const;

        // GetPoses Without the first pos
        bool GetPoses(RefPoses & points, Curves::RSCurve const RSC, double stepsize,StartPos2d From = StartPos2d(0,0,0)) const;
        bool GetPoses(RefPoses & points, Curves::DubinsSpace::DubinsPath const _DBC, double stepsize,StartPos2d From = StartPos2d(0,0,0)) const;

    };
    
} // namespace Utils

#endif