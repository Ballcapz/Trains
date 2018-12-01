#ifndef TRAINS_H
#define TRAINS_H

#include <cstddef>
#include <iostream>
#include <iomanip>
#include <stack>
#include <queue>
#include <vector>
using namespace std;


struct Edge{
        int weight;
        int depart;
        int arrive;
};

class TRAINS{
public:
        // Constructor
        TRAINS(int nodes);
        // Set the edge going from src to dst
	    void set_edge(int src, int dst, int w, int depart, int arrive);
        // To use for testing
        void print_data();
        // Prints the service for all stations
        void print_complete_schedule(vector<string> stationNames);
        void print_one_schedule(vector<string> stationNames, int id);


private:
        int node_count;
        Edge **data;


};


#endif


















