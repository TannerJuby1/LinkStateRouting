//
//  LinkStateRouting.cpp
//  
//
//  Created by Tanner Juby on 4/24/17.
//
//

#include "LinkStateRouting.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <ctime>

struct edge {
    
    int u;
    int v;
    int cost;

};

struct QObject {
    
    int node;
    int cost;
    
};

struct costObject {
    
    int node;
    int cost;
    int fromNode;
    
};

struct forwardingTableObject {
    
    int start;
    int destination;
};


std::vector<costObject> totalCosts;
std::vector<forwardingTableObject> forwardingTable;

/**
 Get Initial Move
 
 Backtracks Dijkstra's results to get the initial move for a particular destination 
 from the source node.
 */
int getInitialMove(int destination, int sourceNode) {
    
    std::vector<costObject> tempTable = totalCosts;
    
    int isFrom = tempTable[destination-1].fromNode;
    
    if (isFrom == sourceNode) {
        return tempTable[destination-1].node;
    } else {
        return getInitialMove(tempTable[destination-1].fromNode, sourceNode);
    }
    
    return -1;
}

/**
 Main
 
 The Main program
 */
int main(int argc, char** argv)
{
    printf("--------------------------------------------------------------\n\nSTARTING PROGRAM\n\n");
    
    std::clock_t begin_time = clock();
    int cost_size = 10000;
    
    int node_count = 0;
    
    // Error check for arguments
    if (argc != 4) {
        printf("ERROR: You need three arguments: $> ./a.out <test-input-file> <node i> <flag>");
        return 0;
    }
    
    // Set arguments
    std::string testFile = argv[1];
    std::string nodeInput = argv[2];
    std::string flagInput = argv[3];
    
    int sourceNode = std::atoi(nodeInput.c_str());
    int flag = std::atoi(flagInput.c_str());
    
    // Read input file to set up data structure
    std::ifstream myfile;
    myfile.open(testFile.c_str());
    
    std::string line;
    
    std::vector<std::vector<edge> > edges;
    
    int firstLineCheck = 0;
    
    // Read the input file
    while (std::getline(myfile, line)) {
        
        std::istringstream iss(line);
        
        // If first line, just get the total number of nodes
        if (firstLineCheck == 0) {
            node_count = std::atoi(line.c_str());
            printf("--------------------------------------------------------------\n\nTOTAL NUMBER OF NODES: %d", node_count);
            firstLineCheck++;
            continue;
        }
        
        // Add the edge to the edges vector
        float a = 0, b = 0, c = 0;
        if (!(iss >> a >> b >> c)) {
            
            //Error
            printf("Error in reading file... \n");
            return 0;
            
        } else {
            // Create Edge Mapping
            if (c != 1073741824) {
                edge newEdge = {.u = a, .v = b, .cost = c};
                
                if (edges.size() == newEdge.u - 1) {
                    std::vector<edge> tempVertexEdges;
                    tempVertexEdges.push_back(newEdge);
                    edges.push_back(tempVertexEdges);
                } else {
                    edges[newEdge.u-1].push_back(newEdge);
                }
            }
        }
    }
    
    float timeForFileRead = float(clock() - begin_time) / CLOCKS_PER_SEC * 1000;

    // Set up the totalCosts vector and the Priority Q
    std::vector<QObject> Q;
    for (int i = 0; i < node_count; i++) {
        
        if (i+1 == sourceNode) {
            
            costObject tempCost = {.node = i+1, .cost = 0, .fromNode = sourceNode};
            totalCosts.push_back(tempCost);
            
        } else {
            
            costObject tempCost = {.node = i+1, .cost = 1073741824, .fromNode = -1};
            totalCosts.push_back(tempCost);
        }
        
        QObject tempQ = {.node = i+1, .cost = totalCosts[i].cost};
        Q.push_back(tempQ);
    }
    
    // Set up step table if user wanted step table to be printed
    if (flag == 1) {
        printf("\n\n--------------------------------------------------------------\n\nSTEP TABLE\n----------\nStep \t N'\t");
        
        for (int i = 0; i < Q.size(); i++) {
            if (Q[i].node != sourceNode) {
                printf("\tD(%d), P(%d)", Q[i].node, Q[i].node);
            }
        }
    }
    
    // Use for step table
    int step = -1;
    std::vector<int> n;

    // Begin Dijkstra's Algorithm
    int check = node_count;
    while (check != 0) {
        
        // Increase the step size and print it out if needed
        step++;
        if (flag == 1) {
            printf("\n%d\t", step);
        }
        
        // Get the node with the lowest cost from Q
        int minVal = 1000;
        int minIndex = -1;
        for (int i = 0; i < Q.size(); i++) {
            int tempVal = Q[i].cost;
            if (tempVal < minVal && tempVal != -1) {
                minVal = tempVal;
                minIndex = i;
            }
        }
        QObject u = Q[minIndex];
        
        // Print out the current N' is if needed
        n.push_back(u.node);
        if (flag == 1) {
            for (int k = 0; k < n.size(); k++) {
                printf("%d", n[k]);
            }
        }
        
        // Evaluate each of u's neighbors
        for (int i = 0; i < edges[u.node-1].size(); i++) {

            // Set the v node to be evaluated
            int v = edges[u.node-1][i].v;
            
            if (v != u.node) {

                // Get the cost between U and V
                int costUV = edges[u.node-1][i].cost;
            
                // Add the cost between U and V to the cost of the current u being evaluated
                int tempCost = 0;
                
                if (totalCosts[u.node-1].cost == 1073741824) {
                    // Cost for this is infinity, set cost to just cost between U and V
                    tempCost = costUV;
                } else {
                    // Add the cost between u and v to the cost already set for node j
                    tempCost = totalCosts[u.node-1].cost + costUV;
                }
                
                // Print out the step if needed
                if (flag == 1) {
                    printf("\t\t%d, %d", tempCost, u.node);
                }
                
                // Check to see if the tempCost for the current path is cheaper than previous paths for v
                if (tempCost < totalCosts[v-1].cost) {
                    totalCosts[v-1].cost = tempCost;
                    
                    totalCosts[v-1].fromNode = u.node;
                    
                    Q[v-1].cost = tempCost;
                }
            }
        }
        
        Q[minIndex].cost = -1;
        check--;
    }
    
    float timeForDijkstras = float(clock() - begin_time) / CLOCKS_PER_SEC * 1000;
    
    // Generate and print forwarding table
    printf("\n\n--------------------------------------------------------------\n\nFORWARDING TABLE FOR NODE %d: \n----------------------------", sourceNode);
    printf("\nDestination \t Link");
    for (int i = 0; i < totalCosts.size(); i++) {
        
        int destination = totalCosts[i].node;
        
        int initial = getInitialMove(destination, sourceNode);
        
        printf("\n   %d\t\t(%d, %d)", destination, sourceNode, initial);
    }
    
    float timeForForwardingTable = float(clock() - begin_time) / CLOCKS_PER_SEC * 1000;
    
    // Print Results
    printf("\n\n--------------------------------------------------------------\n\nRESULTS:\n--------");
    printf("\nTime to execute file read: \t\t%f ms", timeForFileRead);
    printf("\nTime to execute dijkstra's algorithm: \t%f ms", timeForDijkstras - timeForFileRead);
    printf("\nTime to produce forwarding table: \t%f ms", timeForForwardingTable - timeForDijkstras);
    printf("\n\nTotal time to execute: \t\t\t%f ms\n\n--------------------------------------------------------------\n", float(clock() - begin_time) / CLOCKS_PER_SEC * 1000);
    
    return 0;
}


