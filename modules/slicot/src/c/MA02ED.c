/* Translated by Nelson f2c (version 20170901).
   You must link the resulting object file with the libraries:
    -lnlsf2c -lm   (in that order)
*/

#include "nelson_f2c.h"

/* Table of constant values */

static integer c__1 = 1;

EXPORTSYMBOL /* Subroutine */ int ma02ed_(uplo, n, a, lda, uplo_len) char* uplo;
integer* n;
doublereal* a;
integer* lda;
ftnlen uplo_len;
{
    /* System generated locals */
    integer a_dim1, a_offset, i__1, i__2;
    /* Local variables */
    static integer j;
    extern logical lsame_();
    extern /* Subroutine */ int dcopy_();
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
    /*     To store by symmetry the upper or lower triangle of a symmetric */
    /*     matrix, given the other triangle. */
    /*     ARGUMENTS */
    /*     Mode Parameters */
    /*     UPLO    CHARACTER*1 */
    /*             Specifies which part of the matrix is given as follows: */
    /*             = 'U':  Upper triangular part; */
    /*             = 'L':  Lower triangular part. */
    /*             For all other values, the array A is not referenced. */
    /*     Input/Output Parameters */
    /*     N       (input) INTEGER */
    /*             The order of the matrix A.  N >= 0. */
    /*     A       (input/output) DOUBLE PRECISION array, dimension (LDA,N) */
    /*             On entry, the leading N-by-N upper triangular part */
    /*             (if UPLO = 'U'), or lower triangular part (if UPLO = 'L'), */
    /*             of this array must contain the corresponding upper or */
    /*             lower triangle of the symmetric matrix A. */
    /*             On exit, the leading N-by-N part of this array contains */
    /*             the symmetric matrix A with all elements stored. */
    /*     LDA     INTEGER */
    /*             The leading dimension of the array A.  LDA >= max(1,N). */
    /*     CONTRIBUTOR */
    /*     V. Sima, Research Institute for Informatics, Bucharest, Romania, */
    /*     Oct. 1998. */
    /*     REVISIONS */
    /*     - */
    /*     ****************************************************************** */
    /*     .. Scalar Arguments .. */
    /*     .. Array Arguments .. */
    /*     .. Local Scalars .. */
    /*     .. External Functions .. */
    /*     .. External Subroutines .. */
    /*     .. Executable Statements .. */
    /*     For efficiency reasons, the parameters are not checked for errors. */
    /* Parameter adjustments */
    a_dim1 = *lda;
    a_offset = a_dim1 + 1;
    a -= a_offset;
    /* Function Body */
    if (lsame_(uplo, "L", 1L, 1L)) {
        /*        Construct the upper triangle of A. */
        i__1 = *n;
        for (j = 2; j <= i__1; ++j) {
            i__2 = j - 1;
            dcopy_(&i__2, &a[j + a_dim1], lda, &a[j * a_dim1 + 1], &c__1);
            /* L20: */
        }
    } else if (lsame_(uplo, "U", 1L, 1L)) {
        /*        Construct the lower triangle of A. */
        i__1 = *n;
        for (j = 2; j <= i__1; ++j) {
            i__2 = j - 1;
            dcopy_(&i__2, &a[j * a_dim1 + 1], &c__1, &a[j + a_dim1], lda);
            /* L40: */
        }
    }
    return 0;
    /* *** Last line of MA02ED *** */
} /* ma02ed_ */
