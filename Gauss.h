//
// Created by Mylinh Vu on 4/24/23.
//

#ifndef FINALPROJ_SPATIALKEYFRAMING_SP23_CS184_GAUSS_H
#define FINALPROJ_SPATIALKEYFRAMING_SP23_CS184_GAUSS_H

#include <iostream>
#include <cmath>
#include <algorithm>
//#include "SKInterpolator.h"
using namespace std;
typedef vector<double> v_double;
typedef vector<v_double> v2_double;
const int MAXN = 100;
inline void Gauss(v2_double A, v_double& b, int n) {
//inline void Gauss(vector< vector<double> > A,
    vector<double>& b, int n) {
        for (int i = 0; i < n; ++i) {
            int best = i;
            for (int j = i+1; j < n; ++j)
                if ( fabs(A[j][i]) > fabs(A[best][i]) ) best = j;
            for (int j = i; j < n; ++j)
                swap(A[best][j], A[i][j]);
            swap(b[best], b[i]);
            double tmp = A[i][i];
            for (int j = i; j < n; ++j) A[i][j] /= tmp;
            b[i] /= tmp;
            for (int j = 0; j < n; ++j) {
                if (i == j) continue;
                tmp = A[j][i] / A[i][i];
                for (int k = i; k < n; ++k)
                    A[j][k] -= tmp * A[i][k];
                b[j] -= tmp * b[i];
            }
        }
    }
    
#endif //FINALPROJ_SPATIALKEYFRAMING_SP23_CS184_GAUSS_H
