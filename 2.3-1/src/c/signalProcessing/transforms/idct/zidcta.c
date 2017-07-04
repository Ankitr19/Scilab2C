/* Copyright (C) 2016 - IIT Bombay - FOSSEE

 This file must be used under the terms of the CeCILL.
 This source file is licensed as described in the file COPYING, which
 you should have received as part of this distribution.  The terms
 are also available at
 http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt
 Author: Ukasha Noor
 Organization: FOSSEE, IIT Bombay
 Email: toolbox@scilab.in
*/


#include "idct.h"
#include "addition.h"
#include "types.h"
#include "doubleComplex.h" 
/*#include "matrixMultiplication"*/
/*#include <fftw3.h>*/
#include <math.h>

void zidcta(doubleComplex *in,int row,int col,doubleComplex *out)
{
	int i,j,k,u,v;
	int n=col;
	int x,y;
	double res,ress;
	double re,z,q,m;
	doubleComplex accu = DoubleComplex(0, 0);
	doubleComplex temp,mm;
	if(row==1)
	{
		res=1./sqrt(n);
		ress=sqrt(2./n);
		for(u=0;u<row;u++)
		{
			for(v=0;v<col;v++)
			{
				x=v*row+u;
				out[x]=DoubleComplex(0,0);
				for(i=0;i<row;i++)
				{
					for(j=0;j<col;j++)
					{
						y=row*j+i;		
						if(y==0)
						{
							q=res*(cos(((M_PI)*(j)*(v+1./2.))/n));
							out[x]=zadds(out[x],in[y]*q);
						}
						else
						{
							q=ress*(cos(((M_PI)*(j)*(v+1./2.))/n));
							out[x]=zadds(out[x],in[y]*q);
						}
					}
				}
			}
				
		}
	}	
	else	
	{
		for(u=0;u<row;u++)
		{
			for(v=0;v<col;v++)
			{
				x=v*row+u;
				out[x]=DoubleComplex(0,0);
				for(i=0;i<row;i++)
				{
					re=0;
					mm=DoubleComplex(0,0);
					temp=DoubleComplex(0,0);
					for(j=0;j<col;j++)
					{
						y=row*j+i;
						mm=in[j*row+i];
						z=(double)(((double)v+1.0/2.0)*(double)j);
						q=(double)(M_PI/(double)col);	
						mm=mm*(cos(q*z));
						if(j==0)
						temp=zadds(temp,mm*(1./sqrt((double)col)));
						else
						temp=zadds(temp,mm*sqrt(2./col));
					}
					z=(double)(((double)u+1.0/2.0)*(double)i);
					q=(double)(M_PI/(double)row);	
					if(i==0)
					out[x]=zadds(out[x],temp*((cos(z*q))*(1./sqrt(row))));
					else
					out[x]=zadds(out[x],temp*((cos(z*q))*sqrt(2./row)));
				}
			}
		}
	}					
}