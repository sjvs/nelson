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
#include "VertCatDouble.hpp"
#include "ConcatenateNdArray.hpp"
#include "Error.hpp"
#include <Eigen/Dense>
//=============================================================================
namespace Nelson {
//=============================================================================
ArrayOf
VertCatDouble(ArrayOf A, ArrayOf B)
{
    if (!A.isDoubleType()) {
        Error(ERROR_WRONG_ARGUMENT_1_TYPE_DOUBLE_EXPECTED);
    }
    if (!B.isDoubleType()) {
        Error(ERROR_WRONG_ARGUMENT_2_TYPE_DOUBLE_EXPECTED);
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
    Class classA = A.getDataClass();
    Class classB = B.getDataClass();
    Class classC;
    if (classA == classB) {
        classC = classA;
    } else {
        classC = NLS_DCOMPLEX;
        A.promoteType(NLS_DCOMPLEX);
        B.promoteType(NLS_DCOMPLEX);
    }
    if (A.isEmpty(true)) {
        ArrayOf C(B);
        return C;
    }
    if (B.isEmpty(true)) {
        ArrayOf C(A);
        return C;
    }
    indexType newColumnsSize = dimsA.getColumns();
    indexType newRowsSize = dimsA.getRows() + dimsB.getRows();
    indexType newSize = newColumnsSize * newRowsSize;
    Dimensions dimsC = Dimensions(newRowsSize, newColumnsSize);
    void* pRes = nullptr;
    double* ptrC = nullptr;
    double* ptrA = (double*)A.getDataPointer();
    double* ptrB = (double*)B.getDataPointer();
    if (classC == NLS_DCOMPLEX) {
        pRes = ArrayOf::allocateArrayOf(classC, newSize * 2);
        if (newSize != 0) {
            ptrC = (double*)pRes;
            doublecomplex* Cz = reinterpret_cast<doublecomplex*>(ptrC);
            Eigen::Map<Eigen::MatrixXcd> matC(Cz, dimsC.getRows(), dimsC.getColumns());
            doublecomplex* Az = reinterpret_cast<doublecomplex*>(ptrA);
            Eigen::Map<Eigen::MatrixXcd> matA(Az, dimsA.getRows(), dimsA.getColumns());
            doublecomplex* Bz = reinterpret_cast<doublecomplex*>(ptrB);
            Eigen::Map<Eigen::MatrixXcd> matB(Bz, dimsB.getRows(), dimsB.getColumns());
            matC << matA, matB;
        }
    } else {
        pRes = ArrayOf::allocateArrayOf(classC, newSize);
        if (newSize != 0) {
            ptrC = (double*)pRes;
            Eigen::Map<Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>> matA(
                ptrA, dimsA.getRows(), dimsA.getColumns());
            Eigen::Map<Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>> matB(
                ptrB, dimsB.getRows(), dimsB.getColumns());
            Eigen::Map<Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>> matC(
                ptrC, dimsC.getRows(), dimsC.getColumns());
            matC << matA, matB;
        }
    }
    return ArrayOf(classC, dimsC, pRes);
}
//=============================================================================
ArrayOf
VertCatNdArrayDouble(ArrayOf A, ArrayOf B)
{
    if (!A.isNdArrayDoubleType()) {
        Error(ERROR_WRONG_ARGUMENT_1_TYPE_DOUBLE_EXPECTED);
    }
    if (!B.isNdArrayDoubleType()) {
        Error(ERROR_WRONG_ARGUMENT_2_TYPE_DOUBLE_EXPECTED);
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
    Class classC;
    if (classA == classB) {
        classC = classA;
    } else {
        classC = NLS_DCOMPLEX;
        A.promoteType(NLS_DCOMPLEX);
        B.promoteType(NLS_DCOMPLEX);
    }
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
