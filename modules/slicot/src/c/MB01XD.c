/* Translated by Nelson f2c (version 20170901).
   You must link the resulting object file with the libraries:
    -lnlsf2c -lm   (in that order)
*/

#include "nelson_f2c.h"

/* Table of constant values */

static integer c__1 = 1;
static integer c_n1 = -1;
static doublereal c_b15 = 1.;

EXPORTSYMBOL /* Subroutine */ int mb01xd_(uplo, n, a, lda, info, uplo_len) char* uplo;
integer* n;
doublereal* a;
integer *lda, *info;
ftnlen uplo_len;
{
    /* System generated locals */
    integer a_dim1, a_offset, i__1, i__2, i__3;
    /* Local variables */
    static integer i__;
    extern /* Subroutine */ int dgemm_();
    extern logical lsame_();
    extern /* Subroutine */ int mb01xy_(), dtrmm_();
    static logical upper;
    extern /* Subroutine */ int dsyrk_();
    static integer ib, nb, ii;
    extern /* Subroutine */ int xerbla_();
    extern integer ilaenv_();
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
    /*     To compute the matrix product U' * U or L * L', where U and L are */
    /*     upper and lower triangular matrices, respectively, stored in the */
    /*     corresponding upper or lower triangular part of the array A. */
    /*     If UPLO = 'U' then the upper triangle of the result is stored, */
    /*     overwriting the matrix U in A. */
    /*     If UPLO = 'L' then the lower triangle of the result is stored, */
    /*     overwriting the matrix L in A. */
    /*     ARGUMENTS */
    /*     Mode Parameters */
    /*     UPLO    CHARACTER*1 */
    /*             Specifies which triangle (U or L) is given in the array A, */
    /*             as follows: */
    /*             = 'U':  the upper triangular part U is given; */
    /*             = 'L':  the lower triangular part L is given. */
    /*     Input/Output Parameters */
    /*     N       (input) INTEGER */
    /*             The order of the triangular matrices U or L.  N >= 0. */
    /*     A       (input/output) DOUBLE PRECISION array, dimension (LDA,N) */
    /*             On entry, if UPLO = 'U', the leading N-by-N upper */
    /*             triangular part of this array must contain the upper */
    /*             triangular matrix U. */
    /*             On entry, if UPLO = 'L', the leading N-by-N lower */
    /*             triangular part of this array must contain the lower */
    /*             triangular matrix L. */
    /*             On exit, if UPLO = 'U', the leading N-by-N upper */
    /*             triangular part of this array contains the upper */
    /*             triangular part of the product U' * U. The strictly lower */
    /*             triangular part is not referenced. */
    /*             On exit, if UPLO = 'L', the leading N-by-N lower */
    /*             triangular part of this array contains the lower */
    /*             triangular part of the product L * L'. The strictly upper */
    /*             triangular part is not referenced. */
    /*     LDA     INTEGER */
    /*             The leading dimension of array A.  LDA >= max(1,N). */
    /*     Error Indicator */
    /*     INFO    INTEGER */
    /*             = 0:  successful exit; */
    /*             < 0:  if INFO = -i, the i-th argument had an illegal */
    /*                   value. */
    /*     METHOD */
    /*     The matrix product U' * U or L * L' is computed using BLAS 3 */
    /*     operations as much as possible (a block algorithm). */
    /*     FURTHER COMMENTS */
    /*     This routine is a counterpart of LAPACK Library routine DLAUUM, */
    /*     which computes the matrix product U * U' or L' * L. */
    /*     CONTRIBUTOR */
    /*     V. Sima, Research Institute for Informatics, Bucharest, Nov. 2000. */
    /*     REVISIONS */
    /*     - */
    /*     KEYWORDS */
    /*     Elementary matrix operations, matrix operations. */
    /*     ****************************************************************** */
    /*     .. Parameters .. */
    /*     .. */
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
    /*     Test the input scalar arguments. */
    /* Parameter adjustments */
    a_dim1 = *lda;
    a_offset = a_dim1 + 1;
    a -= a_offset;
    /* Function Body */
    *info = 0;
    upper = lsame_(uplo, "U", 1L, 1L);
    if (!upper && !lsame_(uplo, "L", 1L, 1L)) {
        *info = -1;
    } else if (*n < 0) {
        *info = -2;
    } else if (*lda < max(1, *n)) {
        *info = -4;
    }
    if (*info != 0) {
        /*        Error return. */
        i__1 = -(*info);
        xerbla_("MB01XD", &i__1, 6L);
        return 0;
    }
    /*     Quick return, if possible. */
    if (*n == 0) {
        return 0;
    }
    /*     Determine the block size for this environment (as for DLAUUM). */
    nb = ilaenv_(&c__1, "DLAUUM", uplo, n, &c_n1, &c_n1, &c_n1, 6L, 1L);
    if (nb <= 1 || nb >= *n) {
        /*        Use unblocked code. */
        mb01xy_(uplo, n, &a[a_offset], lda, info, 1L);
    } else {
        /*        Use blocked code. */
        if (upper) {
            /*           Compute the product U' * U. */
            i__1 = -nb;
            for (i__ = *n; i__1 < 0 ? i__ >= 1 : i__ <= 1; i__ += i__1) {
                ib = min(nb, i__);
                ii = i__ - ib + 1;
                if (i__ < *n) {
                    i__2 = *n - i__;
                    dtrmm_("Left", "Upper", "Transpose", "Non-unit", &ib, &i__2, &c_b15,
                        &a[ii + ii * a_dim1], lda, &a[ii + (ii + ib) * a_dim1], lda, 4L, 5L, 9L,
                        8L);
                    i__2 = *n - i__;
                    i__3 = i__ - ib;
                    dgemm_("Transpose", "No transpose", &ib, &i__2, &i__3, &c_b15,
                        &a[ii * a_dim1 + 1], lda, &a[(ii + ib) * a_dim1 + 1], lda, &c_b15,
                        &a[ii + (ii + ib) * a_dim1], lda, 9L, 12L);
                }
                mb01xy_("Upper", &ib, &a[ii + ii * a_dim1], lda, info, 5L);
                i__2 = ii - 1;
                dsyrk_("Upper", "Transpose", &ib, &i__2, &c_b15, &a[ii * a_dim1 + 1], lda, &c_b15,
                    &a[ii + ii * a_dim1], lda, 5L, 9L);
                /* L10: */
            }
        } else {
            /*           Compute the product L * L'. */
            i__1 = -nb;
            for (i__ = *n; i__1 < 0 ? i__ >= 1 : i__ <= 1; i__ += i__1) {
                ib = min(nb, i__);
                ii = i__ - ib + 1;
                if (i__ < *n) {
                    i__2 = *n - i__;
                    dtrmm_("Right", "Lower", "Transpose", "Non-unit", &i__2, &ib, &c_b15,
                        &a[ii + ii * a_dim1], lda, &a[ii + ib + ii * a_dim1], lda, 5L, 5L, 9L, 8L);
                    i__2 = *n - i__;
                    i__3 = i__ - ib;
                    dgemm_("No transpose", "Transpose", &i__2, &ib, &i__3, &c_b15,
                        &a[ii + ib + a_dim1], lda, &a[ii + a_dim1], lda, &c_b15,
                        &a[ii + ib + ii * a_dim1], lda, 12L, 9L);
                }
                mb01xy_("Lower", &ib, &a[ii + ii * a_dim1], lda, info, 5L);
                i__2 = ii - 1;
                dsyrk_("Lower", "No Transpose", &ib, &i__2, &c_b15, &a[ii + a_dim1], lda, &c_b15,
                    &a[ii + ii * a_dim1], lda, 5L, 12L);
                /* L20: */
            }
        }
    }
    return 0;
    /* *** Last line of MB01XD *** */
} /* mb01xd_ */
