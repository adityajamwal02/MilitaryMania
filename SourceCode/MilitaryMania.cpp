#include<bits/stdc++.h>
#include<list>
#include<vector>
#include<algorithm>
#include<map>
using namespace std;

#define N 16
#define V 16
#define INF 99999


//-------------------------------------------------------------------------------------------

//Adjacency List representation (graph)

class node{
public:
    string name;                                        //Name of cities
    list<string> nbrs;                                  //List of adjacent neighbour to that city

    node(string name)                                   //Constructor calling (self)
    {
        this->name=name;
    }
};

class graph{

    //All nodes(string, node*)
    unordered_map<string,node*> m;

public:
    graph(vector<string> cities)
    {
        for(auto city : cities)
        {
            m[city]=new node(city);                     //Dynamically allocated nodes
        }                                               //Linked list notation
    }

    void addedge(string x, string y, bool undir=false)  //Adding Edges to neighbouring cities
    {
        m[x]->nbrs.push_back(y);
        //for undirected graph, both ways <--->
        if(undir)
        {
            m[y]->nbrs.push_back(x);
        }
    }

    // Printing Adjacency List with all city pairs
    void printAdjList()
    {
        for(auto citypair : m)
        {
            auto city = citypair.first;
            node *node=citypair.second;
            cout<<" "<<city<<"-->";
            for(auto nbr: node->nbrs)
            {
                cout<<nbr<<",";
            }
            cout<<endl;
        }
    }
};

// MINIMUM WEAPONRY

int weaponry(int prices_weapons[], int n)
{
    vector<vector<int> > dp(n+1,vector<int>(n+1,0));

    for(int i=n-1;i>=0;i--)
    {
        for(int j=0;j<n;j++)
        {
            if(i==j)
            {
                dp[i][i]=n*prices_weapons[i];
            }
            else if(i<j)
            {
                int y=n-(j-i);
                int pick_left=prices_weapons[i]*y + dp[i+1][j];
                int pick_right=prices_weapons[j]*y + dp[i][j-1];

                dp[i][j]=min(pick_left,pick_right);
            }
        }
    }
    for(int i=0;i<n;i++)
    {
        cout<<" ";
        for(int j=0;j<n;j++)
            cout<<dp[i][j]<<" ";
        cout<<endl;
    }
    cout<<"\n Minimum Money To Be Spend (in 10crores): ";
    return dp[0][n-1];
}

//PATH ESCAPE

bool solveMazeUtil(int maze[N][N], int t, int s,int sol[N][N]);

void printSolution(int sol[N][N])
{
	for (int i = 0; i < N; i++)
    {
		for (int j = 0; j < N; j++)
			cout<<" "<<sol[i][j]<<" ";
		cout<<endl;
	}
}

bool isSafe(int maze[N][N], int t, int s)
{
	if (t >= 0 && t < N && s >= 0 && s < N && maze[t][s] == 1)
		return true;
	return false;
}

bool solveMaze(int maze[N][N])
{
	int sol[N][N];
	for(int i=0;i<N;i++)
        for(int j=0;j<N;j++)
        sol[i][j]=0;

	if (solveMazeUtil(maze, 0, 0, sol) == false)
    {
		cout<<"Path doesn't exist. Hold on, Military AirBorne \n";
		return false;
	}
	cout<<" Escape as follows: \n"<<endl;
	printSolution(sol);
	return true;
}

bool solveMazeUtil(int maze[N][N], int x, int y, int sol[N][N])
{
	if (x == N - 1 && y == N - 1 && maze[x][y] == 1)
    {
		sol[x][y] = 1;
		return true;
	}
	if (isSafe(maze, x, y) == true)
        {
		if (sol[x][y] == 1)
			return false;

		sol[x][y] = 1;

		if (solveMazeUtil(maze, x + 1, y, sol) == true)
			return true;

		if (solveMazeUtil(maze, x, y + 1, sol) == true)
			return true;

		sol[x][y] = 0;
		return false;
	}
	return false;
}

