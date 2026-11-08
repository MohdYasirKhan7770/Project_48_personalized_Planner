#ifndef TOPIC_H
#define TOPIC_H

#define MAX_TOPICS 100

struct Topic {
  int id;
  char name[50];
  int difficulty;
  int priority;
  int studyHours;
  float score;
};

void addTopic(struct Topic topics[], int *topicCount);
void viewTopics(struct Topic topics[], int topicCount);

#endif