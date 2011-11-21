/*******************************************************************************
 * Copyright (c) 2006 International Business Machines Corporation.             *
 * All rights reserved. This program and the accompanying materials            *
 * are made available under the terms of the Common Public License v1.0        *
 * which accompanies this distribution, and is available at                    *
 * http://www.opensource.org/licenses/cpl1.0.php                               *
 *                                                                             *
 * Contributors:                                                               *
 *    Douglas M. Pase - initial API and implementation                         *
 *    Tim Besard - prefetching, JIT compilation                                *
 *******************************************************************************/

//
// Configuration
//

// Include guard
#if !defined(SPINBARRIER_H)
#define SPINBARRIER_H

// System includes
#include <pthread.h>


//
// Class definition
//

class SpinBarrier {
public:
	SpinBarrier(int participants);
	~SpinBarrier();

	void barrier();

private:
	int limit; // number of barrier participants
	pthread_barrier_t barrier_obj;
};

#endif
