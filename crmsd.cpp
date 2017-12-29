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

int main()
{

int n=2;
MatrixXf x(n,dim);
/*x << 1, 2, 3, 4, 5, 6;*/
x<<0, 1, 2 ,1 ,4, 1;

MatrixXf mult(1,n);
mult << 1, 1;

MatrixXf xc(1,3);
xc=(mult*x)/n;



MatrixXf y(n,dim);
/*y<< 3, 4, 5, 6, 7, 8;*/
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

/*SVD*/
JacobiSVD<MatrixXf> svd(x.transpose()*y,ComputeThinU|ComputeThinV);
cout<<"Its singular values are:\n"<<svd.singularValues()<<"\n";

cout<<"Its left singular vectors are the columns of the thin U matrix:\n"<<svd.matrixU()<<"\n";

cout<<"Its left singular vectors are the columns of the thin V matrix:\n"<<svd.matrixV()<<"\n";




cout<<"\n";



}

