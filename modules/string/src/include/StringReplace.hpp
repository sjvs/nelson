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
#pragma once
//=============================================================================
#include "ArrayOf.hpp"
#include "nlsString_exports.h"
//=============================================================================
namespace Nelson {
// historic algo.
NLSSTRING_IMPEXP std::wstring
stringReplace(
    std::wstring searchStr, std::wstring pattern, std::wstring replacement, bool doOverlaps);
NLSSTRING_IMPEXP ArrayOf
StringReplace(ArrayOf STR, ArrayOf OLD, ArrayOf NEW, bool doOverlaps);
// modern algo.
NLSSTRING_IMPEXP std::wstring
Replace(std::wstring searchStr, std::wstring pattern, std::wstring replacement);
NLSSTRING_IMPEXP ArrayOf
Replace(ArrayOf STR, ArrayOf OLD, ArrayOf NEW);
} // namespace Nelson
//=============================================================================
