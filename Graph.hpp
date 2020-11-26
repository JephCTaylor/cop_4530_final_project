#ifndef GRAPH_H
#define GRAPH_H

/* This is the header file for the Graph program.  *
 * Kurtis Adams U#14843960 *
 *                         *
 *                         */

#include "Edge.hpp"
#include "GraphBase.hpp"
#include <string>
#include <iostream>
#include <map>
#define INF 10000

class Graph : public GraphBase {
public:
    Graph() { };
    ~Graph();
    void addVertex(std::string label);
    void removeVertex(std::string label);
    void addEdge(std::string label1, std::string label2, unsigned long weight);
    void removeEdge(std::string label1, std::string label2);
    unsigned long shortestPath(std::string startLabel, std::string endLabel, std::vector<std::string> &path);
    void printPath(std::map<std::string, std::string> startLabel, std::string endLabel, std::vector<std::string> &path);

private:
    friend class Edge;
    vector<string> vertVec;
    vector<Edge*> gphComp;
};

#endif