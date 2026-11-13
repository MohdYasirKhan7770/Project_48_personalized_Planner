#include <stdio.h>
#include "topic.h"
#include "algorithms.h"

int main() 

while (1)
    {
        printf("\n========================================\n");
        printf("   PERSONALIZED LEARNING PATH PLANNER\n");
        printf("========================================\n");
        printf("1. Add Topic\n");
        printf("2. View All Topics\n");
        printf("3. Search Topic\n");
        printf("4. Detect Weak Topics\n");
        printf("5. Rank Topics (Priority & Weakness)\n");
        printf("6. Add Prerequisite Relationship\n");
        printf("7. View Prerequisite Graph\n");
        printf("8. Exit\n");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        if (choice == 1)
        {
            addTopic(topics, &topicCount);
        }
        else if (choice == 2)
        {
            viewTopics(topics, topicCount);
        }
        else if (choice == 3)
        {
            searchTopic(topics, topicCount);
        }
        else if (choice == 4)
        {
            detectWeakTopics(topics, topicCount);
        }
        else if (choice == 5)
        {
            rankTopics(topics, topicCount);
        }
        else if (choice == 6)
        {
            addPrerequisite(adjMatrix, topics, topicCount);
        }
        else if (choice == 7)
        {
            viewPrerequisites(adjMatrix, topics, topicCount);
        }
        else if (choice == 8)
        {
            printf("\nThank you for using the Learning Path Planner!\n");
            break;
        }
        else
        {
            printf("\nInvalid choice. Please enter 1-8.\n");
        }
    }

    return 0;
}
