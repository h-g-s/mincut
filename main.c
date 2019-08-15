/********************************************************************************
 * Copyright (c) 2019 Haroldo Gambini Santos
 * 
 * MinCut
 * A self-contained, C99 compatible minimum cut implementation 
 *
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0
 *
 ********************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "macros.h"
#include "mincut.h"

#define ALLOCATE_VECTOR( ptr, type, nElements ) {\
    ptr = (type*) malloc( sizeof(type)*(nElements) ); \
    if (!ptr) { \
       fprintf( stderr, "ERROR: no more memory available. at: %s:%d\n", __FILE__, __LINE__ ); \
       abort(); \
    }; }

int main(int argc, char **argv)
{
    if (argc<4)
    {
        fprintf( stderr, "usage: minc instance s t\n");
        exit( EXIT_FAILURE );
    }

    FILE *f = fopen( argv[1], "r" );
    assert( f );

    int s = atoi( argv[2] );
    int t = atoi( argv[3] );

    int nArcs;
    int read = fscanf( f, "%d", &nArcs );
    assert( read>0 );

    int *tail, *head, *cap;
    ALLOCATE_VECTOR( tail, int, nArcs*3 ); 
    head = tail + nArcs;
    cap = head + nArcs;

    for ( int i=0 ; (i<nArcs) ; ++i )
    {
        read = fscanf( f, "%d %d %d", &tail[i], &head[i], &cap[i] );
        assert( read==3 );
    }

    MinCut *minc = minc_create( nArcs, tail, head, cap, s, t );

    int flow = minc_optimize( minc );
    printf( "min cut has capacity %d\n", flow );
    printf("arcs:\n");

    for ( int i=0 ; (i<minc_n_cut(minc)) ; ++i )
        printf( "\t%d->%d\n", minc_cut_arc_source( minc, i ), minc_cut_arc_destination( minc, i ) );

    minc_free( &minc );

    free( tail );
    fclose( f );
    
    return 0;
}
