#include "node.h"
#include "pq.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Please Note: The implemented code is based off of pseudocode provided by the Professor in the assignment PDF
// There is also high level pseudocode collaboration with my sister Twisha Sharma (tvsharm)
// Eugene is cited throughout the asgn for his explanation during his lab section on 02_18_2022.
// Eugene explained how to set up the assignment for huffman coding as well as explained how to properly begin
// each step of the assignment.
// Audrey is cited for her tutoring session on 02_25_2022 when she helped look over my huffman.c and node.c.
// Audrey also helped me fix syntax error in stack.c during her tutoring session on 03_02_2022
// She specifically helped me with stack_pop()
// Ben is cited for helping me with read_bytes and write_bytes during his tutoring session on 03_01_2022
// During his tutoring session he explained how to best implement read_bytes. Ben also looked over my code.c
// Brian is cited for his section on 02_28_2022 when he helped look over my pq.c
// Brian helped to also explain how to proceed with code.c and the best way to go about implementing the functions
// Brian also helped me during his tutoring session on 03_02_2022 by looking over my io.c file and helping me
// fix compilation and syntax errors

struct PriorityQueue {
    //Node **queue;
    uint32_t head;
    uint32_t tail;
    uint32_t capacity; // tracks maximum amount of nodes it can hold
    Node **Q;
};

PriorityQueue *pq_create(uint32_t capacity) {
    // The constructor for a priority queue.
    // The priority queue’s maximum capacity is specified by capacity.
    PriorityQueue *q = (PriorityQueue *) malloc(sizeof(PriorityQueue));
    if (q) {
        q->head = 0;
        q->tail = 0;
        q->capacity = capacity;
        q->Q = (Node **) calloc(q->capacity, sizeof(Node));
    }
    return q;
}

void pq_delete(PriorityQueue **q) {
    // The destructor for a priority queue.
    // Make sure to set the pointer to NULL after freeing the memory for a priority queue.
    // similar to asgn4 without the for loop
    if (*q) {
        free((*q)->Q); // first free whats inside the queue
        free(*q); // then free the queue
        *q = NULL; // set queue to null
    }
}

bool pq_empty(PriorityQueue *q) {
    // Returns true if the priority queue is empty and false otherwise.
    if (q->capacity == 0) {
        return true;
    } else {
        return false;
    }
}

bool pq_full(PriorityQueue *q) {
    // Returns true if the priority queue is full and false otherwise
    if (q->capacity == q->head) {
        return true;
    } else {
        return false;
    }
}

uint32_t pq_size(PriorityQueue *q) {
    // Returns the number of items currently in the priority queue.
    return q->capacity;
}

bool enqueue(PriorityQueue *q, Node *n) {
    // Enqueues a node into the priority queue.
    // Returns false if the priority queue is full prior to enqueuing the node
    // Returns true otherwise to indicate the successful enqueuing of the node.
    if (q) {
        if (pq_full(q) == true) {
            return false;
        }
        q->Q[q->head] = n; // CITE: Audrey 02_26_2022
        q->head += 1;
        for (uint32_t i = 1; i < q->head; i++) {
            uint32_t j = i; // copy what index you are on
            Node *tempvar = q->Q[i]; // save the value
            while (j > 0 && tempvar < q->Q[j - 1]) {
                q->Q[j] = q->Q[j - 1]; // swap
                j -= 1;
            }
            q->Q[j] = tempvar;
        }
        return true;
    } else {
        return false;
    }
}

bool dequeue(PriorityQueue *q, Node **n) {
    // Dequeues a node from the priority queue, passing it back through the double pointer n.
    // The node dequeued should have the highest priority over all the nodes in the priority queue.
    // Returns false if the priority queue is empty prior to dequeuing a node
    // Returns true otherwise to indicate the successful dequeuing of a node.
    if (q) {
        if (pq_empty(q) == true) {
            return false;
        }
        q->head -= 1;
        n = &q->Q[q->head];
        return true;
    } else {
        return false;
    }
}

void pq_print(PriorityQueue *q) {
    // A debug function to print a priority queue.
    printf("%u\n", q->head);
}
