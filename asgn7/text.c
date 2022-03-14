#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <regex.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include "parser.h"
#include "metric.h"
#include "bf.h"
#include "ht.h"
#include "text.h"

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

#define WORD "[a-zA-Z]+(('|-)[a-zA-Z]+)*"

struct Text {
    HashTable *ht;
    BloomFilter *bf;
    uint32_t word_count; // total number of words in the text
};

uint32_t noiselimit;

Text *text_create(FILE *infile, Text *noise) {
    // The constructor for a text.
    Text *text = (Text *) malloc(sizeof(Text));
    if (text == NULL) {
        return NULL;
    }
    HashTable *ht = ht_create((1 << 19));
    if (ht == NULL) {
        free(text);
        text = NULL;
        return NULL;
    }
    BloomFilter *bf = bf_create((1 << 21));
    if (bf == NULL) {
        free(text);
        text = NULL;
        ht_delete(&ht);
        return NULL;
    }
    regex_t re;
    if (regcomp(&re, WORD, REG_EXTENDED)) {
        fprintf(stderr, "Failed to compile regex. \n");
        regfree(&re);
        bf_delete(&bf);
        ht_delete(&ht);
        free(text);
        text = NULL;
        return NULL;
    }
    text->ht = ht;
    text->bf = bf;
    text->word_count = 0;
    // parse through the file
    char *word = NULL;
    while ((word = next_word(infile, &re)) != NULL) {
        for (uint32_t i = 0; i < strlen(word); i++) {
            word[i] = tolower(word[i]);
        }
        if (noise == NULL) {
            ht_insert(text->ht, word);
            bf_insert(text->bf, word);
        }
        if (noise != NULL) {
            if (text_contains(noise, word) == false) {
                ht_insert(text->ht, word);
                bf_insert(text->bf, word);
                text->word_count++;
            }
        }
    }
    regfree(&re);
    return text;
}

void text_delete(Text **text) {
    // Deletes a text.
    ht_delete(&(*text)->ht);
    bf_delete(&(*text)->bf);
    free(*text);
    *text = NULL;
}

double text_dist(Text *text1, Text *text2, Metric metric) {
    // This function returns the distance between the two texts depending on the metric being used.
    double m = 0;
    double normt1 = 0;
    double normt2 = 0;
    HashTableIterator *ht1 = hti_create(text1->ht);
    HashTableIterator *ht2 = hti_create(text2->ht);
    if (metric == MANHATTAN) {
        while (ht_iter(ht1) != NULL && ht_iter(ht2) != NULL) {
            if (ht_lookup(text1->ht, ht_iter(ht1)->word) != NULL) {
                if (ht_lookup(text2->ht, ht_iter(ht1)->word) != NULL) {
                    normt1 = text_frequency(text1, ht_iter(ht1)->word);
                    text_frequency(text2, ht_iter(ht2)->word);
                    m += fabs(normt1 - normt2);
                }
            }
        }
    }
    if (metric == EUCLIDEAN) {
        while (ht_iter(ht1) != NULL && ht_iter(ht2) != NULL) {
            if (ht_lookup(text1->ht, ht_iter(ht1)->word) != NULL) {
                if (ht_lookup(text2->ht, ht_iter(ht2)->word) != NULL) {
                    normt1 = text_frequency(text1, ht_iter(ht1)->word);
                    normt2 = text_frequency(text2, ht_iter(ht2)->word);
                    m += (normt1 - normt2);
                    m += m * m;
                }
            }
        }
        m += sqrt(m);
    }
    if (metric == COSINE) {
        while (ht_iter(ht1) != NULL && ht_iter(ht2) != NULL) {
            if (ht_lookup(text1->ht, ht_iter(ht1)->word) != NULL) {
                if (ht_lookup(text2->ht, ht_iter(ht2)->word) != NULL) {
                    normt1 = text_frequency(text1, ht_iter(ht1)->word);
                    normt2 = text_frequency(text2, ht_iter(ht2)->word);
                    m += (normt1 - normt2);
                }
            }
        }
        m += 1 - m;
    }
    return m;
}

double text_frequency(Text *text, char *word) {
    // Returns the frequency of the word in the text.
    if (ht_lookup(text->ht, word) != NULL) {
        double nword = ht_lookup(text->ht, word)->count / text->word_count;
        return nword;
    }
    return 0;
}

bool text_contains(Text *text, char *word) {
    // Returns whether or not a word is in the text.
    if (bf_probe(text->bf, word)) {
        return ht_lookup(text->ht, word) != NULL;
    }
    return false;
}

void text_print(Text *text) {
    // A debug function to print the contents of a text.
    printf("word_count = %d\n", text->word_count);
}
