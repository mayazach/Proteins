#include<iostream>
#include"curve.h"
#include"crmsd.h"


using namespace std;

int main()
{
cout<<"new main\n";
double result;

/*func_result=crmsd();*/

/*x<<0, 1, 2 ,1 ,4, 1;*/
/*y<<3 ,5, 7, 12, 16, 1;*/
/*dokimasrikh main pou apla tha kalei th synartish*/
  int i;
  int j;
  


 
  Curve p;
  p.m=4;
  p.dimension=3;
  p.points=new double*[(p.m)];
  for(i=0;i<(p.m);i++)
  {
     p.points[i]=new double[p.dimension];
  
  }

 
  Curve q;
  q.m=4;
  q.dimension=3;
  q.points=new double*[(q.m)];
  for(i=0;i<(q.m);i++)
  {
     q.points[i]=new double[p.dimension];


  }

/*
  p->points[0][0]=0;
  p->points[0][1]=1;
  p->points[1][0]=1;
  p->points[1][1]=1;

  q->points[0][0]=0;
  q->points[0][1]=2;
  q->points[1][0]=1;
  q->points[1][1]=4;
*/

  /*x<<0, 1, 2 ,1 ,4, 1;*/
/*y<<3 ,5, 7, 12, 16, 1;*/


  p.points[0][0]=0;
  p.points[0][1]=1;
  p.points[0][2]=2;
  p.points[1][0]=1;
  p.points[1][1]=4;
  p.points[1][2]=1;
  p.points[2][0]=3;
  p.points[2][1]=5;
  p.points[2][2]=4;
  /*dokimastika prosthetw kai 4o simeio*/        
  p.points[3][0]=2;
  p.points[3][1]=7;
  p.points[3][2]=9;


  q.points[0][0]=3;
  q.points[0][1]=5;
  q.points[0][2]=7;
  q.points[1][0]=12;
  q.points[1][1]=16;
  q.points[1][2]=1;
  q.points[2][0]=2;
  q.points[2][1]=8;
  q.points[2][2]=7;
  /*dokimastika prosthetw kai 4o simeio*/
  q.points[3][0]=1;
  q.points[3][1]=6;
  q.points[3][2]=5;

  

  cout<<"klish crsmd\n";



  result=crmsd(p,q);

}
