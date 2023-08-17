/*********************************************************************
 * Author : BorisVandermeer
 * 
 * Discription ：
 *      A simple cubic spline path library without external 
 *      dependencies.
 * 
*********************************************************************/

#ifndef _INTERPLOATION_SPLINE_CURVE_H_
#define _INTERPLOATION_SPLINE_CURVE_H_

#include<cmath>
#include<vector>
#include<Interplot/Spline.h>

namespace Interplot
{
    class SplineCurve
    {
    public:
        typedef Spline::RefPoints  RefPoints;
        typedef Points::PosPoint2D Point;
        typedef Points::Pos2D      Pos2D;

        SplineCurve(){};
        ~SplineCurve(){};
        void setPoints(RefPoints refps);
        void setPoints(const std::vector<double> & x,const std::vector<double> & y);
        void setPoints(RefPoints refps,double FromHeading,double ToHeading);
        void setPoints(const std::vector<double> & x,const std::vector<double> & y,double FromHeading,double ToHeading);
        void rebuild(double stepsize);
        void setSplines(Spline _xs,Spline _ys);
        double getProjection(Point target,double max_s,double min_s,bool NewtownRefine = true, double gridsize = 0.5) const;
        double getDirectionalProjection(Pos2D target,double max_s,double min_s,bool NewtownRefine = true, double gridsize = 0.5) const;
        bool HasData() const  {return data_flag;}
        Point operator()(double s) const;
        double getHeading(double s) const {return std::atan2(ys_.getDeriv(1,s),xs_.getDeriv(1,s));} 
        double getCurvity(double s) const;
        double getCutvityDeriv(double s) const;

    public:
        double max_s;

    private:
        Spline xs_,ys_;
        bool data_flag = false;
        double getProjectionByNewton(Point target,double s_hint, double s_max) const;
        double getDirectionalProjectionByNewton(Pos2D target,double s_hint, double s_max) const;

    };
    
} // namespace Interplot 

#endif