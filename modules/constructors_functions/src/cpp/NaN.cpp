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
#include "NaN.hpp"
#include <Eigen/Dense>
//=============================================================================
namespace Nelson {
//=============================================================================
ArrayOf
NaN(void)
{
    return NaN(1, 1);
}
//=============================================================================
ArrayOf
NaN(indexType m, indexType n)
{
    double* mat
        = (double*)ArrayOf::allocateArrayOf(NLS_DOUBLE, m * n, Nelson::stringVector(), false);
    Eigen::Map<Eigen::MatrixXd> matNaN(mat, m, n);
    matNaN.setZero();
    matNaN = matNaN.cwiseQuotient(matNaN);
    Dimensions dimMat(m, n);
    ArrayOf res = ArrayOf(NLS_DOUBLE, dimMat, mat);
    return res;
}

};
//=============================================================================
