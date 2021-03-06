/* Translated by Nelson f2c (version 20170901).
   You must link the resulting object file with the libraries:
    -lnlsf2c -lm   (in that order)
*/

#include "nelson_f2c.h"

logical sb02mw_(reig, ieig) doublereal *reig, *ieig;
{
    /* System generated locals */
    logical ret_val;
    /* Local variables */
    extern doublereal dlapy2_();
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
    /*     To select the stable eigenvalues for solving the discrete-time */
    /*     algebraic Riccati equation. */
    /*     ARGUMENTS */
    /*     Input/Output Parameters */
    /*     REIG    (input) DOUBLE PRECISION */
    /*             The real part of the current eigenvalue considered. */
    /*     IEIG    (input) DOUBLE PRECISION */
    /*             The imaginary part of the current eigenvalue considered. */
    /*     METHOD */
    /*     The function value SB02MW is set to .TRUE. for a stable */
    /*     eigenvalue (i.e., with modulus less than one) and to .FALSE., */
    /*     otherwise. */
    /*     REFERENCES */
    /*     None. */
    /*     NUMERICAL ASPECTS */
    /*     None. */
    /*     CONTRIBUTOR */
    /*     V. Sima, Katholieke Univ. Leuven, Belgium, Aug. 1997. */
    /*     REVISIONS */
    /*     - */
    /*     KEYWORDS */
    /*     Algebraic Riccati equation, closed loop system, discrete-time */
    /*     system, optimal regulator, Schur form. */
    /*     ****************************************************************** */
    /*     .. Parameters .. */
    /*     .. Scalar Arguments .. */
    /*     .. External Functions .. */
    /*     .. Executable Statements .. */
    ret_val = dlapy2_(reig, ieig) < 1.;
    return ret_val;
    /* *** Last line of SB02MW *** */
} /* sb02mw_ */
