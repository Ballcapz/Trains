#include <iostream>
#include <fstream>
#include <cstddef>
#include <string>
#include <vector>
#include <algorithm>
#include "trains.h"


using namespace std;


void station_id_lookup(vector<string> stationNames);
void station_name_lookup(vector<string> stationNames, int numberOfNodes);


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
                cout << flush;
                cout << "Enter Option: ";
                cin >> command;
                // if the command is not an integer reprompt the loop
                if (cin.fail())
                {
                        cin.clear();
                        cin.ignore();
                        continue;
                }
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
                                {
                                        cin.clear();
                                        cin.ignore();
                                        continue;
                                }
                                // reprompt if it is an invalid int
                                if (s1 < 1 || s1 > numberOfNodes)
                                {
                                        cout << endl << "Not a valid station ID" << endl;
                                        continue;
                                }
                                t->print_one_schedule(stationNames, s1);
                                break;
                        case 3:
                                station_id_lookup(stationNames);
                                cout << endl << endl;
                                break;
                        case 4:
                                station_name_lookup(stationNames, numberOfNodes);
                                break;
                        case 5:                         // service available

                                cout << "Station 1's id: ";
                                cin >> s1;
                                if (cin.fail())
                                {
                                        cin.clear();
                                        cin.ignore();
                                        continue;
                                }
                                cout << "Station 2's id: ";
                                cin >> s2;
                                
                                if (cin.fail())
                                {
                                        cin.clear();
                                        cin.ignore();
                                        continue;
                                }
                                else
                                {
                                        if ((s1 > 0 && s1 <= numberOfNodes ) && (s2 > 0 && s2 <= numberOfNodes))
                                        {
                                                // bool to check if service will be available at all
                                                bool isService;
                                                isService = t->service_available(s1, s2);

                                                if (isService)
                                                {
                                                        cout << "There is service between " << stationNames[s1-1] << " and " << stationNames[s2-1] << endl << endl; 
                                                }
                                                else
                                                {
                                                        cout << "NO service between " << stationNames[s1-1] << " and " << stationNames[s2-1] << endl << endl; 
                                                }
                                        }
                                        else
                                        {
                                                cout << "Not valid stations." << endl;
                                        }
                                }

                                break;
                        
                        case 6:                 // direct service available
                                cout << "Station 1's id: ";
                                cin >> s1;
                                if (cin.fail())
                                {
                                        cin.clear();
                                        cin.ignore();
                                        continue;
                                }
                                cout << "Station 2's id: ";
                                cin >> s2;
                                
                                if (cin.fail())
                                {
                                        cin.clear();
                                        cin.ignore();
                                        continue;
                                }
                                else
                                {
                                        if ((s1 > 0 && s1 <= numberOfNodes ) && (s2 > 0 && s2 <= numberOfNodes))
                                        {
                                                
                                                t->direct_service_available(stationNames, s1, s2);
                                                cout << endl;

                                        }
                                        else
                                        {
                                                cout << "Not valid stations." << endl;
                                        }
                                }

                                break;

                        case 7:                     // shortest riding time
                                int shortest_time;
                                cout << "Station 1's id: ";
                                cin >> s1;
                                if (cin.fail())
                                {
                                        cin.clear();
                                        cin.ignore();
                                        continue;
                                }
                                cout << "Station 2's id: ";
                                cin >> s2;
                                
                                if (cin.fail())
                                {
                                        cin.clear();
                                        cin.ignore();
                                        continue;
                                }
                                else
                                {
                                        if ((s1 > 0 && s1 <= numberOfNodes ) && (s2 > 0 && s2 <= numberOfNodes))
                                        {
                                                
                                                shortest_time = t->shortest_riding_time(stationNames, s1, s2); 
                                                cout << endl;

                                        }
                                        else
                                        {
                                                cout << "Not valid stations." << endl;
                                                continue;
                                        }
                                }

                                // may need to format the output (zeros/ printf?)

                                int hour;
                                int minute;

                                hour = shortest_time / 60;
                                minute = shortest_time % 60;

                                cout << "The shortest riding time between " << stationNames[0] << " and " << stationNames[3]
                                        << " is " << hour << ":" << minute << endl;
                                
                                break;
                        case 8:                              // shortest total time
                                
                                cout << "Station 1's id: ";
                                cin >> s1;
                                if (cin.fail())
                                {
                                        cin.clear();
                                        cin.ignore();
                                        continue;
                                }
                                cout << "Station 2's id: ";
                                cin >> s2;
                                
                                if (cin.fail())
                                {
                                        cin.clear();
                                        cin.ignore();
                                        continue;
                                }
                                else
                                {
                                        if ((s1 > 0 && s1 <= numberOfNodes ) && (s2 > 0 && s2 <= numberOfNodes))
                                        {
                                                
                                                t->shortest_total_time(stationNames, s1, s2);
                                                cout << endl;

                                        }
                                        else
                                        {
                                                cout << "Not valid stations." << endl;
                                                continue;
                                        }
                                }

                                
                                break;

                        case 9:
                                isRunning = false;
                                break;
                        default:
                                cout << "Enter a valid option" << endl;
                                continue;
                                break;

                }   // end of switch
                


        }       // end of main while loop



        return 0;

}


void station_id_lookup(vector<string> stationNames)
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

void station_name_lookup(vector<string> stationNames, int numberOfNodes)
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
















