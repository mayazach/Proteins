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
	int numConform,n,dimension=3,i,j,k=2;
	int clusters = 5,changes;
	stringstream ss;
	Curve c;
	CurveList mylist;
	Cluster* clusterArray;
	Curve* curveArray;
	string* oldCenters;
	Curve* oldCurves;
	Curve* clusterPoints;

	input.open("bio_small_input.dat");
	output.open("crmsd.dat");
	

	if(input.fail() || output.fail()){
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
	
	oldCenters = new string[clusters];
	oldCurves = new Curve[clusters];
	
	changes = clusters;
	cout << "Random-LLoyd-PAM" << endl;
	randomK(curveArray,n,clusterArray,clusters);
	lloydAssignment(curveArray,n,clusterArray,clusters,'c');
	for(i=0;i<clusters;i++){
			oldCenters[i] = clusterArray[i].getCenter().id;
	}
	while(changes > 0){
		changes = 0;
		pam(clusterArray,clusters,'c');
		for(i=0;i<clusters;i++){
			if(clusterArray[i].getCenter().id != oldCenters[i])
				changes++;
			oldCenters[i] = clusterArray[i].getCenter().id;
		}
		cout << changes << endl;
		if(changes > 0)
			lloydAssignment(curveArray,n,clusterArray,clusters,'c');
	}
	output << "k: " << clusters << endl;
	for(i=0;i<clusters;i++){
		clusterPoints = clusterArray[i].getPoints();
		for(j=0;j<clusterArray[i].getCurveNumber();j++)
			output << clusterPoints[j].id << "\t";
		output << endl;
	}
	
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
