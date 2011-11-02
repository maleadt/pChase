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
#if !defined(Output_h)
#define Output_h

// Local includes
#include "Types.h"
#include "Experiment.h"


//
// Class definition
//

class Output {
public:
	static void print(Experiment &e, int64 ops, double secs, double ck_res);
	static void header(Experiment &e, int64 ops, double secs, double ck_res);
	static void csv(Experiment &e, int64 ops, double secs, double ck_res);
	static void table(Experiment &e, int64 ops, double secs, double ck_res);
private:
};

#endif
