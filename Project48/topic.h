#ifndef TOPIC_H
#define TOPIC_H

#define MAX_TOPICS 100
#define NAME_LENGTH 100

struct Topic
{
    int id;
    char name[NAME_LENGTH];

    /* Used by 0/1 Knapsack */
    int studyTime;
    int masteryGain;
};

/* Add a new topic */
void addTopic(
    struct Topic topics[],
    int *topicCount
);

/* Display all topics */
void displayTopics(
    struct Topic topics[],
    int topicCount
);

#endif