

#include<Curves/CirclesCurve.h>

namespace Curves{

namespace CirclesCurve{

    double CirclesPath::TotalLength(){
        double ans = 0;
        for(auto & seg : Data){
            ans += seg.length * seg.radius;
        }
        return ans;
    }



} // namespace CirclesCurve
} // namespace Curves
