/*******************************************************************************
 * Copyright (c) 2006 International Business Machines Corporation.             *
 * All rights reserved. This program and the accompanying materials            *
 * are made available under the terms of the Common Public License v1.0        *
 * which accompanies this distribution, and is available at                    *
 * http://www.opensource.org/licenses/cpl1.0.php                               *
 *                                                                             *
 * Contributors:                                                               *
 *    Douglas M. pase - initial API and implementation                         *
 *******************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#if defined(NUMA)
#include <numa.h>
#endif

#include "Run.h"

#include "Chain.h"
#include "Timer.h"
#include "SpinBarrier.h"


static double min( double v1, double v2 );

Lock   Run::global_mutex;
int64  Run::_ops_per_chain = 0;
double Run::_seconds       = 1E9;


Run::Run()
: exp(NULL), bp(NULL)
{
}

Run::~Run()
{
}

void
Run::set( Experiment &e, SpinBarrier* sbp )
{
    this->exp = &e;
    this->bp  = sbp;
}

int
Run::run()
{ 
				// first allocate all memory for the chains,
				// making sure it is allocated within the 
				// intended numa domains
    Chain** chain_memory = new Chain* [ this->exp->chains_per_thread ];
    Chain** root         = new Chain* [ this->exp->chains_per_thread ];

#if defined(NUMA)
				// establish the node id where this thread
				// will run. threads are mapped to nodes
				// by the set-up code for Experiment.
    int run_node_id = this->exp->thread_domain[this->thread_id()];
    numa_run_on_node(run_node_id);

				// establish the node id where this thread's
				// memory will be allocated.
    for (int i=0; i < this->exp->chains_per_thread; i++) {
	int alloc_node_id = this->exp->chain_domain[this->thread_id()][i];
	nodemask_t alloc_mask;
	nodemask_zero(&alloc_mask);
	nodemask_set(&alloc_mask, alloc_node_id);
	numa_set_membind(&alloc_mask);

	chain_memory[i] = new Chain[ this->exp->links_per_chain ];
    }
#else
    for (int i=0; i < this->exp->chains_per_thread; i++) {
	chain_memory[i] = new Chain[ this->exp->links_per_chain ];
    }
#endif

    for (int i=0; i < this->exp->chains_per_thread; i++) {
	if (this->exp->access_pattern == Experiment::RANDOM) {
	    root[i] = random_mem_init( chain_memory[i] );
	} else if (0 < this->exp->stride) {
	    root[i] = forward_mem_init( chain_memory[i] );
	} else {
	    root[i] = reverse_mem_init( chain_memory[i] );
	}
    }

				// barrier
    for (int e=-1; e <= this->exp->experiments; e++) {
	this->bp->barrier();

				// start timer
	double start = 0;
	if (this->thread_id() == 0) start = Timer::seconds();
	this->bp->barrier();

				// chase pointers
	if (this->exp->chains_per_thread == 1) {
	    for (int i=0; i < this->exp->iterations; i++) {
		Chain* a = root[0];
		while (a != NULL) {
		    a = a->next;
		}
		this->mem_check( a );
	    }
	} else if (this->exp->chains_per_thread == 2) {
	    for (int i=0; i < this->exp->iterations; i++) {
		Chain* a = root[0];
		Chain* b = root[1];
		while (a != NULL) {
		    a = a->next;
		    b = b->next;
		}
		this->mem_check( a );
		this->mem_check( b );
	    }
	} else if (this->exp->chains_per_thread == 3) {
	    for (int i=0; i < this->exp->iterations; i++) {
		Chain* a = root[0];
		Chain* b = root[1];
		Chain* c = root[2];
		while (a != NULL) {
		    a = a->next;
		    b = b->next;
		    c = c->next;
		}
		this->mem_check( a );
		this->mem_check( b );
		this->mem_check( c );
	    }
	} else if (this->exp->chains_per_thread == 4) {
	    for (int i=0; i < this->exp->iterations; i++) {
		Chain* a = root[0];
		Chain* b = root[1];
		Chain* c = root[2];
		Chain* d = root[3];
		while (a != NULL) {
		    a = a->next;
		    b = b->next;
		    c = c->next;
		    d = d->next;
		}
		this->mem_check( a );
		this->mem_check( b );
		this->mem_check( c );
		this->mem_check( d );
	    }
	} else if (this->exp->chains_per_thread == 5) {
	    for (int i=0; i < this->exp->iterations; i++) {
		Chain* a = root[0];
		Chain* b = root[1];
		Chain* c = root[2];
		Chain* d = root[3];
		Chain* e = root[4];
		while (a != NULL) {
		    a = a->next;
		    b = b->next;
		    c = c->next;
		    d = d->next;
		    e = e->next;
		}
		this->mem_check( a );
		this->mem_check( b );
		this->mem_check( c );
		this->mem_check( d );
		this->mem_check( e );
	    }
	} else if (this->exp->chains_per_thread == 6) {
	    for (int i=0; i < this->exp->iterations; i++) {
		Chain* a = root[0];
		Chain* b = root[1];
		Chain* c = root[2];
		Chain* d = root[3];
		Chain* e = root[4];
		Chain* f = root[5];
		while (a != NULL) {
		    a = a->next;
		    b = b->next;
		    c = c->next;
		    d = d->next;
		    e = e->next;
		    f = f->next;
		}
		this->mem_check( a );
		this->mem_check( b );
		this->mem_check( c );
		this->mem_check( d );
		this->mem_check( e );
		this->mem_check( f );
	    }
	} else if (this->exp->chains_per_thread == 7) {
	    for (int i=0; i < this->exp->iterations; i++) {
		Chain* a = root[0];
		Chain* b = root[1];
		Chain* c = root[2];
		Chain* d = root[3];
		Chain* e = root[4];
		Chain* f = root[5];
		Chain* g = root[6];
		while (a != NULL) {
		    a = a->next;
		    b = b->next;
		    c = c->next;
		    d = d->next;
		    e = e->next;
		    f = f->next;
		    g = g->next;
		}
		this->mem_check( a );
		this->mem_check( b );
		this->mem_check( c );
		this->mem_check( d );
		this->mem_check( e );
		this->mem_check( f );
		this->mem_check( g );
	    }
	} else if (this->exp->chains_per_thread == 8) {
	    for (int i=0; i < this->exp->iterations; i++) {
		Chain* a = root[0];
		Chain* b = root[1];
		Chain* c = root[2];
		Chain* d = root[3];
		Chain* e = root[4];
		Chain* f = root[5];
		Chain* g = root[6];
		Chain* h = root[7];
		while (a != NULL) {
		    a = a->next;
		    b = b->next;
		    c = c->next;
		    d = d->next;
		    e = e->next;
		    f = f->next;
		    g = g->next;
		    h = h->next;
		}
		this->mem_check( a );
		this->mem_check( b );
		this->mem_check( c );
		this->mem_check( d );
		this->mem_check( e );
		this->mem_check( f );
		this->mem_check( g );
		this->mem_check( h );
	    }
	} else if (this->exp->chains_per_thread == 9) {
	    for (int i=0; i < this->exp->iterations; i++) {
		Chain* a = root[0];
		Chain* b = root[1];
		Chain* c = root[2];
		Chain* d = root[3];
		Chain* e = root[4];
		Chain* f = root[5];
		Chain* g = root[6];
		Chain* h = root[7];
		Chain* j = root[8];
		while (a != NULL) {
		    a = a->next;
		    b = b->next;
		    c = c->next;
		    d = d->next;
		    e = e->next;
		    f = f->next;
		    g = g->next;
		    h = h->next;
		    j = j->next;
		}
		this->mem_check( a );
		this->mem_check( b );
		this->mem_check( c );
		this->mem_check( d );
		this->mem_check( e );
		this->mem_check( f );
		this->mem_check( g );
		this->mem_check( h );
		this->mem_check( j );
	    }
	} else if (this->exp->chains_per_thread == 10) {
	    for (int i=0; i < this->exp->iterations; i++) {
		Chain* a = root[0];
		Chain* b = root[1];
		Chain* c = root[2];
		Chain* d = root[3];
		Chain* e = root[4];
		Chain* f = root[5];
		Chain* g = root[6];
		Chain* h = root[7];
		Chain* j = root[8];
		Chain* k = root[9];
		while (a != NULL) {
		    a = a->next;
		    b = b->next;
		    c = c->next;
		    d = d->next;
		    e = e->next;
		    f = f->next;
		    g = g->next;
		    h = h->next;
		    j = j->next;
		    k = k->next;
		}
		this->mem_check( a );
		this->mem_check( b );
		this->mem_check( c );
		this->mem_check( d );
		this->mem_check( e );
		this->mem_check( f );
		this->mem_check( g );
		this->mem_check( h );
		this->mem_check( j );
		this->mem_check( k );
	    }
	} else if (this->exp->chains_per_thread == 11) {
	    for (int i=0; i < this->exp->iterations; i++) {
		Chain* a = root[0];
		Chain* b = root[1];
		Chain* c = root[2];
		Chain* d = root[3];
		Chain* e = root[4];
		Chain* f = root[5];
		Chain* g = root[6];
		Chain* h = root[7];
		Chain* j = root[8];
		Chain* k = root[9];
		Chain* l = root[10];
		while (a != NULL) {
		    a = a->next;
		    b = b->next;
		    c = c->next;
		    d = d->next;
		    e = e->next;
		    f = f->next;
		    g = g->next;
		    h = h->next;
		    j = j->next;
		    k = k->next;
		    l = l->next;
		}
		this->mem_check( a );
		this->mem_check( b );
		this->mem_check( c );
		this->mem_check( d );
		this->mem_check( e );
		this->mem_check( f );
		this->mem_check( g );
		this->mem_check( h );
		this->mem_check( j );
		this->mem_check( k );
		this->mem_check( l );
	    }
	} else if (this->exp->chains_per_thread == 12) {
	    for (int i=0; i < this->exp->iterations; i++) {
		Chain* a = root[0];
		Chain* b = root[1];
		Chain* c = root[2];
		Chain* d = root[3];
		Chain* e = root[4];
		Chain* f = root[5];
		Chain* g = root[6];
		Chain* h = root[7];
		Chain* j = root[8];
		Chain* k = root[9];
		Chain* l = root[10];
		Chain* m = root[11];
		while (a != NULL) {
		    a = a->next;
		    b = b->next;
		    c = c->next;
		    d = d->next;
		    e = e->next;
		    f = f->next;
		    g = g->next;
		    h = h->next;
		    j = j->next;
		    k = k->next;
		    l = l->next;
		    m = m->next;
		}
		this->mem_check( a );
		this->mem_check( b );
		this->mem_check( c );
		this->mem_check( d );
		this->mem_check( e );
		this->mem_check( f );
		this->mem_check( g );
		this->mem_check( h );
		this->mem_check( j );
		this->mem_check( k );
		this->mem_check( l );
		this->mem_check( m );
	    }
	} else if (this->exp->chains_per_thread == 13) {
	    for (int i=0; i < this->exp->iterations; i++) {
		Chain* a = root[0];
		Chain* b = root[1];
		Chain* c = root[2];
		Chain* d = root[3];
		Chain* e = root[4];
		Chain* f = root[5];
		Chain* g = root[6];
		Chain* h = root[7];
		Chain* j = root[8];
		Chain* k = root[9];
		Chain* l = root[10];
		Chain* m = root[11];
		Chain* n = root[12];
		while (a != NULL) {
		    a = a->next;
		    b = b->next;
		    c = c->next;
		    d = d->next;
		    e = e->next;
		    f = f->next;
		    g = g->next;
		    h = h->next;
		    j = j->next;
		    k = k->next;
		    l = l->next;
		    m = m->next;
		    n = n->next;
		}
		this->mem_check( a );
		this->mem_check( b );
		this->mem_check( c );
		this->mem_check( d );
		this->mem_check( e );
		this->mem_check( f );
		this->mem_check( g );
		this->mem_check( h );
		this->mem_check( j );
		this->mem_check( k );
		this->mem_check( l );
		this->mem_check( m );
		this->mem_check( n );
	    }
	} else if (this->exp->chains_per_thread == 14) {
	    for (int i=0; i < this->exp->iterations; i++) {
		Chain* a = root[0];
		Chain* b = root[1];
		Chain* c = root[2];
		Chain* d = root[3];
		Chain* e = root[4];
		Chain* f = root[5];
		Chain* g = root[6];
		Chain* h = root[7];
		Chain* j = root[8];
		Chain* k = root[9];
		Chain* l = root[10];
		Chain* m = root[11];
		Chain* n = root[12];
		Chain* o = root[13];
		while (a != NULL) {
		    a = a->next;
		    b = b->next;
		    c = c->next;
		    d = d->next;
		    e = e->next;
		    f = f->next;
		    g = g->next;
		    h = h->next;
		    j = j->next;
		    k = k->next;
		    l = l->next;
		    m = m->next;
		    n = n->next;
		    o = o->next;
		}
		this->mem_check( a );
		this->mem_check( b );
		this->mem_check( c );
		this->mem_check( d );
		this->mem_check( e );
		this->mem_check( f );
		this->mem_check( g );
		this->mem_check( h );
		this->mem_check( j );
		this->mem_check( k );
		this->mem_check( l );
		this->mem_check( m );
		this->mem_check( n );
		this->mem_check( o );
	    }
	} else if (this->exp->chains_per_thread == 15) {
	    for (int i=0; i < this->exp->iterations; i++) {
		Chain* a = root[0];
		Chain* b = root[1];
		Chain* c = root[2];
		Chain* d = root[3];
		Chain* e = root[4];
		Chain* f = root[5];
		Chain* g = root[6];
		Chain* h = root[7];
		Chain* j = root[8];
		Chain* k = root[9];
		Chain* l = root[10];
		Chain* m = root[11];
		Chain* n = root[12];
		Chain* o = root[13];
		Chain* p = root[14];
		while (a != NULL) {
		    a = a->next;
		    b = b->next;
		    c = c->next;
		    d = d->next;
		    e = e->next;
		    f = f->next;
		    g = g->next;
		    h = h->next;
		    j = j->next;
		    k = k->next;
		    l = l->next;
		    m = m->next;
		    n = n->next;
		    o = o->next;
		    p = p->next;
		}
		this->mem_check( a );
		this->mem_check( b );
		this->mem_check( c );
		this->mem_check( d );
		this->mem_check( e );
		this->mem_check( f );
		this->mem_check( g );
		this->mem_check( h );
		this->mem_check( j );
		this->mem_check( k );
		this->mem_check( l );
		this->mem_check( m );
		this->mem_check( n );
		this->mem_check( o );
		this->mem_check( p );
	    }
	} else if (this->exp->chains_per_thread == 16) {
	    for (int i=0; i < this->exp->iterations; i++) {
		Chain* a = root[0];
		Chain* b = root[1];
		Chain* c = root[2];
		Chain* d = root[3];
		Chain* e = root[4];
		Chain* f = root[5];
		Chain* g = root[6];
		Chain* h = root[7];
		Chain* j = root[8];
		Chain* k = root[9];
		Chain* l = root[10];
		Chain* m = root[11];
		Chain* n = root[12];
		Chain* o = root[13];
		Chain* p = root[14];
		Chain* q = root[15];
		while (a != NULL) {
		    a = a->next;
		    b = b->next;
		    c = c->next;
		    d = d->next;
		    e = e->next;
		    f = f->next;
		    g = g->next;
		    h = h->next;
		    j = j->next;
		    k = k->next;
		    l = l->next;
		    m = m->next;
		    n = n->next;
		    o = o->next;
		    p = p->next;
		    q = q->next;
		}
		this->mem_check( a );
		this->mem_check( b );
		this->mem_check( c );
		this->mem_check( d );
		this->mem_check( e );
		this->mem_check( f );
		this->mem_check( g );
		this->mem_check( h );
		this->mem_check( j );
		this->mem_check( k );
		this->mem_check( l );
		this->mem_check( m );
		this->mem_check( n );
		this->mem_check( o );
		this->mem_check( p );
		this->mem_check( q );
	    }
	}
				// barrier
	this->bp->barrier();

				// stop timer
	double stop = 0;
	if (this->thread_id() == 0) stop = Timer::seconds();
	this->bp->barrier();

	if (0 <= e) {
	    if (this->thread_id() == 0) {
		double delta = stop - start;
		if (0 < delta) {
		    Run::_seconds = min( Run::_seconds, delta );
		}
	    }
	}
    }

    this->bp->barrier();


    for (int i=0; i < this->exp->chains_per_thread; i++) {
	if (chain_memory[i] != NULL) delete [] chain_memory[i];
    }
    if (chain_memory != NULL) delete [] chain_memory;

    return 0;
}

int dummy = 0;
void
Run::mem_check( Chain *m )
{
    if (m == NULL) dummy += 1;
}

static double
min( double v1, double v2 )
{
    if (v2 < v1) return v2;
    return v1;
}

				// exclude 2 and mersienne primes, i.e.,
				// primes of the form 2**n - 1, e.g.,
				// 3, 7, 31, 127
static const int prime_table[] = { 5, 11, 13, 17, 19, 23, 37, 41, 43, 47,
    53, 61, 71, 73, 79, 83, 89, 97, 101, 103, 109, 113, 131, 137, 139, 149,
    151, 157, 163, };
static const int prime_table_size = sizeof prime_table / sizeof prime_table[0];

Chain*
Run::random_mem_init( Chain *mem )
{
				// initialize pointers --
				// choose a page at random, then use
				// one pointer from each cache line
				// within the page.  all pages and
				// cache lines are chosen at random.
    Chain* root = NULL;
    Chain* prev = NULL;
    int link_within_line = 0;
    int64 local_ops_per_chain = 0;

				// we must set a lock because random()
				// is not thread safe
    Run::global_mutex.lock();
    setstate(this->exp->random_state[this->thread_id()]);
    int page_factor = prime_table[ random() % prime_table_size ];
    int page_offset = random() % this->exp->pages_per_chain;
    Run::global_mutex.unlock();

				// loop through the pages
    for (int i=0; i < this->exp->pages_per_chain; i++) {
	int page = (page_factor * i + page_offset) % this->exp->pages_per_chain;
	Run::global_mutex.lock();
	setstate(this->exp->random_state[this->thread_id()]);
	int line_factor = prime_table[ random() % prime_table_size ];
	int line_offset = random() % this->exp->lines_per_page;
	Run::global_mutex.unlock();

				// loop through the lines within a page
	for (int j=0; j < this->exp->lines_per_page; j++) {
	    int line_within_page = (line_factor * j + line_offset) % this->exp->lines_per_page;
	    int link = page * this->exp->links_per_page + line_within_page * this->exp->links_per_line + link_within_line;

	    if (root == NULL) {
//		printf("root       = %d(%d)[0x%x].\n", page, line_within_page, mem+link);
		prev = root = mem + link;
		local_ops_per_chain += 1;
	    } else {
//		printf("0x%x = %d(%d)[0x%x].\n", prev, page, line_within_page, mem+link);
		prev->next = mem + link;
		prev = prev->next;
		local_ops_per_chain += 1;
	    }
	}
    }

    Run::global_mutex.lock();
    Run::_ops_per_chain = local_ops_per_chain;
    Run::global_mutex.unlock();

    return root;
}

Chain*
Run::forward_mem_init( Chain *mem )
{
    Chain* root = NULL;
    Chain* prev = NULL;
    int link_within_line = 0;
    int64 local_ops_per_chain = 0;

    for (int i=0; i < this->exp->lines_per_chain; i += this->exp->stride) {
	int link = i * this->exp->links_per_line + link_within_line;
	if (root == NULL) {
//	    printf("root       = %d(%d)[0x%x].\n", page, line_within_page, mem+link);
	    prev = root = mem + link;
	    local_ops_per_chain += 1;
	} else {
//	    printf("0x%x = %d(%d)[0x%x].\n", prev, page, line_within_page, mem+link);
	    prev->next = mem + link;
	    prev = prev->next;
	    local_ops_per_chain += 1;
	}
    }

    Run::global_mutex.lock();
    Run::_ops_per_chain = local_ops_per_chain;
    Run::global_mutex.unlock();

    return root;
}

Chain*
Run::reverse_mem_init( Chain *mem )
{
    Chain* root = NULL;
    Chain* prev = NULL;
    int link_within_line = 0;
    int64 local_ops_per_chain = 0;

    int stride = -this->exp->stride;
    int last;
    for (int i=0; i < this->exp->lines_per_chain; i += stride) {
	last = i;
    }

    for (int i=last; 0 <= i; i -= stride) {
	int link = i * this->exp->links_per_line + link_within_line;
	if (root == NULL) {
//	    printf("root       = %d(%d)[0x%x].\n", page, line_within_page, mem+link);
	    prev = root = mem + link;
	    local_ops_per_chain += 1;
	} else {
//	    printf("0x%x = %d(%d)[0x%x].\n", prev, page, line_within_page, mem+link);
	    prev->next = mem + link;
	    prev = prev->next;
	    local_ops_per_chain += 1;
	}
    }

    Run::global_mutex.lock();
    Run::_ops_per_chain = local_ops_per_chain;
    Run::global_mutex.unlock();

    return root;
}
