/* Translated by Nelson f2c (version 20170901).
   You must link the resulting object file with the libraries:
    -lnlsf2c -lm   (in that order)
*/

#include "nelson_f2c.h"

/* Table of constant values */

static integer c__1 = 1;
static doublereal c_b10 = 0.;
static doublereal c_b18 = 1.;
static integer c__0 = 0;

EXPORTSYMBOL /* Subroutine */ int tb01zd_(jobz, n, p, a, lda, b, c__, ldc, ncont, z__, ldz, tau,
    tol, dwork, ldwork, info, jobz_len) char* jobz;
integer *n, *p;
doublereal* a;
integer* lda;
doublereal *b, *c__;
integer *ldc, *ncont;
doublereal* z__;
integer* ldz;
doublereal *tau, *tol, *dwork;
integer *ldwork, *info;
ftnlen jobz_len;
{
    /* System generated locals */
    integer a_dim1, a_offset, c_dim1, c_offset, z_dim1, z_offset, i__1, i__2;
    doublereal d__1, d__2;
    /* Local variables */
    static doublereal nblk[1];
    static integer itau;
    static doublereal h__;
    static integer j;
    extern /* Subroutine */ int mb01pd_(), dlarf_();
    static logical ljobf, ljobi;
    extern logical lsame_();
    static doublereal anorm, bnorm;
    static logical ljobz;
    static doublereal b1;
    extern doublereal dlamch_(), dlange_();
    extern /* Subroutine */ int dgehrd_(), dlarfg_(), dlacpy_();
    static doublereal toldef;
    extern /* Subroutine */ int dlaset_(), xerbla_();
    static doublereal fanorm, fbnorm;
    extern /* Subroutine */ int dormhr_();
    static doublereal thresh;
    extern /* Subroutine */ int dorgqr_();
    static doublereal wrkopt;
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
    /*     To find a controllable realization for the linear time-invariant */
    /*     single-input system */
    /*             dX/dt = A * X + B * U, */
    /*                Y  = C * X, */
    /*     where A is an N-by-N matrix, B is an N element vector, C is an */
    /*     P-by-N matrix, and A and B are reduced by this routine to */
    /*     orthogonal canonical form using (and optionally accumulating) */
    /*     orthogonal similarity transformations, which are also applied */
    /*     to C. */
    /*     ARGUMENTS */
    /*     Mode Parameters */
    /*     JOBZ    CHARACTER*1 */
    /*             Indicates whether the user wishes to accumulate in a */
    /*             matrix Z the orthogonal similarity transformations for */
    /*             reducing the system, as follows: */
    /*             = 'N':  Do not form Z and do not store the orthogonal */
    /*                     transformations; */
    /*             = 'F':  Do not form Z, but store the orthogonal */
    /*                     transformations in the factored form; */
    /*             = 'I':  Z is initialized to the unit matrix and the */
    /*                     orthogonal transformation matrix Z is returned. */
    /*     Input/Output Parameters */
    /*     N       (input) INTEGER */
    /*             The order of the original state-space representation, */
    /*             i.e. the order of the matrix A.  N >= 0. */
    /*     P       (input) INTEGER */
    /*             The number of system outputs, or of rows of C.  P >= 0. */
    /*     A       (input/output) DOUBLE PRECISION array, dimension (LDA,N) */
    /*             On entry, the leading N-by-N part of this array must */
    /*             contain the original state dynamics matrix A. */
    /*             On exit, the leading NCONT-by-NCONT upper Hessenberg */
    /*             part of this array contains the canonical form of the */
    /*             state dynamics matrix, given by Z' * A * Z, of a */
    /*             controllable realization for the original system. The */
    /*             elements below the first subdiagonal are set to zero. */
    /*     LDA     INTEGER */
    /*             The leading dimension of array A.  LDA >= MAX(1,N). */
    /*     B       (input/output) DOUBLE PRECISION array, dimension (N) */
    /*             On entry, the original input/state vector B. */
    /*             On exit, the leading NCONT elements of this array contain */
    /*             canonical form of the input/state vector, given by Z' * B, */
    /*             with all elements but B(1) set to zero. */
    /*     C       (input/output) DOUBLE PRECISION array, dimension (LDC,N) */
    /*             On entry, the leading P-by-N part of this array must */
    /*             contain the output/state matrix C. */
    /*             On exit, the leading P-by-N part of this array contains */
    /*             the transformed output/state matrix, given by C * Z, and */
    /*             the leading P-by-NCONT part contains the output/state */
    /*             matrix of the controllable realization. */
    /*     LDC     INTEGER */
    /*             The leading dimension of array C.  LDC >= MAX(1,P). */
    /*     NCONT   (output) INTEGER */
    /*             The order of the controllable state-space representation. */
    /*     Z       (output) DOUBLE PRECISION array, dimension (LDZ,N) */
    /*             If JOBZ = 'I', then the leading N-by-N part of this array */
    /*             contains the matrix of accumulated orthogonal similarity */
    /*             transformations which reduces the given system to */
    /*             orthogonal canonical form. */
    /*             If JOBZ = 'F', the elements below the diagonal, with the */
    /*             array TAU, represent the orthogonal transformation matrix */
    /*             as a product of elementary reflectors. The transformation */
    /*             matrix can then be obtained by calling the LAPACK Library */
    /*             routine DORGQR. */
    /*             If JOBZ = 'N', the array Z is not referenced and can be */
    /*             supplied as a dummy array (i.e. set parameter LDZ = 1 and */
    /*             declare this array to be Z(1,1) in the calling program). */
    /*     LDZ     INTEGER */
    /*             The leading dimension of array Z. If JOBZ = 'I' or */
    /*             JOBZ = 'F', LDZ >= MAX(1,N); if JOBZ = 'N', LDZ >= 1. */
    /*     TAU     (output) DOUBLE PRECISION array, dimension (N) */
    /*             The elements of TAU contain the scalar factors of the */
    /*             elementary reflectors used in the reduction of B and A. */
    /*     Tolerances */
    /*     TOL     DOUBLE PRECISION */
    /*             The tolerance to be used in determining the */
    /*             controllability of (A,B). If the user sets TOL > 0, then */
    /*             the given value of TOL is used as an absolute tolerance; */
    /*             elements with absolute value less than TOL are considered */
    /*             neglijible. If the user sets TOL <= 0, then an implicitly */
    /*             computed, default tolerance, defined by */
    /*             TOLDEF = N*EPS*MAX( NORM(A), NORM(B) ) is used instead, */
    /*             where EPS is the machine precision (see LAPACK Library */
    /*             routine DLAMCH). */
    /*     Workspace */
    /*     DWORK   DOUBLE PRECISION array, dimension (LDWORK) */
    /*             On exit, if INFO = 0, DWORK(1) returns the optimal value */
    /*             of LDWORK. */
    /*     LDWORK  INTEGER */
    /*             The length of the array DWORK. LDWORK >= MAX(1,N,P). */
    /*             For optimum performance LDWORK should be larger. */
    /*     Error Indicator */
    /*     INFO    INTEGER */
    /*             = 0:  successful exit; */
    /*             < 0:  if INFO = -i, the i-th argument had an illegal */
    /*                   value. */
    /*     METHOD */
    /*     The Householder matrix which reduces all but the first element */
    /*     of vector B to zero is found and this orthogonal similarity */
    /*     transformation is applied to the matrix A. The resulting A is then */
    /*     reduced to upper Hessenberg form by a sequence of Householder */
    /*     transformations. Finally, the order of the controllable state- */
    /*     space representation (NCONT) is determined by finding the position */
    /*     of the first sub-diagonal element of A which is below an */
    /*     appropriate zero threshold, either TOL or TOLDEF (see parameter */
    /*     TOL); if NORM(B) is smaller than this threshold, NCONT is set to */
    /*     zero, and no computations for reducing the system to orthogonal */
    /*     canonical form are performed. */
    /*     All orthogonal transformations determined in this process are also */
    /*     applied to the matrix C, from the right. */
    /*     REFERENCES */
    /*     [1] Konstantinov, M.M., Petkov, P.Hr. and Christov, N.D. */
    /*         Orthogonal Invariants and Canonical Forms for Linear */
    /*         Controllable Systems. */
    /*         Proc. 8th IFAC World Congress, Kyoto, 1, pp. 49-54, 1981. */
    /*     [2] Hammarling, S.J. */
    /*         Notes on the use of orthogonal similarity transformations in */
    /*         control. */
    /*         NPL Report DITC 8/82, August 1982. */
    /*     [3] Paige, C.C */
    /*         Properties of numerical algorithms related to computing */
    /*         controllability. */
    /*         IEEE Trans. Auto. Contr., AC-26, pp. 130-138, 1981. */
    /*     NUMERICAL ASPECTS */
    /*                               3 */
    /*     The algorithm requires 0(N ) operations and is backward stable. */
    /*     CONTRIBUTOR */
    /*     V. Sima, Katholieke Univ. Leuven, Belgium, Feb. 1998. */
    /*     REVISIONS */
    /*     V. Sima, Research Institute for Informatics, Bucharest, Oct. 2001, */
    /*     Sept. 2003. */
    /*     KEYWORDS */
    /*     Controllability, minimal realization, orthogonal canonical form, */
    /*     orthogonal transformation. */
    /*     ****************************************************************** */
    /*     .. Parameters .. */
    /*     .. Scalar Arguments .. */
    /*     .. Array Arguments .. */
    /*     .. Local Scalars .. */
    /*     .. Local Arrays .. */
    /*     .. External Functions .. */
    /*     .. External Subroutines .. */
    /*     .. Intrinsic Functions .. */
    /*     .. Executable Statements .. */
    /* Parameter adjustments */
    a_dim1 = *lda;
    a_offset = a_dim1 + 1;
    a -= a_offset;
    --b;
    c_dim1 = *ldc;
    c_offset = c_dim1 + 1;
    c__ -= c_offset;
    z_dim1 = *ldz;
    z_offset = z_dim1 + 1;
    z__ -= z_offset;
    --tau;
    --dwork;
    /* Function Body */
    *info = 0;
    ljobf = lsame_(jobz, "F", 1L, 1L);
    ljobi = lsame_(jobz, "I", 1L, 1L);
    ljobz = ljobf || ljobi;
    /*     Test the input scalar arguments. */
    if (!ljobz && !lsame_(jobz, "N", 1L, 1L)) {
        *info = -1;
    } else if (*n < 0) {
        *info = -2;
    } else if (*p < 0) {
        *info = -3;
    } else if (*lda < max(1, *n)) {
        *info = -5;
    } else if (*ldc < max(1, *p)) {
        *info = -8;
    } else if (*ldz < 1 || ljobz && *ldz < *n) {
        *info = -11;
    } else /* if(complicated condition) */
    {
        /* Computing MAX */
        i__1 = max(1, *n);
        if (*ldwork < max(i__1, *p)) {
            *info = -15;
        }
    }
    if (*info != 0) {
        /*        Error return. */
        i__1 = -(*info);
        xerbla_("TB01ZD", &i__1, 6L);
        return 0;
    }
    /*     Quick return if possible. */
    *ncont = 0;
    dwork[1] = 1.;
    if (*n == 0) {
        return 0;
    }
    /*     (Note: Comments in the code beginning "Workspace:" describe the */
    /*     minimal amount of real workspace needed at that point in the */
    /*     code, as well as the preferred amount for good performance. */
    /*     NB refers to the optimal block size for the immediately */
    /*     following subroutine, as returned by ILAENV.) */
    wrkopt = 1.;
    /*     Calculate the absolute norms of A and B (used for scaling). */
    anorm = dlange_("Max", n, n, &a[a_offset], lda, &dwork[1], 3L);
    bnorm = dlange_("Max", n, &c__1, &b[1], n, &dwork[1], 3L);
    /*     Return if matrix B is zero. */
    if (bnorm == 0.) {
        if (ljobf) {
            dlaset_("Full", n, n, &c_b10, &c_b10, &z__[z_offset], ldz, 4L);
            dlaset_("Full", n, &c__1, &c_b10, &c_b10, &tau[1], n, 4L);
        } else if (ljobi) {
            dlaset_("Full", n, n, &c_b10, &c_b18, &z__[z_offset], ldz, 4L);
        }
        return 0;
    }
    /*     Scale (if needed) the matrices A and B. */
    mb01pd_("S", "G", n, n, &c__0, &c__0, &anorm, &c__0, nblk, &a[a_offset], lda, info, 1L, 1L);
    mb01pd_("S", "G", n, &c__1, &c__0, &c__0, &bnorm, &c__0, nblk, &b[1], n, info, 1L, 1L);
    /*     Calculate the Frobenius norm of A and the 1-norm of B (used for */
    /*     controlability test). */
    fanorm = dlange_("Frobenius", n, n, &a[a_offset], lda, &dwork[1], 9L);
    fbnorm = dlange_("1-norm", n, &c__1, &b[1], n, &dwork[1], 6L);
    toldef = *tol;
    if (toldef <= 0.) {
        /*        Use the default tolerance in controllability determination. */
        thresh = (doublereal)(*n) * dlamch_("EPSILON", 7L);
        toldef = thresh * max(fanorm, fbnorm);
    }
    itau = 1;
    if (fbnorm > toldef) {
        /*        B is not negligible compared with A. */
        if (*n > 1) {
            /*           Transform B by a Householder matrix Z1: store vector */
            /*           describing this temporarily in B and in the local scalar H. */
            dlarfg_(n, &b[1], &b[2], &c__1, &h__);
            b1 = b[1];
            b[1] = 1.;
            /*           Form Z1 * A * Z1. */
            /*           Workspace: need N. */
            dlarf_("Right", n, n, &b[1], &c__1, &h__, &a[a_offset], lda, &dwork[1], 5L);
            dlarf_("Left", n, n, &b[1], &c__1, &h__, &a[a_offset], lda, &dwork[1], 4L);
            /*           Form C * Z1. */
            /*           Workspace: need P. */
            dlarf_("Right", p, n, &b[1], &c__1, &h__, &c__[c_offset], ldc, &dwork[1], 5L);
            b[1] = b1;
            tau[1] = h__;
            ++itau;
        } else {
            b1 = b[1];
            tau[1] = 0.;
        }
        /*        Reduce modified A to upper Hessenberg form by an orthogonal */
        /*        similarity transformation with matrix Z2. */
        /*        Workspace: need N;  prefer N*NB. */
        dgehrd_(n, &c__1, n, &a[a_offset], lda, &tau[itau], &dwork[1], ldwork, info);
        wrkopt = dwork[1];
        /*        Form C * Z2. */
        /*        Workspace: need P;  prefer P*NB. */
        dormhr_("Right", "No transpose", p, n, &c__1, n, &a[a_offset], lda, &tau[itau],
            &c__[c_offset], ldc, &dwork[1], ldwork, info, 5L, 12L);
        wrkopt = max(wrkopt, dwork[1]);
        if (ljobz) {
            /*           Save the orthogonal transformations used, so that they could */
            /*           be accumulated by calling DORGQR routine. */
            if (*n > 1) {
                i__1 = *n - 1;
                i__2 = *n - 1;
                dlacpy_("Full", &i__1, &c__1, &b[2], &i__2, &z__[z_dim1 + 2], ldz, 4L);
            }
            if (*n > 2) {
                i__1 = *n - 2;
                i__2 = *n - 2;
                dlacpy_(
                    "Lower", &i__1, &i__2, &a[a_dim1 + 3], lda, &z__[(z_dim1 << 1) + 3], ldz, 5L);
            }
            if (ljobi) {
                /*              Form the orthogonal transformation matrix Z = Z1 * Z2. */
                /*              Workspace: need N;  prefer N*NB. */
                dorgqr_(n, n, n, &z__[z_offset], ldz, &tau[1], &dwork[1], ldwork, info);
                wrkopt = max(wrkopt, dwork[1]);
            }
        }
        /*        Annihilate the lower part of A and B. */
        if (*n > 2) {
            i__1 = *n - 2;
            i__2 = *n - 2;
            dlaset_("Lower", &i__1, &i__2, &c_b10, &c_b10, &a[a_dim1 + 3], lda, 5L);
        }
        if (*n > 1) {
            i__1 = *n - 1;
            i__2 = *n - 1;
            dlaset_("Full", &i__1, &c__1, &c_b10, &c_b10, &b[2], &i__2, 4L);
        }
        /*        Find NCONT by checking sizes of the sub-diagonal elements of */
        /*        transformed A. */
        if (*tol <= 0.) {
            /* Computing MAX */
            d__1 = fanorm, d__2 = abs(b1);
            toldef = thresh * max(d__1, d__2);
        }
        j = 1;
        /*        WHILE ( J < N and ABS( A(J+1,J) ) > TOLDEF ) DO */
    L10:
        if (j < *n) {
            if ((d__1 = a[j + 1 + j * a_dim1], abs(d__1)) > toldef) {
                ++j;
                goto L10;
            }
        }
        /*        END WHILE 10 */
        /*        First negligible sub-diagonal element found, if any: set NCONT. */
        *ncont = j;
        if (j < *n) {
            a[j + 1 + j * a_dim1] = 0.;
        }
        /*        Undo scaling of A and B. */
        mb01pd_("U", "H", ncont, ncont, &c__0, &c__0, &anorm, &c__0, nblk, &a[a_offset], lda, info,
            1L, 1L);
        mb01pd_("U", "G", &c__1, &c__1, &c__0, &c__0, &bnorm, &c__0, nblk, &b[1], n, info, 1L, 1L);
        if (*ncont < *n) {
            i__1 = *n - *ncont;
            mb01pd_("U", "G", n, &i__1, &c__0, &c__0, &anorm, &c__0, nblk,
                &a[(*ncont + 1) * a_dim1 + 1], lda, info, 1L, 1L);
        }
    } else {
        /*        B is negligible compared with A. No computations for reducing */
        /*        the system to orthogonal canonical form have been performed, */
        /*        except scaling (which is undoed). */
        mb01pd_("U", "G", n, n, &c__0, &c__0, &anorm, &c__0, nblk, &a[a_offset], lda, info, 1L, 1L);
        mb01pd_("U", "G", n, &c__1, &c__0, &c__0, &bnorm, &c__0, nblk, &b[1], n, info, 1L, 1L);
        if (ljobf) {
            dlaset_("Full", n, n, &c_b10, &c_b10, &z__[z_offset], ldz, 4L);
            dlaset_("Full", n, &c__1, &c_b10, &c_b10, &tau[1], n, 4L);
        } else if (ljobi) {
            dlaset_("Full", n, n, &c_b10, &c_b18, &z__[z_offset], ldz, 4L);
        }
    }
    /*     Set optimal workspace dimension. */
    dwork[1] = wrkopt;
    return 0;
    /* *** Last line of TB01ZD *** */
} /* tb01zd_ */
