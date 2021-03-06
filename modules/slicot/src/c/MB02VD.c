/* Translated by Nelson f2c (version 20170901).
   You must link the resulting object file with the libraries:
    -lnlsf2c -lm   (in that order)
*/

#include "nelson_f2c.h"

/* Table of constant values */

static integer c__1 = 1;
static doublereal c_b12 = 1.;
static integer c_n1 = -1;

EXPORTSYMBOL /* Subroutine */ int mb02vd_(
    trans, m, n, a, lda, ipiv, b, ldb, info, trans_len) char* trans;
integer *m, *n;
doublereal* a;
integer *lda, *ipiv;
doublereal* b;
integer *ldb, *info;
ftnlen trans_len;
{
    /* System generated locals */
    integer a_dim1, a_offset, b_dim1, b_offset, i__1;
    /* Local variables */
    static logical tran;
    extern /* Subroutine */ int ma02gd_();
    extern logical lsame_();
    extern /* Subroutine */ int dtrsm_(), dgetrf_(), xerbla_();
    /*     SLICOT RELEASE 5.0. */
    /*     Copyright (c) 2002-2010 NICONET e.V. */
    /*     This program is free software: you can redistribute it and/or */
    /*     modify it under the terms of the GNU General Public License as */
    /*     published by the Free Software Foundation, either version 2 of */
    /*     the License, or (at your option) any later version. */
    /*     This program is distributed in the hope that it will be useful, */
    /*     but WITHOUT ANY WARRANTY; without even the implied warranty of */
    /*     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the */
    /*     GNU General Public License for more details. */
    /*     You should have received a copy of the GNU General Public License */
    /*     along with this program.  If not, see */
    /*     <http://www.gnu.org/licenses/>. */
    /*     PURPOSE */
    /*     To compute the solution to a real system of linear equations */
    /*        X * op(A) = B, */
    /*     where op(A) is either A or its transpose, A is an N-by-N matrix, */
    /*     and X and B are M-by-N matrices. */
    /*     The LU decomposition with partial pivoting and row interchanges, */
    /*     A = P * L * U, is used, where P is a permutation matrix, L is unit */
    /*     lower triangular, and U is upper triangular. */
    /*     ARGUMENTS */
    /*     Mode Parameters */
    /*     TRANS   CHARACTER*1 */
    /*             Specifies the form of op(A) to be used as follows: */
    /*             = 'N':  op(A) = A; */
    /*             = 'T':  op(A) = A'; */
    /*             = 'C':  op(A) = A'. */
    /*     Input/Output Parameters */
    /*     M       (input) INTEGER */
    /*             The number of rows of the matrix B.  M >= 0. */
    /*     N       (input) INTEGER */
    /*             The number of columns of the matrix B, and the order of */
    /*             the matrix A.  N >= 0. */
    /*     A       (input/output) DOUBLE PRECISION array, dimension (LDA,N) */
    /*             On entry, the leading N-by-N part of this array must */
    /*             contain the coefficient matrix A. */
    /*             On exit, the leading N-by-N part of this array contains */
    /*             the factors L and U from the factorization A = P*L*U; */
    /*             the unit diagonal elements of L are not stored. */
    /*     LDA     INTEGER */
    /*             The leading dimension of the array A.  LDA >= MAX(1,N). */
    /*     IPIV    (output) INTEGER array, dimension (N) */
    /*             The pivot indices that define the permutation matrix P; */
    /*             row i of the matrix was interchanged with row IPIV(i). */
    /*     B       (input/output) DOUBLE PRECISION array, dimension (LDB,N) */
    /*             On entry, the leading M-by-N part of this array must */
    /*             contain the right hand side matrix B. */
    /*             On exit, if INFO = 0, the leading M-by-N part of this */
    /*             array contains the solution matrix X. */
    /*     LDB     (input) INTEGER */
    /*             The leading dimension of the array B.  LDB >= max(1,M). */
    /*     INFO    (output) INTEGER */
    /*             = 0:  successful exit; */
    /*             < 0:  if INFO = -i, the i-th argument had an illegal */
    /*                   value; */
    /*             > 0:  if INFO = i, U(i,i) is exactly zero.  The */
    /*                   factorization has been completed, but the factor U */
    /*                   is exactly singular, so the solution could not be */
    /*                   computed. */
    /*     METHOD */
    /*     The LU decomposition with partial pivoting and row interchanges is */
    /*     used to factor A as */
    /*        A = P * L * U, */
    /*     where P is a permutation matrix, L is unit lower triangular, and */
    /*     U is upper triangular.  The factored form of A is then used to */
    /*     solve the system of equations X * A = B or X * A' = B. */
    /*     FURTHER COMMENTS */
    /*     This routine enables to solve the system X * A = B or X * A' = B */
    /*     as easily and efficiently as possible; it is similar to the LAPACK */
    /*     Library routine DGESV, which solves A * X = B. */
    /*     CONTRIBUTOR */
    /*     V. Sima, Research Institute for Informatics, Bucharest, Mar. 2000. */
    /*     REVISIONS */
    /*     - */
    /*     KEYWORDS */
    /*     Elementary matrix operations, linear algebra. */
    /*    ****************************************************************** */
    /*     .. Parameters .. */
    /*     .. Scalar Arguments .. */
    /*     .. */
    /*     .. Array Arguments .. */
    /*     .. */
    /*     .. Local Scalars .. */
    /*     .. */
    /*     .. External Functions .. */
    /*     .. */
    /*     .. External Subroutines .. */
    /*     .. */
    /*     .. Intrinsic Functions .. */
    /*     .. */
    /*     .. Executable Statements .. */
    /*     Test the scalar input parameters. */
    /* Parameter adjustments */
    a_dim1 = *lda;
    a_offset = a_dim1 + 1;
    a -= a_offset;
    --ipiv;
    b_dim1 = *ldb;
    b_offset = b_dim1 + 1;
    b -= b_offset;
    /* Function Body */
    *info = 0;
    tran = lsame_(trans, "T", 1L, 1L) || lsame_(trans, "C", 1L, 1L);
    if (!tran && !lsame_(trans, "N", 1L, 1L)) {
        *info = -1;
    } else if (*m < 0) {
        *info = -2;
    } else if (*n < 0) {
        *info = -3;
    } else if (*lda < max(1, *n)) {
        *info = -5;
    } else if (*ldb < max(1, *m)) {
        *info = -8;
    }
    if (*info != 0) {
        i__1 = -(*info);
        xerbla_("MB02VD", &i__1, 6L);
        return 0;
    }
    /*     Compute the LU factorization of A. */
    dgetrf_(n, n, &a[a_offset], lda, &ipiv[1], info);
    if (*info == 0) {
        if (tran) {
            /*           Compute X = B * A**(-T). */
            ma02gd_(m, &b[b_offset], ldb, &c__1, n, &ipiv[1], &c__1);
            dtrsm_("Right", "Lower", "Transpose", "Unit", m, n, &c_b12, &a[a_offset], lda,
                &b[b_offset], ldb, 5L, 5L, 9L, 4L);
            dtrsm_("Right", "Upper", "Transpose", "NonUnit", m, n, &c_b12, &a[a_offset], lda,
                &b[b_offset], ldb, 5L, 5L, 9L, 7L);
        } else {
            /*           Compute X = B * A**(-1). */
            dtrsm_("Right", "Upper", "NoTranspose", "NonUnit", m, n, &c_b12, &a[a_offset], lda,
                &b[b_offset], ldb, 5L, 5L, 11L, 7L);
            dtrsm_("Right", "Lower", "NoTranspose", "Unit", m, n, &c_b12, &a[a_offset], lda,
                &b[b_offset], ldb, 5L, 5L, 11L, 4L);
            ma02gd_(m, &b[b_offset], ldb, &c__1, n, &ipiv[1], &c_n1);
        }
    }
    return 0;
    /* *** Last line of MB02VD *** */
} /* mb02vd_ */