void path_escape()
{
    int random_i[10],random_j[10];
    int min_range=1,max_range=14;
    int maze[N][N] ={   { 1, 0 , 0 , 0 , 1  , 0  , 0  , 1  , 1  , 0  , 0  , 0  , 0  , 0  , 0 , 0 },
                        { 1, 1 , 1 , 1 , 0  , 0  , 0  , 0  , 1  , 1  , 1  , 1  , 1  , 0  , 0 , 0 },
                        { 0, 1 , 0 , 1 , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0 , 1 },
                        { 0, 1 , 0 , 1 , 1  , 0  , 0  , 1  , 0  , 1  , 1  , 0  , 0  , 1  , 0 , 0 },
                        { 1, 1 , 1 , 1 , 1  , 0  , 0  , 0  , 1  , 1  , 0  , 0  , 0  , 0  , 1 , 0 },
                        { 0, 0 , 0 , 0 , 1  , 1  , 1  , 1  , 0  , 0  , 0  , 1  , 0  , 0  , 0 , 0 },
                        { 0, 0 , 0 , 0 , 1  , 0  , 1  , 1  , 0  , 1  , 1  , 0  , 0  , 0  , 0 , 0 },
                        { 1, 0 , 0 , 1 , 0  , 0  , 0  , 1  , 1  , 1  , 0  , 0  , 1  , 0  , 0 , 1 },
                        { 1, 0 , 0 , 0 , 1  , 0  , 0  , 1  , 0  , 1  , 0  , 1  , 0  , 1  , 1 , 0 },
                        { 0, 0 , 0 , 1 , 1  , 0  , 1  , 0  , 0  , 1  , 1  , 0  , 0  , 1  , 0 , 0 },
                        { 0, 0 , 0 , 0 , 0  , 0  , 1  , 0  , 0  , 1  , 0  , 0  , 0  , 0  , 0 , 0 },
                        { 0, 1 , 0 , 0 , 0  , 1  , 0  , 0  , 0  , 1  , 1  , 1  , 1  , 1  , 1 , 0 },
                        { 1, 1 , 0 , 0 , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 1  , 1  , 0  , 1 , 0 },
                        { 0, 0 , 0 , 1 , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 1  , 1  , 0 , 1 },
                        { 0, 0 , 0 , 1 , 0  , 0  , 0  , 1  , 0  , 0  , 1  , 0  , 0  , 1  , 1 , 1 },
                        { 1, 0 , 1 , 0 , 0  , 0  , 1  , 0  , 0  , 0  , 0  , 0  , 0  , 1  , 0 , 1 }
                    };

    srand(time(NULL));
    for(int i=0;i<5;i++)
    {
    random_i[i]=min_range+(rand()%(max_range-min_range+1));
    random_j[i]=min_range+(rand()%(max_range-min_range+1));
    maze[random_i[i]][random_j[i]]=0;
    }
    solveMaze(maze);
}

// FLYOD WARSHALL PART

void print_flyod(int dist[][V]);

void floydWarshall(int graph[][V])
{
	int dist[V][V];

	for (int i = 0; i < V; i++)
		for (int j = 0; j < V; j++)
			dist[i][j] = graph[i][j];

	for (int k = 0; k < V; k++)
	{
		// Pick all vertices as source one by one
		for (int i = 0; i < V; i++)
		{
			// Pick all vertices as destination for the
			// above picked source
			for (int j = 0; j < V; j++)
			{
				// If vertex k is on the shortest path from
				// i to j, then update the value of
				// dist[i][j]
				if (dist[i][j] > (dist[i][k] + dist[k][j])
					&& (dist[k][j] != INF
						&& dist[i][k] != INF))
					dist[i][j] = dist[i][k] + dist[k][j];
			}
		}
	}

	print_flyod(dist);
}

