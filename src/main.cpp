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
//      // Print the complete schedule
        t->print_complete_schedule(stationNames);
        
        cout << endl << endl;
        // Print the schedule for one station (station 3 currently)
        t->print_one_schedule(stationNames, 3);
//
//      Lookup the id of a station name *************************************
        cout << "Enter station name: ";
        string key;
        cin >> key;

        // Look up the station's id
        
        vector<string>::iterator itr = find(stationNames.begin(), stationNames.end(), key);

        if (itr != stationNames.cend()) 
        {
                cout << key  << "'s station id is " << (distance(stationNames.begin(), itr)) + 1;
        }
        else
        {
                cout << key  << " is not a station" << endl;
        }
// ***************************************************************************


        cout << endl << endl;

        // look up the station's name
        
        cout << "Enter station id: ";
        int sId;
        cin >> sId;
        if (cin.fail())
        {   
                cout << "Sorry, you did not enter a station id" << endl;
                goto no_lookup;
        }
        else
        {
                if (sId > 0 && sId <= numberOfNodes)
                {
                        cout << sId << "'s station name is " << stationNames[sId-1] << endl << endl;
                }
                else
                {
                        cout << sId << " is not a station" << endl;
                }
        }

        no_lookup:

        cout << endl << endl;





       // determine if direct service is available between two stations 
       
        int station1_id, station2_id;
        cout << "Station 1's id: ";
        cin >> station1_id;
        if (cin.fail())
        {
                cout << "That's not a station id..." << endl;
                goto no_station;
        }
        cout << "Station 2's id: ";
        cin >> station2_id;
        
        if (cin.fail())
        {
                cout << "That's not a station id..." << endl;
                goto no_station;
        }
        else
        {
                if ((station1_id > 0 && station1_id <= numberOfNodes ) && (station2_id > 0 && station2_id <= numberOfNodes))
                {
                        t->direct_service_available(stationNames, station1_id, station2_id);
                }
                else
                {
                        cout << "Not valid stations.." << endl;
                }
        }

no_station:


// Determine if there is any service between station a and b

        cout << "Station 1's id: ";
        cin >> station1_id;
        if (cin.fail())
        {
                cout << "That's not a station id..." << endl;
                goto no_station_2;
        }
        cout << "Station 2's id: ";
        cin >> station2_id;
        
        if (cin.fail())
        {
                cout << "That's not a station id..." << endl;
                goto no_station_2;
        }
        else
        {
                if ((station1_id > 0 && station1_id <= numberOfNodes ) && (station2_id > 0 && station2_id <= numberOfNodes))
                {
                        bool isService;
                        isService = t->service_available(station1_id, station2_id);

                        if (isService)
                        {
                                cout << "There is service between " << stationNames[station1_id-1] << " and " << stationNames[station2_id-1] << endl; 
                        }
                        else
                        {
                                cout << "NO service between " << stationNames[station1_id-1] << " and " << stationNames[station2_id-1] << endl; 
                        }
                }
                else
                {
                        cout << "Not valid stations.." << endl;
                }
        }

no_station_2:

// Shortes riding time (not formatted yet)

        int shortest_time = t->shortest_riding_time(stationNames, 1, 3); 

            int hour;
            int minute;

            hour = shortest_time / 60;
            minute = shortest_time % 60;

            cout << "The shortest riding time between " << stationNames[0] << " and " << stationNames[3]
                    << " is " << hour << ":" << minute << endl;



        cout << endl;
        t->shortest_total_time(stationNames, 1, 3);




        return 0;

}




















