// write SKInterpolator.cpp

#include "SKInterpolator.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <math.h>
#include <algorithm>
#include <iterator>
#include <iomanip>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cmath>
#include <ctime>
#include <cctype>
#include <limits>
#include <stdexcept>
#include <functional>
#include <numeric>
#include <utility>
#include <map>
#include <set>
#include <list>
#include <stack>
#include <queue>
#include <deque>
#include <bitset>
#include <complex>
#include <locale>
#include <memory>
#include <cstddef>
#include <cassert>
#include <stdexcept>

using namespace std;

// constructor and destructor
FunctionSet::FunctionSet(int jointsize)
{
    functionP = RadialBasisFunction();
    functionXaxis = v_RBF(jointsize);
    functionYaxis = v_RBF(jointsize);
    functionZaxis = v_RBF(jointsize);
}

void FunctionSet::SetRotationMatrices(v_Vector3 curPosies, v2_Matrix3 parameters)
{
    for (int i = 0; i < curPosies.size(); i++)
    {
        functionXaxis[i].SetParameters(parameters[i][0]);
        functionYaxis[i].SetParameters(parameters[i][1]);
        functionZaxis[i].SetParameters(parameters[i][2]);
    }
}

void FunctionSet::SetRootPosition(v_Vector3 curPosies, v_Vector3 charPosies)
{
    functionP.SetParameters(charPosies, curPosies);
}

v_Matrix3 FunctionSet::GetRotationMatrices(Vector3 cursorPos)
{
    v_Matrix3 rotationMatrices;
    for (int i = 0; i < functionXaxis.size(); i++)
    {
        Matrix3 rotationMatrix;
        rotationMatrix.FromAxes(functionXaxis[i].GetFunction(cursorPos), functionYaxis[i].GetFunction(cursorPos), functionZaxis[i].GetFunction(cursorPos));
        rotationMatrices.push_back(rotationMatrix);
    }
    return rotationMatrices;
}

Vector3 FunctionSet::GetRootPosition(Vector3 cursorPos)
{
    return functionP.GetFunction(cursorPos);
}

Matrix3 FunctionSet::Normalize(Vector3 x, Vector3 y, Vector3 z)
{
    Matrix3 rotationMatrix;
    rotationMatrix.FromAxes(x, y, z);
    return rotationMatrix;
}

SpatialKeyframing::SpatialKeyframing(const SKKeyframeSet &skframeset)
{
    keyframeSets = new SKKeyframeSet(skframeset);
    functionSet = new FunctionSet(18);
}

void SpatialKeyframing::Compute()
{
    v_Vector3 curPosies = keyframeSets->GetCurPosies();
    v_Vector3 charPosies = keyframeSets->GetCharPosies();
    v2_Matrix3 parameters = keyframeSets->GetParameters();
    functionSet->SetRotationMatrices(curPosies, parameters);
    functionSet->SetRootPosition(curPosies, charPosies);
}

void SpatialKeyframing::Set(SKKeyframeSet *skframeset)
{
    keyframeSets = skframeset;
}

void SpatialKeyframing::SetFunctionSets(v_Vector3 curPosies, v_Vector3 charPosies, v2_Matrix3 parameters)
{
    functionSet->SetRotationMatrices(curPosies, parameters);
    functionSet->SetRootPosition(curPosies, charPosies);
}

SKPose SpatialKeyframing::GetPose(Vector3 curPos)
{
    SKPose pose;
    pose.rotationMatrices = functionSet->GetRotationMatrices(curPos);
    pose.rootPosition = functionSet->GetRootPosition(curPos);
    return pose;
}

SKPose SpatialKeyframing::GetPose(Vector3 curPos, v_Vector3 curPosies, v_Vector3 charPosies, v2_Matrix3 parameters)
{
    functionSet->SetRotationMatrices(curPosies, parameters);
    functionSet->SetRootPosition(curPosies, charPosies);
    SKPose pose;
    pose.rotationMatrices = functionSet->GetRotationMatrices(curPos);
    pose.rootPosition = functionSet->GetRootPosition(curPos);
    return pose;
}