void print_flyod(int dist[][V])
{
	cout << "\n Shortest distances between every pair of vertices \n "<<endl;
	for (int i = 0; i < V; i++) {
		for (int j = 0; j < V; j++) {
			if (dist[i][j] == INF)
				cout << "INF"
					<< "	 ";
			else
				cout << dist[i][j] << "	 ";
		}
		cout << endl;
	}
}

void flyod_graph()
{
    int graph[V][V] = { { 0  ,INF,INF,INF,10 ,INF,INF,20 ,15 ,INF,INF,INF,INF,INF,INF,INF },
    					{ INF,0  ,10 ,INF,INF,INF,INF,INF,INF,INF,INF,45 ,30 ,INF,INF,INF },
    					{ INF,10 ,0  ,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,35  },
    					{ INF,INF,INF,0  ,55 ,INF,INF,60 ,INF,15 ,INF,INF,INF,20 ,INF,INF },
    					{ 10 ,INF,INF,55 ,0  ,INF,INF,INF,25 ,45 ,INF,INF,INF,INF,30 ,INF },
    					{ INF,INF,INF,INF,INF,0  ,INF,INF,INF,INF,INF,70 ,INF,INF,INF,INF },
    					{ INF,INF,INF,INF,INF,INF,0  ,INF,INF,20 ,40 ,INF,INF,INF,INF,INF },
    					{ 20 ,INF,INF,60 ,INF,INF,INF,0  ,INF,INF,INF,INF,INF,INF,INF,75  },
    					{ 15 ,INF,INF,INF,25 ,INF,INF,INF,0  ,INF,INF,INF,INF,INF,35 ,INF },
    					{ INF,INF,INF,15 ,45 ,INF,30 ,INF,INF,0  ,65 ,INF,INF,INF,INF,INF },
    					{ INF,INF,INF,INF,INF,INF,40 ,INF,INF,65 ,0  ,INF,INF,INF,70 ,INF },
    					{ INF,85 ,INF,INF,INF,70, INF,INF,INF,INF,INF,0  ,INF,INF,INF,INF },
    					{ INF,30 ,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,0  ,INF,INF,INF },
    					{ INF,INF,INF,20 ,INF,INF,INF,INF,INF,INF,INF,INF,INF,0  ,INF,40  },
    					{ INF,INF,INF,30 ,INF,INF,INF,35 ,INF,INF,70 ,INF,INF,INF,0  ,INF },
    					{ INF,INF,35 ,INF,INF,INF,75 ,INF,INF,INF,INF,INF,INF,40 ,INF,0   }
    				};

	floydWarshall(graph);
}


//-----------------------------------------------------------------------------------------------------

// Comparator (Comparing a and b, string name and int casualties

bool cmp(pair<string, int>& a, pair<string, int>& b)
{
    return a.second < b.second;
}

// Sorting map

void sort(map<string, int>& mp)
{

    // Declare vector of pairs
    vector<pair<string, int> > A;

    // Copy key-value pair from Map to vector of pairs
    for(auto &it : mp) {
        A.push_back(it);
    }

    // Sort using comparator function
    sort(A.begin(), A.end(), cmp);

    // Print the sorted value
    for (auto& it : A) {
        cout<<" "<<it.first<< ' ' << it.second<<endl;
    }
}

int Binary_search(vector<string> cities,int n,string data)
{
    sort(cities.begin(),cities.end());
    int l=0;
    int r=n+1;
    while(l<=r){
       int mid=(l+r)/2;
        if(data==cities[mid])
            return mid;
        else if(data<cities[mid])
            r=mid-1;
        else
            l=mid+1;

    }
    return -1;
}

// RADIX SORT PART

