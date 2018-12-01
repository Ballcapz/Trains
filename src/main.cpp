#include <iostream>
#include <fstream>
#include <cstddef>
#include <string>
#include <vector>
#include <algorithm>
#include "trains.h"


using namespace std;


int main(int argc, char** argv)
{
        TRAINS *t = NULL;
        std::ifstream input;
        std::ifstream scheduleInput;
        int cmd, argument;
        string station;
        vector<int> stationList;
        vector<string> stationNames;

        if (argc < 3)
        {
                std::cout << "usage: ./a.out <stations.dat> <routes.dat>\n";
                return 0;
        }

        input.open(argv[1]);

        while (true)
        {

                input >> argument;
                input >> station;
                if (input.eof() ) break;
                stationList.push_back(argument);
                stationNames.push_back(station);

        }


        input.close();


        int numberOfNodes = stationList.size();

        t = new TRAINS(numberOfNodes);

//void TRAINS::set_edge(int source, int destination, int w, int depart, int arrive)
// need to read the second file and set edges

        scheduleInput.open(argv[2]);
        int src, dst, depart, arrive, weight;


       while (true)
        {
                scheduleInput >> src;
                scheduleInput >> dst;
                scheduleInput >> depart;
                scheduleInput >> arrive;
                if (scheduleInput.eof() ) break;
                weight = arrive - depart; 
                t->set_edge(src, dst, weight, depart, arrive);


        }

        scheduleInput.close();

// TESTING
        t->print_complete_schedule(stationNames);
        
        cout << endl << endl;

        t->print_one_schedule(stationNames, 3);

        cout << "Enter station name: ";
        string key;
        cin >> key;

        // Look up the station's id
        
        vector<string>::iterator itr = find(stationNames.begin(), stationNames.end(), key);

        if (itr != stationNames.cend()) 
        {
                cout << key << "'s station id is " << distance(stationNames.begin(), itr);
        }
        else
        {
                cout << key << " is not a station" << endl;
        }

        cout << endl << endl;



        return 0;

}






