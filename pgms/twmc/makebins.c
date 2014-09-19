/* ----------------------------------------------------------------- 
FILE:	    makebins.c                                       
DESCRIPTION:determines number of bins for overlap calculation
CONTENTS:   makebins( INT )
DATE:	    Feb 13, 1988 
REVISIONS:
	    Feb 27, 1988 - now called from config1 and calculates
		numbins based on cell area. In future, use variance.
	    Mar  1, 1988 - added variance.
	    Nov 20, 1988 - fixed aspect ratio.
----------------------------------------------------------------- */
#ifndef lint
static char SccsId[] = "@(#) makebins.c version 3.3 9/5/90" ;
#endif

#include <custom.h>
#include <yalecad/debug.h>

makebins( numbins )
INT numbins ;
{

BINBOXPTR bptr ;
DOUBLE xbins, ybins ;
INT i, j ;

ybins = sqrt( chipaspectG * (DOUBLE) numbins ) ;
ybins = ceil( ybins ) ;
xbins = sqrt( (DOUBLE) numbins / chipaspectG ) ;
xbins = ceil( xbins ) ;

maxBinXG = (INT) xbins ;
maxBinYG = (INT) ybins ;

/* take bins for border around chip into account */
/* bins will be labeled [0..maxBinsXG] for a total of maxBinsXG+1 bins */
maxBinXG++ ;
maxBinYG++ ;
OUT2("maxBinXG automatically set to:%d\n", maxBinXG );
OUT2("maxBinYG automatically set to:%d\n", maxBinYG );

binptrG = (BINBOXPTR **)Ysafe_malloc( (1+maxBinXG)*sizeof(BINBOXPTR *)) ; 
for( i = 0 ; i <= maxBinXG ; i++ ) {
    binptrG[i]=(BINBOXPTR*) Ysafe_malloc((1+maxBinYG)*sizeof(BINBOXPTR));
    for( j = 0 ; j <= maxBinYG ; j++ ) {
	bptr = binptrG[i][j] = (BINBOXPTR) Ysafe_malloc( sizeof(BINBOX));
	bptr->cells = 
	    (INT *) Ysafe_malloc( (EXPCELLPERBIN+1) * sizeof(INT));
	/* zero position holds current number cells in bin */
	bptr->cells[0] = 0 ;
	/* space holds current size of array */
	bptr->space = EXPCELLPERBIN + 1 ;
    }
}

} /* end function make bins */
