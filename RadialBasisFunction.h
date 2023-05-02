//
// Created by Mylinh Vu on 4/24/23.
//

#ifndef FINALPROJ_SPATIALKEYFRAMING_SP23_CS184_RADIALBASISFUNCTION_H
#define FINALPROJ_SPATIALKEYFRAMING_SP23_CS184_RADIALBASISFUNCTION_H

#include "ogre-13.6.4/OgreMain/include/Ogre.h"
#include <vector>
#include <iostream>
#include "SpatialKeyframing.h"
//#include "SKInterpolator.h"
#include "gauss.h"
using namespace Ogre;
//typedef std::vector<Vector3> v_Vector3;
class RadialBasisFunction
{
public:
    v_Vector3 curPositions;
    v_Vector3 values;
    v_Vector3 d;
    v_Vector3 p;
    RadialBasisFunction();
    RadialBasisFunction(v_Vector3 curPosies,
                        v_Vector3 value)
    {
//curPositions = curPosies;
//values = value;
        Set(curPositions, values);
    }
    void Set(v_Vector3 curPosies, v_Vector3 values);
    void Calculate();
    v_double CalculateSub(v2_double matrix,
                          v_double values);
    v_double Solve(v2_double matrix, v_double values);
    double Phai(Vector3 curP1, Vector3 curP2);
    Vector3 Get(Vector3 cursorPos);
};

#endif //FINALPROJ_SPATIALKEYFRAMING_SP23_CS184_RADIALBASISFUNCTION_H
