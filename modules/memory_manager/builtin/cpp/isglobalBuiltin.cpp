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
#include "isglobalBuiltin.hpp"
#include "Error.hpp"
#include "IsValidVariableName.hpp"
//=============================================================================
using namespace Nelson;
//=============================================================================
ArrayOfVector
Nelson::MemoryGateway::isglobalBuiltin(Evaluator* eval, int nLhs, const ArrayOfVector& argIn)
{
    Context* ctxt = eval->getContext();
    Scope* globalScope = ctxt->getGlobalScope();
    if (nLhs > 1) {
        Error(ERROR_WRONG_NUMBERS_OUTPUT_ARGS);
    }
    if (argIn.size() != 1) {
        Error(ERROR_WRONG_NUMBERS_INPUT_ARGS);
    }
    if (!argIn[0].isSingleString()) {
        Error(ERROR_WRONG_ARGUMENT_1_TYPE_STRING_EXPECTED);
    }
    std::string arg = argIn[0].getContentAsCString();
    if (!IsValidVariableName(arg)) {
        Error(_W("Argument must contain a valid variable name."));
    }
    bool bIsGlobal = globalScope->isVariable(arg);
    ArrayOfVector retval;
    retval.push_back(ArrayOf::logicalConstructor(bIsGlobal));
    return retval;
}
//=============================================================================
