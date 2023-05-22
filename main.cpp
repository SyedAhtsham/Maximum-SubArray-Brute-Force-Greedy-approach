//
//  main.cpp
//  Maximum Subarray Problem
//
//  Created by Syed Ahtsham on 11/17/20.
//  Copyright © 2020 Syed Ahtsham. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string.h>
#include <climits>
#include <stdlib.h>
#include <algorithm>    // std::shuffle
#include <array>        // std::array
#include <random>       // std::default_random_engine
#include <chrono>
#include <time.h>


using namespace std;


//Brute Force Approach Function
int MaxSubArrayBruteForce(int arr[], int n){
    int max = arr[0];
    int lower_index = 0;
    int higher_index = 1;
    int total = max;
    for(int i=0; i<n; i++)
    {

        for(int j=i+1; j<n; j++)
        {
           total = total+arr[j];
            if(max<total)
            {
                max = total;
                lower_index = i;
                higher_index = j;
            }

        }
        total = arr[i+1];
    }
    return max;
}


//Divide and Conquer Approach Algorithm Implementation
int MaxCrossing(int Arr[], int low, int high, int mid)
{
    
    int max1 = Arr[mid];
    int total = 0;
    for(int i=mid; i>=low; i--)
    {
        total = total+Arr[i];
        if(max1<total)
            max1 = total;
    }
    
    int max2 = Arr[mid+1];
    total = 0;
    for(int j=mid+1; j<high+1; j++)
    {
        total = total+Arr[j];
        if(max2<total)
        {
            max2 = total;
        }
    }
    
    return max1+max2;
    
}


//This function will return the maximum integer from three integer values
int Max(int a, int b, int c)
{
    if(a>b&&a>c)
        return a;
    if(b>a&&b>c)
        return b;
   
    return c;
        
}


//This function will return the maximum subarray using the divide and conquer paradigm
int MaxSubArrayDivConquer(int Arr[], int low, int high)
{
    int L, R, C, mid;
    if(low==high)
        return Arr[low];
    else{
        mid = (low+high)/2;
        L = MaxSubArrayDivConquer(Arr, low, mid);
        R = MaxSubArrayDivConquer(Arr, mid+1, high);
        C = MaxCrossing(Arr, low, high, mid);
    }
    
    return Max(L, R, C);
}

//This function will shuffle an array in order to make it distinct to other arrays
void shuffle_array(int arr[], int n)
{
  
   // obtain a time-based seed:
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

    shuffle (&arr[0], &arr[n-1], std::default_random_engine(seed));

}


//This function will create a file with the given name and the size of the array
void createFile(string fileName, int n)
{
    int arr[n];
    
    for(int i=0; i<n; i++)
    {
        int v2 = rand() % ((1000*2)+1) + (-1000) +1;

        arr[i] = v2;
    }
    
    shuffle_array(arr, n);
    
    ofstream myfile;

      myfile.open(fileName);
       for(int i=0; i<n; i++)
       {
           myfile<<arr[i]<<" ";
       }

           myfile.close();
    
    
}

//This function will read the file with the given fileName and insert the elements into an array
void readFile(string fileName, int arr[], int n)
{
    int i=0;
    
    ifstream myfile;
    
    myfile.open(fileName);
    
    if(myfile.is_open())
    {
        while(myfile.good())
        {
            myfile>>arr[i];
            i++;
        }
        
        myfile.close();
        
    }
    else{
        cout<<"Error opening File"<<endl;
    }
  
}


//MAIN FUNCTION

