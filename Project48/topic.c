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
