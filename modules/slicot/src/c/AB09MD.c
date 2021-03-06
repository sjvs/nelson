/* Translated by Nelson f2c (version 20170901).
   You must link the resulting object file with the libraries:
    -lnlsf2c -lm   (in that order)
*/

#include "nelson_f2c.h"

EXPORTSYMBOL /* Subroutine */ int ab09md_(dico, job, equil, ordsel, n, m, p, nr, alpha, a, lda, b,
    ldb, c__, ldc, ns, hsv, tol, iwork, dwork, ldwork, iwarn, info, dico_len, job_len, equil_len,
    ordsel_len) char *dico,
    *job, *equil, *ordsel;
integer *n, *m, *p, *nr;
doublereal *alpha, *a;
integer* lda;
doublereal* b;
integer* ldb;
doublereal* c__;
integer *ldc, *ns;
doublereal *hsv, *tol;
integer* iwork;
doublereal* dwork;
integer *ldwork, *iwarn, *info;
ftnlen dico_len;
ftnlen job_len;
ftnlen equil_len;
ftnlen ordsel_len;
{
    /* System generated locals */
    integer a_dim1, a_offset, b_dim1, b_offset, c_dim1, c_offset, i__1, i__2, i__3;
    /* Builtin functions */
    double sqrt();
    /* Local variables */
    static integer ierr;
    extern /* Subroutine */ int tb01id_(), ab09ax_(), tb01kd_();
    extern logical lsame_();
    static logical discr;
    extern doublereal dlamch_();
    static integer nn, kt, ku, kw, nu;
    extern /* Subroutine */ int xerbla_();
    static doublereal maxred;
    static logical fixord;
    static integer iwarnl;
    static doublereal alpwrk;
    static integer nu1, wrkopt, nra, kti, kwi, kwr, lwr;
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
    /*     To compute a reduced order model (Ar,Br,Cr) for an original */
    /*     state-space representation (A,B,C) by using either the square-root */
    /*     or the balancing-free square-root Balance & Truncate (B & T) */
    /*     model reduction method for the ALPHA-stable part of the system. */
    /*     ARGUMENTS */
    /*     Mode Parameters */
    /*     DICO    CHARACTER*1 */
    /*             Specifies the type of the original system as follows: */
    /*             = 'C':  continuous-time system; */
    /*             = 'D':  discrete-time system. */
    /*     JOB     CHARACTER*1 */
    /*             Specifies the model reduction approach to be used */
    /*             as follows: */
    /*             = 'B':  use the square-root Balance & Truncate method; */
    /*             = 'N':  use the balancing-free square-root */
    /*                     Balance & Truncate method. */
    /*     EQUIL   CHARACTER*1 */
    /*             Specifies whether the user wishes to preliminarily */
    /*             equilibrate the triplet (A,B,C) as follows: */
    /*             = 'S':  perform equilibration (scaling); */
    /*             = 'N':  do not perform equilibration. */
    /*     ORDSEL  CHARACTER*1 */
    /*             Specifies the order selection method as follows: */
    /*             = 'F':  the resulting order NR is fixed; */
    /*             = 'A':  the resulting order NR is automatically determined */
    /*                     on basis of the given tolerance TOL. */
    /*     Input/Output Parameters */
    /*     N       (input) INTEGER */
    /*             The order of the original state-space representation, i.e. */
    /*             the order of the matrix A.  N >= 0. */
    /*     M       (input) INTEGER */
    /*             The number of system inputs.  M >= 0. */
    /*     P       (input) INTEGER */
    /*             The number of system outputs.  P >= 0. */
    /*     NR      (input/output) INTEGER */
    /*             On entry with ORDSEL = 'F', NR is the desired order of the */
    /*             resulting reduced order system.  0 <= NR <= N. */
    /*             On exit, if INFO = 0, NR is the order of the resulting */
    /*             reduced order model. For a system with NU ALPHA-unstable */
    /*             eigenvalues and NS ALPHA-stable eigenvalues (NU+NS = N), */
    /*             NR is set as follows: if ORDSEL = 'F', NR is equal to */
    /*             NU+MIN(MAX(0,NR-NU),NMIN), where NR is the desired order */
    /*             on entry, and NMIN is the order of a minimal realization */
    /*             of the ALPHA-stable part of the given system; NMIN is */
    /*             determined as the number of Hankel singular values greater */
    /*             than NS*EPS*HNORM(As,Bs,Cs), where EPS is the machine */
    /*             precision (see LAPACK Library Routine DLAMCH) and */
    /*             HNORM(As,Bs,Cs) is the Hankel norm of the ALPHA-stable */
    /*             part of the given system (computed in HSV(1)); */
    /*             if ORDSEL = 'A', NR is the sum of NU and the number of */
    /*             Hankel singular values greater than */
    /*             MAX(TOL,NS*EPS*HNORM(As,Bs,Cs)). */
    /*     ALPHA   (input) DOUBLE PRECISION */
    /*             Specifies the ALPHA-stability boundary for the eigenvalues */
    /*             of the state dynamics matrix A. For a continuous-time */
    /*             system (DICO = 'C'), ALPHA <= 0 is the boundary value for */
    /*             the real parts of eigenvalues, while for a discrete-time */
    /*             system (DICO = 'D'), 0 <= ALPHA <= 1 represents the */
    /*             boundary value for the moduli of eigenvalues. */
    /*             The ALPHA-stability domain does not include the boundary. */
    /*     A       (input/output) DOUBLE PRECISION array, dimension (LDA,N) */
    /*             On entry, the leading N-by-N part of this array must */
    /*             contain the state dynamics matrix A. */
    /*             On exit, if INFO = 0, the leading NR-by-NR part of this */
    /*             array contains the state dynamics matrix Ar of the reduced */
    /*             order system. */
    /*             The resulting A has a block-diagonal form with two blocks. */
    /*             For a system with NU ALPHA-unstable eigenvalues and */
    /*             NS ALPHA-stable eigenvalues (NU+NS = N), the leading */
    /*             NU-by-NU block contains the unreduced part of A */
    /*             corresponding to ALPHA-unstable eigenvalues in an */
    /*             upper real Schur form. */
    /*             The trailing (NR+NS-N)-by-(NR+NS-N) block contains */
    /*             the reduced part of A corresponding to ALPHA-stable */
    /*             eigenvalues. */
    /*     LDA     INTEGER */
    /*             The leading dimension of array A.  LDA >= MAX(1,N). */
    /*     B       (input/output) DOUBLE PRECISION array, dimension (LDB,M) */
    /*             On entry, the leading N-by-M part of this array must */
    /*             contain the original input/state matrix B. */
    /*             On exit, if INFO = 0, the leading NR-by-M part of this */
    /*             array contains the input/state matrix Br of the reduced */
    /*             order system. */
    /*     LDB     INTEGER */
    /*             The leading dimension of array B.  LDB >= MAX(1,N). */
    /*     C       (input/output) DOUBLE PRECISION array, dimension (LDC,N) */
    /*             On entry, the leading P-by-N part of this array must */
    /*             contain the original state/output matrix C. */
    /*             On exit, if INFO = 0, the leading P-by-NR part of this */
    /*             array contains the state/output matrix Cr of the reduced */
    /*             order system. */
    /*     LDC     INTEGER */
    /*             The leading dimension of array C.  LDC >= MAX(1,P). */
    /*     NS      (output) INTEGER */
    /*             The dimension of the ALPHA-stable subsystem. */
    /*     HSV     (output) DOUBLE PRECISION array, dimension (N) */
    /*             If INFO = 0, the leading NS elements of HSV contain the */
    /*             Hankel singular values of the ALPHA-stable part of the */
    /*             original system ordered decreasingly. */
    /*             HSV(1) is the Hankel norm of the ALPHA-stable subsystem. */
    /*     Tolerances */
    /*     TOL     DOUBLE PRECISION */
    /*             If ORDSEL = 'A', TOL contains the tolerance for */
    /*             determining the order of reduced system. */
    /*             For model reduction, the recommended value is */
    /*             TOL = c*HNORM(As,Bs,Cs), where c is a constant in the */
    /*             interval [0.00001,0.001], and HNORM(As,Bs,Cs) is the */
    /*             Hankel-norm of the ALPHA-stable part of the given system */
    /*             (computed in HSV(1)). */
    /*             If TOL <= 0 on entry, the used default value is */
    /*             TOL = NS*EPS*HNORM(As,Bs,Cs), where NS is the number of */
    /*             ALPHA-stable eigenvalues of A and EPS is the machine */
    /*             precision (see LAPACK Library Routine DLAMCH). */
    /*             This value is appropriate to compute a minimal realization */
    /*             of the ALPHA-stable part. */
    /*             If ORDSEL = 'F', the value of TOL is ignored. */
    /*     Workspace */
    /*     IWORK   INTEGER array, dimension (LIWORK) */
    /*             LIWORK = 0, if JOB = 'B'; */
    /*             LIWORK = N, if JOB = 'N'. */
    /*     DWORK   DOUBLE PRECISION array, dimension (LDWORK) */
    /*             On exit, if INFO = 0, DWORK(1) returns the optimal value */
    /*             of LDWORK. */
    /*     LDWORK  INTEGER */
    /*             The length of the array DWORK. */
    /*             LDWORK >= MAX(1,N*(2*N+MAX(N,M,P)+5) + N*(N+1)/2). */
    /*             For optimum performance LDWORK should be larger. */
    /*     Warning Indicator */
    /*     IWARN   INTEGER */
    /*             = 0:  no warning; */
    /*             = 1:  with ORDSEL = 'F', the selected order NR is greater */
    /*                   than NSMIN, the sum of the order of the */
    /*                   ALPHA-unstable part and the order of a minimal */
    /*                   realization of the ALPHA-stable part of the given */
    /*                   system. In this case, the resulting NR is set equal */
    /*                   to NSMIN. */
    /*             = 2:  with ORDSEL = 'F', the selected order NR is less */
    /*                   than the order of the ALPHA-unstable part of the */
    /*                   given system. In this case NR is set equal to the */
    /*                   order of the ALPHA-unstable part. */
    /*     Error Indicator */
    /*     INFO    INTEGER */
    /*             = 0:  successful exit; */
    /*             < 0:  if INFO = -i, the i-th argument had an illegal */
    /*                   value; */
    /*             = 1:  the computation of the ordered real Schur form of A */
    /*                   failed; */
    /*             = 2:  the separation of the ALPHA-stable/unstable diagonal */
    /*                   blocks failed because of very close eigenvalues; */
    /*             = 3:  the computation of Hankel singular values failed. */
    /*     METHOD */
    /*     Let be the following linear system */
    /*          d[x(t)] = Ax(t) + Bu(t) */
    /*          y(t)    = Cx(t)                               (1) */
    /*     where d[x(t)] is dx(t)/dt for a continuous-time system and x(t+1) */
    /*     for a discrete-time system. The subroutine AB09MD determines for */
    /*     the given system (1), the matrices of a reduced order system */
    /*          d[z(t)] = Ar*z(t) + Br*u(t) */
    /*          yr(t)   = Cr*z(t)                             (2) */
    /*     such that */
    /*     HSV(NR+NS-N) <= INFNORM(G-Gr) <= 2*[HSV(NR+NS-N+1)+...+HSV(NS)], */
    /*     where G and Gr are transfer-function matrices of the systems */
    /*     (A,B,C) and (Ar,Br,Cr), respectively, and INFNORM(G) is the */
    /*     infinity-norm of G. */
    /*     The following procedure is used to reduce a given G: */
    /*     1) Decompose additively G as */
    /*          G = G1 + G2 */
    /*        such that G1 = (As,Bs,Cs) has only ALPHA-stable poles and */
    /*        G2 = (Au,Bu,Cu) has only ALPHA-unstable poles. */
    /*     2) Determine G1r, a reduced order approximation of the */
    /*        ALPHA-stable part G1. */
    /*     3) Assemble the reduced model Gr as */
    /*           Gr = G1r + G2. */
    /*     To reduce the ALPHA-stable part G1, if JOB = 'B', the square-root */
    /*     Balance & Truncate method of [1] is used, and for an ALPHA-stable */
    /*     continuous-time system (DICO = 'C'), the resulting reduced model */
    /*     is balanced. For ALPHA-stable systems, setting TOL < 0, the */
    /*     routine can be used to compute balanced minimal state-space */
    /*     realizations. */
    /*     If JOB = 'N', the balancing-free square-root version of the */
    /*     Balance & Truncate method [2] is used to reduce the ALPHA-stable */
    /*     part G1. */
    /*     REFERENCES */
    /*     [1] Tombs M.S. and Postlethwaite I. */
    /*         Truncated balanced realization of stable, non-minimal */
    /*         state-space systems. */
    /*         Int. J. Control, Vol. 46, pp. 1319-1330, 1987. */
    /*     [2] Varga A. */
    /*         Efficient minimal realization procedure based on balancing. */
    /*         Proc. of IMACS/IFAC Symp. MCTS, Lille, France, May 1991, */
    /*         A. El Moudui, P. Borne, S. G. Tzafestas (Eds.), */
    /*         Vol. 2, pp. 42-46. */
    /*     NUMERICAL ASPECTS */
    /*     The implemented methods rely on accuracy enhancing square-root or */
    /*     balancing-free square-root techniques. */
    /*                                         3 */
    /*     The algorithms require less than 30N  floating point operations. */
    /*     CONTRIBUTOR */
    /*     C. Oara, University "Politehnica" Bucharest. */
    /*     A. Varga, German Aerospace Center, DLR Oberpfaffenhofen. */
    /*     February 1999. Based on the RASP routines SADSDC, SRBT and SRBFT. */
    /*     REVISIONS */
    /*     Mar. 1999, V. Sima, Research Institute for Informatics, Bucharest. */
    /*     Nov. 2000, A. Varga, DLR Oberpfaffenhofen. */
    /*     KEYWORDS */
    /*     Balancing, minimal realization, model reduction, multivariable */
    /*     system, state-space model, state-space representation. */
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
    --hsv;
    --iwork;
    --dwork;
    /* Function Body */
    *info = 0;
    *iwarn = 0;
    discr = lsame_(dico, "D", 1L, 1L);
    fixord = lsame_(ordsel, "F", 1L, 1L);
    /*     Test the input scalar arguments. */
    if (!(lsame_(dico, "C", 1L, 1L) || discr)) {
        *info = -1;
    } else if (!(lsame_(job, "B", 1L, 1L) || lsame_(job, "N", 1L, 1L))) {
        *info = -2;
    } else if (!(lsame_(equil, "S", 1L, 1L) || lsame_(equil, "N", 1L, 1L))) {
        *info = -3;
    } else if (!(fixord || lsame_(ordsel, "A", 1L, 1L))) {
        *info = -4;
    } else if (*n < 0) {
        *info = -5;
    } else if (*m < 0) {
        *info = -6;
    } else if (*p < 0) {
        *info = -7;
    } else if (fixord && (*nr < 0 || *nr > *n)) {
        *info = -8;
    } else if (discr && (*alpha < 0. || *alpha > 1.) || !discr && *alpha > 0.) {
        *info = -9;
    } else if (*lda < max(1, *n)) {
        *info = -11;
    } else if (*ldb < max(1, *n)) {
        *info = -13;
    } else if (*ldc < max(1, *p)) {
        *info = -15;
    } else /* if(complicated condition) */
    {
        /* Computing MAX */
        /* Computing MAX */
        i__3 = max(*n, *m);
        i__1 = 1, i__2 = *n * ((*n << 1) + max(i__3, *p) + 5) + *n * (*n + 1) / 2;
        if (*ldwork < max(i__1, i__2)) {
            *info = -21;
        }
    }
    if (*info != 0) {
        /*        Error return. */
        i__1 = -(*info);
        xerbla_("AB09MD", &i__1, 6L);
        return 0;
    }
    /*     Quick return if possible. */
    /* Computing MIN */
    i__1 = min(*n, *m);
    if (min(i__1, *p) == 0) {
        *nr = 0;
        dwork[1] = 1.;
        return 0;
    }
    if (lsame_(equil, "S", 1L, 1L)) {
        /*        Scale simultaneously the matrices A, B and C: */
        /*        A <- inv(D)*A*D,  B <- inv(D)*B and C <- C*D, where D is a */
        /*        diagonal matrix. */
        /*        Workspace: N. */
        maxred = 100.;
        tb01id_("All", n, m, p, &maxred, &a[a_offset], lda, &b[b_offset], ldb, &c__[c_offset], ldc,
            &dwork[1], info, 3L);
    }
    /*     Correct the value of ALPHA to ensure stability. */
    alpwrk = *alpha;
    if (discr) {
        if (*alpha == 1.) {
            alpwrk = 1. - sqrt(dlamch_("E", 1L));
        }
    } else {
        if (*alpha == 0.) {
            alpwrk = -sqrt(dlamch_("E", 1L));
        }
    }
    /*     Allocate working storage. */
    nn = *n * *n;
    ku = 1;
    kwr = ku + nn;
    kwi = kwr + *n;
    kw = kwi + *n;
    lwr = *ldwork - kw + 1;
    /*     Reduce A to a block-diagonal real Schur form, with the */
    /*     ALPHA-unstable part in the leading diagonal position, using a */
    /*     non-orthogonal similarity transformation A <- inv(T)*A*T and */
    /*     apply the transformation to B and C: B <- inv(T)*B and C <- C*T. */
    /*     Workspace needed:      N*(N+2); */
    /*     Additional workspace:  need   3*N; */
    /*                            prefer larger. */
    tb01kd_(dico, "Unstable", "General", n, m, p, &alpwrk, &a[a_offset], lda, &b[b_offset], ldb,
        &c__[c_offset], ldc, &nu, &dwork[ku], n, &dwork[kwr], &dwork[kwi], &dwork[kw], &lwr, &ierr,
        1L, 8L, 7L);
    if (ierr != 0) {
        if (ierr != 3) {
            *info = 1;
        } else {
            *info = 2;
        }
        return 0;
    }
    wrkopt = (integer)(dwork[kw] + (doublereal)(kw - 1));
    iwarnl = 0;
    *ns = *n - nu;
    if (fixord) {
        /* Computing MAX */
        i__1 = 0, i__2 = *nr - nu;
        nra = max(i__1, i__2);
        if (*nr < nu) {
            iwarnl = 2;
        }
    } else {
        nra = 0;
    }
    /*     Finish if only unstable part is present. */
    if (*ns == 0) {
        *nr = nu;
        dwork[1] = (doublereal)wrkopt;
        return 0;
    }
    nu1 = nu + 1;
    /*     Allocate working storage. */
    kt = 1;
    kti = kt + nn;
    kw = kti + nn;
    /*     Compute a B & T approximation of the stable part. */
    /*     Workspace: need   N*(2*N+MAX(N,M,P)+5) + N*(N+1)/2; */
    /*                prefer larger. */
    i__1 = *ldwork - kw + 1;
    ab09ax_(dico, job, ordsel, ns, m, p, &nra, &a[nu1 + nu1 * a_dim1], lda, &b[nu1 + b_dim1], ldb,
        &c__[nu1 * c_dim1 + 1], ldc, &hsv[1], &dwork[kt], n, &dwork[kti], n, tol, &iwork[1],
        &dwork[kw], &i__1, iwarn, &ierr, 1L, 1L, 1L);
    *iwarn = max(*iwarn, iwarnl);
    if (ierr != 0) {
        *info = ierr + 1;
        return 0;
    }
    *nr = nra + nu;
    /* Computing MAX */
    i__1 = wrkopt, i__2 = (integer)dwork[kw] + kw - 1;
    dwork[1] = (doublereal)max(i__1, i__2);
    return 0;
    /* *** Last line of AB09MD *** */
} /* ab09md_ */