int main()
{
    

        //the files names are stored in a seperate array just to use them in array while reading files
        string filesArr[10] = {"n100.txt", "n1000.txt", "n2000.txt", "n3000.txt", "n4000.txt", "n5000.txt", "n6000.txt","n7000.txt","n8000.txt","n9000.txt" };
    
        //the sizes of each files are also stored in array to use in loop
        int sizeArr[10] = {100, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000};
        double totalArrBF[4][10] = {0};        //2d array to store the values of execution time for Brute force for multiple runs
        double totalArrDC[4][10] = {0};        //2d array to store the values of execution time for Divide and Conquer for multiple runs



        ofstream myfile;   //myfile variable to write into a file later

        myfile.open("executionTimes12.csv");    //This .csv file is comma sperated which will be opened in Excel

    
    //These will be headings of the cells in the excel file
       

        //while loop's counter
        int j=0;

        //while loop for multiple runs of the each file
        while(j<4)
        {
            myfile<<"Run No. "<<j+1<<endl;
            myfile<<"Input Size (n)"<<",";
                   myfile<<"Brute Force Approach (ms)"<<",";
                   myfile<<"Divide and Conquer Approach (ms)"<<endl;

        for(int i=0; i<10; i++)         //for loop for each file (100-9000)
        {
            //this array will be used to store the all read elements from the file
            int arr[sizeArr[i]];
            
            //file is read into an array
            readFile(filesArr[i], arr, sizeArr[i]);

            //this will write the current file size on the .csv file
            myfile<<sizeArr[i]<<",";
            
            //time function will start the timer before the start of the execution of the Brute force function
        auto start1 = chrono::steady_clock::now();
        MaxSubArrayBruteForce(arr, sizeArr[i]);

        auto end1 = chrono::steady_clock::now();
            //time function will end the timer after the execution of the Brute force function

            //taking differnce between start time and end time to get the execution time
        auto diff1 = end1 - start1;
            
            //writing the execution time of the Brute force approach on the file in terms of milli seconds
        myfile << chrono::duration <double, milli> (diff1).count()<<",";

            //here we are storing the execution time in a seperate array for taking average later on
        totalArrBF[j][i] = chrono::duration <double, milli> (diff1).count();
            
            //Time started for the Divide and conquer approach
        auto start2 = chrono::steady_clock::now();
        MaxSubArrayDivConquer(arr, 0, sizeArr[i]-1);
            //time ended for div and conquer
        auto end2 = chrono::steady_clock::now();
        auto diff2 = end2 - start2;

            //writing the execution time on file for div and conquer
        myfile << chrono::duration <double, milli> (diff2).count()  << endl;

            //storing the execution time for div and conquer in 2d array for average later on
            totalArrDC[j][i] = chrono::duration <double, milli> (diff2).count();


            }
            //incrementing the while loop counter
                j++;
            myfile<<endl;
        }


        //these two arrays for storing the total sum of the execution times for each file at each index, for taking average later on
        double totalBF[10] = {0};
        double totalDC[10] = {0};
        for (int j=0; j<4; j++) {
               for(int k=0; k<10; k++)
               {
                   totalBF[k] += totalArrBF[j][k];
                   totalDC[k] += totalArrDC[j][k];
               }

           }
        cout<<endl;
        cout<<endl;


        ofstream myfile2;

    //this file will be written with average execution time for each file
        myfile2.open("averageExecutionTimes12.csv");

    myfile2<<"Average Execution times"<<endl;
        myfile2<<"Input Size (n)"<<",";
        myfile2<<"Avg Exec Time Brute Force (ms)"<<","<<"Avg Exec Time Divide & Conquer (ms)"<<endl;
        for(int k=0; k<10; k++)
        {
            myfile2<<sizeArr[k]<<","<<totalBF[k]/4<<","<<totalDC[k]/4<<endl;
        }

        cout<<endl;


        myfile2.close();
            myfile.close();


    return 0;
}



//CODE FOR EXECUTION TIME CALCULATION
//int SIZE = 100000;
//   int arr[SIZE];
//   readFile("n100000.txt", arr, SIZE);
//
//
//       auto start1 = chrono::steady_clock::now();
//       cout<<"Max subarray Brute Force: "<< MaxSubArrayBruteForce(arr, SIZE);
//
//       auto end1 = chrono::steady_clock::now();
//
//       auto diff1 = end1 - start1;
//   cout<<endl;
//
//           cout << "Time taken: " <<chrono::duration <double, milli> (diff1).count();
//
//   cout<<endl;
//
//       auto start2 = chrono::steady_clock::now();
//       cout<<"Max Subarray Sum Divide and Conquer: " <<MaxSubArrayDivConquer(arr, 0, SIZE-1);
//       auto end2 = chrono::steady_clock::now();
//       auto diff2 = end2 - start2;
//   cout<<endl;
//
//       cout<<"Time taken: " << chrono::duration <double, milli> (diff2).count()  << endl;
//
//   cout<<endl;
//
