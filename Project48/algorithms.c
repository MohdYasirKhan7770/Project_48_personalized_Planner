#include <stdio.h>
#include "algorithms.h"

// Initialize the adjacency matrix by setting all cells to 0
void initGraph(int adjMatrix[MAX_TOPICS][MAX_TOPICS])
{
    for (int i = 0; i < MAX_TOPICS; i++)
    {
        for (int j = 0; j < MAX_TOPICS; j++)
        {
            adjMatrix[i][j] = 0;
        }
    }
}

// Add a prerequisite dependency: prereq -> target
void addPrerequisite(int adjMatrix[MAX_TOPICS][MAX_TOPICS], struct Topic topics[], int topicCount)
{
    int prereqId, targetId;

    if (topicCount < 2)
    {
        printf("\nYou need at least 2 topics to define prerequisites!\n");
        return;
    }

    printf("\n--- Add Prerequisite Relationship ---\n");
    printf("Rule format: [Prerequisite Topic] must be studied BEFORE [Target Topic]\n\n");

    printf("Enter Prerequisite Topic ID: ");
    scanf("%d", &prereqId);

    printf("Enter Target Topic ID: ");
    scanf("%d", &targetId);

    // Validate that prereq != target (cannot be prerequisite of itself)
    if (prereqId == targetId)
    {
        printf("\nError: A topic cannot be a prerequisite of itself!\n");
        return;
    }

    // Convert IDs to array indices
    int u = getTopicIndexById(topics, topicCount, prereqId);
    int v = getTopicIndexById(topics, topicCount, targetId);

    if (u == -1)
    {
        printf("\nError: Prerequisite Topic ID %d not found!\n", prereqId);
        return;
    }
    if (v == -1)
    {
        printf("\nError: Target Topic ID %d not found!\n", targetId);
        return;
    }

    // Check if relationship already exists
    if (adjMatrix[u][v] == 1)
    {
        printf("\nThis prerequisite relationship already exists!\n");
        return;
    }

    // Set directed edge in the adjacency matrix
    adjMatrix[u][v] = 1;

    printf("\nSuccess: '%s' (ID %d) is now a prerequisite for '%s' (ID %d).\n",
           topics[u].name, topics[u].id,
           topics[v].name, topics[v].id);
}

// Display all defined prerequisites in human-readable format
void viewPrerequisites(int adjMatrix[MAX_TOPICS][MAX_TOPICS], struct Topic topics[], int topicCount)
{
    int edgeCount = 0;

    if (topicCount == 0)
    {
        printf("\nNo topics added yet.\n");
        return;
    }

    printf("\n=======================================================\n");
    printf("            PREREQUISITE RELATIONSHIPS (GRAPH)         \n");
    printf("=======================================================\n");

    for (int i = 0; i < topicCount; i++)
    {
        for (int j = 0; j < topicCount; j++)
        {
            if (adjMatrix[i][j] == 1)
            {
                printf("  [%d] %-18s  --->  [%d] %s\n",
                       topics[i].id, topics[i].name,
                       topics[j].id, topics[j].name);
                edgeCount++;
            }
        }
    }

    if (edgeCount == 0)
    {
        printf("  No prerequisite relationships defined yet.\n");
    }
    else
    {
        printf("-------------------------------------------------------\n");
        printf("Total prerequisite rules: %d\n", edgeCount);
    }
}
