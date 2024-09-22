/*
    Dijkstras Algorithm.
    Author: Owen Walstrom
    Date: 9/21/2024

    will show least path to each node from specified source node.
    
*/
#include<bits/stdc++.h>
using namespace std ;

int cost[100][100] , n  ; 

int getMin(int dist[] , bool visited[]){
    int key = 0 ; 
    int min = INT_MAX ; 
    for(int i=0;i < n ; i++){
        if(!visited[i] && dist[i]<min){
            min = dist[i] ; 
            key = i ; 
        }
    }
    return key ; 
}

void display(int dist[] , int par[] ){
   for(int i =0 ;i < n ;i++){
       int temp = par[i] ; 
       cout<<i << " <- " ;
       while(temp!=-1)
       {
           cout<< temp << " <- " ;
           temp = par[temp] ; 
       }
       cout<<endl; 
       cout<<"::::Distance = " << dist[i] ; 
       cout<<endl; 
   } 
}


void dijkstra(int src ){
    int par[100] , dist[100] ; 
    bool visited[100] ={0} ; 
    fill(dist , dist+n  , INT_MAX ) ; 

    dist[src] =0 ; 
    par[src] =-1 ;
    
    for(int g = 0  ;g<n-1 ; g++){
        int u = getMin( dist ,  visited )  ; 
        visited[u] = true ;
        cout<< " min = " << u <<endl; 
        for(int v =0 ; v< n ;v++){
            if(!visited[v] && (dist[u]+cost[u][v]) <  dist[v] && cost[u][v]!=9999)
            {
                par[v] = u ; 
                dist[v] = dist[u] + cost[u][v] ; 
            }
        }
    }
    
    display(dist , par) ; 
}



int main(void) { 
    cout<<"Enter n : " ; 
    cin>>n ; 
    cout<<"Enter cost matrix : \n" ; 
    for(int i = 0 ;i < n ; i++){
        for(int j = 0 ; j< n ; j++)cin>>cost[i][j] ; 
    }
    int src ; 
    cout<<"\nEnter source : " ;  cin>>src ;
    dijkstra(src) ; 
}

/*COST MATRIX (paste in when prompted)

0   10  999 999 999
999 0   2   999 4
999 999 0   9   8
999 999 7   0   999
999 1   8   2   0


*/


