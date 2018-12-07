#include "trains.h"
#define MAX 9999


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


int TRAINS::minDistance(int dist[], bool Marked[])
{
	int min = MAX, min_index;

	for (int v = 0; v < node_count; v++)
	{
		if (Marked[v] == false && dist[v] <= min)
		{
			min = dist[v];
			min_index = v;
		}
	}
	return min_index;
}


int TRAINS::shortest_riding_time(vector<string> stationNames, int src, int dst)
{
        bool isAvailable = service_available(src, dst);

        if (!isAvailable)
        {
               cout << "No service between " << stationNames[src] << " and " << stationNames[dst] << endl; 
               return 0;
        }

            src--;
            dst--;
            int dist[node_count];
            bool Marked[node_count];

            for (int x=0; x<node_count; x++)
            {
                dist[x] = MAX;
                Marked[x] = false;
            }

            dist[src] = 0;

            for (int count = 0; count < node_count - 1; count++)
            {
                int u = minDistance(dist, Marked);

                Marked[u] = true;

                for (int v = 0; v < node_count; v++)
                {
                    if (!Marked[v] && data[u][v].weight && dist[u] != MAX && dist[u] + data[u][v].weight < dist[v])
                    {
                        dist[v] = data[u][v].weight;
                    }
                }
            }
        


            int shortest_time = 0;
            for (int i = 0; i < node_count; i++)
            {
                        if (dist[i] != MAX)
                        {
                                shortest_time += dist[i];
                        }
            }

            return shortest_time;

}


void TRAINS::shortest_total_time(vector<string> stationNames, int src, int dst)
{
        bool isAvailable = service_available(src, dst);

        if (!isAvailable)
        {
               cout << "No service between " << stationNames[src] << " and " << stationNames[dst] << endl; 
               return;
        }

            src--;
            dst--;


            int dist[node_count];
            bool Marked[node_count];

            for (int x=0; x<node_count; x++)
            {
                dist[x] = MAX;
                Marked[x] = false;
            }

            dist[src] = 0;
            int firstDepart = 0;
            int firstDepartW = MAX;

                for (int j = 0; j < node_count; ++j)
                {
                        if (data[src][j].weight != 0)
                        {
                                if (data[src][j].weight < firstDepartW)
                                {
                                        firstDepart = data[src][j].depart;
                                }
                        }
                }

                


            for (int count = 0; count < node_count - 1; count++)
            {
                int u = minDistance(dist, Marked);

                Marked[u] = true;

                for (int v = 0; v < node_count; v++)
                {
                    if (!Marked[v] && data[u][v].weight && dist[u] != MAX && dist[u] + data[u][v].weight < dist[v])
                    {
                        dist[v] = data[u][v].arrive;
                    }
                }
            }


                // the arrival times are stored in dst
            int shortest_time = 0;

            shortest_time = dist[dst] - firstDepart;
                
            int shortRide = shortest_riding_time(stationNames, src+1, dst+1);

            if (shortRide > shortest_time)
                    shortest_time += 2400;

        
            int hour;
            int minute;

            hour = shortest_time / 60;
            minute = shortest_time % 60;

            cout << "The shortest total time between " << stationNames[src] << " and " << stationNames[dst]
                    << " is " << hour << ":";
            printf("%02d", minute);
            cout << endl;

}


















