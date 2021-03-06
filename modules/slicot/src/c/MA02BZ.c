/* Translated by Nelson f2c (version 20170901).
   You must link the resulting object file with the libraries:
    -lnlsf2c -lm   (in that order)
*/

#include "nelson_f2c.h"

/* Table of constant values */

static integer c_n1 = -1;
static integer c__1 = 1;

EXPORTSYMBOL /* Subroutine */ int ma02bz_(side, m, n, a, lda, side_len) char* side;
integer *m, *n;
doublecomplex* a;
integer* lda;
ftnlen side_len;
{
    /* System generated locals */
    integer a_dim1, a_offset, i__1, i__2;
    /* Local variables */
    static integer i__, j, k;
    extern logical lsame_();
    static integer m2, n2;
    extern /* Subroutine */ int zswap_();
    static logical bsides;
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
    /*     To reverse the order of rows and/or columns of a given matrix A */
    /*     by pre-multiplying and/or post-multiplying it, respectively, with */
    /*     a permutation matrix P, where P is a square matrix of appropriate */
    /*     order, with ones down the secondary diagonal. */
    /*     ARGUMENTS */
    /*     Mode Parameters */
    /*     SIDE    CHARACTER*1 */
    /*             Specifies the operation to be performed, as follows: */
    /*             = 'L': the order of rows of A is to be reversed by */
    /*                    pre-multiplying A with P; */
    /*             = 'R': the order of columns of A is to be reversed by */
    /*                    post-multiplying A with P; */
    /*             = 'B': both the order of rows and the order of columns */
    /*                    of A is to be reversed by pre-multiplying and */
    /*                    post-multiplying A with P. */
    /*     Input/Output Parameters */
    /*     M       (input) INTEGER */
    /*             The number of rows of the matrix A.  M >= 0. */
    /*     N       (input) INTEGER */
    /*             The number of columns of the matrix A.  N >= 0. */
    /*     A       (input/output) COMPLEX*16 array, dimension (LDA,N) */
    /*             On entry, the leading M-by-N part of this array must */
    /*             contain the given matrix whose rows and/or columns are to */
    /*             be permuted. */
    /*             On exit, the leading M-by-N part of this array contains */
    /*             the matrix P*A if SIDE = 'L', or A*P if SIDE = 'R', or */
    /*             P*A*P if SIDE = 'B'. */
    /*     LDA     INTEGER */
    /*             The leading dimension of the array A.  LDA >= max(1,M). */
    /*     CONTRIBUTOR */
    /*     A. Varga, German Aerospace Center, */
    /*     DLR Oberpfaffenhofen, March 1998. */
    /*     Complex version: V. Sima, Research Institute for Informatics, */
    /*     Bucharest, Nov. 2008. */
    /*     REVISIONS */
    /*     - */
    /*    ****************************************************************** */
    /*     .. Scalar Arguments .. */
    /*     .. Array Arguments .. */
    /*     .. Local Scalars .. */
    /*     .. External Functions .. */
    /*     .. External Subroutines .. */
    /*     .. Executable Statements .. */
    /* Parameter adjustments */
    a_dim1 = *lda;
    a_offset = a_dim1 + 1;
    a -= a_offset;
    /* Function Body */
    bsides = lsame_(side, "B", 1L, 1L);
    if ((lsame_(side, "L", 1L, 1L) || bsides) && *m > 1) {
        /*        Compute P*A. */
        m2 = *m / 2;
        k = *m - m2 + 1;
        i__1 = *n;
        for (j = 1; j <= i__1; ++j) {
            zswap_(&m2, &a[j * a_dim1 + 1], &c_n1, &a[k + j * a_dim1], &c__1);
            /* L10: */
        }
    }
    if ((lsame_(side, "R", 1L, 1L) || bsides) && *n > 1) {
        /*        Compute A*P. */
        n2 = *n / 2;
        k = *n - n2 + 1;
        i__1 = *m;
        for (i__ = 1; i__ <= i__1; ++i__) {
            i__2 = -(*lda);
            zswap_(&n2, &a[i__ + a_dim1], &i__2, &a[i__ + k * a_dim1], lda);
            /* L20: */
        }
    }
    return 0;
    /* *** Last line of MA02BZ *** */
} /* ma02bz_ */
