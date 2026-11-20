#include <stdio.h>
#include <string.h>
#include "topic.h"


/* =========================================================
   ADD A NEW TOPIC
   ========================================================= */

void addTopic(
    struct Topic topics[],
    int *topicCount)
{
    if (*topicCount >= MAX_TOPICS)
    {
        printf("\nMaximum topic limit reached!\n");
        return;
    }

    int newId;

    printf("\n========================================\n");
    printf("              ADD TOPIC\n");
    printf("========================================\n");


    /* -------------------------
       ENTER TOPIC ID
       ------------------------- */

    printf("Enter Topic ID: ");

    if (scanf("%d", &newId) != 1)
    {
        printf("\nInvalid Topic ID!\n");

        while (getchar() != '\n')
        {
            /* clear input */
        }

        return;
    }


    /* -------------------------
       CHECK DUPLICATE ID
       ------------------------- */

    for (int i = 0; i < *topicCount; i++)
    {
        if (topics[i].id == newId)
        {
            printf(
                "\nError: Topic ID %d already exists!\n",
                newId
            );

            return;
        }
    }


    topics[*topicCount].id = newId;


    /*
       Clear newline left by scanf()
    */

    getchar();


    /* -------------------------
       ENTER TOPIC NAME
       ------------------------- */

    printf("Enter Topic Name: ");

    fgets(
        topics[*topicCount].name,
        NAME_LENGTH,
        stdin
    );


    /*
       Remove newline added by fgets()
    */

    topics[*topicCount].name[
        strcspn(
            topics[*topicCount].name,
            "\n"
        )
    ] = '\0';


    /* -------------------------
       ENTER STUDY TIME
       ------------------------- */

    printf("Enter Study Time (hours): ");

    if (scanf(
            "%d",
            &topics[*topicCount].studyTime
        ) != 1)
    {
        printf("\nInvalid Study Time!\n");

        while (getchar() != '\n')
        {
            /* clear input */
        }

        return;
    }


    if (topics[*topicCount].studyTime <= 0)
    {
        printf(
            "\nStudy time must be greater than 0.\n"
        );

        return;
    }


    /* -------------------------
       ENTER MASTERY GAIN
       ------------------------- */

    printf("Enter Mastery Gain: ");

    if (scanf(
            "%d",
            &topics[*topicCount].masteryGain
        ) != 1)
    {
        printf("\nInvalid Mastery Gain!\n");

        while (getchar() != '\n')
        {
            /* clear input */
        }

        return;
    }


    if (topics[*topicCount].masteryGain < 0)
    {
        printf(
            "\nMastery gain cannot be negative.\n"
        );

        return;
    }


    /* -------------------------
       TOPIC SUCCESSFULLY ADDED
       ------------------------- */

    (*topicCount)++;


    printf("\nTopic added successfully!\n");

    printf("========================================\n");
}


/* =========================================================
   DISPLAY ALL TOPICS
   ========================================================= */

void displayTopics(
    struct Topic topics[],
    int topicCount)
{
    if (topicCount == 0)
    {
        printf("\nNo topics added yet.\n");
        return;
    }


    printf("\n============================================================\n");
    printf("                     TOPIC LIST\n");
    printf("============================================================\n");

    printf(
        "%-8s %-25s %-12s %-12s\n",
        "ID",
        "Topic",
        "Time",
        "Mastery"
    );

    printf(
        "------------------------------------------------------------\n"
    );


    for (int i = 0; i < topicCount; i++)
    {
        printf(
            "%-8d %-25s %-12d %-12d\n",
            topics[i].id,
            topics[i].name,
            topics[i].studyTime,
            topics[i].masteryGain
        );
    }


    printf(
        "============================================================\n"
    );

    printf(
        "Total Topics: %d\n",
        topicCount
    );
}