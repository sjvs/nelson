/* Translated by Nelson f2c (version 20170901).
   You must link the resulting object file with the libraries:
    -lnlsf2c -lm   (in that order)
*/

#include "nelson_f2c.h"

/* Table of constant values */

static integer c__1 = 1;

EXPORTSYMBOL /* Subroutine */ int tb01ty_(
    mode, ioff, joff, nrow, ncol, size, x, ldx, bvect) integer *mode,
    *ioff, *joff, *nrow, *ncol;
doublereal *size, *x;
integer* ldx;
doublereal* bvect;
{
    /* System generated locals */
    integer x_dim1, x_offset, i__1;
    doublereal d__1;
    /* Builtin functions */
    double log(), pow_di();
    /* Local variables */
    static integer base;
    static doublereal test, expt;
    static integer i__, j;
    extern /* Subroutine */ int dscal_();
    static doublereal scale;
    extern doublereal dasum_();
    static integer iexpt;
    extern doublereal dlamch_();
    static doublereal abssum, div, eps;
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
    /*     Balances the rows (MODE .EQ. 0) or columns (MODE .NE. 0) of the */
    /*     (NROW x NCOL) block of the matrix X with offset (IOFF,JOFF), i.e. */
    /*     with first (top left) element (IOFF + 1,JOFF + 1).  Each non- */
    /*     zero row (column) is balanced in the sense that it is multiplied */
    /*     by that integer power of the base of the machine floating-point */
    /*     representation for which the sum of the absolute values of its */
    /*     entries (i.e. its 1-norm) satisfies */
    /*        (SIZE / BASE) .LT. ABSSUM .LE. SIZE */
    /*     for SIZE as input.  (Note that this form of scaling does not */
    /*     introduce any rounding errors.)  The vector BVECT then contains */
    /*     the appropriate scale factors in rows (IOFF + 1)...(IOFF + NROW) */
    /*     (columns (JOFF + 1)...(JOFF + NCOL) ).  In particular, if the */
    /*     I-th row (J-th column) of the block is 'numerically' non-zero */
    /*     with 1-norm given by BASE**(-EXPT) for some real EXPT, then the */
    /*     desired scale factor (returned as element IOFF + I (JOFF + J) of */
    /*     BVECT) is BASE**IEXPT, where IEXPT is the largest integer .LE. */
    /*     EXPT: this integer is precisely the truncation INT(EXPT) except */
    /*     for negative non-integer EXPT, in which case this value is too */
    /*     high by 1 and so must be adjusted accordingly.  Finally, note */
    /*     that the element of BVECT corresponding to a 'numerically' zero */
    /*     row (column) is simply set equal to 1.0. */
    /*     For efficiency, no tests of the input scalar parameters are */
    /*     performed. */
    /*     REVISIONS */
    /*     - */
    /*     ****************************************************************** */
    /*     .. Scalar Arguments .. */
    /*     .. Array Arguments .. */
    /*     .. Local Scalars .. */
    /*     .. External Functions .. */
    /*     .. External Subroutines .. */
    /*     .. Intrinsic Functions .. */
    /*     .. Executable Statements .. */
    /* Parameter adjustments */
    x_dim1 = *ldx;
    x_offset = x_dim1 + 1;
    x -= x_offset;
    --bvect;
    /* Function Body */
    base = (integer)dlamch_("Base", 4L);
    eps = dlamch_("Epsilon", 7L);
    div = 1. / log((doublereal)base);
    if (*mode != 0) {
        /*        Balance one column at a time using its column-sum norm. */
        i__1 = *joff + *ncol;
        for (j = *joff + 1; j <= i__1; ++j) {
            abssum = dasum_(nrow, &x[*ioff + 1 + j * x_dim1], &c__1) / abs(*size);
            test = abssum / (doublereal)(*nrow);
            if (test > eps) {
                /*              Non-zero column: calculate (and apply) correct scale */
                /*              factor. */
                expt = -div * log(abssum);
                iexpt = (integer)expt;
                if (iexpt < 0 && (doublereal)iexpt != expt) {
                    --iexpt;
                }
                d__1 = (doublereal)base;
                scale = pow_di(&d__1, &iexpt);
                bvect[j] = scale;
                dscal_(nrow, &scale, &x[*ioff + 1 + j * x_dim1], &c__1);
            } else {
                /*              'Numerically' zero column: do not rescale. */
                bvect[j] = 1.;
            }
            /* L10: */
        }
    } else {
        /*        Balance one row at a time using its row-sum norm. */
        i__1 = *ioff + *nrow;
        for (i__ = *ioff + 1; i__ <= i__1; ++i__) {
            abssum = dasum_(ncol, &x[i__ + (*joff + 1) * x_dim1], ldx) / abs(*size);
            test = abssum / (doublereal)(*ncol);
            if (test > eps) {
                /*              Non-zero row: calculate (and apply) correct scale factor. */
                expt = -div * log(abssum);
                iexpt = (integer)expt;
                if (iexpt < 0 && (doublereal)iexpt != expt) {
                    --iexpt;
                }
                d__1 = (doublereal)base;
                scale = pow_di(&d__1, &iexpt);
                bvect[i__] = scale;
                dscal_(ncol, &scale, &x[i__ + (*joff + 1) * x_dim1], ldx);
            } else {
                /*              'Numerically' zero row: do not rescale. */
                bvect[i__] = 1.;
            }
            /* L20: */
        }
    }
    return 0;
    /* *** Last line of TB01TY *** */
} /* tb01ty_ */
