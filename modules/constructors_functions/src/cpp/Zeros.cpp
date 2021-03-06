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
#include "Zeros.hpp"
#include "Error.hpp"
//=============================================================================
namespace Nelson {
ArrayOf
Zeros(Evaluator* eval, Class cl)
{
    Dimensions dims(1, 1);
    return Zeros(eval, dims, cl);
}
//=============================================================================
ArrayOf
Zeros(Evaluator* eval, Dimensions dims, Class cl)
{
    dims.simplify();
    switch (cl) {
    case NLS_LOGICAL: {
        indexType nbElements = dims.getElementCount();
        logical* mat = nullptr;
        if (nbElements != 0) {
            mat = (logical*)ArrayOf::allocateArrayOf(cl, nbElements);
        }
        return ArrayOf(cl, dims, mat, false);
    } break;
    case NLS_INT8: {
        indexType nbElements = dims.getElementCount();
        int8* mat = nullptr;
        if (nbElements != 0) {
            mat = (int8*)ArrayOf::allocateArrayOf(cl, nbElements);
        }
        return ArrayOf(cl, dims, mat, false);
    } break;
    case NLS_UINT8: {
        indexType nbElements = dims.getElementCount();
        uint8* mat = nullptr;
        if (nbElements != 0) {
            mat = (uint8*)ArrayOf::allocateArrayOf(cl, nbElements);
        }
        return ArrayOf(cl, dims, mat, false);
    } break;
    case NLS_INT16: {
        indexType nbElements = dims.getElementCount();
        int16* mat = nullptr;
        if (nbElements != 0) {
            mat = (int16*)ArrayOf::allocateArrayOf(cl, nbElements);
        }
        return ArrayOf(cl, dims, mat, false);
    } break;
    case NLS_UINT16: {
        indexType nbElements = dims.getElementCount();
        uint16* mat = nullptr;
        if (nbElements != 0) {
            mat = (uint16*)ArrayOf::allocateArrayOf(cl, nbElements);
        }
        return ArrayOf(cl, dims, mat, false);
    } break;
    case NLS_INT32: {
        indexType nbElements = dims.getElementCount();
        int32* mat = nullptr;
        if (nbElements != 0) {
            mat = (int32*)ArrayOf::allocateArrayOf(cl, nbElements);
        }
        return ArrayOf(cl, dims, mat, false);
    } break;
    case NLS_UINT32: {
        indexType nbElements = dims.getElementCount();
        uint32* mat = nullptr;
        if (nbElements != 0) {
            mat = (uint32*)ArrayOf::allocateArrayOf(cl, nbElements);
        }
        return ArrayOf(cl, dims, mat, false);
    } break;
    case NLS_INT64: {
        indexType nbElements = dims.getElementCount();
        int64* mat = nullptr;
        if (nbElements != 0) {
            mat = (int64*)ArrayOf::allocateArrayOf(cl, nbElements);
        }
        return ArrayOf(cl, dims, mat, false);
    } break;
    case NLS_UINT64: {
        indexType nbElements = dims.getElementCount();
        uint64* mat = nullptr;
        if (nbElements != 0) {
            mat = (uint64*)ArrayOf::allocateArrayOf(cl, nbElements);
        }
        return ArrayOf(cl, dims, mat, false);
    } break;
    case NLS_SINGLE: {
        indexType nbElements = dims.getElementCount();
        single* mat = nullptr;
        if (nbElements != 0) {
            mat = (single*)ArrayOf::allocateArrayOf(cl, nbElements);
        }
        return ArrayOf(cl, dims, mat, false);
    } break;
    case NLS_DOUBLE: {
        indexType nbElements = dims.getElementCount();
        double* mat = nullptr;
        if (nbElements != 0) {
            mat = (double*)ArrayOf::allocateArrayOf(cl, nbElements);
        }
        return ArrayOf(cl, dims, mat, false);
    } break;
    case NLS_SCOMPLEX: {
        indexType nbElements = dims.getElementCount();
        single* mat = nullptr;
        if (nbElements != 0) {
            mat = (single*)ArrayOf::allocateArrayOf(cl, nbElements * 2);
        }
        return ArrayOf(cl, dims, mat, false);
    } break;
    case NLS_DCOMPLEX: {
        indexType nbElements = dims.getElementCount();
        double* mat = nullptr;
        if (nbElements != 0) {
            mat = (double*)ArrayOf::allocateArrayOf(cl, nbElements * 2);
        }
        return ArrayOf(cl, dims, mat, false);
    } break;
    default:
        Error(ERROR_TYPE_NOT_SUPPORTED);
    }
    return ArrayOf();
}
//=============================================================================
}
//=============================================================================
