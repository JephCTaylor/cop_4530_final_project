#ifndef EDGE_H
#define EDGE_H

/* This is the header file for the Edge class, needed for the Graph program.  *
 * Kurtis Adams U#14843960 *
 *                         *
 *                         */

#include <string>

using namespace std;
const string EMPTY_STRING = " ";

class Edge 
{
    public:
        string u;
        string v;
        unsigned long eWeight;
        Edge()
        {
            eWeight = 0;
            u = EMPTY_STRING;
            v = EMPTY_STRING;
        };
        ~Edge();
};

#endif 