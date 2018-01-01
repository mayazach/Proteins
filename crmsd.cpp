#include<iostream>
#include <Eigen/Dense>
#include<Eigen/SVD>
#include"curve.h"

using namespace std;
using namespace Eigen;
int dim=3;

/*tropos gia na dinw times sta stoixeia tou pinaka*/
/*mult(0,1)=0;*/

/*int main()
{

int n=2;
MatrixXf a(n,dim);
a << 1, 2, 3, 4, 5, 6;

MatrixXf mult(1,n);
mult << 1, 1;

MatrixXf xc(1,3);
xc=(mult*a)/n;




MatrixXf b(n,dim);
b<< 3, 4, 5, 6, 7, 8;

MatrixXf yc(1,3);
yc=(mult*b)/n;



cout<<a;

cout<<"\n";

cout<<mult;

cout<<"\n";

cout<<"xc="<<xc;

cout<<"\n";

cout<<b;

cout<<"\n";

cout<<"yc="<<yc;

cout<<"\n";

MatrixXf pin(n,dim);
VectorXf v(dim);
v<< xc(0,0),xc(0,1),xc(0,2);
pin=a.rowwise()-v.transpose();

cout<<"pin=a-xc="<<pin;

cout<<"\n";



}
*/

/*int main()
{

int n=2;
MatrixXf x(n,dim);
x<<0, 1, 2 ,1 ,4, 1;

MatrixXf mult(1,n);
mult << 1, 1;

MatrixXf xc(1,3);
xc=(mult*x)/n;



MatrixXf y(n,dim);
y<<3 ,5, 7, 12, 16, 1;
MatrixXf yc(1,3);
yc=(mult*y)/n;



cout<<x;

cout<<"\n";

cout<<mult;

cout<<"\n";

cout<<"xc="<<xc;

cout<<"\n";

cout<<y;

cout<<"\n";

cout<<"yc="<<yc;

cout<<"\n";

MatrixXf pin(n,dim);
VectorXf v(dim);
v<< xc(0,0),xc(0,1),xc(0,2);
x=x.rowwise()-v.transpose();

v<<yc(0,0),yc(0,1),yc(0,2);
y=y.rowwise()-v.transpose();

cout<<"pin=x-xc=\n"<<x;


cout<<"\n";

cout<<"pin=y-yc=\n"<<y<<"\n";


MatrixXf z(dim,dim);
z=x.transpose()*y;

cout<<"x.transpose()*y=\n"<<z<<"\n";


JacobiSVD<MatrixXf> svd(x.transpose()*y,ComputeThinU|ComputeThinV);
cout<<"Its singular values are:\n"<<svd.singularValues()<<"\n";

cout<<"Its left singular vectors are the columns of the thin U matrix:\n"<<svd.matrixU()<<"\n";

cout<<"Its left singular vectors are the columns of the thin V matrix:\n"<<svd.matrixV()<<"\n";




cout<<"\n";



}
*/

