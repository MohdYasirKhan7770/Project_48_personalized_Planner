#include "topic.h"
#include <stdio.h>


int main() {
  struct Topic topics[MAX_TOPICS];

  int topicCount = 0;
  int choice;

  while (1) {
    printf("\n========================================\n");
    printf("   PERSONALIZED LEARNING PATH PLANNER\n");
    printf("========================================\n");

    printf("1. Add Topic\n");
    printf("2. View All Topics\n");
    printf("3. Exit\n");

    printf("\nEnter your choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
      addTopic(topics, &topicCount);
    }

    else if (choice == 2) {
      viewTopics(topics, topicCount);
    }

    else if (choice == 3) {
      printf("\nThank you for using the Learning Path Planner!\n");
      break;
    }

    else {
      printf("\nInvalid choice. Please enter 1, 2, or 3.\n");
    }
  }

  return 0;
}