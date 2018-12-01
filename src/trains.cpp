#include "trains.h"



TRAINS::TRAINS(int nodes)
{
        data = new Edge* [nodes];

        for (int i = 0; i < nodes; ++i)
        {
                data[i] = new Edge [nodes];
                for (int j = 0; j < nodes; ++j)
                {
                        data[i][j].weight = 0;
                        data[i][j].depart = 0;
                        data[i][j].arrive = 0;
                }
        }

        node_count = nodes;
}

void TRAINS::set_edge(int source, int destination, int w, int depart, int arrive)
{

        data[source - 1][destination - 1].weight =  w;
        data[source - 1][destination - 1].depart =  depart;
        data[source - 1][destination - 1].arrive =  arrive;

}


void TRAINS::print_data()
{
	cout<<endl;
	for (int i = 0; i < node_count; i++)
	{
		for (int j = 0; j < node_count; j++)
		{
			cout<<data[i][j].weight<<" ";
		}
		cout<<endl;
	}

}

void TRAINS::print_complete_schedule(vector<string> stationNames)
{
        
        cout << endl;
        for (int i = 0; i < node_count; i++)
        {
                cout << "Service for " << stationNames[i] << endl << endl;
                for (int j = 0; j < node_count; j++)
                {
                        if (data[i][j].weight != 0)
                        {
                                cout << "Departure to " << stationNames[j] << " at " << data[i][j].depart << ", arriving at " << data[i][j].arrive;
                                cout << endl << endl;
                                
                        }
                }
        }
}


void TRAINS::print_one_schedule(vector<string> stationNames, int id)
{
       cout << endl;
       cout << "Service for " << stationNames[id] << endl;
       int i = id;

       for (int j = 0; j < node_count; j++)
       {
                if (data[i][j].weight != 0)
                {
                        cout << "Departure to " << stationNames[j] << " at " << data[i][j].depart << ", arriving at " << data[i][j].arrive;
                        cout << endl << endl;
                                
                }
                
       }
}


























