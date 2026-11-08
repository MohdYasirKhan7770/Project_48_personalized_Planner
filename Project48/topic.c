#include "topic.h"
#include <stdio.h>

void addTopic(struct Topic topics[], int *topicCount) {
  if (*topicCount >= MAX_TOPICS) {
    printf("\nTopic limit reached!\n");
    return;
  }

  printf("\n--- Add New Topic ---\n");

  printf("Enter Topic ID: ");
  scanf("%d", &topics[*topicCount].id);

  printf("Enter Topic Name: ");
  scanf(" %49[^\n]", topics[*topicCount].name);

  printf("Enter Difficulty (1-5): ");
  scanf("%d", &topics[*topicCount].difficulty);

  printf("Enter Priority (1-5): ");
  scanf("%d", &topics[*topicCount].priority);

  printf("Enter Required Study Hours: ");
  scanf("%d", &topics[*topicCount].studyHours);

  printf("Enter Assessment Score: ");
  scanf("%f", &topics[*topicCount].score);

  (*topicCount)++;

  printf("\nTopic added successfully!\n");
}

void viewTopics(struct Topic topics[], int topicCount) {
  if (topicCount == 0) {
    printf("\nNo topics have been added yet.\n");
    return;
  }

  printf("\n========== ALL TOPICS ==========\n");

  for (int i = 0; i < topicCount; i++) {
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