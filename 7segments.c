#define F_CPU 1000000UL
// #include <avr/io.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <util/delay.h>

// static uint8_t DDRB = 0;
// static uint8_t DDRC = 0;
// static uint8_t DDRD = 0;

// static uint8_t PORTB = 0;
// static uint8_t PORTC = 0;
// static uint8_t PORTD = 0;

// static uint8_t PB0 = 0;
// static uint8_t PB1 = 1;
// static uint8_t PB2 = 2;
// static uint8_t PB3 = 3;
// static uint8_t PB4 = 4;
// static uint8_t PB5 = 5;
// static uint8_t PB6 = 6;
// static uint8_t PB7 = 7;

// static uint8_t PC0 = 0;
// static uint8_t PC1 = 1;
// static uint8_t PC2 = 2;
// static uint8_t PC3 = 3;
// static uint8_t PC4 = 4;
// static uint8_t PC5 = 5;
// static uint8_t PC6 = 6;
// static uint8_t PC7 = 7;

// static uint8_t PD0 = 0;
// static uint8_t PD1 = 1;
// static uint8_t PD2 = 2;
// static uint8_t PD3 = 3;
// static uint8_t PD4 = 4;
// static uint8_t PD5 = 5;
// static uint8_t PD6 = 6;
// static uint8_t PD7 = 7;

struct RP {
    uint8_t *registry;
    uint8_t pin;
};


// CONSTANTS
static RP STICKS[7] = {
    {&DDRD, PD6}, // a
    {&DDRD, PD4}, // b
    {&DDRD, PD2}, // c
    {&DDRC, PC5}, // d
    {&DDRC, PC4}, // e
    {&DDRD, PD5}, // f
    {&DDRD, PD3}, // g
};

static RP SEGMENTS[4] = {
    {&DDRC, PC0},
    {&DDRC, PC1},
    {&DDRC, PC2},
    {&DDRC, PC3},
};

// INTERFACES
struct RP* get_stick_by_name(char n) {
    struct RP *stick;

    if (n == 'a') return &STICKS[0];
    if (n == 'b') return &STICKS[1];
    if (n == 'c') return &STICKS[2];
    if (n == 'd') return &STICKS[3];
    if (n == 'e') return &STICKS[4];
    if (n == 'f') return &STICKS[5];
    if (n == 'g') return &STICKS[6];
};

//
void set_n_bit(uint8_t *bits, int bit, int n){
   *bits = (*bits & ~(1<<n)) | (bit<<n);
};

//
void show_stick(char n) {
    struct RP *stick = get_stick_by_name(n);
    set_n_bit(stick->registry, 1, stick->pin);
};

//
void hide_stick(char n) {
    struct RP *stick = get_stick_by_name(n);
    set_n_bit(stick->registry, 1, stick->pin);
};

//
void activate_segment(uint8_t n) {
    struct RP &seg = SEGMENTS[n];
    uint8_t * port;

    if (seg.registry == &DDRB) port = &PORTB;
    if (seg.registry == &DDRC) port = &PORTC;
    if (seg.registry == &DDRD) port = &PORTD;

    set_n_bit(seg.registry, 1, seg.pin);
    set_n_bit(port, 1, seg.pin);
};

//
void deactivate_segment(uint8_t n) {
    struct RP &seg = SEGMENTS[n];
    uint8_t * port;

    if (seg.registry == &DDRB) port = &PORTB;
    if (seg.registry == &DDRC) port = &PORTC;
    if (seg.registry == &DDRD) port = &PORTD;

    set_n_bit(seg.registry, 0, seg.pin);
    set_n_bit(port, 0, seg.pin);
};

//
void clear_segment() {
    uint8_t i;
    for (i=0; i<sizeof(STICKS)/sizeof(STICKS[0]); i++) {
        set_n_bit(STICKS[i].registry, 0, STICKS[i].pin);
    }
};

//

int main() {
    
    activate_segment(0);
    activate_segment(1);
    activate_segment(2);
    activate_segment(3);

    show_stick('a');
    show_stick('b');
    show_stick('c');
    show_stick('d');
    show_stick('e');
    show_stick('f');
    show_stick('g');


    while (1) {
    }
    
    return 0;
}
