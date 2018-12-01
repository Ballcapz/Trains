#include <iostream>
#include <fstream>
#include <cstddef>
#include <string>
#include <vector>
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


        t->print_complete_schedule(stationNames);
        
        cout << endl << endl;

        t->print_one_schedule(stationNames, 1);
        t->print_one_schedule(stationNames, 2);
        t->print_one_schedule(stationNames, 3);

//        t->print_data();

        return 0;

}






