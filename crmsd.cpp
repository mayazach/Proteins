#include<iostream>
#include <cmath>
#include <Eigen/Dense>
#include<Eigen/SVD>
#include"curve.h"
#include "crmsd.h"
#include "distance.h"


using namespace std;
using namespace Eigen;
int dim=3;

double crmsd(Curve a,Curve b){
   int i;
   int j;
   double result;
   //cout<<"crmsd begins!!\n";

   int n=2;
   int m1;
   int m2;
   
   if((a.m)<(b.m))
   {
      n=a.m;
   }
   else
   {
      n=b.m;

   }
   //cout<<"ok1\n";
   MatrixXd x(n,dim);
   MatrixXd y(n,dim);
   //cout<<"ok2\n";
   /*x<<0, 1, 2 ,1 ,4, 1;*/
   /*gia kathe kabulh lamvanoume ypopsi ta n prwta simeia*/
   for(i=0;i<n;i++)
   {  
      for(j=0;j<dim;j++)
      {  
         /*cout<<"x["<<i<<"]"<<"["<<j<<"]"<<"\n";*/
         x(i,j)=a.points[i][j];   
      
      }
   }
   for(i=0;i<n;i++)
   {
      for(j=0;j<dim;j++)
      {
         y(i,j)=b.points[i][j];

      }

   }
   //cout<<"first n points of curves\n";
   /*cout<<"x="<<x<<"\n";
   cout<<"y="<<y<<"\n";*/

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



   /*cout<<x;

   cout<<"\n";

   cout<<mult;

   cout<<"\n";

   cout<<"xc="<<xc;

   cout<<"\n";

   cout<<y;

   cout<<"\n";

   cout<<"yc="<<yc;

   cout<<"\n";*/

   MatrixXd pin(n,dim);
   VectorXd v(dim);
   v<< xc(0,0),xc(0,1),xc(0,2);
   x=x.rowwise()-v.transpose();

   v<<yc(0,0),yc(0,1),yc(0,2);
   y=y.rowwise()-v.transpose();

   /*cout<<"pin=x-xc=\n"<<x;


   cout<<"\n";

   cout<<"pin=y-yc=\n"<<y<<"\n";*/


   MatrixXd z(dim,dim);
   z=x.transpose()*y;

   //cout<<"x.transpose()*y=\n"<<z<<"\n";


   JacobiSVD<MatrixXd> svd(x.transpose()*y,ComputeThinU|ComputeThinV);
   /*cout<<"Its singular values are:\n"<<svd.singularValues()<<"\n";

   cout<<"Its left singular vectors are the columns of the thin U matrix:\n"<<svd.matrixU()<<"\n";

   cout<<"Its left singular vectors are the columns of the thin V matrix:\n"<<svd.matrixV()<<"\n";
   
   


   cout<<"\n";*/
   MatrixXd q(dim,dim);
   q=svd.matrixU()*svd.matrixV().transpose();
   double det=q.determinant();
   
   /*cout<<"q="<<q<<"\n";
   cout<<"det="<<det<<"\n";*/

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
   
   //cout<<"Its left singular vectors are the columns of the thin U matrix:(modified if det<0)\n"<<umd<<"\n";
   
   

   MatrixXd temp(n,dim);
   MatrixXd temp1(n,dim);
   temp=x*q;
   temp1=temp-y;
   /*cout<<"temp1="<<temp1<<"\n";*/
   result=temp1.norm();
   result=result/sqrt(n);
   /*cout<<"crmsd result="<<result<<"\n";*/
   


   return result;
   /*return 2;*/
}

double cfrechet(Curve a,Curve b){
   int i,j,m1,m2,n=2;
   double result;
   
   if((a.m)<(b.m))
      n=a.m;
   else
      n=b.m;
   
   MatrixXd x(n,dim);
   MatrixXd y(n,dim);
   
   for(i=0;i<n;i++){  
      for(j=0;j<dim;j++){  
         x(i,j)=a.points[i][j];   
      }
   }
   for(i=0;i<n;i++){
      for(j=0;j<dim;j++){
         y(i,j)=b.points[i][j];
      }
   }

   MatrixXd mult(1,n);
   /*mult << 1, 1;*/
   for(i=0;i<n;i++){
      mult(i)=1;
   }
   MatrixXd xc(1,3);
   xc=(mult*x)/n;
   MatrixXd yc(1,3);
   yc=(mult*y)/n;

   MatrixXd pin(n,dim);
   VectorXd v(dim);
   v<< xc(0,0),xc(0,1),xc(0,2);
   x=x.rowwise()-v.transpose();

   v<<yc(0,0),yc(0,1),yc(0,2);
   y=y.rowwise()-v.transpose();

   MatrixXd z(dim,dim);
   z=x.transpose()*y;

   JacobiSVD<MatrixXd> svd(x.transpose()*y,ComputeThinU|ComputeThinV);

   MatrixXd q(dim,dim);
   q=svd.matrixU()*svd.matrixV().transpose();
   double det=q.determinant();
   MatrixXd umd(dim,dim);
   umd=svd.matrixU();
  
   if(det<0){
     for(i=0;i<dim;i++){
        for(j=0;j<(dim-1);j++){
            umd(i,j)=umd(i,j);
        }
        umd(i,j)=umd(i,j)*(-1);
     }
     q=umd*svd.matrixV().transpose();
   }

   MatrixXd xq(n,dim);
   xq=x*q;
   Curve xcurve,ycurve;
   xcurve.dimension = dim;
   ycurve.dimension = dim;
   xcurve.m = n;
   ycurve.m = n;
   xcurve.points = new double*[xcurve.m];
   ycurve.points = new double*[ycurve.m];
   for(i=0;i<n;i++){
	xcurve.points[i] = new double[xcurve.dimension];
        ycurve.points[i] = new double[ycurve.dimension];
   }
   for(i=0;i<n;i++){
	for(j=0;j<dim;j++){
		xcurve.points[i][j] = xq(i,j);
		ycurve.points[i][j] = y(i,j);
	}
   }
   result = dfd(&xcurve,&ycurve);
   for(i=0;i<n;i++){
	delete [] xcurve.points[i];
        delete [] ycurve.points[i];
   }
   delete [] xcurve.points;
   delete [] ycurve.points;
   return result;
} 

