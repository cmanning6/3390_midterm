// github repo: https://github.com/cmanning6/3390_midterm.git
//
//
//Author: Gordon Griesel
//Date: April 7, 2019
//
//Modified by  : Chad Manning
//Modified date: April 11th, 2019
//
//Purpose: Framework for a coding exam
//
//See instructions on assignment web page to produce a unit-test
//for the vec_length function.
//
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#ifdef UNIT_TEST
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
using namespace std;
#endif

//type defines
typedef double Flt;
typedef Flt Vec[3];

//prototype
Flt vec_length(Vec v);

//Array of vector values
const Flt arr[] = {
   1.0,   0.0,
   1.0,   1.0,
  -1.2,   2.5,
  99.9,  99.9,
   2.2,  -1.2,
   0.0,   0.0
};

/*
*	Function that reads data from a CSV into a 2-D vector.
*/
#ifdef UNIT_TEST
void readCSV(vector< vector<double>>& db, vector< vector <double>>& pDB, string filename)
{
	ifstream file;
    file.open(filename);

	string line="", val="";
    int i = -1;
	while (getline(file, line)) {
		stringstream iss(line);
        db.push_back(vector<double>());
        ++i;
		while (getline(iss, val, '\t')) {
			db[i].push_back(atof(val.c_str()));
		}
	}
    for (unsigned int i = 0; i < db.size(); i++) {
        pDB.push_back(vector<double>());
        pDB[i].push_back(db[i][2]);
        pDB[i].push_back(db[i][3]);
        pDB[i].push_back(db[i][4]);
    }
}
#endif

int main(int argc, char *argv[])
{
    printf("                                    \n");
    printf("3350 software engineering           \n");

    #ifdef UNIT_TEST
    string filename = "data.txt";
    vector< vector<double>> actualV;
    vector< vector <double>> knownV;
    double tolerance = atof(argv[1]);
    int errors = 0;
    readCSV(actualV, knownV, filename);
    printf("\nBegin Unit Test of vec_length()\n");
    printf("Tolerance = %.2f\n\n\n", tolerance);
    #endif

    //Program to calculate vector normalization and length.
	//


    //read until sentinel found.
    unsigned int i=0;

    //Pre processor directive runs the original program or the unit test
    // depending on which file is run
    #ifndef UNIT_TEST
    printf("                                    \n");
    printf("Calculation of vector lengths:      \n");
    printf("                                    \n");
    printf("     x         y         length     \n");
    printf("     --------  --------  ---------- \n");

    Vec v = { arr[i*2+0], arr[i*2+1] };
    do {
        Flt ret = vec_length(v);

        printf("%3i  %8.5lf  %8.5lf  %10.5lf\n", i+1, v[0], v[1], ret);
        ++i;
        v[0] = arr[i*2+0];
        v[1] = arr[i*2+1];
    } while (!(v[0]==0.0 && v[1]==0.0));

    printf("\n\nProgram complete.\n\n");
    #endif

    #ifdef UNIT_TEST
    printf("     x         y         length     actual\n");
    printf("     --------  --------  ---------- ----------\n");

    Vec v = {actualV[0][0], actualV[0][1]};
        do {
        Flt ret = vec_length(v);

        printf("%3i  %8.5lf  %8.5lf  %10.5lf %10.5lf",
                 i+1, v[0], v[1], ret, knownV[i][2]);
        //If the difference is more than the tolerance then there was an
        // error
        if (abs(knownV[i][2] - ret) > tolerance) {
            ++errors;
            printf("  <--- ERROR\n");
        } else {
            printf("\n");
        }

        ++i;
        v[0] = actualV[i][0];
        v[1] = actualV[i][1];
    } while (i < actualV.size() - 1);

    printf("\n\nUnit Test complete.\n");
    printf("%d errors\n\n", errors);
    #endif

    return 0;
}

Flt vec_length(Vec v)
{
    //Normalize a vector.
    //Return the original length of the vector.
    //
    //input: the 2 components of a vector
    //output: the pre-normalized vector length is returned
    //        the vector argument is scaled to a length of 1.0
    //
    //A degenerate vector causes an error condition.
    //It will return a length of 0.0
    //and an arbitrary vector with length 1.0.
    //
    //calculate the vector dot product with itself...
    Flt dot = v[0]*v[0] + v[1]*v[1];
    //check for degenerate vector...
    if (dot == 0.0) {
        //set an arbitrary vector of length 1.0
        //printf("ERROR vector magnitude is zero.\n");
        v[0] = 1.0;
        v[1] = 0.0;
        return 0.0;
    }
    //vector has a magnitude so continue.
    Flt len = sqrt(dot);
    Flt oolen = 1.0 / len;
    v[0] *= oolen;
    v[1] *= oolen;
    return len;
}