int getmax(int arr[], int n)
{
    int max_e=arr[0];
    for(int i=0;i<n;i++)
    {
        max_e=max(max_e,arr[i]);
    }
    return max_e;
}
void countsort(int arr[],int n,int exp)
{
    int output[n];
    int i, countarr[10]={0};

    for(i=0;i<n;i++)
    {
        countarr[(arr[i]/exp)%10]++;
    }
    for(i=1;i<10;i++)
    {
        countarr[i]+=countarr[i-1];
    }
    for(i=n-1;i>=0;i--)
    {
        output[countarr[(arr[i]/exp)%10]-1]=arr[i];
        countarr[(arr[i]/exp)%10]--;
    }
    for(i=0;i<n;i++)
        arr[i]=output[i];
}
void radixsort(int arr[], int n)
{
    int max_e=getmax(arr,n);
    for(int exp=1;max_e/exp>0;exp*=10)
        countsort(arr,n,exp);
}

 void print_terror()
 {

        string terror_groups[6]={"Lashkar-e-Jabbar","Lashkar-e-Omar","Hizb-ul-Mujahideen",
                    "Lashkar-e- Toiba","Al Badr","Jaish-e-Mohammed"};
        int *arr=new int[5];

        cout<<"\n BEFORE SORTING \n"<<endl;
        for(int i=0;i<6;i++)
        {
            if(terror_groups[i]=="Lashkar-e-Jabbar")
            {
                arr[i]=84;
                cout<<" "<<terror_groups[i]<<"\t"<<arr[i]<<endl;
            }

            else if(terror_groups[i]=="Lashkar-e-Omar")
            {
                arr[i]=56;
                cout<<" "<<terror_groups[i]<<"\t \t"<<arr[i]<<endl;
            }

            else if(terror_groups[i]=="Hizb-ul-Mujahideen")
            {
                arr[i]=103;
                cout<<" "<<terror_groups[i]<<"\t"<<arr[i]<<endl;
            }

            else if(terror_groups[i]=="Lashkar-e- Toiba")
            {
                arr[i]=412;
                cout<<" "<<terror_groups[i]<<"\t"<<arr[i]<<endl;
            }

            else if(terror_groups[i]=="Al Badr")
            {
                arr[i]=179;
                cout<<" "<<terror_groups[i]<<"\t \t"<<arr[i]<<endl;
            }

            else if(terror_groups[i]=="Jaish-e-Mohammed")
            {
                arr[i]=268;
                cout<<" "<<terror_groups[i]<<"\t"<<arr[i]<<endl;
            }

        }

        radixsort(arr,6);

        cout<<"\n AFTER SORTING \n"<<endl;
        for(int i=0;i<6;i++)
        {
            if(arr[i]==84)
                cout<<" Lashkar-e-Jabbar"<<"\t"<<arr[i]<<endl;
            else if(arr[i]==56)
                cout<<" Lashkar-e-Omar"<<" \t"<<arr[i]<<endl;
            else if(arr[i]==103)
                cout<<" Hizb-ul-Mujahideen"<<"\t"<<arr[i]<<endl;
            else if(arr[i]==412)
                cout<<" Lashkar-e- Toiba"<<"\t"<<arr[i]<<endl;
            else if(arr[i]==179)
                cout<<" Al Badr"<<" \t \t"<<arr[i]<<endl;
            else if(arr[i]==268)
                cout<<" Jaish-e-Mohammed"<<"\t"<<arr[i]<<endl;
        }
}

//----------------------------------------------------------------------------------------------------------------

/*In war times situations we need to provide supplies of
    food and bandages which can be divided as per value and for this
        fractional knapsack can be used.In order to save fuel the two inputs
            are the petrol saved per district along with weight of supplies.*/

struct Item
{
	int value, weight;
	// Constructor
	Item(int value, int weight)
	{
		this->value = value;
		this->weight = weight;
	}
};

// Comparison function to sort Item according to val/weight
// ratio
bool comp(struct Item a, struct Item b)
{
	double r1=(double)a.value/(double)a.weight;
	double r2=(double)b.value/(double)b.weight;
	return r1 > r2;
}

