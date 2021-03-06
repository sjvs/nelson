/* Translated by Nelson f2c (version 20170901).
   You must link the resulting object file with the libraries:
    -lnlsf2c -lm   (in that order)
*/

#include "nelson_f2c.h"

/* Table of constant values */

static integer c__0 = 0;
static integer c_n1 = -1;

EXPORTSYMBOL /* Subroutine */ int ab08md_(equil, n, m, p, a, lda, b, ldb, c__, ldc, d__, ldd, rank,
    tol, iwork, dwork, ldwork, info, equil_len) char* equil;
integer *n, *m, *p;
doublereal* a;
integer* lda;
doublereal* b;
integer* ldb;
doublereal* c__;
integer* ldc;
doublereal* d__;
integer *ldd, *rank;
doublereal* tol;
integer* iwork;
doublereal* dwork;
integer *ldwork, *info;
ftnlen equil_len;
{
    /* System generated locals */
    integer a_dim1, a_offset, b_dim1, b_offset, c_dim1, c_offset, d_dim1, d_offset, i__1, i__2,
        i__3, i__4;
    /* Builtin functions */
    double sqrt();
    /* Local variables */
    static integer i__;
    extern /* Subroutine */ int tb01id_();
    static integer sigma;
    extern logical lsame_();
    extern /* Subroutine */ int ab08nx_();
    static integer ninfz, nkrol;
    static doublereal toler;
    extern doublereal dlamch_(), dlange_();
    static integer nm, np, ro, kw, mu, nu;
    extern /* Subroutine */ int dlacpy_(), xerbla_();
    static doublereal maxred;
    static logical lequil;
    static doublereal thresh, svlmax;
    static logical lquery;
    static integer wrkopt;
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
    /*     To compute the normal rank of the transfer-function matrix of a */
    /*     state-space model (A,B,C,D). */
    /*     ARGUMENTS */
    /*     Mode Parameters */
    /*     EQUIL   CHARACTER*1 */
    /*             Specifies whether the user wishes to balance the compound */
    /*             matrix (see METHOD) as follows: */
    /*             = 'S':  Perform balancing (scaling); */
    /*             = 'N':  Do not perform balancing. */
    /*     Input/Output Parameters */
    /*     N       (input) INTEGER */
    /*             The number of state variables, i.e., the order of the */
    /*             matrix A.  N >= 0. */
    /*     M       (input) INTEGER */
    /*             The number of system inputs.  M >= 0. */
    /*     P       (input) INTEGER */
    /*             The number of system outputs.  P >= 0. */
    /*     A       (input) DOUBLE PRECISION array, dimension (LDA,N) */
    /*             The leading N-by-N part of this array must contain the */
    /*             state dynamics matrix A of the system. */
    /*     LDA     INTEGER */
    /*             The leading dimension of array A.  LDA >= MAX(1,N). */
    /*     B       (input) DOUBLE PRECISION array, dimension (LDB,M) */
    /*             The leading N-by-M part of this array must contain the */
    /*             input/state matrix B of the system. */
    /*     LDB     INTEGER */
    /*             The leading dimension of array B.  LDB >= MAX(1,N). */
    /*     C       (input) DOUBLE PRECISION array, dimension (LDC,N) */
    /*             The leading P-by-N part of this array must contain the */
    /*             state/output matrix C of the system. */
    /*     LDC     INTEGER */
    /*             The leading dimension of array C.  LDC >= MAX(1,P). */
    /*     D       (input) DOUBLE PRECISION array, dimension (LDD,M) */
    /*             The leading P-by-M part of this array must contain the */
    /*             direct transmission matrix D of the system. */
    /*     LDD     INTEGER */
    /*             The leading dimension of array D.  LDD >= MAX(1,P). */
    /*     RANK    (output) INTEGER */
    /*             The normal rank of the transfer-function matrix. */
    /*     Tolerances */
    /*     TOL     DOUBLE PRECISION */
    /*             A tolerance used in rank decisions to determine the */
    /*             effective rank, which is defined as the order of the */
    /*             largest leading (or trailing) triangular submatrix in the */
    /*             QR (or RQ) factorization with column (or row) pivoting */
    /*             whose estimated condition number is less than 1/TOL. */
    /*             If the user sets TOL to be less than SQRT((N+P)*(N+M))*EPS */
    /*             then the tolerance is taken as SQRT((N+P)*(N+M))*EPS, */
    /*             where EPS is the machine precision (see LAPACK Library */
    /*             Routine DLAMCH). */
    /*     Workspace */
    /*     IWORK   INTEGER array, dimension (2*N+MAX(M,P)+1) */
    /*     DWORK   DOUBLE PRECISION array, dimension (LDWORK) */
    /*             On exit, if INFO = 0, DWORK(1) returns the optimal value */
    /*             of LDWORK. */
    /*     LDWORK  INTEGER */
    /*             The length of the array DWORK. */
    /*             LDWORK >= (N+P)*(N+M) + */
    /*                       MAX( MIN(P,M) + MAX(3*M-1,N), 1, */
    /*                            MIN(P,N) + MAX(3*P-1,N+P,N+M) ) */
    /*             For optimum performance LDWORK should be larger. */
    /*             If LDWORK = -1, then a workspace query is assumed; */
    /*             the routine only calculates the optimal size of the */
    /*             DWORK array, returns this value as the first entry of */
    /*             the DWORK array, and no error message related to LDWORK */
    /*             is issued by XERBLA. */
    /*     Error Indicator */
    /*     INFO    INTEGER */
    /*             = 0:  successful exit; */
    /*             < 0:  if INFO = -i, the i-th argument had an illegal */
    /*                   value. */
    /*     METHOD */
    /*     The routine reduces the (N+P)-by-(M+N) compound matrix (B  A) */
    /*                                                            (D  C) */
    /*     to one with the same invariant zeros and with D of full row rank. */
    /*     The normal rank of the transfer-function matrix is the rank of D. */
    /*     REFERENCES */
    /*     [1] Svaricek, F. */
    /*         Computation of the Structural Invariants of Linear */
    /*         Multivariable Systems with an Extended Version of */
    /*         the Program ZEROS. */
    /*         System & Control Letters, 6, pp. 261-266, 1985. */
    /*     [2] Emami-Naeini, A. and Van Dooren, P. */
    /*         Computation of Zeros of Linear Multivariable Systems. */
    /*         Automatica, 18, pp. 415-430, 1982. */
    /*     NUMERICAL ASPECTS */
    /*     The algorithm is backward stable (see [2] and [1]). */
    /*     CONTRIBUTOR */
    /*     A. Varga, German Aerospace Center, Oberpfaffenhofen, May 2001. */
    /*     REVISIONS */
    /*     V. Sima, Research Institute for Informatics, Bucharest, June 2001, */
    /*     Dec. 2003, Jan. 2009, Mar. 2009, Apr. 2009. */
    /*     KEYWORDS */
    /*     Multivariable system, orthogonal transformation, */
    /*     structural invariant. */
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
    --iwork;
    --dwork;
    /* Function Body */
    np = *n + *p;
    nm = *n + *m;
    *info = 0;
    lequil = lsame_(equil, "S", 1L, 1L);
    lquery = *ldwork == -1;
    wrkopt = np * nm;
    /*     Test the input scalar arguments. */
    if (!lequil && !lsame_(equil, "N", 1L, 1L)) {
        *info = -1;
    } else if (*n < 0) {
        *info = -2;
    } else if (*m < 0) {
        *info = -3;
    } else if (*p < 0) {
        *info = -4;
    } else if (*lda < max(1, *n)) {
        *info = -6;
    } else if (*ldb < max(1, *n)) {
        *info = -8;
    } else if (*ldc < max(1, *p)) {
        *info = -10;
    } else if (*ldd < max(1, *p)) {
        *info = -12;
    } else {
        /* Computing MAX */
        /* Computing MAX */
        i__3 = *m * 3 - 1;
        /* Computing MAX */
        i__4 = *p * 3 - 1, i__4 = max(i__4, np);
        i__1 = min(*p, *m) + max(i__3, *n), i__1 = max(i__1, 1), i__2 = min(*p, *n) + max(i__4, nm);
        kw = wrkopt + max(i__1, i__2);
        if (lquery) {
            svlmax = 0.;
            ninfz = 0;
            i__1 = max(1, np);
            ab08nx_(n, m, p, p, &c__0, &svlmax, &dwork[1], &i__1, &ninfz, &iwork[1], &iwork[1], &mu,
                &nu, &nkrol, tol, &iwork[1], &dwork[1], &c_n1, info);
            /* Computing MAX */
            i__1 = kw, i__2 = wrkopt + (integer)dwork[1];
            wrkopt = max(i__1, i__2);
        } else if (*ldwork < kw) {
            *info = -17;
        }
    }
    if (*info != 0) {
        /*        Error return. */
        i__1 = -(*info);
        xerbla_("AB08MD", &i__1, 6L);
        return 0;
    } else if (lquery) {
        dwork[1] = (doublereal)wrkopt;
        return 0;
    }
    /*     Quick return if possible. */
    if (min(*m, *p) == 0) {
        *rank = 0;
        dwork[1] = 1.;
        return 0;
    }
    i__1 = (*n << 1) + 1;
    for (i__ = 1; i__ <= i__1; ++i__) {
        iwork[i__] = 0;
        /* L10: */
    }
    /*     (Note: Comments in the code beginning "Workspace:" describe the */
    /*     minimal amount of real workspace needed at that point in the */
    /*     code, as well as the preferred amount for good performance.) */
    /*     Construct the compound matrix  ( B  A ), dimension (N+P)-by-(M+N). */
    /*                                    ( D  C ) */
    /*     Workspace: need   (N+P)*(N+M). */
    dlacpy_("Full", n, m, &b[b_offset], ldb, &dwork[1], &np, 4L);
    dlacpy_("Full", p, m, &d__[d_offset], ldd, &dwork[*n + 1], &np, 4L);
    dlacpy_("Full", n, n, &a[a_offset], lda, &dwork[np * *m + 1], &np, 4L);
    dlacpy_("Full", p, n, &c__[c_offset], ldc, &dwork[np * *m + *n + 1], &np, 4L);
    /*     If required, balance the compound matrix (default MAXRED). */
    /*     Workspace: need   N. */
    kw = wrkopt + 1;
    if (lequil) {
        maxred = 0.;
        tb01id_("A", n, m, p, &maxred, &dwork[np * *m + 1], &np, &dwork[1], &np,
            &dwork[np * *m + *n + 1], &np, &dwork[kw], info, 1L);
        wrkopt += *n;
    }
    /*     If required, set tolerance. */
    thresh = sqrt((doublereal)(np * nm)) * dlamch_("Precision", 9L);
    toler = *tol;
    if (toler < thresh) {
        toler = thresh;
    }
    svlmax = dlange_("Frobenius", &np, &nm, &dwork[1], &np, &dwork[kw], 9L);
    /*     Reduce this system to one with the same invariant zeros and with */
    /*     D full row rank MU (the normal rank of the original system). */
    /*     Real workspace: need   (N+P)*(N+M) + */
    /*                            MAX( 1, MIN(P,M) + MAX(3*M-1,N), */
    /*                                    MIN(P,N) + MAX(3*P-1,N+P,N+M) ); */
    /*                     prefer larger. */
    /*     Integer workspace: 2*N+MAX(M,P)+1. */
    ro = *p;
    sigma = 0;
    ninfz = 0;
    i__1 = *ldwork - kw + 1;
    ab08nx_(n, m, p, &ro, &sigma, &svlmax, &dwork[1], &np, &ninfz, &iwork[1], &iwork[*n + 1], &mu,
        &nu, &nkrol, &toler, &iwork[(*n << 1) + 2], &dwork[kw], &i__1, info);
    *rank = mu;
    /* Computing MAX */
    i__1 = wrkopt, i__2 = (integer)dwork[kw] + kw - 1;
    dwork[1] = (doublereal)max(i__1, i__2);
    return 0;
    /* *** Last line of AB08MD *** */
} /* ab08md_ */
