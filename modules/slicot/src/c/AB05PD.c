/* Translated by Nelson f2c (version 20170901).
   You must link the resulting object file with the libraries:
    -lnlsf2c -lm   (in that order)
*/

#include "nelson_f2c.h"

/* Table of constant values */

static doublereal c_b9 = 0.;
static integer c__0 = 0;
static doublereal c_b26 = 1.;
static integer c__1 = 1;

EXPORTSYMBOL /* Subroutine */ int ab05pd_(over, n1, m, p, n2, alpha, a1, lda1, b1, ldb1, c1, ldc1,
    d1, ldd1, a2, lda2, b2, ldb2, c2, ldc2, d2, ldd2, n, a, lda, b, ldb, c__, ldc, d__, ldd, info,
    over_len) char* over;
integer *n1, *m, *p, *n2;
doublereal *alpha, *a1;
integer* lda1;
doublereal* b1;
integer* ldb1;
doublereal* c1;
integer* ldc1;
doublereal* d1;
integer* ldd1;
doublereal* a2;
integer* lda2;
doublereal* b2;
integer* ldb2;
doublereal* c2;
integer* ldc2;
doublereal* d2;
integer *ldd2, *n;
doublereal* a;
integer* lda;
doublereal* b;
integer* ldb;
doublereal* c__;
integer* ldc;
doublereal* d__;
integer *ldd, *info;
ftnlen over_len;
{
    /* System generated locals */
    integer a_dim1, a_offset, a1_dim1, a1_offset, a2_dim1, a2_offset, b_dim1, b_offset, b1_dim1,
        b1_offset, b2_dim1, b2_offset, c_dim1, c_offset, c1_dim1, c1_offset, c2_dim1, c2_offset,
        d_dim1, d_offset, d1_dim1, d1_offset, d2_dim1, d2_offset, i__1, i__2;
    /* Local variables */
    static integer i__, j;
    extern logical lsame_();
    static logical lover;
    extern /* Subroutine */ int daxpy_(), dlascl_(), dlacpy_(), dlaset_(), xerbla_();
    static integer n1p1;
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
    /*     To compute the state-space model G = (A,B,C,D) corresponding to */
    /*     the sum G = G1 + alpha*G2, where G1 = (A1,B1,C1,D1) and */
    /*     G2 = (A2,B2,C2,D2).  G, G1, and G2 are the transfer-function */
    /*     matrices of the corresponding state-space models. */
    /*     ARGUMENTS */
    /*     Mode Parameters */
    /*     OVER    CHARACTER*1 */
    /*             Indicates whether the user wishes to overlap pairs of */
    /*             arrays, as follows: */
    /*             = 'N':  Do not overlap; */
    /*             = 'O':  Overlap pairs of arrays: A1 and A, B1 and B, */
    /*                     C1 and C, and D1 and D, i.e. the same name is */
    /*                     effectively used for each pair (for all pairs) */
    /*                     in the routine call.  In this case, setting */
    /*                     LDA1 = LDA, LDB1 = LDB, LDC1 = LDC, and LDD1 = LDD */
    /*                     will give maximum efficiency. */
    /*     Input/Output Parameters */
    /*     N1      (input) INTEGER */
    /*             The number of state variables in the first system, i.e. */
    /*             the order of the matrix A1, the number of rows of B1 and */
    /*             the number of columns of C1.  N1 >= 0. */
    /*     M       (input) INTEGER */
    /*             The number of input variables of the two systems, i.e. the */
    /*             number of columns of matrices B1, D1, B2 and D2.  M >= 0. */
    /*     P       (input) INTEGER */
    /*             The number of output variables of the two systems, i.e. */
    /*             the number of rows of matrices C1, D1, C2 and D2.  P >= 0. */
    /*     N2      (input) INTEGER */
    /*             The number of state variables in the second system, i.e. */
    /*             the order of the matrix A2, the number of rows of B2 and */
    /*             the number of columns of C2.  N2 >= 0. */
    /*     ALPHA   (input) DOUBLE PRECISION */
    /*             The coefficient multiplying G2. */
    /*     A1      (input) DOUBLE PRECISION array, dimension (LDA1,N1) */
    /*             The leading N1-by-N1 part of this array must contain the */
    /*             state transition matrix A1 for the first system. */
    /*     LDA1    INTEGER */
    /*             The leading dimension of array A1.  LDA1 >= MAX(1,N1). */
    /*     B1      (input) DOUBLE PRECISION array, dimension (LDB1,M) */
    /*             The leading N1-by-M part of this array must contain the */
    /*             input/state matrix B1 for the first system. */
    /*     LDB1    INTEGER */
    /*             The leading dimension of array B1.  LDB1 >= MAX(1,N1). */
    /*     C1      (input) DOUBLE PRECISION array, dimension (LDC1,N1) */
    /*             The leading P-by-N1 part of this array must contain the */
    /*             state/output matrix C1 for the first system. */
    /*     LDC1    INTEGER */
    /*             The leading dimension of array C1. */
    /*             LDC1 >= MAX(1,P) if N1 > 0. */
    /*             LDC1 >= 1 if N1 = 0. */
    /*     D1      (input) DOUBLE PRECISION array, dimension (LDD1,M) */
    /*             The leading P-by-M part of this array must contain the */
    /*             input/output matrix D1 for the first system. */
    /*     LDD1    INTEGER */
    /*             The leading dimension of array D1.  LDD1 >= MAX(1,P). */
    /*     A2      (input) DOUBLE PRECISION array, dimension (LDA2,N2) */
    /*             The leading N2-by-N2 part of this array must contain the */
    /*             state transition matrix A2 for the second system. */
    /*     LDA2    INTEGER */
    /*             The leading dimension of array A2.  LDA2 >= MAX(1,N2). */
    /*     B2      (input) DOUBLE PRECISION array, dimension (LDB2,M) */
    /*             The leading N2-by-M part of this array must contain the */
    /*             input/state matrix B2 for the second system. */
    /*     LDB2    INTEGER */
    /*             The leading dimension of array B2.  LDB2 >= MAX(1,N2). */
    /*     C2      (input) DOUBLE PRECISION array, dimension (LDC2,N2) */
    /*             The leading P-by-N2 part of this array must contain the */
    /*             state/output matrix C2 for the second system. */
    /*     LDC2    INTEGER */
    /*             The leading dimension of array C2. */
    /*             LDC2 >= MAX(1,P) if N2 > 0. */
    /*             LDC2 >= 1 if N2 = 0. */
    /*     D2      (input) DOUBLE PRECISION array, dimension (LDD2,M) */
    /*             The leading P-by-M part of this array must contain the */
    /*             input/output matrix D2 for the second system. */
    /*     LDD2    INTEGER */
    /*             The leading dimension of array D2.  LDD2 >= MAX(1,P). */
    /*     N       (output) INTEGER */
    /*             The number of state variables (N1 + N2) in the resulting */
    /*             system, i.e. the order of the matrix A, the number of rows */
    /*             of B and the number of columns of C. */
    /*     A       (output) DOUBLE PRECISION array, dimension (LDA,N1+N2) */
    /*             The leading N-by-N part of this array contains the state */
    /*             transition matrix A for the resulting system. */
    /*             The array A can overlap A1 if OVER = 'O'. */
    /*     LDA     INTEGER */
    /*             The leading dimension of array A.  LDA >= MAX(1,N1+N2). */
    /*     B       (output) DOUBLE PRECISION array, dimension (LDB,M) */
    /*             The leading N-by-M part of this array contains the */
    /*             input/state matrix B for the resulting system. */
    /*             The array B can overlap B1 if OVER = 'O'. */
    /*     LDB     INTEGER */
    /*             The leading dimension of array B.  LDB >= MAX(1,N1+N2). */
    /*     C       (output) DOUBLE PRECISION array, dimension (LDC,N1+N2) */
    /*             The leading P-by-N part of this array contains the */
    /*             state/output matrix C for the resulting system. */
    /*             The array C can overlap C1 if OVER = 'O'. */
    /*     LDC     INTEGER */
    /*             The leading dimension of array C. */
    /*             LDC >= MAX(1,P) if N1+N2 > 0. */
    /*             LDC >= 1 if N1+N2 = 0. */
    /*     D       (output) DOUBLE PRECISION array, dimension (LDD,M) */
    /*             The leading P-by-M part of this array contains the */
    /*             input/output matrix D for the resulting system. */
    /*             The array D can overlap D1 if OVER = 'O'. */
    /*     LDD     INTEGER */
    /*             The leading dimension of array D.  LDD >= MAX(1,P). */
    /*     Error Indicator */
    /*     INFO    INTEGER */
    /*             = 0:  successful exit; */
    /*             < 0:  if INFO = -i, the i-th argument had an illegal */
    /*                   value. */
    /*     METHOD */
    /*     The matrices of the resulting systems are determined as: */
    /*           ( A1   0  )             ( B1 ) */
    /*       A = (         ) ,       B = (    ) , */
    /*           ( 0    A2 )             ( B2 ) */
    /*       C = ( C1  alpha*C2 ) ,  D = D1 + alpha*D2 . */
    /*     REFERENCES */
    /*     None */
    /*     NUMERICAL ASPECTS */
    /*     None */
    /*     CONTRIBUTORS */
    /*     A. Varga, German Aerospace Research Establishment, */
    /*     Oberpfaffenhofen, Germany, and V. Sima, Katholieke Univ. Leuven, */
    /*     Belgium, Nov. 1996. */
    /*     REVISIONS */
    /*     V. Sima, Research Institute for Informatics, Bucharest, July 2003, */
    /*     Feb. 2004. */
    /*     KEYWORDS */
    /*     Multivariable system, state-space model, state-space */
    /*     representation. */
    /*     ****************************************************************** */
    /*     .. Parameters .. */
    /*     .. Scalar Arguments .. */
    /*     .. Array Arguments .. */
    /*     .. Local Scalars .. */
    /*     .. External Functions .. */
    /*     .. External Subroutines .. */
    /*     .. Intrinsic Functions .. */
    /*     .. Executable Statements .. */
    /* Parameter adjustments */
    a1_dim1 = *lda1;
    a1_offset = a1_dim1 + 1;
    a1 -= a1_offset;
    b1_dim1 = *ldb1;
    b1_offset = b1_dim1 + 1;
    b1 -= b1_offset;
    c1_dim1 = *ldc1;
    c1_offset = c1_dim1 + 1;
    c1 -= c1_offset;
    d1_dim1 = *ldd1;
    d1_offset = d1_dim1 + 1;
    d1 -= d1_offset;
    a2_dim1 = *lda2;
    a2_offset = a2_dim1 + 1;
    a2 -= a2_offset;
    b2_dim1 = *ldb2;
    b2_offset = b2_dim1 + 1;
    b2 -= b2_offset;
    c2_dim1 = *ldc2;
    c2_offset = c2_dim1 + 1;
    c2 -= c2_offset;
    d2_dim1 = *ldd2;
    d2_offset = d2_dim1 + 1;
    d2 -= d2_offset;
    a_dim1 = *lda;
    a_offset = a_dim1 + 1;
    a -= a_offset;
    b_dim1 = *ldb;
    b_offset = b_dim1 + 1;
    b -= b_offset;
    c_dim1 = *ldc;
    c_offset = c_dim1 + 1;
    c__ -= c_offset;
    d_dim1 = *ldd;
    d_offset = d_dim1 + 1;
    d__ -= d_offset;
    /* Function Body */
    lover = lsame_(over, "O", 1L, 1L);
    *n = *n1 + *n2;
    *info = 0;
    /*     Test the input scalar arguments. */
    if (!lover && !lsame_(over, "N", 1L, 1L)) {
        *info = -1;
    } else if (*n1 < 0) {
        *info = -2;
    } else if (*m < 0) {
        *info = -3;
    } else if (*p < 0) {
        *info = -4;
    } else if (*n2 < 0) {
        *info = -5;
    } else if (*lda1 < max(1, *n1)) {
        *info = -8;
    } else if (*ldb1 < max(1, *n1)) {
        *info = -10;
    } else if (*n1 > 0 && *ldc1 < max(1, *p) || *n1 == 0 && *ldc1 < 1) {
        *info = -12;
    } else if (*ldd1 < max(1, *p)) {
        *info = -14;
    } else if (*lda2 < max(1, *n2)) {
        *info = -16;
    } else if (*ldb2 < max(1, *n2)) {
        *info = -18;
    } else if (*n2 > 0 && *ldc2 < max(1, *p) || *n2 == 0 && *ldc2 < 1) {
        *info = -20;
    } else if (*ldd2 < max(1, *p)) {
        *info = -22;
    } else if (*lda < max(1, *n)) {
        *info = -25;
    } else if (*ldb < max(1, *n)) {
        *info = -27;
    } else if (*n > 0 && *ldc < max(1, *p) || *n == 0 && *ldc < 1) {
        *info = -29;
    } else if (*ldd < max(1, *p)) {
        *info = -31;
    }
    if (*info != 0) {
        /*        Error return. */
        i__1 = -(*info);
        xerbla_("AB05PD", &i__1, 6L);
        return 0;
    }
    /*     Quick return if possible. */
    /* Computing MAX */
    i__1 = *n, i__2 = min(*m, *p);
    if (max(i__1, i__2) == 0) {
        return 0;
    }
    n1p1 = *n1 + 1;
    /*                       ( A1   0  ) */
    /*     Construct     A = (         ) . */
    /*                       ( 0    A2 ) */
    if (lover && *lda1 <= *lda) {
        if (*lda1 < *lda) {
            for (j = *n1; j >= 1; --j) {
                for (i__ = *n1; i__ >= 1; --i__) {
                    a[i__ + j * a_dim1] = a1[i__ + j * a1_dim1];
                    /* L10: */
                }
                /* L20: */
            }
        }
    } else {
        dlacpy_("F", n1, n1, &a1[a1_offset], lda1, &a[a_offset], lda, 1L);
    }
    if (*n2 > 0) {
        dlaset_("F", n1, n2, &c_b9, &c_b9, &a[n1p1 * a_dim1 + 1], lda, 1L);
        dlaset_("F", n2, n1, &c_b9, &c_b9, &a[n1p1 + a_dim1], lda, 1L);
        dlacpy_("F", n2, n2, &a2[a2_offset], lda2, &a[n1p1 + n1p1 * a_dim1], lda, 1L);
    }
    /*                        ( B1 ) */
    /*     Construct      B = (    ) . */
    /*                        ( B2 ) */
    if (lover && *ldb1 <= *ldb) {
        if (*ldb1 < *ldb) {
            for (j = *m; j >= 1; --j) {
                for (i__ = *n1; i__ >= 1; --i__) {
                    b[i__ + j * b_dim1] = b1[i__ + j * b1_dim1];
                    /* L30: */
                }
                /* L40: */
            }
        }
    } else {
        dlacpy_("F", n1, m, &b1[b1_offset], ldb1, &b[b_offset], ldb, 1L);
    }
    if (*n2 > 0) {
        dlacpy_("F", n2, m, &b2[b2_offset], ldb2, &b[n1p1 + b_dim1], ldb, 1L);
    }
    /*     Construct      C = ( C1 alpha*C2 ) . */
    if (lover && *ldc1 <= *ldc) {
        if (*ldc1 < *ldc) {
            for (j = *n1; j >= 1; --j) {
                for (i__ = *p; i__ >= 1; --i__) {
                    c__[i__ + j * c_dim1] = c1[i__ + j * c1_dim1];
                    /* L50: */
                }
                /* L60: */
            }
        }
    } else {
        dlacpy_("F", p, n1, &c1[c1_offset], ldc1, &c__[c_offset], ldc, 1L);
    }
    if (*n2 > 0) {
        dlacpy_("F", p, n2, &c2[c2_offset], ldc2, &c__[n1p1 * c_dim1 + 1], ldc, 1L);
        if (*alpha != 1.) {
            dlascl_(
                "G", &c__0, &c__0, &c_b26, alpha, p, n2, &c__[n1p1 * c_dim1 + 1], ldc, info, 1L);
        }
    }
    /*     Construct       D = D1 + alpha*D2 . */
    if (lover && *ldd1 <= *ldd) {
        if (*ldd1 < *ldd) {
            for (j = *m; j >= 1; --j) {
                for (i__ = *p; i__ >= 1; --i__) {
                    d__[i__ + j * d_dim1] = d1[i__ + j * d1_dim1];
                    /* L70: */
                }
                /* L80: */
            }
        }
    } else {
        dlacpy_("F", p, m, &d1[d1_offset], ldd1, &d__[d_offset], ldd, 1L);
    }
    i__1 = *m;
    for (j = 1; j <= i__1; ++j) {
        daxpy_(p, alpha, &d2[j * d2_dim1 + 1], &c__1, &d__[j * d_dim1 + 1], &c__1);
        /* L90: */
    }
    return 0;
    /* *** Last line of AB05PD *** */
} /* ab05pd_ */
