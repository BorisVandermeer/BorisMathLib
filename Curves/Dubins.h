// Referance : https://github.com/AndrewWalker/Dubins-Curves

#pragma once

#define EDUBOK        (0)   /* No error */
#define EDUBCOCONFIGS (1)   /* Colocated configurations */
#define EDUBPARAM     (2)   /* Path parameterisitation error */
#define EDUBBADRHO    (3)   /* the rho value is invalid */
#define EDUBNOPATH    (4)   /* no connection between configurations with this word */

namespace Curves{

    class DubinsSpace{
    public : 
        typedef enum {
            LSL = 0,
            LSR = 1,
            RSL = 2,
            RSR = 3,
            RLR = 4,
            LRL = 5
        } DubinsPathType;

        typedef struct {
            double qi[3];     // Initial configuration
            double param[3];  // Lengths of the three segments
            double rho;       // Model forward velocity / model angular velocity
            DubinsPathType type; 
        } DubinsPath;

        typedef int (*DubinsPathSamplingCallback)(double q[3], double t, void* user_data);

        int CalcShortestPath(DubinsPath* path, double q0[3], double q1[3], double rho);

        int CalcPath(DubinsPath* path, double q0[3], double q1[3], double rho, DubinsPathType pathType);

        double CalcPathLength(DubinsPath* path);

        double CalcSegmentLength(DubinsPath* path, int i);

        double SegmentLengthNormalized( DubinsPath* path, int i );

        DubinsPathType GetPathType(DubinsPath* path) const;

        int SampleOnePath(DubinsPath* path, double t, double q[3]);

        int SamplePaths(DubinsPath* path,  double stepSize, DubinsPathSamplingCallback cb, void* user_data);

        int CalcPathEndpoint(DubinsPath* path, double q[3]);

        int ExtractSubpath(DubinsPath* path, double t, DubinsPath* newpath);

    };

} // namespace Curves

