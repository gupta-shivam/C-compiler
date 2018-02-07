#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lex.h"
#include "lex1.c"

char* symbol_table[1024];
int tail = 0;
int rel_jmp=0;
FILE *fp, *fp2;

int search(char* a)
{
	int t=0;
	while(t < tail)
	{
		if(strcmp(symbol_table[t], a) == 0)
			return t;
		t++;
	}
	return -1;
}

int get_symbol_mem()
{
	char subbuff[yyleng+1];
	int memory_no;
    memcpy( subbuff, yytext, yyleng );
    subbuff[yyleng] = '\0';
	memory_no = search(subbuff);
	if(memory_no == -1)
	{
		symbol_table[tail] = (char *)malloc(yyleng+1);
		memcpy( symbol_table[tail], subbuff, yyleng+1 );
    	fprintf(fp2, "MVI A, 0\n");
    	fprintf(fp2, "STA %d\n", tail*2+610);
    	memory_no = tail;
		tail++;
	}
	return memory_no*2+610;
}

int get_register_no()
{
	return ((*(yytext+1)-48)*2)+600;
}

int get_no()
{
	
    char subbuff[yyleng+1];
    memcpy( subbuff, yytext, yyleng );
    subbuff[yyleng] = '\0';
	return atoi(subbuff);
}


void generate()
{
	while( !match (EOI) )
	{
		if ( match(LABELID) )
		{
			//print label
			fprintf(fp2, "%s", yytext);
			advance();
		}
		else if( match(GOTO) )
		{
			advance();
			// get label string
			// print JP label
			fprintf(fp2, "JMP %s",yytext);
			advance();
		}
		else if( match(IFZ) )
		{
			advance();
			int operand1 = get_register_no();
			// mov operand one to accumulator
			// MOV A 00
			// CMP A operand1
			//
			fprintf(fp2, "MVI AX, 1\n");
			fprintf(fp2, "CMP %d\n",operand1);
			advance();
			if( match(GOTO) )
			{
				advance();
				if( match(LABELID) )
				{
					// get_label_no
					//print jnz label1
					fprintf(fp2, "JNZ %s\n",yytext);
					// JZ Label1
					advance();
				}
				
			}
		}
		//t0 += t1/3
		//t0 -= t1/3
		//t0 *= t1/3
		//t0 /= t1/3
		//t0 = t1/3
		else if( match(TEMPID) )
		{
			int operand1 = get_register_no();
			advance();
			if(match(PLUS))
			{
				advance();
				advance();
				if(match(TEMPID))
				{
					//getregister number
					int operand2 = get_register_no();
					fprintf(fp2, "LDA %d\n", operand1);
					fprintf(fp2, "ADD %d\n",operand2);
					fprintf(fp2, "MOV %d,A\n", operand1);
					advance();
				}
				else if(match(NUM))
				{
					int curnumber = get_no();
					fprintf(fp2, "LDA %d\n", operand1);
					fprintf(fp2, "ADI %d\n",curnumber);
					fprintf(fp2, "MOV %d,A\n", operand1);
					advance();	
				}
			}
			else if(match(MINUS))
			{
				advance();
				advance();
				if(match(TEMPID))
				{
					//getregister number
					int operand2 = get_register_no();
					fprintf(fp2, "LDA %d\n", operand1);
					fprintf(fp2, "SUB %d\n",operand2);
					fprintf(fp2, "MOV %d,A\n", operand1);
					advance();
				}
				else if(match(NUM))
				{
					int curnumber = get_no();
					fprintf(fp2, "LDA %d\n", operand1);
					fprintf(fp2, "SUI %d\n",curnumber);
					fprintf(fp2, "MOV %d,A\n", operand1);
					advance();	
				}
			}
			else if(match(EQUALS))
			{
				advance();
				if(match(TEMPID))
				{
					int operand2 = get_register_no();	
					advance();
					if (match(LT))
					{
						advance();
						if(match(TEMPID))
						{
							int operand3 = get_register_no();
							printf("LDA %d\n", operand2 );
							printf("CMP %d\n", operand3 );
							printf("JC K%d\n", label);
							printf("MOV %d, 0\n", operand1 );
							label++;
							printf("JMP K%d\n", label);
							printf("K%d : MOV %d, 1\n", label-1, operand1);
							printf("K%d : 	\n", label );
							label++;
						}						
					}
					else if (match(GT))
					{
						advance();
						if(match(TEMPID))
						{
							int operand3 = get_register_no();
							printf("LDA %d\n", operand2 );
							printf("CMP %d\n", operand3 );
							printf("JC K%d\n", label);
							printf("MOV %d, 1\n", operand1 );
							label++;
							printf("JMP K%d\n", label);
							printf("K%d : MOV %d, 0\n", label-1, operand1);
							printf("K%d : 	\n", label );
							label++;
						}
					}
					else if(match(EQUALS))
					{
						advance();
						if(match(TEMPID))
						{
							int operand3 = get_register_no();
							printf("LDA %d\n", operand2 );
							printf("CMP %d\n", operand3 );
							printf("JZ K%d\n", label);
							printf("MOV %d, 1\n", operand1);
							label++;
							printf("JMP K%d\n", label);
							printf("K%d : MOV %d, 0\n", label-1, operand1);
							printf("K%d : 	\n", label );
							label++;
						}
					}
					else
					{					
						fprintf(fp2, "LDA %d\n", operand2);
						fprintf(fp2, "MOV %d,A\n", operand1);

					}
				}
				else if(match(NUM))
				{
					int curnumber = get_no();
					fprintf(fp2, "MOV %d,%d\n", operand1,curnumber);
					advance();	
				}
			}
			else if (match(TIMES))
			{
				advance();
				if(match(TEMPID))
				{
					//getregister number
					int operand2 = get_register_no();
					fprintf(fp2, "LDA %d\n", operand1);
					fprintf(fp2, "MUL %d\n",operand2);
					fprintf(fp2, "MOV %d,A\n", operand1);
					advance();
				}
				else if(match(NUM))
				{
					int curnumber = get_no();
					fprintf(fp2, "LDA %d\n", operand1);
					fprintf(fp2, "MLI %d\n",curnumber);
					fprintf(fp2, "MOV %d,A\n", operand1);
					advance();	
				}
			}
			else if (match(DIVIDE))
			{
				advance();
				if(match(TEMPID))
				{
					//getregister number
					int operand2 = get_register_no();
					fprintf(fp2, "LDA %d\n", operand1);
					fprintf(fp2, "DIV %d\n",operand2);
					fprintf(fp2, "MOV %d,A\n", operand1);
					advance();
				}
				else if(match(NUM))
				{
					int curnumber = get_no();
					fprintf(fp2, "LDA %d\n", operand1);
					fprintf(fp2, "DVI %d\n",curnumber);
					fprintf(fp2, "MOV %d,A\n", operand1);
					advance();	
				}
			}
		}
		// _a = t0
		else if(match(ID))
		{
			int operand1 = get_symbol_mem();
			advance();
			if (match(EQUALS))
			{
				advance();
				if (match(TEMPID))
				{
					int operand2 = get_register_no();
					fprintf(fp2, "LDA %d\n",operand2 );
					fprintf(fp2, "STA %d\n",operand1 );
					advance();
				}
			}
		}		
	}
}

int main()
{
	fp = fopen("3addr.txt", "r");
	fp2 = fopen("8086.txt", "w");
	generate();
	fprintf(fp2, "HLT");
	fclose(fp);
	fclose(fp2);
}