// Main greedy function to solve problem
double fractionalKnapsack(int W, struct Item arr[], int n)
{
	// sorting Item on basis of ratio
	sort(arr, arr+n, comp);

	// Uncomment to see new order of Items with their ratio
	for (int i = 0; i < n; i++)
	{
		cout<<" "<<arr[i].value<<":"<<arr[i].weight<<"-->"<<
		((double)arr[i].value/arr[i].weight)<<endl;
	}

	double finalvalue = 0.0;

	for (int i = 0; i < n; i++)
    {
		if(arr[i].weight<=W)
		 {
			W-=arr[i].weight;
			finalvalue+=arr[i].value;
		}
		// If we can't add current Item, add fractional part of it
		else {
			finalvalue += arr[i].value* ((double)W/(double)arr[i].weight);
			break;
		}
	}
	cout<<"\n Maximum value of fuel saved by sending supplies= ";
	return finalvalue;
}


int minDistance(int dist[],bool sptSet[])
{
    int min=INT_MAX,min_index;

    for (int v = 0; v < V; v++)
    if(sptSet[v]==false&&dist[v]<=min)
    min=dist[v],min_index=v;

    return min_index;
}
    /*
    o----->Kathua-->Samba,Udhampur,Doda,
    n----->Samba-->Jammu,Kathua,
    m----->Poonch-->Baramulla,Rajouri,Budga,Kulgam,
    l----->Budga-->Baramulla,Poonch,Srinagar,Shopian,Pulwama,
    k----->Kishtwar-->Doda,
    j----->Kupwara-->Baramulla,Gander Bal,
    i----->Kulgam-->Shopian,Jammu,Poonch,
    h----->Pulwama-->Srinagar,Budga,Shopian,
    g----->Baramulla-->Kupwara,Poonch,Budga,Gander Bal,
    f----->Gander Bal-->Kupwara,Baramulla,Srinagar,
    e----->Doda-->Kathua,Kishtwar,
    d----->Udhampur-->Kathua,
    c----->Rajouri-->Poonch,Jammu,
    b----->Srinagar-->Gander Bal,Budga,Pulwama,
    a----->Jammu-->Kulgam,Rajouri,Samba,
    */

void printdijk(int dist[])
{
    char a[]={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r'};
    cout <<" Vertex     Distance from Source" << endl;
    for (int i = 0; i < V; i++)
        cout <<" "<< a[i] << " \t\t"<<dist[i]<< endl;
}

void dijkstra(int graph[V][V], int src)
{
    int dist[V];

    bool sptSet[V]; // sptSet[i] will be true if vertex i is included in shortest
    // path tree or shortest distance from src to i is finalized

    for (int i = 0; i < V; i++)
        dist[i]=INT_MAX,sptSet[i]=false;

    // Distance of source vertex from itself is always 0
    dist[src] = 0;

    for (int count=0;count<V-1;count++)
    {
    // Pick the minimum distance vertex from the set of vertices not
    // yet processed. u is always equal to src in the first iteration.
        int u=minDistance(dist, sptSet);

    // Mark the picked vertex as processed
        sptSet[u]=true;

    // Update dist value of the adjacent vertices of the picked vertex.
        for (int v = 0; v < V; v++)
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX
            && dist[u] + graph[u][v] < dist[v])
            dist[v] = dist[u] + graph[u][v];
    }

    printdijk(dist);
}


