#include "node.h"
#include "pq.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Please Note: Professor Long is cited throughout this assignment for providing the pseudocode in the assignment7 PDF document.
// Professor Long is also cited for the help he gave as Walter Sobchack (Elmer) on discord in the CSE13s - Winter2022 - Professor Long server.
// Throughout this assignment, I had high-level pseudocode collaboration with my sister Twisha Sharma (tvsharma)
// Eugene is cited throughout this assignment for this help with explaining how to properly begin and correctly implement this assignment
// during his section on 03_04_2022
// Ben is cited for his tutoring session on 03_08_2022
// during it he helped me understand that to access the salt array we should treat it as a pointer because we want to access the whole
// array, not a specific part of the array.
// Audrey is cited for her tutoring session on 03_09_2022
// during it she helped me understand how to properly delete the hash table as my destructor function was running errors.

struct PriorityQueue {
    uint32_t head;
    uint32_t tail;
    uint32_t capacity; // tracks maximum amount of nodes it can hold
    char **author;
    double *distance;
};

PriorityQueue *pq_create(uint32_t capacity) {
    // The constructor for a priority queue.
    // The priority queue’s maximum capacity is specified by capacity.
    PriorityQueue *q = (PriorityQueue *) malloc(sizeof(PriorityQueue));
    if (q == NULL) {
        return NULL;
    }
    else {
        q->head = 0;
        q->tail = 0;
        q->capacity = capacity;
        q->author = (char **) calloc(q->capacity, sizeof(char *));
        q->distance = (double *) calloc(q->capacity, sizeof(double));

        if (q->author && q->distance) {
            return q;
        }
        //free(q);
    }
    return NULL;
}

void pq_delete(PriorityQueue **q) {
    // The destructor for a priority queue.
    // Make sure to set the pointer to NULL after freeing the memory for a priority queue.
    // similar to asgn4 without the for loop
    if (q) {
        free((*q)->author); // first free whats inside the queue
        free((*q)->distance); // then free the queue
        free(*q);
        *q = NULL; // set queue to null
    }
}
bool pq_empty(PriorityQueue *q) {
    // Returns true if the priority queue is empty and false otherwise.
    if (q->head == 0) {
        return true;
    }
    return false;
}

bool pq_full(PriorityQueue *q) {
    // Returns true if the priority queue is full and false otherwise
    if (q->capacity == q->head) {
        return true;
    }
    return false;
}

uint32_t pq_size(PriorityQueue *q) {
    // Returns the number of items currently in the priority queue.
    return q->head;
}

bool enqueue(PriorityQueue *q, char *author, double dist) {
    //
    if (q) {
         if (pq_full(q)) {
             return false;
         }
         q->author[q->head] = author;
         q->distance[q->head] = dist;
         uint32_t queuesize = pq_size(q);
         if (queuesize == 0) {
             q->head = q->head + 1;
             return true;
         }
         for (uint32_t i = pq_size(q); i > 0; i --) {
             if (q->distance[i] < q->distance[i - 1]) {
                 double tempdistance = q->distance[i];
                 q->distance[i] = q->distance[i - 1];
                 q->distance[i - 1] = tempdistance;
                 char *tempstring = q->author[i];
                 q->author[i] = q->author[i - 1];
                 q->author[i - 1] = tempstring;
             }
         }
         q->head = q->head + 1; // parenthesis (q->head + 1)
         return true;
    }
    return false;
}

bool dequeue(PriorityQueue *q, char **author, double *dist) {
    //
    if (q) {
        if (pq_empty(q)) {
            return false;
        }
        *author = q->author[q->tail];
        *dist = q->distance[q->tail];
        uint32_t queuesize = pq_size(q);
        for (uint32_t i = 1; i < queuesize; i ++) {
            q->distance[i - 1] = q->distance[1];
            q->author[i - 1] = q->author[i];
        }
        q->head = q->head - 1;
        return true;
    }
    return false;
}

void pq_print(PriorityQueue *q) {
    // A debug function to print a priority queue.
    printf("the queue size: %u\n", q->head);
}
