//
// Created by Mylinh Vu on 4/24/23.
//

#ifndef FINALPROJ_SPATIALKEYFRAMING_SP23_CS184_SPATIALKEYFRAMING_H
#define FINALPROJ_SPATIALKEYFRAMING_SP23_CS184_SPATIALKEYFRAMING_H

#include"ogre-13.6.4/OgreMain/include/Ogre.h"
#include "RadialBasisFunction.h"
//#include"SKInterpolator.h"
#include <vector>
using namespace Ogre;
typedef std::vector<v_Vector3>
        v2_Vector3; typedef std::vector<Matrix3>
        v_Matrix3; typedef std::vector<v_Matrix3>
        v2_Matrix3;
//typedef std::vector<FunctionSet>
v_FunctionSet;
typedef std::vector<RadialBasisFunction> v_RBF;
class FunctionSet { public:
    RadialBasisFunction functionP;
    v_RBF functionXaxis; //jointsize
    functions
            v_RBF functionYaxis;
    v_RBF functionZaxis;
//FunctionSet():functionP(NULL),functionXaxis
    (NULL),functionYaxis(NULL),functionZaxis(NULL){}
//constructor and destructor
    FunctionSet(int jointsize);
    void SetRotationMatrices(v_Vector3 curPosies,
                             v2_Matrix3 parameters);
    void SetRootPosition(v_Vector3 curPosies, v_Vector3
    charPosies);
    v_Matrix3 GetRotationMatrices(Vector3 cursorPos);
    Vector3 GetRootPosition(Vector3 cursorPos);
    Matrix3 Normalize(Vector3 x, Vector3 y, Vector3 z);
protected: private: };
class SpatialKeyframing { public:
    SKKeyframeSet *keyframeSets;
    FunctionSet *functionSet;
    SpatialKeyframing():keyframeSets(new SKKeyframeSet()
    ),functionSet( new FunctionSet(18) ){}
//hardcode 18
    SpatialKeyframing(const SKKeyframeSet&
    skframeset);//Added in v0.91
    ~SpatialKeyframing()
    {
        if (functionSet!=NULL)
        {
            delete functionSet;
        }
        if (keyframeSets)
        {
            delete keyframeSets;
        }
    }
    void Compute();
    void Set(SKKeyframeSet*);
    void SetFunctionSets(v_Vector3 curPosies, v_Vector3
    charPosies, v2_Matrix3 parameters);
    SKPose GetPose(Vector3 curPos);
protected: private: };

#endif //FINALPROJ_SPATIALKEYFRAMING_SP23_CS184_SPATIALKEYFRAMING_H