/*
ATTEMPT 1

#include<iostream>
#include<stdio.h>
#include<bits/stdc++.h>
using namespace std;

#define INF 999

int vertexCount, sourceVertex, graph[100][100];
int distancesArray[100];
bool visitedFlagArray[100] = {0};
int parentsVertex[100];

void initializeDistanceValues(){
    for(int i = 0; i < vertexCount; i++){
        parentsVertex[i] = i;
        distancesArray[i] = INF;
    }
    distancesArray[sourceVertex] = 0;
};

int getNearestUnvisitedVertex(){
    int minValue = INF;
    int minVertex = 0;
    for(int i = 0; i < vertexCount; i++){
        if(!visitedFlagArray[i] && distancesArray[i] < minValue){
            minValue = distancesArray[i];
            minVertex = i;
        }
    }
    return minVertex;
};

void dijkstra(){
    for(int i = 0; i < vertexCount; i++){
        int nearestUnvisitedVertex = getNearestUnvisitedVertex();
        visitedFlagArray[nearestUnvisitedVertex] = true;

        for(int adjacent = 0; adjacent < vertexCount; adjacent++){
            if(graph[nearestUnvisitedVertex][adjacent] != INF && distancesArray[adjacent] < distancesArray[nearestUnvisitedVertex] + 
                graph[nearestUnvisitedVertex][adjacent]){
                    distancesArray[adjacent] = distancesArray[nearestUnvisitedVertex] + graph[nearestUnvisitedVertex][adjacent];
                    parentsVertex[adjacent] = nearestUnvisitedVertex;
            }
        }
    }
};

void display(){
    cout<<"Vertex:\t\t\tCost :\t\t\tPath";

    for(int i = 0; i < vertexCount; i++){
        cout << i << "\t\t\t" << distancesArray[i] << "\t\t\t"<<" ";
        cout << i << " ";
        int parentVertex = parentsVertex[i];
        while(parentVertex != sourceVertex){
            cout << " <- " << parentVertex << " ";
            parentVertex = parentsVertex[parentVertex];
        }
        cout << endl;
    }
};

int main() {
    cin >> vertexCount;
    for(int i = 0; i < vertexCount; i++){
        for(int j = 0; j < vertexCount; j++){
            cin >> graph[i][j];
        }
    }
    cin >> sourceVertex;
    initializeDistanceValues();
    dijkstra();
    display();
    return 0;
};




ATTEMPT 2

#include <iostream>
#include <vector>
using namespace std;

class Edge{
    private:
        int startVertex, endVertex, weight;
    public: 
        Edge(int startVertex, int endVertex, int weight){
            this->startVertex = startVertex;
            this->endVertex = endVertex;
            this->weight = weight;
        }
        ~Edge(){}
        int getStartVertex(){
            return this->startVertex;
        }
        int getEndVertex(){
            return this->endVertex;
        }
        int getWeight(){
            return this->weight;
        }
};
class WeightedGraph{
    private:
        vector<int> vertices;
        vector<Edge*> edges;
    public:
        WeightedGraph(){
            int vertexCount, edgeCount;
            cout << "Enter Total Number of Vertices in Graph: ";
            cin >> vertexCount;
            cout << "\nEnter Total Number of Edges in Graph: ";
            cin >> edgeCount;
            for(int i = 0; i < vertexCount; i++){
                this->vertices.push_back(i);
            }
            for(int i = 0; i < edgeCount; i++){
                int startVertex, endVertex, weight;
                cout << "\nEnter Edge " << i << " information:"; 
                cout << "\nEnter Start Vertex (integer): ";
                cin >> startVertex;
                cout << "\nEnter End Vertex (integer): ";
                cin >> endVertex;
                cout << "\nEnter Edge Weight (integer): ";
                cin >> weight;
                //(Edge* name - new Edge() is for heap allocation meaning this object will exsist outside of current scope)
                //(Edge name - Edge() is for stack allocation meaning this object be destroyed at the end of current scope)
                Edge* newEdge = new Edge(startVertex, endVertex, weight);
                this->edges.push_back(newEdge);
            }
        }
        WeightedGraph(vector<int> vertices, vector<Edge*> edges){
            this->vertices = vertices;
            this->edges = edges;
        }
        ~WeightedGraph(){}
        void display(){
            cout << "Vertices: ";
            for(int i = 0; i < this->vertices.size(); i++){
                cout << this->vertices[i] << ", ";
            }     
            cout << "\n";
            for(int i = 0; i < this->edges.size(); i++){
                cout << "Start Vertex: " << this->edges[i]->getStartVertex() << ", End Vertex: " << this->edges[i]->getEndVertex() << ", Weight: " << this->edges[i]->getWeight() <<"\n";
            }
        }
        void shortestPath(){
            int startVertex, endVertex;
            cout << "\nEnter Start Vertex (integer): ";
            cin >> startVertex;
            cout << "\nEnter End Vertex (integer): ";
            cin >> endVertex;
            vector<int> visitedVertices = {};
            vector<int> unvisistedVertices = this->vertices;
            int distance[this->vertices.size()];
            for(int i = 0; i < this->vertices.size(); i++){
                if(i == 0){
                    distance[i] = 0; //let distance of start vertex from start vertex = 0
                }else{
                    distance[i] = INT_MAX; //let distance of all other vertices from start = infinity
                }
            }
            while(visitedVertices.size() < unvisistedVertices.size()){ //WHILE vertices remain unvisited
                int currentVertex = unvisistedVertices[0];
                for(int i = 0; i < unvisistedVertices.size(); i++){ //visit unvisited vertex with the smallest known distance from the start vertex (call this current vertex)
                    if(currentVertex > unvisistedVertices[i]){
                        currentVertex = unvisistedVertices[i];
                    }
                }

            }
        }
};


int main(){
    //Create Graph
    Edge* edge0 = new Edge(0, 1, 10);
    Edge* edge1 = new Edge(0, 4, 3);
    Edge* edge2 = new Edge(1, 2, 2);
    Edge* edge3 = new Edge(1, 4, 4);
    Edge* edge4 = new Edge(2, 3, 9);
    Edge* edge5 = new Edge(3, 2, 7);
    Edge* edge6 = new Edge(4, 1, 1);
    Edge* edge7 = new Edge(4, 2, 8);
    Edge* edge8 = new Edge(4, 3, 2);

    WeightedGraph graph = WeightedGraph({0, 1, 2, 3, 4, 5}, {edge0, edge1, edge2, edge3, edge4, edge5, edge6, edge7, edge8});
    //graph.display();

    //Dijkstras Algorithm

    return 0;
};
*/




/*
    PSUEDOCODE 1
    let distance of start vertex from start vertex = 0
    let distance of all other vertices from start = infinity

    WHILE vertices remain unvisited
        visit unvisited vertex with the smallest known distance from the start vertex (call this current vertex)
        FOR each unvisited neighbor of the current vertex...
            Calculate the distance from the start vertex
            IF the calculated distance of the this vertex is less than the known distance...
                Update the shortest distance to this vertex
                Update the previous vertex with the current vertex
            end IF
        Next unvisited neighbour
        add the current vertex to the list of visited vertices
    END WHILE
*/
      



/*

    PSUEDOCODE 2
    let distance of start vertex from start vertex = 0
    let distance of all other vertices from start = infinity

    Repeat until all vertices visited
        visit the unvisited vertex with the smallest known distance from the start vertex
        For the current vertex, examine its unvisited neighbors
        for the current vertex, calculate the distance of each neighbor from the start vertex
        if the calculated distance of a vertex is less than the known distance, update the shortest distance
        Ypdate the previous vertex for each of the updated distances
        Add the current vertex to the list of visited vertices.
*/
