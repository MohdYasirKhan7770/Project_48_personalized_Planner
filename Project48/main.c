#include <stdio.h>

struct Topic {
  int id;
  char name[50];
  int difficulty;
  int priority;
  int studyHours;
  float score;
};

int main() {
  struct Topic topic1;

  printf("=== PERSONALIZED LEARNING PATH PLANNER ===\n\n");

  printf("Enter Topic ID: ");
  scanf("%d", &topic1.id);

  printf("Enter Topic Name: ");
  scanf(" %[^\n]", topic1.name);

  printf("Enter Difficulty (1-5): ");
  scanf("%d", &topic1.difficulty);

  printf("Enter Priority (1-5): ");
  scanf("%d", &topic1.priority);

  printf("Enter Required Study Hours: ");
  scanf("%d", &topic1.studyHours);

  printf("Enter Assessment Score: ");
  scanf("%f", &topic1.score);

  printf("\n--- Topic Information ---\n");

  printf("ID: %d\n", topic1.id);
  printf("Name: %s\n", topic1.name);
  printf("Difficulty: %d\n", topic1.difficulty);
  printf("Priority: %d\n", topic1.priority);
  printf("Study Hours: %d\n", topic1.studyHours);
  printf("Assessment Score: %.2f%%\n", topic1.score);

  return 0;
}