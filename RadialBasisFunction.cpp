//
// Created by Mylinh Vu on 4/24/23.
//

#include "RadialBasisFunction.h"
RadialBasisFunction::RadialBasisFunction()
{
    curPositions.resize(0);
    values.resize(0);
    d.resize(0);
    p.resize(0);
}
void RadialBasisFunction::Set(v_Vector3 curPosies,
                              v_Vector3 value)
{
    curPositions = curPosies;
    values = value;
    Calculate();
}
void RadialBasisFunction::Calculate()
{
    int keysize = curPositions.size();
    v_double vx(keysize);
    v_double vy(keysize);
    v_double vz(keysize);
    for (int i=0; i<keysize; i++)
    {
        vx[i] = values[i].x;
        vy[i] = values[i].y;
        vz[i] = values[i].z;
    }
    v2_double matrix(keysize+4);
    for (int i=0; i<keysize+4; i++)
    {
        matrix[i].resize(keysize+4);
    }
    for (int j=0; j<keysize; j++)
    {
        for (int i=j; i<keysize; i++)
        {
            matrix[i][j] = Phai(curPositions[i],
                                curPositions[j]);
        }
        matrix[keysize][j] = 1.0;
        matrix[keysize+1][j] = curPositions[j].x;
        matrix[keysize+2][j] = curPositions[j].y;
        matrix[keysize+3][j] = curPositions[j].z;
    }
    for (int j=0; j<keysize+4; j++)
    {
        for (int i=j+1; i<keysize+4; i++)
        {
            matrix[j][i] = matrix[i][j];
        }
    }
    v_double dpX = CalculateSub(matrix, vx);
    v_double dpY = CalculateSub(matrix, vy);
    v_double dpZ = CalculateSub(matrix, vz);
    d.resize(keysize);
    for (int i=0; i<keysize; i++)
    {
        d[i] = Vector3(dpX[i], dpY[i], dpZ[i]);
    }
    p.resize(4);
    for (int i=0; i<4; i++)
    {
        p[i] = Vector3(dpX[keysize+i],
                       dpY[keysize+i], dpZ[keysize+i]);
    }
}
v_double RadialBasisFunction::CalculateSub(
        v2_double matrix, v_double values)
{
    v_double array((values.size())+4);
    for(int i = 0; i < values.size(); i++)
        array[i] = values[i];
    v_double array2;
    try
    {
        array2 = Solve(matrix, array);
//Solve(matrix, array);
    }
    catch(Exception e)
    {
//std::cout<<"Solve failed! "<< e<<endl;
    }
    return array2;
}
v_double RadialBasisFunction::Solve(v2_double
                                    matrix, v_double array)
{
    Gauss(matrix, array, array.size());
    return array;
}
double RadialBasisFunction::Phai(Vector3 curP1,
                                 Vector3 curP2)
{
    return (curP1-curP2).length();
}
Vector3 RadialBasisFunction::Get(Vector3 curPos)
{
    int keysize = curPositions.size();
    if (keysize==0)
    {
        return Vector3(0, 0, 0);
    }
    if (keysize==1)
    {
        return values[0];
    }
    double x = 0.0;
    double y = 0.0;
    double z = 0.0;
    double m = 0.0;
    for (int i=0; i<keysize; i++)
    {
        m = Phai(curPos, curPositions[i]);
        x += d[i].x * m;
        y += d[i].y * m;
        z += d[i].z * m;
    }
    x += p[0].x + p[1].x * curPos.x + p[2].x *
                                      curPos.y + p[3].x * curPos.z;
    y += p[0].y + p[1].y * curPos.x + p[2].y *
                                      curPos.y + p[3].y * curPos.z;
    z += p[0].z + p[1].z * curPos.x + p[2].z *
                                      curPos.y + p[3].z * curPos.z;
    return Vector3(x, y, z);
}