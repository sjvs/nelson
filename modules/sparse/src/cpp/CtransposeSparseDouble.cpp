//=============================================================================
// Copyright (c) 2016-2017 Allan CORNET (Nelson)
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
#include <Eigen/Dense>
#include <Eigen/Sparse>
#include "CtransposeSparseDouble.hpp"
//=============================================================================
namespace Nelson {
    //=============================================================================
    ArrayOf CtransposeSparseDouble(ArrayOf A)
    {
        ArrayOf C;
        if (A.isComplex())
        {
            Eigen::SparseMatrix<doublecomplex, 0, signedIndexType> *spMatA = (Eigen::SparseMatrix<doublecomplex, 0, signedIndexType> *)A.getSparseDataPointer();
            Eigen::SparseMatrix<doublecomplex, 0, signedIndexType> *spMatC;
            try
            {
                spMatC = new Eigen::SparseMatrix<doublecomplex, 0, signedIndexType>(spMatA->cols(), spMatA->rows());
            }
            catch (std::bad_alloc &e)
            {
                e.what();
                spMatC = nullptr;
                throw Exception(ERROR_MEMORY_ALLOCATION);
            }
            *spMatC = spMatA->adjoint();
            Dimensions dimsC = Dimensions(spMatC->rows(), spMatC->cols());
            C = ArrayOf(NLS_DCOMPLEX, dimsC, (void*)spMatC, true);
        }
        else
        {
            Eigen::SparseMatrix<double, 0, signedIndexType> *spMatA = (Eigen::SparseMatrix<double, 0, signedIndexType> *)A.getSparseDataPointer();
            Eigen::SparseMatrix<double, 0, signedIndexType> *spMatC;
            try
            {
                spMatC = new Eigen::SparseMatrix<double, 0, signedIndexType>(spMatA->cols(), spMatA->rows());
            }
            catch (std::bad_alloc &e)
            {
                e.what();
                spMatC = nullptr;
                throw Exception(ERROR_MEMORY_ALLOCATION);
            }
            *spMatC = spMatA->adjoint();
            Dimensions dimsC = Dimensions(spMatC->rows(), spMatC->cols());
            C = ArrayOf(NLS_DOUBLE, dimsC, (void*)spMatC, true);
        }
        return C;
    }
    //=============================================================================
}
//=============================================================================