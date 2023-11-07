

#pragma once

#include<vector>
#include<Points/PointsType.h>

namespace Curves{

namespace CirclesCurve{

    enum SegmentType{
        L_SEG = 0,
        S_SEG = 1,
        R_SEG = 2,
        LN_SEG = 3,
        SN_SEG = 4,
        RN_SEG = 5,
        NOP_SEG = 6,
    };

    struct PathSegment{
        SegmentType type;
        double radius;
        double length;  // 弧度变化
    };


    class CirclesPath{
    public:
        CirclesPath() = default;
        double TotalLength();
        auto size(){return Data.size();}
    public :
        std::vector<PathSegment> Data;
        Points::Pos2D From;
    };
}

}
