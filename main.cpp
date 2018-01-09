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
	ofstream output,frechet;
	int numConform,n,dimension=3,i,j,k=2,size;
	int clusters = 5,changes;
	double* distances;
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
	frechet.open("frechet.dat");
	

	if(input.fail() || output.fail() || frechet.fail()){
		cerr << "Error opening file" << endl;
		return 1;
	}
	cout << arprog(5) << endl;
	cout << arprog(12) << endl;
	input >> numConform >> n;
	size = arprog(numConform);
	distances = new double[size];
	cout << size << endl;
	for(i=0;i<size;i++)
		distances[i] = -1;
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

	clusterArray = new Cluster[clusters];
	for(i=0;i<clusters;i++){
		clusterArray[i].setId(i);
		clusterArray[i].initArray(numConform);
	}
	/*
	changes = clusters;
	cout << "c-RMSD clustering" << endl;
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
	*/
	changes = clusters;
	cout << "Frechet distance clustering" << endl;
	randomK(curveArray,numConform,clusterArray,clusters);
	lloydAssignment(curveArray,numConform,clusterArray,clusters,'r',distances);
	for(i=0;i<clusters;i++){
			oldCenters[i] = clusterArray[i].getCenter().id;
	}
	while(changes > 0){
		changes = 0;
		pam(clusterArray,clusters,'r',distances,numConform);
		for(i=0;i<clusters;i++){
			if(clusterArray[i].getCenter().id != oldCenters[i])
				changes++;
			oldCenters[i] = clusterArray[i].getCenter().id;
		}
		cout << changes << endl;
		if(changes > 0)
			lloydAssignment(curveArray,numConform,clusterArray,clusters,'r',distances);
	}
	for(i=0;i<clusters;i++){
		frechet << "k: " << i << endl;
		clusterPoints = clusterArray[i].getPoints();
		for(j=0;j<clusterArray[i].getCurveNumber();j++)
			frechet << clusterPoints[j].id << "\t";
		frechet << endl;
	}

	delete [] distances;
	for(i=0;i<numConform;i++){
		for(j=0;j<curveArray[i].m;j++)
			delete [] curveArray[i].points[j];
		delete [] curveArray[i].points;
	}
	delete [] clusterArray;
	delete [] curveArray;
	input.close();
	output.close();
	frechet.close();
}
