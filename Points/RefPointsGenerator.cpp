/*********************************************************************
 * Author : BorisVandermeer
 * 
 * Discription ：
 *      Generate States Form a referance Path
 * 
*********************************************************************/

#include<assert.h>
#include<Points/RefPointsGenerator.h>

using namespace std;
namespace PointsTools{

    Interplot::SplineCurve PointsGenHandller::toSplineCurve(RefPoints & points) const{
        Interplot::SplineCurve ans;
        ans.setPoints(points);
        return ans;
    }

    PointsGenHandller::Pos2d PointsGenHandller::GetPose(Curves::RSCurve const RSC, double s,StartPos2d From) const{
        Pos2d ans;
        double v,seg = s;
        double tmpx = 0,tmpy = 0,tmpphi= From.phi;
        for(int j=0;j<5&&seg>0;j++){
            if(RSC.length[j]<0.0){
                v = std::max(-seg, RSC.length[j]);
                seg += v;
            } else {
                v = std::min(seg, RSC.length[j]);
                seg -= v;
            }

            switch(RSC.type_[j]){
                case Curves::RSCurveSegmentType::RS_LEFT:
                    tmpx = tmpx + std::sin(tmpphi + v) - std::sin(tmpphi);
                    tmpy = tmpy - std::cos(tmpphi + v) + std::cos(tmpphi);
                    tmpphi = tmpphi + v;
                    break;
                case Curves::RSCurveSegmentType::RS_RIGHT:
                    tmpx = tmpx - std::sin(tmpphi - v) + std::sin(tmpphi);
                    tmpy = tmpy + std::cos(tmpphi - v) - std::cos(tmpphi);
                    tmpphi = tmpphi - v;
                    break;
                case Curves::RSCurveSegmentType::RS_STRAIGHT:
                    tmpx = v * std::cos(tmpphi) + tmpx;
                    tmpy = v * std::sin(tmpphi) + tmpy;
                    break;
                case Curves::RSCurveSegmentType::RS_NOP:
                    break;
            }
        }
        ans.x = tmpx*RSC.radius+From.x;
        ans.y = tmpy*RSC.radius+From.y;
        ans.phi = tmpphi;
        return ans;
    }


    PointsGenHandller::Pos2d PointsGenHandller::GetPose(Curves::DubinsSpace::DubinsPath const _DBC, double s,StartPos2d From) const{
        
        Pos2d ans;
        Curves::DubinsSpace DBSH;
        auto DBC = _DBC;

        typedef enum {
            L_SEG = 0,
            S_SEG = 1,
            R_SEG = 2
        } SegmentType;

        const SegmentType DIRDATA[][3] = {
            { L_SEG, S_SEG, L_SEG },
            { L_SEG, S_SEG, R_SEG },
            { R_SEG, S_SEG, L_SEG },
            { R_SEG, S_SEG, R_SEG },
            { R_SEG, L_SEG, R_SEG },
            { L_SEG, R_SEG, L_SEG }
        };

        double v,seg = s;
        double tmpx = 0,tmpy = 0,tmpphi= From.phi;
        for(int j=0;j<3&&seg>0;j++){
            v = std::min(seg, DBC.param[j]);
            seg -= v;

            switch(DIRDATA[DBC.type][j]){
                case L_SEG:
                    tmpx = tmpx + std::sin(tmpphi + v) - std::sin(tmpphi);
                    tmpy = tmpy - std::cos(tmpphi + v) + std::cos(tmpphi);
                    tmpphi = tmpphi + v;
                    break;
                case R_SEG:
                    tmpx = tmpx - std::sin(tmpphi - v) + std::sin(tmpphi);
                    tmpy = tmpy + std::cos(tmpphi - v) - std::cos(tmpphi);
                    tmpphi = tmpphi - v;
                    break;
                case S_SEG:
                    tmpx = v * std::cos(tmpphi) + tmpx;
                    tmpy = v * std::sin(tmpphi) + tmpy;
                    break;
                default :
                    break;
            }
        }
        ans.x = tmpx*DBC.rho+From.x;
        ans.y = tmpy*DBC.rho+From.y;
        ans.phi = tmpphi;

        return ans;

    }

        
    bool PointsGenHandller::GetPoses(RefPoses & poses, Curves::RSCurve const RSC, double stepsize,StartPos2d From) const{
        // double phi = 0;
        size_t num = RSC.TotalLength()/stepsize+1;
        double seglen = RSC.TotalLength()/RSC.radius;
        
        for(double i=1;i<=num;i++){
            double v,seg = static_cast<double>(i)*seglen/num;
            double tmpx = 0,tmpy = 0,tmpphi= From.phi;
            for(int j=0;j<5&&seg>0;j++){
                if(RSC.length[j]<0.0){
                    v = std::max(-seg, RSC.length[j]);
                    seg += v;
                } else {
                    v = std::min(seg, RSC.length[j]);
                    seg -= v;
                }

                switch(RSC.type_[j]){
                    case Curves::RSCurveSegmentType::RS_LEFT:
                        tmpx = tmpx + std::sin(tmpphi + v) - std::sin(tmpphi);
                        tmpy = tmpy - std::cos(tmpphi + v) + std::cos(tmpphi);
                        tmpphi = tmpphi + v;
                        break;
                    case Curves::RSCurveSegmentType::RS_RIGHT:
                        tmpx = tmpx - std::sin(tmpphi - v) + std::sin(tmpphi);
                        tmpy = tmpy + std::cos(tmpphi - v) - std::cos(tmpphi);
                        tmpphi = tmpphi - v;
                        break;
                    case Curves::RSCurveSegmentType::RS_STRAIGHT:
                        tmpx = v * std::cos(tmpphi) + tmpx;
                        tmpy = v * std::sin(tmpphi) + tmpy;
                        break;
                    case Curves::RSCurveSegmentType::RS_NOP:
                        break;
                }
            }
            poses.x.push_back(tmpx*RSC.radius+From.x);
            poses.y.push_back(tmpy*RSC.radius+From.y);
            poses.phi.push_back(tmpphi);
        }

        return true;
        
    }

