#include <stdio.h>
#include "algorithms.h"

/* ============================================================
   PROJECT 48
   PERSONALIZED LEARNING PATH AND ASSESSMENT PLANNER

   algorithms.c

   Main Algorithm:
   0/1 Knapsack using Dynamic Programming

   Supporting Structure:
   Directed Graph using Adjacency Matrix for prerequisites
   ============================================================ */


/* ============================================================
   FUNCTION: getTopicIndexById

   Finds the array index of a topic using its ID.

   Returns:
   index -> if topic exists
   -1    -> if topic does not exist
   ============================================================ */

int getTopicIndexById(
    struct Topic topics[],
    int topicCount,
    int id)
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


/* ============================================================
   FUNCTION: initGraph

   Initializes the prerequisite graph.

   0 = no prerequisite relationship
   1 = prerequisite relationship exists
   ============================================================ */

void initGraph(
    int adjMatrix[MAX_TOPICS][MAX_TOPICS])
{
    for (int i = 0; i < MAX_TOPICS; i++)
    {
        for (int j = 0; j < MAX_TOPICS; j++)
        {
            adjMatrix[i][j] = 0;
        }
    }
}


/* ============================================================
   FUNCTION: addPrerequisite

   Creates a directed prerequisite relationship.

   Example:

       C Programming ---> Data Structures

   means:

       C Programming must be studied before Data Structures.
   ============================================================ */

void addPrerequisite(
    int adjMatrix[MAX_TOPICS][MAX_TOPICS],
    struct Topic topics[],
    int topicCount)
{
    int prereqId;
    int targetId;


    /* At least two topics are required */

    if (topicCount < 2)
    {
        printf(
            "\nYou need at least 2 topics "
            "to define prerequisites!\n"
        );

        return;
    }


    printf("\n============================================\n");
    printf("            ADD PREREQUISITE\n");
    printf("============================================\n");

    printf(
        "Rule: Prerequisite Topic must be studied "
        "BEFORE Target Topic.\n\n"
    );


    /* Input prerequisite */

    printf("Enter Prerequisite Topic ID: ");

    if (scanf("%d", &prereqId) != 1)
    {
        printf("\nInvalid input!\n");

        while (getchar() != '\n')
        {
            /* Clear invalid input */
        }

        return;
    }


    /* Input target */

    printf("Enter Target Topic ID: ");

    if (scanf("%d", &targetId) != 1)
    {
        printf("\nInvalid input!\n");

        while (getchar() != '\n')
        {
            /* Clear invalid input */
        }

        return;
    }


    /* Prevent self dependency */

    if (prereqId == targetId)
    {
        printf(
            "\nError: A topic cannot be "
            "a prerequisite of itself!\n"
        );

        return;
    }


    /* Find topic positions */

    int u = getTopicIndexById(
        topics,
        topicCount,
        prereqId
    );

    int v = getTopicIndexById(
        topics,
        topicCount,
        targetId
    );


    /* Validate prerequisite topic */

    if (u == -1)
    {
        printf(
            "\nError: Prerequisite Topic ID %d "
            "not found!\n",
            prereqId
        );

        return;
    }


    /* Validate target topic */

    if (v == -1)
    {
        printf(
            "\nError: Target Topic ID %d "
            "not found!\n",
            targetId
        );

        return;
    }


    /* Check duplicate relationship */

    if (adjMatrix[u][v] == 1)
    {
        printf(
            "\nThis prerequisite relationship "
            "already exists!\n"
        );

        return;
    }


    /* ========================================================
       ADD DIRECTED EDGE

       u ---> v

       u = prerequisite
       v = target
       ======================================================== */

    adjMatrix[u][v] = 1;


    printf(
        "\nSuccess: '%s' (ID %d) is now "
        "a prerequisite for '%s' (ID %d).\n",
        topics[u].name,
        topics[u].id,
        topics[v].name,
        topics[v].id
    );
}


/* ============================================================
   FUNCTION: viewPrerequisites

   Displays every prerequisite relationship stored
   inside the adjacency matrix.
   ============================================================ */

void viewPrerequisites(
    int adjMatrix[MAX_TOPICS][MAX_TOPICS],
    struct Topic topics[],
    int topicCount)
{
    int edgeCount = 0;


    if (topicCount == 0)
    {
        printf("\nNo topics added yet.\n");

        return;
    }


    printf("\n====================================================\n");
    printf("           PREREQUISITE RELATIONSHIPS\n");
    printf("====================================================\n");


    /*
       Traverse the adjacency matrix.

       adjMatrix[i][j] == 1

       means:

       Topic i ---> Topic j
    */

    for (int i = 0; i < topicCount; i++)
    {
        for (int j = 0; j < topicCount; j++)
        {
            if (adjMatrix[i][j] == 1)
            {
                printf(
                    "[%d] %-20s ---> [%d] %s\n",
                    topics[i].id,
                    topics[i].name,
                    topics[j].id,
                    topics[j].name
                );

                edgeCount++;
            }
        }
    }


    if (edgeCount == 0)
    {
        printf(
            "No prerequisite relationships "
            "defined yet.\n"
        );
    }


    printf("----------------------------------------------------\n");

    printf(
        "Total prerequisite relationships: %d\n",
        edgeCount
    );

    printf("====================================================\n");
}


