//=============================================================================
// Copyright (c) 2016-2018 Allan CORNET (Nelson)
//=============================================================================
// LICENCE_BLOCK_BEGIN
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
// LICENCE_BLOCK_END
//=============================================================================
#include "ColonDouble.hpp"
#include "Exception.hpp"
#include <Eigen/Dense>
#include <cmath>
#include "Warning.hpp"
//=============================================================================
namespace Nelson {
//=============================================================================
ArrayOf
colon_double(ArrayOf a, ArrayOf b)
{
    double A = 0;
    double B = 0;
    bool warningArrayAsScalar = false;
    if (a.isEmpty() || b.isEmpty()) {
        A = 1;
        B = 0;
    } else {
        if (a.isScalar()) {
            A = a.getContentAsDoubleScalar();
        } else {
            warningArrayAsScalar = true;
            A = a.getContentAsDoubleScalar(true);
        }
        if (b.isScalar()) {
            B = b.getContentAsDoubleScalar();
        } else {
            warningArrayAsScalar = true;
            B = b.getContentAsDoubleScalar(true);
        }
    }
    if (warningArrayAsScalar) {
        Warning(L"array-as-scalar", _W("Array used as scalar."));
    }
    return double_colon(A, B);
}
//=============================================================================
ArrayOf
colon_double(ArrayOf a, ArrayOf b, ArrayOf c)
{
    double A = 0;
    double B = 0;
    double C = 0;
    bool warningArrayAsScalar = false;
    if (a.isEmpty() || b.isEmpty() || c.isEmpty()) {
        A = 1;
        B = 0;
        C = 0;
    } else {
        if (a.isScalar()) {
            A = a.getContentAsDoubleScalar();
        } else {
            warningArrayAsScalar = true;
            A = a.getContentAsDoubleScalar(true);
        }
        if (b.isScalar()) {
            B = b.getContentAsDoubleScalar();
        } else {
            warningArrayAsScalar = true;
            B = b.getContentAsDoubleScalar(true);
        }
        if (c.isScalar()) {
            C = c.getContentAsDoubleScalar();
        } else {
            warningArrayAsScalar = true;
            C = c.getContentAsDoubleScalar(true);
        }
    }
    if (warningArrayAsScalar) {
        Warning(L"array-as-scalar", _W("Array used as scalar."));
    }
    return double_colon(A, B, C);
}
//=============================================================================
ArrayOf
double_colon(double low, double high, double step)
{
    if (step == 0) {
        return ArrayOf::emptyConstructor(1, 0);
    }
    if (std::isnan(low) || std::isnan(high) || std::isnan(step)) {
        Dimensions Cdim(1, 1);
        return ArrayOf::doubleConstructor(nan(""));
    }
    if (!std::isfinite(low) || !std::isfinite(high) || !std::isfinite(step)) {
        throw Exception(_W("Invalid range."));
    }
    if (low < high) {
        if (step < 0) {
            return ArrayOf::emptyConstructor(1, 0);
        }
    }
    if (low > high) {
        if (step > 0) {
            return ArrayOf::emptyConstructor(1, 0);
        }
    }
    double dn = (double)((((high - low) / step) + 1));
    int n = (int)round((double)(dn));
    ArrayOf V = ArrayOf::doubleVectorConstructor(n);
    double* pV = (double*)V.getReadWriteDataPointer();
    if (dn == (double(n))) {
        Eigen::Map<Eigen::VectorXd> Range(pV, n);
        Range = Eigen::VectorXd::LinSpaced(n, low, high);
    } else {
        // We must use another algo. in this case
        // 1:2:10
        int i = 0;
        double v = low;
        while ((low < high && v <= high) || (low > high && v >= high)) {
            pV[i] = v;
            v = v + step;
            i++;
        }
    }
    return V;
}
//=============================================================================
}
//=============================================================================
