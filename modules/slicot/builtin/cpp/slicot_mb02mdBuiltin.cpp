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
#include "slicot_mb02mdBuiltin.hpp"
#include "Error.hpp"
//=============================================================================
using namespace Nelson;
//=============================================================================
#ifdef __cplusplus
extern "C"
{
#endif
    extern int
    mb02md_(const char* JOB, int* M, int* N, int* L, int* RANK, double* C, int* LDC, double* S,
        double* X, int* LDX, double* TOL, int* IWORK, double* DWORK, int* LDWORK, int* IWARN,
        int* INFO);
#ifdef __cplusplus
}
#endif
//=============================================================================
// [RANK_OUT, C_OUT, S, X, IWARN, INFO] = slicot_mb02md(JOB, M, N, L, RANK_IN, C_IN, TOL)
//=============================================================================
ArrayOfVector
Nelson::SlicotGateway::slicot_mb02mdBuiltin(Evaluator* eval, int nLhs, const ArrayOfVector& argIn)
{
    ArrayOfVector retval;
    if (nLhs > 6) {
        Error(ERROR_WRONG_NUMBERS_OUTPUT_ARGS);
    }
    if (argIn.size() != 7) {
        Error(ERROR_WRONG_NUMBERS_INPUT_ARGS);
    }
    // INPUT VARIABLES
    ArrayOf JOB = argIn[0];
    Dimensions dimsJOB = JOB.getDimensions();
    std::string JOB_string = JOB.getContentAsCString();
    const char* JOB_ptr = JOB_string.c_str();
    ArrayOf M = argIn[1];
    Dimensions dimsM = M.getDimensions();
    M.promoteType(NLS_INT32);
    int* M_ptr = (int*)M.getDataPointer();
    ArrayOf N = argIn[2];
    Dimensions dimsN = N.getDimensions();
    N.promoteType(NLS_INT32);
    int* N_ptr = (int*)N.getDataPointer();
    ArrayOf L = argIn[3];
    Dimensions dimsL = L.getDimensions();
    L.promoteType(NLS_INT32);
    int* L_ptr = (int*)L.getDataPointer();
    ArrayOf TOL = argIn[6];
    Dimensions dimsTOL = TOL.getDimensions();
    TOL.promoteType(NLS_DOUBLE);
    double* TOL_ptr = (double*)TOL.getDataPointer();
    // IN/OUT VARIABLES
    ArrayOf RANK = argIn[4];
    Dimensions dimsRANK = RANK.getDimensions();
    RANK.promoteType(NLS_INT32);
    ArrayOf RANK_output = RANK;
    RANK_output.ensureSingleOwner();
    int* RANK_output_ptr = (int*)RANK_output.getDataPointer();
    ArrayOf C = argIn[5];
    Dimensions dimsC = C.getDimensions();
    C.promoteType(NLS_DOUBLE);
    ArrayOf C_output = C;
    C_output.ensureSingleOwner();
    double* C_output_ptr = (double*)C_output.getDataPointer();
    // LOCAL VARIABLES
    ArrayOf LDC = ArrayOf::int32VectorConstructor(1);
    int* LDC_ptr = (int*)LDC.getDataPointer();
    LDC_ptr[0] = std::max(std::max(1, (int)M.getContentAsInteger32Scalar()),
        (int)N.getContentAsInteger32Scalar() + (int)L.getContentAsInteger32Scalar());
    ArrayOf LDX = ArrayOf::int32VectorConstructor(1);
    int* LDX_ptr = (int*)LDX.getDataPointer();
    LDX_ptr[0] = std::max(1, (int)N.getContentAsInteger32Scalar());
    ArrayOf IWORK = ArrayOf::int32Matrix2dConstructor(1, 1);
    int* IWORK_ptr = (int*)IWORK.getDataPointer();
    ArrayOf DWORK = ArrayOf::doubleMatrix2dConstructor(1,
        (int)M.getContentAsInteger32Scalar()
                * ((int)N.getContentAsInteger32Scalar() + (int)L.getContentAsInteger32Scalar())
            + std::max(3
                          * std::min((int)M.getContentAsInteger32Scalar(),
                                (int)N.getContentAsInteger32Scalar()
                                    + (int)L.getContentAsInteger32Scalar())
                      + std::max(std::max((int)M.getContentAsInteger32Scalar(),
                                     (int)N.getContentAsInteger32Scalar()
                                         + (int)L.getContentAsInteger32Scalar()),
                            5
                                * std::min((int)M.getContentAsInteger32Scalar(),
                                      (int)N.getContentAsInteger32Scalar()
                                          + (int)L.getContentAsInteger32Scalar())),
                  3 * (int)L.getContentAsInteger32Scalar()));
    double* DWORK_ptr = (double*)DWORK.getDataPointer();
    ArrayOf LDWORK = ArrayOf::int32VectorConstructor(1);
    int* LDWORK_ptr = (int*)LDWORK.getDataPointer();
    LDWORK_ptr[0] = (int)M.getContentAsInteger32Scalar()
            * ((int)N.getContentAsInteger32Scalar() + (int)L.getContentAsInteger32Scalar())
        + std::max(3
                      * std::min((int)M.getContentAsInteger32Scalar(),
                            (int)N.getContentAsInteger32Scalar()
                                + (int)L.getContentAsInteger32Scalar())
                  + std::max(std::max((int)M.getContentAsInteger32Scalar(),
                                 (int)N.getContentAsInteger32Scalar()
                                     + (int)L.getContentAsInteger32Scalar()),
                        5
                            * std::min((int)M.getContentAsInteger32Scalar(),
                                  (int)N.getContentAsInteger32Scalar()
                                      + (int)L.getContentAsInteger32Scalar())),
              3 * (int)L.getContentAsInteger32Scalar());
    // OUTPUT VARIABLES
    ArrayOf S_output = ArrayOf::doubleMatrix2dConstructor(
        (indexType)std::min((int)M.getContentAsInteger32Scalar(),
            (int)N.getContentAsInteger32Scalar() + (int)L.getContentAsInteger32Scalar()),
        (indexType)1);
    double* S_output_ptr = (double*)S_output.getDataPointer();
    ArrayOf X_output
        = ArrayOf::doubleMatrix2dConstructor((indexType)(int)L.getContentAsInteger32Scalar(),
            (indexType)std::max(1, (int)N.getContentAsInteger32Scalar()));
    double* X_output_ptr = (double*)X_output.getDataPointer();
    ArrayOf IWARN_output = ArrayOf::int32VectorConstructor(1);
    int* IWARN_output_ptr = (int*)IWARN_output.getDataPointer();
    ArrayOf INFO_output = ArrayOf::int32VectorConstructor(1);
    int* INFO_output_ptr = (int*)INFO_output.getDataPointer();
    // CHECK INPUT VARIABLES DIMENSIONS
    if (!dimsJOB.isScalar()) {
        Error(_W("Input argument #1: scalar expected."));
    }
    if (!dimsM.isScalar()) {
        Error(_W("Input argument #2: scalar expected."));
    }
    if (!dimsN.isScalar()) {
        Error(_W("Input argument #3: scalar expected."));
    }
    if (!dimsL.isScalar()) {
        Error(_W("Input argument #4: scalar expected."));
    }
    if (!dimsRANK.isScalar()) {
        Error(_W("Input argument #5: scalar expected."));
    }
    Dimensions dimsC_expected(
        std::max(std::max(1, (int)M.getContentAsInteger32Scalar()),
            (int)N.getContentAsInteger32Scalar() + (int)L.getContentAsInteger32Scalar()),
        (int)N.getContentAsInteger32Scalar() + (int)L.getContentAsInteger32Scalar());
    if (!dimsC.equals(dimsC_expected)) {
        Error(_("Input argument #6: wrong size.") + " " + dimsC_expected.toString() + " "
            + "expected" + ".");
    }
    if (!dimsTOL.isScalar()) {
        Error(_W("Input argument #7: scalar expected."));
    }
    // CALL EXTERN FUNCTION
    try {
        mb02md_(JOB_ptr, M_ptr, N_ptr, L_ptr, RANK_output_ptr, C_output_ptr, LDC_ptr, S_output_ptr,
            X_output_ptr, LDX_ptr, TOL_ptr, IWORK_ptr, DWORK_ptr, LDWORK_ptr, IWARN_output_ptr,
            INFO_output_ptr);
    } catch (std::runtime_error& e) {
        e.what();
        Error("mb02md function fails.");
    }
    // ASSIGN OUTPUT VARIABLES
    if (nLhs > 0) {
        retval.push_back(RANK_output);
    }
    if (nLhs > 1) {
        retval.push_back(C_output);
    }
    if (nLhs > 2) {
        retval.push_back(S_output);
    }
    if (nLhs > 3) {
        retval.push_back(X_output);
    }
    if (nLhs > 4) {
        retval.push_back(IWARN_output);
    }
    if (nLhs > 5) {
        retval.push_back(INFO_output);
    }
    return retval;
}
//=============================================================================
