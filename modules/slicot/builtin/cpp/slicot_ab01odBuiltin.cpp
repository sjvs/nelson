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
// Generated by Nelson Interface Generator 1.0.0
//=============================================================================
#include "Error.hpp"
#include "slicot_ab01odBuiltin.hpp"
//=============================================================================
using namespace Nelson;
//=============================================================================
#ifdef __cplusplus
extern "C"
{
#endif
extern int ab01od_ ( const char *STAGES, const char *JOBU, const char *JOBV, int *N, int *M, double *A, int *LDA, double *B, int *LDB, double *U, int *LDU, double *V, int *LDV, int *NCONT, int *INDCON, int *KSTAIR, double *TOL, int *IWORK, double *DWORK, int *LDWORK, int *INFO);
#ifdef __cplusplus
}
#endif
//=============================================================================
// [A_OUT, B_OUT, U_OUT, V, NCONT_OUT, INDCON_OUT, KSTAIR_OUT, INFO] = slicot_ab01od(STAGES, JOBU, JOBV, A_IN, B_IN, U_IN, NCONT_IN, INDCON_IN, KSTAIR_IN, TOL)
//=============================================================================
ArrayOfVector Nelson::SlicotGateway::slicot_ab01odBuiltin(Evaluator* eval, int nLhs, const ArrayOfVector& argIn)
{
    ArrayOfVector retval;
    if (nLhs > 8)
    {
        Error(eval, ERROR_WRONG_NUMBERS_OUTPUT_ARGS);
    }
    if (argIn.size() != 10)
    {
        Error(eval, ERROR_WRONG_NUMBERS_INPUT_ARGS);
    }
    // INPUT VARIABLES
    ArrayOf STAGES = argIn[0];
    Dimensions dimsSTAGES = STAGES.getDimensions();
    std::string STAGES_string = STAGES.getContentAsCString();
    const char* STAGES_ptr = STAGES_string.c_str();
    ArrayOf JOBU = argIn[1];
    Dimensions dimsJOBU = JOBU.getDimensions();
    std::string JOBU_string = JOBU.getContentAsCString();
    const char* JOBU_ptr = JOBU_string.c_str();
    ArrayOf JOBV = argIn[2];
    Dimensions dimsJOBV = JOBV.getDimensions();
    std::string JOBV_string = JOBV.getContentAsCString();
    const char* JOBV_ptr = JOBV_string.c_str();
    ArrayOf TOL = argIn[9];
    Dimensions dimsTOL = TOL.getDimensions();
    TOL.promoteType(NLS_DOUBLE);
    double *TOL_ptr = (double*)TOL.getDataPointer();
    // IN/OUT VARIABLES
    ArrayOf A = argIn[3];
    Dimensions dimsA = A.getDimensions();
    A.promoteType(NLS_DOUBLE);
    ArrayOf A_output = A;
    A_output.ensureSingleOwner();
    double *A_output_ptr = (double*)A_output.getDataPointer();
    ArrayOf B = argIn[4];
    Dimensions dimsB = B.getDimensions();
    B.promoteType(NLS_DOUBLE);
    ArrayOf B_output = B;
    B_output.ensureSingleOwner();
    double *B_output_ptr = (double*)B_output.getDataPointer();
    ArrayOf U = argIn[5];
    Dimensions dimsU = U.getDimensions();
    U.promoteType(NLS_DOUBLE);
    ArrayOf U_output = U;
    U_output.ensureSingleOwner();
    double *U_output_ptr = (double*)U_output.getDataPointer();
    ArrayOf NCONT = argIn[6];
    Dimensions dimsNCONT = NCONT.getDimensions();
    NCONT.promoteType(NLS_INT32);
    ArrayOf NCONT_output = NCONT;
    NCONT_output.ensureSingleOwner();
    int *NCONT_output_ptr = (int*)NCONT_output.getDataPointer();
    ArrayOf INDCON = argIn[7];
    Dimensions dimsINDCON = INDCON.getDimensions();
    INDCON.promoteType(NLS_INT32);
    ArrayOf INDCON_output = INDCON;
    INDCON_output.ensureSingleOwner();
    int *INDCON_output_ptr = (int*)INDCON_output.getDataPointer();
    ArrayOf KSTAIR = argIn[8];
    Dimensions dimsKSTAIR = KSTAIR.getDimensions();
    KSTAIR.promoteType(NLS_INT32);
    ArrayOf KSTAIR_output = KSTAIR;
    KSTAIR_output.ensureSingleOwner();
    int *KSTAIR_output_ptr = (int*)KSTAIR_output.getDataPointer();
    // LOCAL VARIABLES
    ArrayOf N = ArrayOf::int32VectorConstructor(1);
    int* N_ptr = (int*)N.getDataPointer();
    N_ptr[0] = (int)A.getDimensions().getRows();
    ArrayOf M = ArrayOf::int32VectorConstructor(1);
    int* M_ptr = (int*)M.getDataPointer();
    M_ptr[0] = (int)B.getDimensions().getColumns();
    ArrayOf LDA = ArrayOf::int32VectorConstructor(1);
    int* LDA_ptr = (int*)LDA.getDataPointer();
    LDA_ptr[0] = std::max(1, (int)A.getDimensions().getRows());
    ArrayOf LDB = ArrayOf::int32VectorConstructor(1);
    int* LDB_ptr = (int*)LDB.getDataPointer();
    LDB_ptr[0] = std::max(1, (int)A.getDimensions().getRows());
    ArrayOf LDU = ArrayOf::int32VectorConstructor(1);
    int* LDU_ptr = (int*)LDU.getDataPointer();
    LDU_ptr[0] = std::max(1, (int)A.getDimensions().getRows());
    ArrayOf LDV = ArrayOf::int32VectorConstructor(1);
    int* LDV_ptr = (int*)LDV.getDataPointer();
    LDV_ptr[0] = STAGES.getContentAsCString().compare("F") != 0 && JOBV.getContentAsCString().compare("I") == 0 ? std::max(1, (int)B.getDimensions().getColumns()) : 1;
    ArrayOf IWORK = ArrayOf::int32Matrix2dConstructor(1 , (int)B.getDimensions().getColumns());
    int* IWORK_ptr = (int*)IWORK.getDataPointer();
    ArrayOf DWORK = ArrayOf::doubleMatrix2dConstructor(1 , std::max(1, std::max((int)A.getDimensions().getRows(), (int)B.getDimensions().getColumns()) + std::max((int)A.getDimensions().getRows(), 3 * (int)B.getDimensions().getColumns())));
    double * DWORK_ptr = (double*)DWORK.getDataPointer();
    ArrayOf LDWORK = ArrayOf::int32VectorConstructor(1);
    int* LDWORK_ptr = (int*)LDWORK.getDataPointer();
    LDWORK_ptr[0] = STAGES.getContentAsCString().compare("B") != 0 ? std::max(1, std::max((int)A.getDimensions().getRows(), (int)B.getDimensions().getColumns()) + std::max((int)A.getDimensions().getRows(), 3 * (int)B.getDimensions().getColumns())) : std::max(1, std::max((int)A.getDimensions().getRows(), (int)B.getDimensions().getColumns()) + std::max((int)A.getDimensions().getRows(), (int)B.getDimensions().getColumns()));
    // OUTPUT VARIABLES
    ArrayOf V_output = ArrayOf::doubleMatrix2dConstructor((indexType)std::max(1, (int)B.getDimensions().getColumns()), (indexType)(int)B.getDimensions().getColumns());
    double *V_output_ptr = (double*)V_output.getDataPointer();
    ArrayOf INFO_output = ArrayOf::int32VectorConstructor(1);
    int *INFO_output_ptr = (int*)INFO_output.getDataPointer();
    // CHECK INPUT VARIABLES DIMENSIONS
    if (!dimsSTAGES.isScalar())
    {
        Error(eval, _W("Input argument #1: scalar expected."));
    }
    if (!dimsJOBU.isScalar())
    {
        Error(eval, _W("Input argument #2: scalar expected."));
    }
    if (!dimsJOBV.isScalar())
    {
        Error(eval, _W("Input argument #3: scalar expected."));
    }
    Dimensions dimsA_expected(std::max(1, (int)A.getDimensions().getRows()), (int)A.getDimensions().getRows());
    if (!dimsA.equals(dimsA_expected))
    {
        Error(eval, _("Input argument #4: wrong size.") + " " + dimsA_expected.toString() + " " + "expected" + ".");
    }
    Dimensions dimsB_expected(std::max(1, (int)A.getDimensions().getRows()), (int)B.getDimensions().getColumns());
    if (!dimsB.equals(dimsB_expected))
    {
        Error(eval, _("Input argument #5: wrong size.") + " " + dimsB_expected.toString() + " " + "expected" + ".");
    }
    Dimensions dimsU_expected(std::max(1, (int)A.getDimensions().getRows()), (int)A.getDimensions().getRows());
    if (!dimsU.equals(dimsU_expected))
    {
        Error(eval, _("Input argument #6: wrong size.") + " " + dimsU_expected.toString() + " " + "expected" + ".");
    }
    if (!dimsNCONT.isScalar())
    {
        Error(eval, _W("Input argument #7: scalar expected."));
    }
    if (!dimsINDCON.isScalar())
    {
        Error(eval, _W("Input argument #8: scalar expected."));
    }
    Dimensions dimsKSTAIR_expected(1, (int)A.getDimensions().getRows());
    if (!dimsKSTAIR.equals(dimsKSTAIR_expected))
    {
        Error(eval, _("Input argument #9: wrong size.") + " " + dimsKSTAIR_expected.toString() + " " + "expected" + ".");
    }
    if (!dimsTOL.isScalar())
    {
        Error(eval, _W("Input argument #10: scalar expected."));
    }
    // CALL EXTERN FUNCTION
    try
    {
        ab01od_ ( STAGES_ptr, JOBU_ptr, JOBV_ptr, N_ptr, M_ptr, A_output_ptr, LDA_ptr, B_output_ptr, LDB_ptr, U_output_ptr, LDU_ptr, V_output_ptr, LDV_ptr, NCONT_output_ptr, INDCON_output_ptr, KSTAIR_output_ptr, TOL_ptr, IWORK_ptr, DWORK_ptr, LDWORK_ptr, INFO_output_ptr);
    }
    catch (std::runtime_error &e)
    {
        e.what();
        Error(eval, "ab01od function fails.");
    }
    // ASSIGN OUTPUT VARIABLES
    if (nLhs > 0)
    {
        retval.push_back(A_output);
    }
    if (nLhs > 1)
    {
        retval.push_back(B_output);
    }
    if (nLhs > 2)
    {
        retval.push_back(U_output);
    }
    if (nLhs > 3)
    {
        retval.push_back(V_output);
    }
    if (nLhs > 4)
    {
        retval.push_back(NCONT_output);
    }
    if (nLhs > 5)
    {
        retval.push_back(INDCON_output);
    }
    if (nLhs > 6)
    {
        retval.push_back(KSTAIR_output);
    }
    if (nLhs > 7)
    {
        retval.push_back(INFO_output);
    }
    return retval;
}
//=============================================================================