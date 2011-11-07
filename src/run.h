/*******************************************************************************
 * Copyright (c) 2006 International Business Machines Corporation.             *
 * All rights reserved. This program and the accompanying materials            *
 * are made available under the terms of the Common Public License v1.0        *
 * which accompanies this distribution, and is available at                    *
 * http://www.opensource.org/licenses/cpl1.0.php                               *
 *                                                                             *
 * Contributors:                                                               *
 *    Douglas M. Pase - initial API and implementation                         *
 *******************************************************************************/

//
// Configuration
//

// Include guard
#if !defined(RUN_H)
#define RUN_H

// Local includes
#include "thread.h"
#include "lock.h"
#include "chain.h"
#include "types.h"
#include "experiment.h"
#include "spinbarrier.h"


//
// Class definition
//

class Run: public Thread {
public:
	Run();
	~Run();
	int run();
	void set(Experiment &e, SpinBarrier* sbp);

	static int64 ops_per_chain() {
		return _ops_per_chain;
	}
	static double seconds() {
		return _seconds;
	}

private:
	Experiment* exp; // experiment data
	SpinBarrier* bp; // spin barrier used by all threads

	void mem_check(Chain *m);
	Chain* random_mem_init(Chain *m);
	Chain* forward_mem_init(Chain *m);
	Chain* reverse_mem_init(Chain *m);
	Chain* stream_mem_init(Chain *m);

	static Lock global_mutex; // global lock
	static int64 _ops_per_chain; // total number of operations per chain
	static double _seconds; // total number of seconds
};

#endif
