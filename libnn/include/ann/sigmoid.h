/* sigmoid.h
 * 
 * This file is part of EALib.
 * 
 * Copyright 2012 David B. Knoester.
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef _ANN_SIGMOID_H_
#define _ANN_SIGMOID_H_

#include <cmath>

namespace ann {

	double step(double x, double lv=0.0, double uv=1.0) {
        if(x > 0.0) {
            return uv;
        } 
        return lv;
    }
	
	/*! Heaviside function (aka unit step), a binary activation sigmoid type.
     
     \warning The definition of H(0) can be significant; this was not selected
     with care.
	 */
	struct heaviside {
		//! Constructor.
		heaviside() {
		}
		
		//! Calculate the heaviside function of x.
		double operator()(double x) {
			return (x <= 0.0) ? 0.0 : 1.0;
		}

		// it's not clear what the derivative is here...
        //		//! Calculate the derivative of the logistic sigmoid of x.
        //		double derivative(double x) {
        //		}	
	};

    
	/*! Logistic function, a type of sigmoid.
	 */
	struct logistic {
		//! Constructor.
		logistic(double l=1.0) : lambda(l) {
		}
		
		//! Calculate the logistic sigmoid of x.
		double operator()(double x) {
			return 1/(1+exp(-lambda*x));
		}
		
		//! Calculate the derivative of the logistic sigmoid of x.
		double derivative(double x) {
			double s = operator()(x);
			return s * (1 - s);
		}	
		
		double lambda; //!< Lambda; steepens the gradient of the sigmoid.
	};
	
	
	/*! Hyperbolic tangent function, a type of sigmoid.
	 */
	struct hyperbolic_tangent {
		//! Constructor.
		hyperbolic_tangent(double l=3.0) : _lambda(l) { }
		
		//! Calculate the hyperbolic tangent of x.
		double operator()(double x) {
			return tanh(_lambda*x);
		}
		
		//! Calculate the derivative of the hyperbolic tangent of x.
		double derivative(double x) {
			return 1-pow(operator()(x), 2);
		}
        
        double _lambda; //!< Used to steepen the gradient of the sigmoid.
	};
	
} // nn

#endif
