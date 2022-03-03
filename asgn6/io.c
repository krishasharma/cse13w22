#include "code.h"
#include "node.h"
#include "pq.h"
#include "stack.h"
#include "io.h"
#include <unistd.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

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

static uint8_t buffer[BLOCK]; // BLOCK byte buffer
static uint32_t byte_index = 0;
static uint32_t bit_index;
static uint8_t writebuffer[BLOCK];
static uint32_t buffer_top = 0; // write_codes buffer index

int read_bytes(int infile, uint8_t *buf, int nbytes) {
    // This will be a useful wrapper function to perform reads.
    // This function will loop calls to read() until we have read all the bytes that were specified (nbytes) into the byte buffer buf.
    // Or until, there are no more bytes to read.
    // The number of bytes that were read from the input file descriptor, infile, is returned.
    // This function should be used whenever you need to perform a read.
    int bytes_read = 0;
    int current_bytes_read = 0;
    if (nbytes == 0) {
        return 0;
    }
    while ((current_bytes_read = read(infile, buf + bytes_read, nbytes - bytes_read)) > 0) {
        bytes_read += current_bytes_read;
        if (bytes_read == nbytes) {
            break;
        }
    }
    return bytes_read;
}

int write_bytes(int outfile, uint8_t *buf, int nbytes) {
    // This function is very much the same as read_bytes(), except that it is for looping calls to write().
    // write() is not guaranteed to write out all the specified bytes (nbytes)
    // Therefore, loop until we have either written out all the bytes specified from the byte buffer buf, or no bytes were written.
    // The number of bytes written out to the output file descriptor, outfile, is returned.
    // Use this function whenever you need to perform a write.
    int byte_write = 0;
    int current_byte_write = 0;
    if (nbytes == 0) {
        return 0;
    }
    while ((current_byte_write = write(outfile, buf + byte_write, nbytes - byte_write)) > 0) {
        byte_write += current_byte_write;
        if (byte_write == nbytes) {
            break;
        }
    }
    return byte_write;
}

bool read_bit(int infile, uint8_t *bit) {
    // Maintain a static buffer of bytes and an index into the buffer that tracks which bit to return through the pointer bit
    // The buffer will store BLOCK number of bytes, where BLOCK is yet another macro defined in defines.h.
    // This function returns false if there are no more bits that can be read
    // This function returns true if there are still bits to read.
    if (byte_index == 0) { // if the buffer is empty
        bit_index = 0; // set the bit_index equal to 0
        byte_index = read_bytes(infile, buffer, BLOCK); // read in the file and fill the buffer
    }

    uint8_t current_byte = buffer[byte_index / 8]; // CITE: Eugene's section on 02_25_2022
    uint8_t current_bit = current_byte >> (bit_index % 8); // CITE: Eugene's section on 02_25_2022
    current_bit &= 0x1;

    *bit = current_bit;
    bit_index += 1;

    byte_index -= bit_index / 8;

    if (byte_index == 0) {
        return false;
    } else {
        return true;
    }
}

void write_code(int outfile, Code *c) {
    // This function makes use of a static buffer and index.
    // Each bit in the code c will be buffered into the buffer.
    // The bits will be buffered starting from the 0 th bit in c.
    // When the buffer of BLOCK bytes is filled with bits, write the contents of the buffer to outfile.
    if (code_get_bit(c, buffer_top) == true) {
        writebuffer[buffer_top]
            = c->bits[buffer_top / 8]
              & (1 << (buffer_top % 8)); // set the bit to 1 and buffer to buffer
        buffer_top += 1;
    }
    if (code_get_bit(c, buffer_top) == false) {
        writebuffer[buffer_top]
            = c->bits[buffer_top / 8]
              & ~(1 << (buffer_top % 8)); // set the bit to 0 and buffer to buffer
        buffer_top += 1;
    }
    write_bytes(outfile, writebuffer, BLOCK); // write the block of bit  to the outfile
}

void flush_codes(int outfile) {
    // The sole purpose of this function is to write out any leftover, buffered bits.
    // Make sure that any extra bits in the last byte are zeroed before flushing the codes.
    while (buffer_top != 0) {
        buffer[buffer_top / 8] &= ~(1 << (buffer_top % 8));
        buffer_top -= 1;
    }
    write_bytes(
        outfile, buffer, byte_index); // CITE: Eugene's section on 02_25_2022; zeros out the buffer
}
