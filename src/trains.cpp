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


void TRAINS::direct_service_available(vector<string> stationNames, int s1, int s2)
{
        s1--;
        s2--;

       if (data[s1][s2].weight != 0)
       {
                cout << "Direct service is available from " << stationNames[s1] << " to " << stationNames[s2] << endl;
                return;
       }
       else if (data[s1][s2].weight == 0)
       {
               cout << "No direct service available from " << stationNames[s1] << " to " << stationNames[s2] << endl;
               return;
       }       
}
        


bool TRAINS::service_available(int src, int dst)
{
        src--;
        dst--;
        if (src == dst)
                return true;

        // mark all as not visited
        bool *visited = new bool[node_count];
        for (int i = 0; i < node_count; ++i)
                visited[i] = false;
       
        
        queue<int> q;

        q.push(src);
        visited[src] = true;

        while (q.empty() == false)
        {
                int vertex = q.front();
                q.pop();

                if (visited[dst] == true)
                {
                        return true;
                }

                for (int i = 0; i < node_count; ++i)
                {
                        int neighbor = i;
                        int edge_one = data[vertex][i].weight;


                        if (edge_one = 0 ) {continue; }

                        if (visited[neighbor] == false)
                        {
                                q.push(neighbor);
                                visited[neighbor] = true;
                        }
                }
        }

        

        return false;
}






















