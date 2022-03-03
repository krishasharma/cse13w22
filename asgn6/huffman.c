#include "pq.h"
#include "node.h"
#include "code.h"
#include "stack.h"
#include "defines.h"
#include "io.h"
#include "huffman.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

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

Node *build_tree(uint64_t hist[static ALPHABET]) {
    // Constructs a Huffman tree given a computed histogram.
    // The histogram will have ALPHABET indices, one index for each possible symbol.
    // Returns the root node of the constructed tree.
    // The use of static array indices in parameter declarations is a C99 addition.
    // In this case, it informs the compiler that the histogram hist should have at least ALPHABET number of indices.
    uint32_t capacity = 257; // takes into account the open spot in the circular queue??
    PriorityQueue *pq = pq_create(capacity);
    int index = 0;
    for (index = 0; index <= 256; index += 1) {
        if (hist[index] != 0) {
            Node *child = node_create(index, hist[index]);
            enqueue(pq, child);
        }
    }
    while (pq_size(pq) > 1) {
        Node *leftdequeue;
        dequeue(pq, &leftdequeue);
        Node *rightdequeue;
        dequeue(pq, &rightdequeue);
        Node *parent = node_join(leftdequeue, rightdequeue);
        enqueue(pq, parent);
    }
    Node *root;
    dequeue(pq, &root);
    return root;
}

void build_codes(Node *root, Code table[static ALPHABET]) {
    // Populates a code table, building the code for each symbol in the Huffman tree.
    // The constructed codes are copied to the code table, table, which has ALPHABET indices.
    // It has one index for each possible symbol.
    if (root != NULL) {
        Code *code = NULL;
        uint8_t *x = NULL;
        if (!root->left) {
            if (!root->right) {
                code = &table[root->symbol];
            }
        } else {
            if (root->left) {
                code_push_bit(code, 0);
                build_codes(root->left, &table[0]);
                code_pop_bit(code, x);
            }
            if (root->right) {
                code_push_bit(code, 1);
                build_codes(root->right, &table[1]);
                code_pop_bit(code, x);
            }
        }
    }
}

void dump_tree(int outfile, Node *root) {
    // Conducts a post-order traversal of the Huffman tree rooted at root, writing it to outfile.
    // This should write an ‘L’ followed by the byte of the symbol for each leaf, and an ‘I’ for interior nodes.
    // You should not write a symbol for an interior node.
    uint8_t L = 'L';
    uint8_t I = 'I';
    if (root) {
        dump_tree(outfile, root->left);
        dump_tree(outfile, root->right);
        if (!root->left && !root->right) {
            write_bytes(outfile, &L, 1);
            write_bytes(outfile, &root->symbol, 1);
        } else {
            write_bytes(outfile, &I, 1);
        }
    }
}

Node *rebuild_tree(uint16_t nbytes, uint8_t tree[static nbytes]) {
    // Reconstructs a Huffman tree given its post-order tree dump stored in the array tree_dump.
    // The length in bytes of tree_dump is given by nbytes.
    // Returns the root node of the reconstructed tree.
    Stack *stack = stack_create(nbytes);
    uint8_t L = 'L';
    uint8_t I = 'I';
    for (int i = 0; i < nbytes; i += 1) { // you need to also be incrementing i somewhere else???
        if (tree[i] == L) {
            nbytes -= 1;
            Node *child = node_create(
                tree[i + 1], 0); // i + 1 becasue the symbol will come after L in the encoded output
            stack_push(stack, child);
        }
        if (tree[i] == I) {
            // CITE: Audrey's tutoring session on 03_02_2022
            // pop the right and left child from the stack instead of creating entirely new nodes.
            Node *lchild;
            stack_pop(stack, &lchild);
            Node *rchild;
            stack_pop(stack, &rchild);
            Node *parent = node_join(lchild, rchild);
            stack_push(stack, parent);
        }
    }
    Node *root;
    stack_pop(stack, &root);
    stack_delete(&stack);
    return root;
}

void delete_tree(Node **root) {
    // This will require a post-order traversal of the tree to free all the nodes.
    // Remember to set the pointer to NULL after you are finished freeing all the allocated memory.
    if (*root) {
        delete_tree((&(*root)->left));
        delete_tree((&(*root)->right));
    }
    free(*root);
    *root = NULL;
}