    bool PointsGenHandller::GetPoses(RefPoses & poses, Curves::DubinsSpace::DubinsPath const _DBC, double stepsize,StartPos2d From) const{
        // double phi = 0;
        Curves::DubinsSpace DBSH;
        auto DBC = _DBC;
        size_t num = DBSH.CalcPathLength(&DBC)/stepsize+1;
        double seglen = DBSH.CalcPathLength(&DBC)/DBC.rho;

        typedef enum {
            L_SEG = 0,
            S_SEG = 1,
            R_SEG = 2
        } SegmentType;

        const SegmentType DIRDATA[][3] = {
            { L_SEG, S_SEG, L_SEG },
            { L_SEG, S_SEG, R_SEG },
            { R_SEG, S_SEG, L_SEG },
            { R_SEG, S_SEG, R_SEG },
            { R_SEG, L_SEG, R_SEG },
            { L_SEG, R_SEG, L_SEG }
        };
            
        for(double i=1;i<=num;i++){
            double v,seg = static_cast<double>(i)*seglen/num;
            double tmpx = 0,tmpy = 0,tmpphi= From.phi;
            for(int j=0;j<3&&seg>0;j++){
                v = std::min(seg, DBC.param[j]);
                seg -= v;

                switch(DIRDATA[DBC.type][j]){
                    case L_SEG:
                        tmpx = tmpx + std::sin(tmpphi + v) - std::sin(tmpphi);
                        tmpy = tmpy - std::cos(tmpphi + v) + std::cos(tmpphi);
                        tmpphi = tmpphi + v;
                        break;
                    case R_SEG:
                        tmpx = tmpx - std::sin(tmpphi - v) + std::sin(tmpphi);
                        tmpy = tmpy + std::cos(tmpphi - v) - std::cos(tmpphi);
                        tmpphi = tmpphi - v;
                        break;
                    case S_SEG:
                        tmpx = v * std::cos(tmpphi) + tmpx;
                        tmpy = v * std::sin(tmpphi) + tmpy;
                        break;
                    default :
                        break;
                }
            }
            poses.x.push_back(tmpx*DBC.rho+From.x);
            poses.y.push_back(tmpy*DBC.rho+From.y);
            poses.phi.push_back(tmpphi);
        }

        return true;
        
    }
}// namespace Utils