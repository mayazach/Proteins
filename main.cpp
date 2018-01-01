#include <iostream>
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <sstream>
#include <limits>
#include <ctime>
#include "curveList.h"
#include "distance.h"
#include "randomnum.h"
#include "hash.h"
#include "gridcurves.h"
#include "kfunctions.h"
#include "kmeans_initialization.h"
#include "binaryTree.h"

using namespace std;

int main(int argc, char** argv){
	ifstream input;
	ofstream output;
	int numConform,n,dimension=3,i,j;
	stringstream ss;
	Curve c;
	CurveList mylist;
	Curve* curveArray;

	input.open("bio_small_input.dat");

	if(input.fail()){
		cerr << "Error opening file" << endl;
		return 1;
	}
	input >> numConform >> n;
	c.dimension = 3;
	c.m = n;
	for(i=0;i<numConform;i++){
		ss.str("");
		ss << i;
		ss >> c.id;
		ss.clear();
		c.points = new double*[c.m];
		for(j=0;j<c.m;j++)
			c.points[j] = new double[c.dimension];
		for(j=0;j<n;j++)
			input >> c.points[j][0] >> c.points[j][1] >> c.points[j][2];
		c.inDataset = true;
		mylist.push(c);
	}
	curveArray = new Curve[numConform];
	for(i=0;i<numConform;i++)
		curveArray[i] = mylist.remove();
	
	for(i=0;i<numConform;i++)
		curvePrint(curveArray[i]);

	for(i=0;i<numConform;i++){
		for(j=0;j<curveArray[i].m;j++)
			delete [] curveArray[i].points[j];
		delete [] curveArray[i].points;
	}
	delete [] curveArray;
	input.close();
}
