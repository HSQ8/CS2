#include <iostream>
#include <cmath>
using namespace std;

double qfsolve(double a, double b, double c){
/**
 * @brief Solves the given quadratic equation.
 *
 * This function, given real coefficients A, B, C to the equation
 * A*x*x + B*x + C = 0, returns the real part of a solution to the
 * equation thus defined. Where two real solutions exist, the one
 * closer to positive infinity is chosen.
 *
 * @param a the quadratic coefficient.
 * @param b the linear coefficient.
 * @param c the constant coefficient.
 *
 * @return the real part of a solution to the defined quadratic equation,
 *         as described.
 */

	if ((b * b - 4 * a * c) < 0){
		return -b/ 2 / a ;
	} else{
		return -b/ 2 / a + sqrt(b*b - 4*a*c) / 2 / a;
	}

}


int main(int argc, char ** argv)
{
    // This should print 422. Be sure to try some more test cases though!
    cout << qfsolve(1.0, 2.0, 3.0) << endl; // -1
    cout << qfsolve(1.0, -2.0, 3.0) << endl; // 1
    cout << qfsolve(5.0, -2.0, 3.0) << endl; // .2
    cout << qfsolve(5.0, 7.0, 3.0) << endl; // .7
    cout << qfsolve(5.0, 2.0, -10.0) << endl; // 1.22829

    return 0;
}
