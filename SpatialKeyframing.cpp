//
// Created by Mylinh Vu on 4/24/23.
//

#include "SpatialKeyframing.h"
#include "ogre-13.6.4/OgreMain/include/Ogre.h"
#include <vector>

using namespace Ogre;

typedef std::vector<Vector3> v_Vector3;

FunctionSet::FunctionSet(int i) {
    functionXaxis.resize(i);
    functionYaxis.resize(i);
    functionYaxis.resize(i);
}
SpatialKeyframing::SpatialKeyframing(const
                                     SKKeyframeSet &skframeset) {
/*keyframeSets->resize(skframeset.size());
for (int i=0; i<skframeset.size(); i++)
{
(*keyframeSets)[i].pose = skframeset[0].pose;
}*/
    keyframeSets = new SKKeyframeSet(0);
    functionSet = new FunctionSet(0);
    int test = skframeset.size();
    (*keyframeSets).resize(skframeset.size());
    std::copy(skframeset.begin(),
              skframeset.end(),
              keyframeSets->begin());
    int jointsize =
            (*keyframeSets)[0].pose.jointOrientations.size();
    functionSet->functionXaxis.resize(jointsize);
    functionSet->functionYaxis.resize(jointsize);
    functionSet->functionZaxis.resize(jointsize);
}
void SpatialKeyframing::Compute()
//Entry of setting keyframe {
if ((*keyframeSets).empty())
{
functionSet = NULL;
return;
}
Set(keyframeSets);
}
void SpatialKeyframing::Set(SKKeyframeSet* keyframes) {
    int keysize = (*keyframes).size();
    int jointsize =
            (*keyframes)[0].pose.jointOrientations.size();
    v2_Matrix3 parameters(jointsize);
    for (int i=0; i<jointsize; i++)
    {
        parameters[i].resize(keysize);
    }
    v_Vector3 cursorPositions(keysize);
    v_Vector3 charPositions(keysize);
    for (int i=0; i<keysize; i++)
    {
        cursorPositions[i]=(*keyframes)[i].cursorPosition;
        SKPose keyparameter=(*keyframes)[i].pose;
        charPositions[i]=keyparameter.charPosition;
        for(int j=0; j<jointsize; j++)
        {
            parameters[j][i] =
                    keyparameter.jointOrientations[j];
        }
    }
    SetFunctionSets(cursorPositions, charPositions,
                    parameters);
}
void SpatialKeyframing::SetFunctionSets(v_Vector3
                                        curPosies, v_Vector3 charPosies, v2_Matrix3 parameters)
matrices and root
position separately here {
(*functionSet).SetRotationMatrices(curPosies,
        parameters);
(*functionSet).SetRootPosition(curPosies,
        charPosies);
}
void FunctionSet::SetRotationMatrices(v_Vector3
                                      curPosies, v2_Matrix3 parameters) {
    int jointsize = parameters.size();
    functionXaxis.resize(jointsize);
    functionYaxis.resize(jointsize);
    functionZaxis.resize(jointsize);
    int keysize = curPosies.size();
    for (int j=0; j<jointsize; j++)
    {
        v_Vector3 xs(keysize);
        v_Vector3 ys(keysize);
        v_Vector3 zs(keysize);
        for (int i=0; i<keysize; i++)
        {
            Matrix3 &m = parameters[j][i];
            xs[i] = Vector3(m[0]);
            ys[i] = Vector3(m[1]);
            zs[i] = Vector3(m[2]);
        }
        functionXaxis[j].Set(curPosies, xs);
        functionYaxis[j].Set(curPosies, ys);
        functionZaxis[j].Set(curPosies, zs);
    }
}
void FunctionSet::SetRootPosition(v_Vector3 curPosies,
                                  v_Vector3 charPosies) {
    functionP.Set(curPosies, charPosies);
}
SKPose SpatialKeyframing::GetPose(Vector3 curPos)
//Entry of getting keyframe {
SKPose skpose;
int jointsize = (*functionSet).functionXaxis.size();
v_Matrix3 rotMatrix(jointsize);
Vector3 rootPos;
rootPos = (*functionSet).GetRootPosition(curPos);
rotMatrix = (*functionSet).GetRotationMatrices
        (curPos);
skpose.charPosition = rootPos;
skpose.jointOrientations = rotMatrix;
return skpose;
}
v_Matrix3 FunctionSet::GetRotationMatrices(Vector3
                                           curPos) {
    int jointsize = functionXaxis.size();
    v_Matrix3 matrix(jointsize);
    for(int i=0; i<jointsize; i++)
    {
        Vector3 vx = functionXaxis[i].Get(curPos);
        Vector3 vy = functionYaxis[i].Get(curPos);
        Vector3 vz = functionZaxis[i].Get(curPos);
        matrix[i] = Normalize(vx, vy, vz);
    }
    return matrix;
}
Vector3 FunctionSet::GetRootPosition(Vector3 curPos) {
    return functionP.Get(curPos);
}
Matrix3 FunctionSet::Normalize(Vector3 x, Vector3 y,
                               Vector3 z) {
/*double xL = x.length();
double yL = y.length();
double zL = z.length();*/
    x.normalise();
    y.normalise();
    z.normalise();
    for (int i=0; i<10; i++)
    {
        double r = x.dotProduct(y) * x.dotProduct(y) +
                   y.dotProduct(z) * y.dotProduct(z) +
                   z.dotProduct(x) * z.dotProduct(x);
        if (r<9.99999999999999E-007)
            break;
        Vector3 x1 = y.crossProduct(z);
        x1.normalise();
        Vector3 y1 = z.crossProduct(x);
        y1.normalise();
        Vector3 z1 = x.crossProduct(y);
        z1.normalise();
        x = x + x1;
        x.normalise();
        y = y + y1;
        y.normalise();
        z = z + z1;
        z.normalise();
    }
    return Matrix3( x.x, x.y, x.z,
                    y.x, y.y, y.z,
                    z.x, z.y, z.z);
}