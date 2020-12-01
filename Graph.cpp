/* This is the header file for the Graph program.  *
 * Kurtis Adams U#14843960      *
 * Jefferson Taylor U#96232253  *
 *                         */

#include "Graph.hpp"
#include <string>
#include <vector>
#include <queue>
#include <map>

using namespace std;


/* Function is the destructor for Graph. */
Graph::~Graph() 
{
        gphComp.erase(gphComp.begin(), gphComp.end());
};


/* Function creates & adds labeled vertex to graph. */
void Graph::addVertex(std::string label) 
{
    /* Handles if label already exists, so that if so it doesn't add it to the vector. *
     * Otherwise if it doesn't exist, it adds it. */
    for (unsigned int i = 0; i < vertVec.size(); i++) 
    {
        if (vertVec.at(i) == label) 
        {
            return; 
        }
    }
    vertVec.push_back(label);
};


/* Function removes labeled vertex from graph and the edges between that vertex and others *
 * within the graph. */
void Graph::removeVertex(std::string label) 
{
    for(unsigned int i = 0; i <  vertVec.size(); i++) 
    {
        if(vertVec.at(i) == label) 
        {
            /* Removes the label from the vector if it exists. */
             vertVec.erase(vertVec.begin() + i);
        
            for(unsigned int j = 0; j < gphComp.size(); j++) 
            {
                Edge *tmpEdge = new Edge();
                tmpEdge = gphComp.at(j);
                
                if(tmpEdge->u == label || tmpEdge->v == label)
                {
                    gphComp.erase(gphComp.begin() + j);
                }
            }
        }
    }
};


/* Function adds an edge with the value of the variable "weight" to the graph. This is placed between *
 * the "label1" and "label2" vertices given that "label1" and "label2" exist and no edge currently exists *
 * between them. */
void Graph::addEdge(std::string label1, std::string label2, unsigned long weight) 
{
    bool uIsThere = false;
    bool vIsThere = false;

    for(unsigned int i = 0; i < vertVec.size(); i++) 
    {
        /* Using bool variables to check if the labels already exist. */
        if(vertVec.at(i) == label1) 
        { 
            uIsThere = true; 
        }

        if(vertVec.at(i) == label2) 
        { 
            vIsThere = true; 
        }
    }
    
    /* If they do exist, following creates the edge object and places it. */
    if(uIsThere == true && vIsThere == true) 
    {
        Edge *newEdge = new Edge();
        newEdge->u = label1;
        newEdge->v = label2;
        newEdge->eWeight = weight;
        gphComp.push_back(newEdge);
    }
};


/* Function removes edge from graph between "label1" and "label2" vertices if they and an edge *
 * between them exist. */
void Graph::removeEdge(std::string label1, std::string label2) 
{
    Edge *tmpEdge = new Edge();

    /* Following iterates through all edgeds that exist to remove the edge. *
     * Provided that it exists. */
    for(unsigned int i = 0; i < gphComp.size(); i++) 
    {
        tmpEdge = gphComp.at(i);

        if(tmpEdge->u == label1 && tmpEdge->v == label2)
        {
            gphComp.erase(gphComp.begin() + i);
        }
    }
};


/* Function uses Dijkstra's Algorithm to calculate shortest path between "startlabel" and "endlabel" vertices. *
 * Returns a value that is the sum of the edges between the two vertices. */
unsigned long Graph::shortestPath(std::string startLabel, std::string endLabel, std::vector<std::string> &path) 
{
    priority_queue<pair<int, string>, vector <pair<int, string> >, greater<pair<int, string> > > priQueue;
    
    map<string,string> labeledVerts;
    map<string,int> weightMap;
    
    /* Following initializes the Dijkstra table with EMPTY_STRING strings  and  INF weights. */
    for (auto label : vertVec) 
    {
        labeledVerts[label] = EMPTY_STRING;
        weightMap[label] = INF;
    }

    /* Folowing adds the starting point to the priority queue before the while loop does *
     * Djikstra's Algorithm. */
    priQueue.push(make_pair(0, startLabel));
    weightMap[startLabel] = 0;
    
    while (!priQueue.empty()) 
    {
        string curVertex;

        string topLabel = priQueue.top().second;
        priQueue.pop();

        /* Following checks all it's adjacent neighbors and their weights. */
        for (auto adjNeighbor : gphComp) 
        {
            if(adjNeighbor->u == topLabel) 
            { 
                curVertex = adjNeighbor->v; 
            } else if(adjNeighbor->v == topLabel)
              { 
                  curVertex = adjNeighbor->u; 
              } else 
                { 
                    continue; 
                }

            /* Following holds the current vertex's temporary weight. Followed by *
             * the if statement that does the Djikstra's Algorithm calculation. */
            int weight = adjNeighbor->eWeight;

            if (weightMap[topLabel] + weight < weightMap[curVertex]) 
            {
                labeledVerts[curVertex] = topLabel;
                weightMap[curVertex] = weightMap[topLabel] + weight;
                priQueue.push(make_pair(weightMap[curVertex], curVertex));
            }
        }
    }
    path.push_back(startLabel);

    printPath(labeledVerts, endLabel, path);
    return weightMap[endLabel];
};


/* Function recursively returns shortest path. */
void Graph::printPath(map<string, string> labeledVerts, string endLabel , vector<string> &path) 
{
    if (labeledVerts[endLabel] == EMPTY_STRING) 
    { 
        return; 
    }
    printPath(labeledVerts, labeledVerts[endLabel], path);
    path.push_back(endLabel);
};