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
#include "NeqDouble.hpp"
#include "Exception.hpp"
//=============================================================================
namespace Nelson {
//=============================================================================
ArrayOf
double_ne_double(ArrayOf a, ArrayOf b)
{
    indexType r = 0, c = 0;
    Dimensions dimC;
    if (a.isScalar()) {
        r = 0;
        c = 1;
        dimC = b.getDimensions();
    } else if (b.isScalar()) {
        r = 1;
        c = 0;
        dimC = a.getDimensions();
    } else {
        r = 1;
        c = 1;
        dimC = a.getDimensions();
    }
    indexType Clen = dimC.getElementCount();
    logical* Cp = (logical*)new_with_exception<logical>(Clen);
    double* Ap = (double*)a.getDataPointer();
    double* Bp = (double*)b.getDataPointer();
    indexType m = 0, p = 0;
    for (indexType k = 0; k < Clen; k++) {
        Cp[k] = (Ap[m] != Bp[p]) ? logical(1) : logical(0);
        m += r;
        p += c;
    }
    return ArrayOf(NLS_LOGICAL, dimC, Cp);
}
//=============================================================================
}
//=============================================================================