double crmsd(Curve* a,Curve* b)
{
   int i;
   int j;
   cout<<"crmsd begins!!\n";

   int n=2;
   int m1;
   int m2;
   
   if((a->m)<(b->m))
   {
      n=a->m;
   }
   else
   {
      n=b->m;

   }
   cout<<"ok1\n";
   MatrixXd x(n,dim);
   MatrixXd y(n,dim);
   cout<<"ok2\n";
   /*x<<0, 1, 2 ,1 ,4, 1;*/
   /*gia kathe kabulh lamvanoume ypopsi ta n prwta simeia*/
   for(i=0;i<n;i++)
   {  
      for(j=0;j<dim;j++)
      {  
         cout<<"x["<<i<<"]"<<"["<<j<<"]"<<"\n";
         x(i,j)=a->points[i][j];   
      
      }
   }
   for(i=0;i<n;i++)
   {
      for(j=0;j<dim;j++)
      {
         y(i,j)=b->points[i][j];

      }

   }
   cout<<"first n points of curves\n";
   cout<<"x="<<x<<"\n";
   cout<<"y="<<y<<"\n";

   MatrixXd mult(1,n);
   /*mult << 1, 1;*/
   for(i=0;i<n;i++)
   {
      mult(i)=1;


   }
   MatrixXd xc(1,3);
   xc=(mult*x)/n;



   /*MatrixXf y(n,dim);
   y<<3 ,5, 7, 12, 16, 1;*/
   MatrixXd yc(1,3);
   yc=(mult*y)/n;



   cout<<x;

   cout<<"\n";

   cout<<mult;

   cout<<"\n";

   cout<<"xc="<<xc;

   cout<<"\n";

   cout<<y;

   cout<<"\n";

   cout<<"yc="<<yc;

   cout<<"\n";

   MatrixXd pin(n,dim);
   VectorXd v(dim);
   v<< xc(0,0),xc(0,1),xc(0,2);
   x=x.rowwise()-v.transpose();

   v<<yc(0,0),yc(0,1),yc(0,2);
   y=y.rowwise()-v.transpose();

   cout<<"pin=x-xc=\n"<<x;


   cout<<"\n";

   cout<<"pin=y-yc=\n"<<y<<"\n";


   MatrixXd z(dim,dim);
   z=x.transpose()*y;

   cout<<"x.transpose()*y=\n"<<z<<"\n";


   JacobiSVD<MatrixXd> svd(x.transpose()*y,ComputeThinU|ComputeThinV);
   cout<<"Its singular values are:\n"<<svd.singularValues()<<"\n";

   cout<<"Its left singular vectors are the columns of the thin U matrix:\n"<<svd.matrixU()<<"\n";

   cout<<"Its left singular vectors are the columns of the thin V matrix:\n"<<svd.matrixV()<<"\n";
   
   


   cout<<"\n";
   MatrixXd q(dim,dim);
   q=svd.matrixU()*svd.matrixV().transpose();
   double det=q.determinant();
   
   cout<<"q="<<q<<"\n";
   cout<<"det="<<det<<"\n";

   /*umd->U modified*/
   MatrixXd umd(dim,dim);
   umd=svd.matrixU();

   /*det<0->xrisimopoieitai o U modified*/
   /*dokimastika thetw thn det arnitikh gia na dw an leitourgei*/
   /*det=-2;*/
  
   if(det<0)
   {
     for(i=0;i<dim;i++)
     {
        for(j=0;j<(dim-1);j++)
        {
            umd(i,j)=umd(i,j);
        
        }
        /*j=dim-1,dil teleutaia stilh tou pinaka*/
        umd(i,j)=umd(i,j)*(-1);
        
     }
    

    /*ypoligizetai kasana o pinakas q*/
     q=umd*svd.matrixV().transpose();

   }

   cout<<"Its left singular vectors are the columns of the thin U matrix:(modified if det<0)\n"<<umd<<"\n";
 

   
     

  
  





   
  
      



   return 2;


}


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
  


 
  Curve* p=new Curve();
  p->m=4;
  p->dimension=3;
  p->points=new double*[(p->m)];
  for(i=0;i<(p->m);i++)
  {
     p->points[i]=new double[p->dimension];
  
  }

 
  Curve* q =new Curve();
  q->m=4;
  q->dimension=3;
  q->points=new double*[(q->m)];
  for(i=0;i<(q->m);i++)
  {
     q->points[i]=new double[p->dimension];


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


  p->points[0][0]=0;
  p->points[0][1]=1;
  p->points[0][2]=2;
  p->points[1][0]=1;
  p->points[1][1]=4;
  p->points[1][2]=1;
  p->points[2][0]=3;
  p->points[2][1]=5;
  p->points[2][2]=4;
  /*dokimastika prosthetw kai 4o simeio*/        
  p->points[3][0]=2;
  p->points[3][1]=7;
  p->points[3][2]=9;


  q->points[0][0]=3;
  q->points[0][1]=5;
  q->points[0][2]=7;
  q->points[1][0]=12;
  q->points[1][1]=16;
  q->points[1][2]=1;
  q->points[2][0]=2;
  q->points[2][1]=8;
  q->points[2][2]=7;
  /*dokimastika prosthetw kai 4o simeio*/
  q->points[3][0]=1;
  q->points[3][1]=6;
  q->points[3][2]=5;




  cout<<"klish crsmd\n";



  result=crmsd(p,q);

 



}


