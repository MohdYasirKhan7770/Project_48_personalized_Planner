#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "topic.h"

// Initialize all adjacency matrix entries to 0 (no edges)
void initGraph(int adjMatrix[MAX_TOPICS][MAX_TOPICS]);

// Add a directed edge: prereqId -> targetId
void addPrerequisite(int adjMatrix[MAX_TOPICS][MAX_TOPICS], struct Topic topics[], int topicCount);

// View all existing prerequisite relationships
void viewPrerequisites(int adjMatrix[MAX_TOPICS][MAX_TOPICS], struct Topic topics[], int topicCount);

#endif
