#include <iostream>
#include <fstream>
#include <cstddef>
#include <string>
#include <vector>
#include <algorithm>
#include "trains.h"


using namespace std;


void station_id_lookup();
void station_name_lookup();


int main(int argc, char** argv)
{
        TRAINS *t = NULL;
        std::ifstream input;
        std::ifstream scheduleInput;
        int cmd, argument;
        string station;
        vector<int> stationList;
        vector<string> stationNames;
        // Check for the correct number of files when starting the program
        if (argc < 3)
        {
                std::cout << "usage: ./a.out <stations.dat> <routes.dat>\n";
                return 0;
        }
        
        // open, read, store and close the file of stations
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

        // initialize the graph and set the number of nodes in the graph
        int numberOfNodes = stationList.size();

        t = new TRAINS(numberOfNodes);

//void TRAINS::set_edge(int source, int destination, int w, int depart, int arrive)
// need to read the second file and set edges

        // open, read, write, and close the file of routes
        scheduleInput.open(argv[2]);
        // temp values to store the file data in each line
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


        // Main driver of the program, ask user for input then make a decison
        // based on what they entered
        
        // bool to track the running of the program
        bool isRunning = true;
        // int to retrieve command from the user
        int command;
        // ints to get prompts from user if need be
        int s1, s2;
               // print one time at the top of the scheduler 
                cout << "**********************************************************" << endl;
                cout << "                  DBE RAILWAYS SHCEDULER                  " << endl;
                cout << "**********************************************************" << endl;
                cout << "Options - (Enter the number of your selected option)" << endl;
                cout << "(1) - Print full schedule" << endl;
                cout << "(2) - Print station schedule" << endl;
                cout << "(3) - Look up stationd id" << endl;
                cout << "(4) - Look up station name" << endl;
                cout << "(5) - Service available" << endl;
                cout << "(6) - Nonstop service available" << endl;
                cout << "(7) - Find route (Shortest riding time)" << endl;
                cout << "(8) - Find route (Shortest overall travel time)" << endl;
                cout << "(9) - Exit" << endl;

        while (isRunning)
        {
                cout << "Enter Option: ";
                cin >> command;
                // if the command is not an integer reprompt the loop
                if (cin.fail())
                        continue;
                // reprompt if it is an invalid int
                if (command < 1 || command > 9)
                {
                        cout << endl << "Please enter an integer 1-9" << endl;
                        continue;
                }
                
                // chooses what is happening in the scheduler
                switch (command){
                        case 1:
                                t->print_complete_schedule(stationNames); 
                                break;
                        case 2:
                                cout << "Enter Station Id: ";
                                cin >> s1;
                                // if the command is not an integer reprompt the loop
                                if (cin.fail())
                                        continue;
                                // reprompt if it is an invalid int
                                if (command < 1 || command > numberOfNodes)
                                {
                                        cout << endl << "Not a valid station ID" << endl;
                                        continue;
                                }
                                // MAKE SURE TO CHANGE THE VALUE IN THE FUNCTION BY ONE TO REFERENCE THE STATIONS CORRECTLY!!!! 
                                t->print_one_schedule(stationNames, s1);
                                break;
                        case 3:
                                station_id_lookup();
                                break;
                        case 4:
                                station_name_lookup();
                                break;
                        case 5:

                                break;

                }   // end of switch
                


        }


// TESTING
//      // Print the complete schedule
        t->print_complete_schedule(stationNames);
        
        cout << endl << endl;
        // Print the schedule for one station (station 3 currently)
        t->print_one_schedule(stationNames, 3);
//
//      Lookup the id of a station name *************************************
        station_id_lookup();
// ***************************************************************************
        cout << endl << endl;

        // look up the station's name
        station_name_lookup();
        cout << endl << endl;
        /////////////////////////////




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


void station_id_lookup()
{
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

}

void station_name_lookup()
{
        cout << "Enter station id: ";
        int sId;
        cin >> sId;
        if (cin.fail())
        {   
                cout << "Sorry, you did not enter a station id" << endl;
                return;
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


}
