void SingleSourcePath()
{
      int graph[V][V]={{0,0,0,0,1,0,0,1,1,0,0,0,0,0,0,0},
                       {0,0,1,0,0,0,0,0,0,0,0,1,1,0,0,0},
                       {0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                       {0,0,0,0,1,0,0,1,0,1,0,0,0,1,0,0},
                       {1,0,0,1,0,0,0,0,1,1,0,0,0,0,1,0},
                       {0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0},
                       {0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0},
                       {1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1},
                       {1,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0},
                       {0,0,0,1,1,0,1,0,0,0,1,0,0,0,0,0},
                       {0,0,0,0,0,0,1,0,0,1,0,0,0,0,1,0},
                       {0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0},
                       {0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                       {0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1},
                       {0,0,0,1,0,0,0,1,0,0,1,0,0,0,0,0},
                       {0,0,1,0,0,0,1,0,0,0,0,0,0,1,0,0}
                    };

        dijkstra(graph, 0);
}


const int x = 16;   //vertex no.
const int colors[x] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
int counter = 0;
bool problem = false;
int a[100],k=0,b[100],l=0;

    /*
        A-Shopian
        B-Kathua
        C-Samba
        D-Poonch
        E-Budga
        F-Kishtwar
        G-Kupwara
        H-Kulgam
        I-Pulwama
        J-Baramulla
        K-Gander Bal
        L-Doda
        M-Udhampur
        N-Rajouri
        O-Srinagar
        P-Jammu
    */

   bool graf[x][x]={{0,0,0,0,1,0,0,1,1,0,0,0,0,0,0,0},
                    {0,0,1,0,0,0,0,0,0,0,0,1,1,0,0,0},
                    {0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                    {0,0,0,0,1,0,0,1,0,1,0,0,0,1,0,0},
                    {1,0,0,1,0,0,0,0,1,1,0,0,0,0,1,0},
                    {0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0},
                    {1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1},
                    {1,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0},
                    {0,0,0,1,1,0,1,0,0,0,1,0,0,0,0,0},
                    {0,0,0,0,0,0,1,0,0,1,0,0,0,0,1,0},
                    {0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0},
                    {0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                    {0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1},
                    {0,0,0,1,0,0,0,1,0,0,1,0,0,0,0,0},
                    {0,0,1,0,0,0,1,0,0,0,0,0,0,1,0,0}
                };


    char vertex_names[x] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P'};
    int rate_list[x]; //{ 0,0,0,0,0,0,0,0,0,0};

    struct Graf
    {
        char vertex_id[x];
        int vertex_rates[x];
        bool adj[x][x];
        int colors[x];
        bool colored[x];
    };

    //welsh powell

    void colorIt(Graf g)
    {
        counter++;
        int biggest=0;
        int temp_rate = 0;

    //rate listing from adj matrix (counting edges)

        if (counter == 1)
        for (int i = 0; i < x; i++)
            for (int j = 0; j < x; j++)
                if (g.adj[i][j])
                    rate_list[i]++;


    for (int w = 0; w < x; w++)
        if (!g.colored[w])
        {
            g.vertex_rates[w] = rate_list[w];
            if (temp_rate < g.vertex_rates[w])
            {
                temp_rate = g.vertex_rates[w];
                biggest = w;
            }
        }

    //coloring biggest one first

    g.colors[biggest] = colors[counter];
    b[l]=g.colors[biggest];
    l++;
    //std::cout << g.vertex_id[biggest] <<":color "<< g.colors[biggest]<<std::endl;

    //coloring which doesn't have path with biggest one

    for (int e=0;e < x;e++)
        if (!g.adj[biggest][e] && biggest!=e && !g.colored[e]) {
            for (int t = 0; t < x;t++) {

                if(g.adj[e][t] &&g.colors[t]==g.colors[biggest]) problem = true;

                    if (t == x - 1 && !problem) {
                        g.colors[e] = colors[counter];
                        a[k]=g.colors[biggest];
                        k++;
                        //	std::cout << g.vertex_id[e] <<":color "<< g.colors[e] << std::endl;
                        g.colored[e] = true;
                        problem = false;
                    }
                    else if (t == x - 1) problem = false;
            }
        }

    g.colored[biggest] = true;

    //somehow it gives sometimes "access violation" error

    if (std::all_of(std::begin(g.colored), std::end(g.colored), [](bool i) { return i; }))
        { std::cout << "Graph fully covered" << std::endl; }

    else colorIt(g); 
}

void delay(float number_of_seconds)
{
    // Converting time into milli_seconds
    float milli_seconds = float(1000 * number_of_seconds);

    // Storing start time
    clock_t start_time = clock();

    // looping till required time is not achieved
    while (clock() < start_time + milli_seconds)
        ;
}

//-------------------------------------------------------------------------------------------------

int main()
{
    vector<string> cities={"Kupwara","Baramulla","Poonch","Budga",
                            "Rajouri","Kulgam","Pulwama","Srinagar",
                            "Gander Bal","Kishtwar","Doda","Udhampur",
                            "Jammu","Samba","Kathua","Shopian"};

    graph g(cities);
    int n=cities.size();
    char ch,alp;
    int d;


    //All Added neigbouring edges to the cities
    g.addedge("Kupwara","Baramulla",1);
    g.addedge("Kupwara","Gander Bal",1);
    g.addedge("Baramulla","Poonch",1);
    g.addedge("Baramulla","Budga",1);
    g.addedge("Baramulla","Gander Bal",1);
    g.addedge("Poonch","Rajouri",1);
    g.addedge("Poonch","Budga",1);
    g.addedge("Gander Bal","Srinagar",1);
    g.addedge("Srinagar","Budga",1);
    g.addedge("Srinagar","Pulwama",1);
    g.addedge("Budga","Shopian",1);
    g.addedge("Budga","Pulwama",1);
    g.addedge("Pulwama","Shopian",1);
    g.addedge("Shopian","Kulgam",1);
    g.addedge("Kulgam","Jammu",1);
    g.addedge("Kulgam","Poonch",1);
    g.addedge("Jammu","Rajouri",1);
    g.addedge("Jammu","Samba",1);
    g.addedge("Kathua","Samba",1);
    g.addedge("Kathua","Udhampur",1);
    g.addedge("Kathua","Doda",1);
    g.addedge("Doda","Kishtwar",1);

    // initialize container
    map<string, int> mp;
    // Inserting Casualties in different districts; Data Bound
    mp.emplace("Gander Bal", 10);
    mp.emplace("Kulgam", 10);
    mp.emplace("Rajouri", 5);
    mp.emplace("Shopian", 90);
    mp.emplace("Doda", 0);
    mp.emplace("Kathua", 3);
    mp.emplace("Udhampur", 5);
    mp.emplace("Baramulla", 5);
    mp.emplace("Budga", 6);
    mp.emplace("Poonch", 3);
    mp.emplace("Srinagar", 20);
    mp.emplace("Samba", 5);
    mp.emplace("Kishtwar", 4);
    mp.emplace("Jammu", 10);
    mp.emplace("Kupwara", 20);
    mp.emplace("Pulwama", 80);

    //Choices
    cout<<" \t \t -------------------------------------"<<endl;
    cout<<" \t \t \t   MILITARY SOFTWARE "<<endl;
    cout<<" \t \t -------------------------------------";
    cout<<endl;
    input:
    cout<<"\n \t \t \t   CHOOSE OPERATION "<<endl;
    cout<<"\t \t  1. WAR CONDITIONS \t 2. DAILY DRILLS "<<endl;
    cin>>d;

    if(d==2)
    {
        for(int i=0;i<5;i++)
        {
            cout<<"\n \t \t \t CHOOSE FROM FOLLOWING: \n \t \t \t(a) VIEW MAP RELATION \n \t \t \t(b) SEARCH A DISTRICT \n"
                        " \t \t \t(c) CLASSIFY TERROR-GROUPS \n \t \t \t(d) MINIMUM COST OF WEAPONS \n "
                        "\t \t \t(e) VIEW SHORTEST PATH FROM SINGLE SOURCE"<<endl;
            cin>>ch;
            cout<<endl;

            switch(ch)
            {
                case 'a':
                    {
                        cout<<" J&K Terror-Prone District Map \n"<<endl;
                        g.printAdjList();
                        break;
                    }

                case 'b':
                    {
                        string data;
                        cout<<"Enter city to be searched: ";
                        cin>>data;
                        int result=Binary_search(cities,n,data);
                        if(result==-1)
                            cout << "District not found" << endl;
                        else
                            cout << "District found at: " <<result+1<< endl;
                        break;
                    }

                case 'c':
                    print_terror();
                    break;

                case 'd':
                    {
                        int prices_weapons[]={2,3,5,1,4};
                        int z=5;
                        int dp[10][10]={0};
                        cout<<weaponry(prices_weapons,z)<<endl;
                        break;
                    }

                case 'e':
                    SingleSourcePath();
                    break;
            }
            delay(1.5);
    }
    cout<<"\n BACK TO HOME PAGE? (Y/N) ";
    cin>>alp;
    if(alp=='Y'||alp=='y')
        goto input;
    else
     {
        cout<<"\n \n \tPROJECT DONE BY: \n";
        delay(1);
        cout<<" \tADITYA JAMWAL (20103283) -> B10 \n";
        delay(1);
        cout<<" \tTANUPRIYA PATHAK (20103288) -> B10 \n";
        delay(1);
        cout<<" \tYASH KAPOOR (20103296) -> B10 \n";
        delay(1);
     }
   }

    else if(d==1)
    {
        for(int i=0;i<6;i++)
        {

            cout<<"\n \t \t \t CHOOSE FROM FOLLOWING: \n \t \t \t(a) VIEW MAP RELATION \n \t \t \t(b) VIEW AREA-WISE FATALITIES \n"
                        "\t \t \t(c) MINIMUM TROOPS TO COVER \n \t \t \t(d) VIEW PATH ESCAPE \n \t \t \t(e) SUPPLIES STORAGE"
                        "\n \t \t \t(f) ALL PAIRS SHORTEST PATH"<<endl;
            cin>>ch;
            cout<<endl;

            switch(ch)
            {
                case 'a':
                    cout<<" J&K Terror-Prone District Map \n"<<endl;
                    g.printAdjList();
                    break;

                case 'b':
                    cout<<" Fatalities Rate Per 1000 Population \n"<<endl;
                    sort(mp);
                    break;

                case 'c':
                    {
                        Graf graf1;
                        //init color
                        for (int y = 0; y < x; y++)
                        {
                            graf1.colors[y] = 99;
                            graf1.colored[y] = false;
                        }

                        colorIt(graf1);

                        cout<<"\n";
                        cout<<"The number of troops required to cover graph are"<<"   "<<b[l-1];
                        cout<<endl;
                        break;
                    }

                case 'd':
                    path_escape();
                    break;

                case 'e':
                    {
                     int W = 680;
                     Item arr[] = { { 60, 10 }, { 100, 20 }, { 120, 30 }, { 150, 40 }, { 220, 40 }, { 10, 30 }, { 20, 90 }, { 90, 30 }, { 120, 40 },
                                    { 140, 60 }, { 90, 30 }, { 80, 30 }, { 120, 60 }, { 20, 70 }, { 120, 30 }, { 120, 20 }, { 10, 40 }, { 10, 10 } };
                     int n=sizeof(arr)/sizeof(arr[0]);
                     cout<<fractionalKnapsack(W, arr, n)<<"L"<<endl;
                     break;
                    }

                case 'f':
                    flyod_graph();
                    break;
            }
            delay(1.5);
        }
        cout<<"\n BACK TO HOME PAGE? (Y/N) ";
        cin>>alp;
        if(alp=='Y'||alp=='y')
            goto input;
    /*
        else{
            cout<<"\n \n \tPROJECT DONE BY: \n";
            delay(1);
            cout<<" \tADITYA JAMWAL (20103283) -> B10 \n";
            delay(1);
            cout<<" \tTANUPRIYA PATHAK (20103288) -> B10 \n";
            delay(1);
            cout<<" \tYASH KAPOOR (20103296) -> B10 \n";
            delay(1);
            exit(0);
            }
    }*/
    else
    {
        cout<<endl<<"\n ENTER (1) or (2)";
        goto input;
    }
    return 0;
}
