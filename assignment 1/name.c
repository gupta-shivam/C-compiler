#include <stdlib.h>

#define NO_OF_REG 8

char  *Names[] = { "t0", "t1", "t2", "t3", "t4", "t5", "t6", "t7" };   
char  *LabelNames[] = { "l0", "l1", "l2", "l3", "l4", "l5", "l6", "l7" };
char  **Namep  = Names;   
char  **Labelp  = LabelNames;   

char  *newname()   
{   
    if( Namep >= &Names[ sizeof(Names)/sizeof(*Names) ] )   
    {   
        fprintf( stderr, "%d: Expression too complex\n", yylineno );   
        exit( 1 );   
    }   
   
    return( *Namep++ );   
}   
   
void freename(char *s)
{   
    if( Namep > Names )   
    *--Namep = s;   
    else   
    fprintf(stderr, "%d: (Internal error) Name stack underflow\n",   
                                yylineno );   
}   

void freeall()
{
    Namep  = Names;   
}

char  *newlabel()   
{   
    if( Labelp >= &LabelNames[ sizeof(LabelNames)/sizeof(*LabelNames) ] )   
    {   
        fprintf( stderr, "%d: Expression too complex\n", yylineno );   
        exit( 1 );   
    }   
   
    return( *Labelp++ );   
}   