/* ============================================================
   FUNCTION: generateLearningPlan

   MAIN OPTIMIZATION ALGORITHM

   Algorithm:
       0/1 Knapsack using Dynamic Programming

   Problem:

       Every topic has:

       1. Study Time
       2. Mastery Gain

       Student has limited available time.

       Goal:

       Select the combination of topics that gives the
       MAXIMUM TOTAL MASTERY without exceeding available time.

   Knapsack Mapping:

       Item     = Topic
       Weight   = Study Time
       Value    = Mastery Gain
       Capacity = Available Study Time
   ============================================================ */

void generateLearningPlan(
    struct Topic topics[],
    int topicCount,
    int availableTime)
{
    /*
       Maximum supported study time for this version
       is 100 hours.
    */

    const int MAX_STUDY_TIME = 100;


    /* Validate topic count */

    if (topicCount == 0)
    {
        printf("\nNo topics available.\n");

        return;
    }


    /* Validate available time */

    if (availableTime <= 0)
    {
        printf(
            "\nAvailable study time must "
            "be greater than 0.\n"
        );

        return;
    }


    if (availableTime > MAX_STUDY_TIME)
    {
        printf(
            "\nMaximum supported study time "
            "is %d hours.\n",
            MAX_STUDY_TIME
        );

        return;
    }


    /*
       DP TABLE

       dp[i][t]

       represents:

       Maximum mastery obtainable using
       the first i topics when t hours
       are available.
    */

    int dp[MAX_TOPICS + 1][101];


    /* ========================================================
       INITIALIZE DP TABLE
       ======================================================== */

    for (int i = 0; i <= topicCount; i++)
    {
        for (int t = 0; t <= availableTime; t++)
        {
            dp[i][t] = 0;
        }
    }


    /* ========================================================
       BUILD THE DP TABLE
       ======================================================== */

    for (int i = 1; i <= topicCount; i++)
    {
        /*
           Current topic is topics[i - 1]
           because arrays start from index 0.
        */

        int studyTime =
            topics[i - 1].studyTime;

        int masteryGain =
            topics[i - 1].masteryGain;


        /*
           Validate topic values.
        */

        if (studyTime <= 0 || masteryGain < 0)
        {
            printf(
                "\nError: Invalid study time/mastery "
                "for topic '%s'.\n",
                topics[i - 1].name
            );

            return;
        }


        for (int t = 0; t <= availableTime; t++)
        {
            /*
               If current topic can fit within
               the available time.
            */

            if (studyTime <= t)
            {
                /*
                   OPTION 1:
                   Include current topic.
                */

                int includeTopic =
                    masteryGain +
                    dp[i - 1][t - studyTime];


                /*
                   OPTION 2:
                   Do not include current topic.
                */

                int excludeTopic =
                    dp[i - 1][t];


                /*
                   Store the better option.
                */

                if (includeTopic > excludeTopic)
                {
                    dp[i][t] = includeTopic;
                }
                else
                {
                    dp[i][t] = excludeTopic;
                }
            }

            else
            {
                /*
                   Current topic cannot fit.

                   Therefore copy the result
                   without this topic.
                */

                dp[i][t] =
                    dp[i - 1][t];
            }
        }
    }


    /* ========================================================
       FINAL OPTIMAL VALUE
       ======================================================== */

    int maximumMastery =
        dp[topicCount][availableTime];


    printf("\n====================================================\n");
    printf("          PERSONALIZED LEARNING PLAN\n");
    printf("====================================================\n");

    printf(
        "Available Study Time : %d hours\n",
        availableTime
    );

    printf(
        "Maximum Mastery Gain : %d\n",
        maximumMastery
    );


    printf("\nRecommended Topics\n");
    printf("----------------------------------------------------\n");


    /* ========================================================
       BACKTRACKING

       The DP table tells us the maximum mastery.

       Now we move backwards through the table to determine
       WHICH topics were selected.
       ======================================================== */

    int remainingTime = availableTime;

    int totalTime = 0;

    int selectedCount = 0;


    for (int i = topicCount;
         i > 0 && remainingTime > 0;
         i--)
    {
        /*
           If current DP value is different from
           the value directly above it, the current
           topic contributed to the optimal answer.
        */

        if (dp[i][remainingTime] !=
            dp[i - 1][remainingTime])
        {
            printf(
                "[%d] %-20s | Time: %d h | Mastery: %d\n",
                topics[i - 1].id,
                topics[i - 1].name,
                topics[i - 1].studyTime,
                topics[i - 1].masteryGain
            );


            totalTime +=
                topics[i - 1].studyTime;


            remainingTime -=
                topics[i - 1].studyTime;


            selectedCount++;
        }
    }


    /* If no topic could be selected */

    if (selectedCount == 0)
    {
        printf(
            "No topic can be completed within "
            "the available study time.\n"
        );
    }


    printf("----------------------------------------------------\n");


    printf(
        "Topics Selected      : %d\n",
        selectedCount
    );


    printf(
        "Total Study Time Used: %d/%d hours\n",
        totalTime,
        availableTime
    );


    printf(
        "Total Mastery Gain   : %d\n",
        maximumMastery
    );


    printf("====================================================\n");
}