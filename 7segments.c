// Hello world! Cplayground is an online sandbox that makes it easy to try out
// code.

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


static uint8_t DDRB = 0;
static uint8_t DDRC = 0;
static uint8_t DDRD = 0;

static uint8_t PORTB = 0;
static uint8_t PORTC = 0;
static uint8_t PORTD = 0;

static uint8_t PB0 = 0;
static uint8_t PB1 = 1;
static uint8_t PB2 = 2;
static uint8_t PB3 = 3;
static uint8_t PB4 = 4;
static uint8_t PB5 = 5;
static uint8_t PB6 = 6;
static uint8_t PB7 = 7;

static uint8_t PC0 = 0;
static uint8_t PC1 = 1;
static uint8_t PC2 = 2;
static uint8_t PC3 = 3;
static uint8_t PC4 = 4;
static uint8_t PC5 = 5;
static uint8_t PC6 = 6;
static uint8_t PC7 = 7;

static uint8_t PD0 = 0;
static uint8_t PD1 = 1;
static uint8_t PD2 = 2;
static uint8_t PD3 = 3;
static uint8_t PD4 = 4;
static uint8_t PD5 = 5;
static uint8_t PD6 = 6;
static uint8_t PD7 = 7;

struct RP {
    uint8_t *registry;
    uint8_t pin;
};


// CONSTANTS
static RP STICKS[7] = {
    {&DDRB, PB0},
    {&DDRB, PB1},
    {&DDRB, PB2},
    {&DDRB, PB3},
    {&DDRB, PB4},
    {&DDRB, PB5},
    {&DDRB, PB6},
};

static RP SEGMENTS[4] = {
    {&DDRB, PB0},
    {&DDRC, PC1},
    {&DDRD, PD2},
    {&DDRB, PB3},
};

// INTERFACES
struct RP get_stick_by_name(char n) {
    struct RP stick;
    switch (n) {
        case 'a': stick = STICKS[0];
        case 'b': stick = STICKS[1];
        case 'c': stick = STICKS[2];
        case 'd': stick = STICKS[3];
        case 'e': stick = STICKS[4];
        case 'f': stick = STICKS[5];
        case 'g': stick = STICKS[6];
    };
    return stick;
};

//
void set_n_bit(uint8_t* bits, int bit, int n){
   *bits = (*bits & ~(1<<n)) | (bit<<n);
};

//
void show_stick(char n) {
    struct RP stick = get_stick_by_name(n);
    set_n_bit(stick.registry, 1, stick.pin);
};

//
void hide_stick(char n) {
    struct RP stick = get_stick_by_name(n);
    set_n_bit(stick.registry, 0, stick.pin);
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

    printf("%i\n", DDRB);

    show_stick('a');
    show_stick('b');
    show_stick('c');
    show_stick('d');
    show_stick('e');

    printf("%i\n", DDRB);

    clear_segment();

    printf("%i\n", DDRB);


    // hide_stick('c');
    // hide_stick('b');
    // hide_stick('a');

    // // set_n_bit(&DDRB, 0, 2);
    // // set_n_bit(&DDRB, 0, 1);
    // // set_n_bit(&DDRB, 0, 0);

    // // set_n_bit(&DDRB, 1, 2);

    // printf("%i\n", DDRB);

    // activate_segment(0);
    // activate_segment(1);
    // activate_segment(2);
    // activate_segment(3);
    // printf("PORTB: %i\n", PORTB);
    // printf("PORTC: %i\n", PORTC);
    // printf("PORTD: %i\n", PORTD);

    // deactivate_segment(0);
    // deactivate_segment(1);
    // deactivate_segment(2);
    // deactivate_segment(3);
    // printf("PORTB: %i\n", PORTB);
    // printf("PORTC: %i\n", PORTC);
    // printf("PORTD: %i\n", PORTD);

    
    return 0;
}
