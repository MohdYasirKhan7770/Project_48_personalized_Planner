#include <stdio.h>
#include "topic.h"
#include "algorithms.h"

int main(void)
{
    struct Topic topics[MAX_TOPICS];
    int adjMatrix[MAX_TOPICS][MAX_TOPICS];
    int topicCount = 0;
    int choice;

    initGraph(adjMatrix);

    while (1)
    {
        printf("\n========================================\n");
        printf("   PERSONALIZED LEARNING PATH PLANNER\n");
        printf("========================================\n");
        printf("1. Add Topic\n");
        printf("2. View All Topics\n");
        printf("3. Search Topic by ID (Linear Search)\n");
        printf("4. Add Prerequisite Relationship\n");
        printf("5. View Prerequisite Graph\n");
        printf("6. Generate Optimal Study Plan (0/1 Knapsack DP)\n");
        printf("7. Exit\n");
        printf("\nEnter your choice: ");

        if (scanf("%d", &choice) != 1)
        {
            printf("\nInvalid choice. Please enter a number.\n");
            while (getchar() != '\n');
            continue;
        }

        if (choice == 1)
        {
            addTopic(topics, &topicCount);
        }
        else if (choice == 2)
        {
            displayTopics(topics, topicCount);
        }
        else if (choice == 3)
        {
            searchTopic(topics, topicCount);
        }
        else if (choice == 4)
        {
            addPrerequisite(adjMatrix, topics, topicCount);
        }
        else if (choice == 5)
        {
            viewPrerequisites(adjMatrix, topics, topicCount);
        }
        else if (choice == 6)
        {
            int availableTime;
            printf("\nEnter your available study time (hours): ");
            if (scanf("%d", &availableTime) == 1)
            {
                generateLearningPlan(topics, topicCount, availableTime);
            }
            else
            {
                printf("\nInvalid time entered!\n");
                while (getchar() != '\n');
            }
        }
        else if (choice == 7)
        {
            printf("\nThank you for using the Learning Path Planner!\n");
            break;
        }
        else
        {
            printf("\nInvalid choice. Please enter 1-7.\n");
        }
    }

    return 0;
}
