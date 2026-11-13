#include <stdio.h>
#include "topic.h"


// Function to add a new topic
void addTopic(struct Topic topics[], int *topicCount)
{
    // Check if maximum number of topics has been reached
    if (*topicCount >= MAX_TOPICS)
    {
        printf("\nTopic limit reached!\n");
        return;
    }

    printf("\n--- Add New Topic ---\n");

    // Take Topic ID
    printf("Enter Topic ID: ");
    scanf("%d", &topics[*topicCount].id);

    // Take Topic Name
    printf("Enter Topic Name: ");
    scanf(" %49[^\n]", topics[*topicCount].name);

    // Take Difficulty
    printf("Enter Difficulty (1-5): ");
    scanf("%d", &topics[*topicCount].difficulty);

    // Take Priority
    printf("Enter Priority (1-5): ");
    scanf("%d", &topics[*topicCount].priority);

    // Take required study hours
    printf("Enter Required Study Hours: ");
    scanf("%d", &topics[*topicCount].studyHours);

    // Take assessment score
    printf("Enter Assessment Score: ");
    scanf("%f", &topics[*topicCount].score);

    // Increase number of stored topics
    (*topicCount)++;

    printf("\nTopic added successfully!\n");
}


// Function to display all topics
void viewTopics(struct Topic topics[], int topicCount)
{
    // Check if there are no topics
    if (topicCount == 0)
    {
        printf("\nNo topics have been added yet.\n");
        return;
    }

    printf("\n========== ALL TOPICS ==========\n");

    // Loop through all stored topics
    for (int i = 0; i < topicCount; i++)
    {
        printf("\nTopic %d\n", i + 1);
        printf("-----------------------------\n");

        printf("ID: %d\n", topics[i].id);
        printf("Name: %s\n", topics[i].name);
        printf("Difficulty: %d\n", topics[i].difficulty);
        printf("Priority: %d\n", topics[i].priority);
        printf("Study Hours: %d\n", topics[i].studyHours);
        printf("Assessment Score: %.2f%%\n", topics[i].score);
    }
}


// Function to search for a topic using its ID
void searchTopic(struct Topic topics[], int topicCount)
{
    int searchID;
    int found = 0;

    // Check if there are no topics
    if (topicCount == 0)
    {
        printf("\nNo topics have been added yet.\n");
        return;
    }

    // Ask user for Topic ID
    printf("\nEnter Topic ID to search: ");
    scanf("%d", &searchID);

    // Linear Search
    for (int i = 0; i < topicCount; i++)
    {
        // Check if current topic ID matches searched ID
        if (topics[i].id == searchID)
        {
            printf("\n--- Topic Found ---\n");

            printf("ID: %d\n", topics[i].id);
            printf("Name: %s\n", topics[i].name);
            printf("Difficulty: %d\n", topics[i].difficulty);
            printf("Priority: %d\n", topics[i].priority);
            printf("Study Hours: %d\n", topics[i].studyHours);
            printf("Assessment Score: %.2f%%\n", topics[i].score);

            found = 1;

            // Stop searching because topic was found
            break;
        }
    }

    // If no matching topic was found
    if (found == 0)
    {
        printf("\nTopic not found!\n");
    }
}


// ============================================================
// STEP 4: Detect Weak Topics based on assessment scores
// Algorithm: Linear Scan with Threshold Filtering
// Time Complexity: O(n) - checks each topic once
// Space Complexity: O(1) - no extra arrays needed
// ============================================================
void detectWeakTopics(struct Topic topics[], int topicCount)
{
    float threshold;
    int weakCount = 0;

    // Check if there are no topics
    if (topicCount == 0)
    {
        printf("\nNo topics have been added yet.\n");
        return;
    }

    // Ask the user for the weakness threshold
    printf("\nEnter weakness threshold (e.g., 50 means scores below 50%% are weak): ");
    scanf("%f", &threshold);

    printf("\n========== WEAK TOPICS (Score < %.2f%%) ==========\n", threshold);

    // Linear scan: check every topic one by one
    for (int i = 0; i < topicCount; i++)
    {
        // If this topic's score is below the threshold, it's weak
        if (topics[i].score < threshold)
        {
            printf("\n[WEAK] Topic: %s\n", topics[i].name);
            printf("       ID: %d\n", topics[i].id);
            printf("       Score: %.2f%%\n", topics[i].score);
            printf("       Difficulty: %d | Priority: %d\n",
                   topics[i].difficulty, topics[i].priority);

            weakCount++;
        }
    }

    // Summary
    if (weakCount == 0)
    {
        printf("\nGreat! No weak topics found above the threshold.\n");
    }
    else
    {
        printf("\n-----------------------------\n");
        printf("Total weak topics: %d out of %d\n", weakCount, topicCount);
    }
}


// Helper function: calculate Urgency Score for a topic
// Formula: (Priority * 20) + (100 - Score)
float calculateUrgency(struct Topic t)
{
    return (t.priority * 20.0f) + (100.0f - t.score);
}


// ============================================================
// STEP 5: Sort and Rank Topics by Urgency (Priority + Weakness)
// Algorithm: Selection Sort (Descending Order)
// Time Complexity: O(n^2) comparisons, O(n) swaps
// Space Complexity: O(n) for the display copy
// ============================================================
void rankTopics(struct Topic topics[], int topicCount)
{
    if (topicCount == 0)
    {
        printf("\nNo topics have been added yet.\n");
        return;
    }

    // Create a local copy so we do not alter the user's original order
    struct Topic sorted[MAX_TOPICS];
    for (int i = 0; i < topicCount; i++)
    {
        sorted[i] = topics[i];
    }

    // Selection Sort: find the topic with maximum urgency and place at index i
    for (int i = 0; i < topicCount - 1; i++)
    {
        int maxIdx = i;
        for (int j = i + 1; j < topicCount; j++)
        {
            if (calculateUrgency(sorted[j]) > calculateUrgency(sorted[maxIdx]))
            {
                maxIdx = j;
            }
        }

        // Swap the highest urgency topic into position i
        if (maxIdx != i)
        {
            struct Topic temp = sorted[i];
            sorted[i] = sorted[maxIdx];
            sorted[maxIdx] = temp;
        }
    }

    // Display the ranked topics in a formatted table
    printf("\n===================================================================\n");
    printf("   RANKED TOPICS (Most Urgent to Least Urgent)\n");
    printf("   Formula: Urgency = (Priority * 20) + (100 - Score)\n");
    printf("===================================================================\n");
    printf("%-5s %-6s %-20s %-8s %-10s %-10s\n", "Rank", "ID", "Name", "Priority", "Score", "Urgency");
    printf("-------------------------------------------------------------------\n");

    for (int i = 0; i < topicCount; i++)
    {
        float urgency = calculateUrgency(sorted[i]);
        printf("%-5d %-6d %-20s %-8d %6.2f%%   %8.2f\n",
               i + 1,
               sorted[i].id,
               sorted[i].name,
               sorted[i].priority,
               sorted[i].score,
               urgency);
    }
    printf("-------------------------------------------------------------------\n");
}


// Helper function: Find the array index (0 to topicCount-1) for a given Topic ID
// Returns -1 if the ID is not found.
int getTopicIndexById(struct Topic topics[], int topicCount, int id)
{
    for (int i = 0; i < topicCount; i++)
    {
        if (topics[i].id == id)
        {
            return i;
        }
    }
    return -1;
}

