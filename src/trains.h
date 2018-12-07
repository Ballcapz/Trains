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
        // print the service for the station that the user chooses (the id)
        void print_one_schedule(vector<string> stationNames, int id);
        // direct service from station 1 to station 2
        void direct_service_available(vector<string> stationNames, int s1, int s2);
        // search for any available route between stations (do a bfs from src to dst)
        bool service_available(int src, int dst);
        // shortest riding time on the train
        int shortest_riding_time(vector<string> stationNames, int src, int dst);
        // shortest overall travel time
        void shortest_total_time(vector<string> stationNames, int src, int dst);
        // helper for shortest time funcs
        int minDistance(int dist[], bool Marked[]);



        


private:
        int node_count;
        Edge **data;


};


#endif


















