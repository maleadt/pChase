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

// Implementation header
#include "lock.h"

// System includes
#include <cstdio>


//
// Implementation
//

Lock::Lock() {
	pthread_mutex_init(&(this->mutex), NULL);
}

Lock::~Lock() {
	pthread_mutex_destroy(&(this->mutex));
}

void Lock::lock() {
	pthread_mutex_lock(&(this->mutex));
}

int Lock::test() {
	return pthread_mutex_trylock(&(this->mutex));
}

void Lock::unlock() {
	pthread_mutex_unlock(&(this->mutex));
}

