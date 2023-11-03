
/*********************************************************************
 * Author : BorisVandermeer
 * 
 * Discription ：
 *      A Simple implement of 2D Circles
 * 
*********************************************************************/
#include<cmath>
#include<Fitting/Fitting.h>

namespace Fitting{

    Geometry::Line LinearFitting(Points::PosPoint2Ds points){

        Geometry::Line ans;

        double xmean = 0.0;
        double ymean = 0.0;

        for(auto & x : points.x) xmean+=x;
        for(auto & y : points.y) ymean+=y;

        xmean/=points.size();
        ymean/=points.size();

        double sumx2 = 0;
        double sumy2 = 0;
        double sumyx = 0.0;

        for(int i = points.size()-1;i>=0;i--){
            sumx2 += (points.x[i]-xmean)*(points.x[i]-xmean);
            sumy2 += (points.y[i]-ymean)*(points.y[i]-ymean);
            sumyx += (points.y[i]-ymean)*(points.x[i]-xmean);
        }

        ans.point = Vectors::Vector2D(xmean,ymean);
        if(fabs(sumx2)<1e-5){
            ans.direction = Vectors::Vector2D(0,1);
            return ans;
        }

        ans.direction = Vectors::Vector2D(sumx2,sumyx)/std::max(sumx2,sumyx);
        return ans;
    }
    
}// namespace Fitting