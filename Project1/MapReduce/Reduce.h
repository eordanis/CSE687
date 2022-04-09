/********************************************************
* Reduce.h -	   
* CSE687 SP22  
* Stephanie Eordanidis & JT Washington
*********************************************************/
#ifndef __REDUCE_H_INCLUDED__
#define __REDUCE_H_INCLUDED__
#pragma once
#include<string>  
#include<iterator>
#include<vector>
using namespace std;

class Reduce
{
public: void reduce(string key, vector<int>::iterator counts);
public: void exporter(string key, int count);
};
#endif

