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
#include "VertCatString.hpp"
#include "ConcatenateNdArray.hpp"
#include "Error.hpp"
#include <Eigen/Dense>
//=============================================================================
namespace Nelson {
//=============================================================================
ArrayOf
VertCatString(ArrayOf A, ArrayOf B)
{
    if (!A.isString()) {
        Error(ERROR_WRONG_ARGUMENT_1_TYPE_STRING_EXPECTED);
    }
    if (!B.isString()) {
        Error(ERROR_WRONG_ARGUMENT_2_TYPE_STRING_EXPECTED);
    }
    if (A.isEmpty(false)) {
        ArrayOf C(B);
        return C;
    }
    if (B.isEmpty(false)) {
        ArrayOf C(A);
        return C;
    }
    Dimensions dimsA = A.getDimensions();
    Dimensions dimsB = B.getDimensions();
    if (dimsA.getColumns() != dimsB.getColumns()) {
        Error(ERROR_DIMENSIONS_NOT_CONSISTENT);
    }
    indexType newColumnsSize = dimsA.getColumns();
    indexType newRowsSize = dimsA.getRows() + dimsB.getRows();
    indexType newSize = newColumnsSize * newRowsSize;
    Dimensions dimsC = Dimensions(newRowsSize, newColumnsSize);
    charType* ptrA = (charType*)A.getDataPointer();
    charType* ptrB = (charType*)B.getDataPointer();
    charType* ptrC = (charType*)ArrayOf::allocateArrayOf(NLS_CHAR, newSize);
    Eigen::Map<Eigen::Matrix<charType, Eigen::Dynamic, Eigen::Dynamic>> matA(
        ptrA, dimsA.getRows(), dimsA.getColumns());
    Eigen::Map<Eigen::Matrix<charType, Eigen::Dynamic, Eigen::Dynamic>> matB(
        ptrB, dimsB.getRows(), dimsB.getColumns());
    Eigen::Map<Eigen::Matrix<charType, Eigen::Dynamic, Eigen::Dynamic>> matC(
        ptrC, dimsC.getRows(), dimsC.getColumns());
    matC << matA, matB;
    return ArrayOf(NLS_CHAR, dimsC, (void*)ptrC);
}
//=============================================================================
ArrayOf
VertCatNdArrayString(ArrayOf A, ArrayOf B)
{
    if (!A.isNdArrayStringType()) {
        Error(ERROR_WRONG_ARGUMENT_1_TYPE_STRING_EXPECTED);
    }
    if (!B.isNdArrayStringType()) {
        Error(ERROR_WRONG_ARGUMENT_2_TYPE_STRING_EXPECTED);
    }
    Dimensions dimsA = A.getDimensions();
    Dimensions dimsB = B.getDimensions();
    if (dimsA.getColumns() != dimsB.getColumns()) {
        Error(ERROR_DIMENSIONS_NOT_CONSISTENT);
    }
    if (dimsA.getLength() != dimsB.getLength()) {
        Error(ERROR_DIMENSIONS_NOT_CONSISTENT);
    }
    for (indexType k = 0; k < dimsA.getLength(); k++) {
        if (k != 0) {
            if (dimsA.getDimensionLength(k) != dimsB.getDimensionLength(k)) {
                Error(ERROR_DIMENSIONS_NOT_CONSISTENT);
            }
        }
    }
    Class classA = A.getDataClass();
    Class classB = B.getDataClass();
    Class classC = classA;
    ArrayOfMatrix m;
    ArrayOfVector v;
    v.push_back(A);
    m.push_back(v);
    v.clear();
    v.push_back(B);
    m.push_back(v);
    return ConcatenateNdArray(m, classC);
}
//=============================================================================

}
//=============================================================================
