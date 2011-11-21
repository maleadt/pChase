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
#if !defined(CHAIN_H)
#define CHAIN_H


//
// Struct definition
//

/*
 * Note that the Chain object should always be a Plain Old Data (POD) object,
 * because it is used from within JIT-generated assembly code, so we need to
 * be able to refer to its data members using the C macro offsetof. This is
 * only possible in case of a POD object.
 */

struct Chain {
	Chain* next;
};

#endif
