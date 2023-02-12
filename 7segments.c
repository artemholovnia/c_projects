#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int BASE_ANOD = 1;
int SEGMENTS_NUM = 4;

struct RP {
    uint8_t *registry;
    uint8_t pin;
};


// CONSTANTS
static RP STICKS[7] = {
    {&DDRB, PB2}, // a (11)
    {&DDRB, PB3}, // b (7)
    {&DDRD, PD6}, // c (4)
    {&DDRB, PB0}, // d (2)
    {&DDRD, PD7}, // e (1)
    {&DDRB, PB4}, // f (10)
    {&DDRD, PD5}, // g (5)
};

static RP SEGMENTS[4] = {
    {&DDRC, PC2},
    {&DDRB, PB5},
    {&DDRC, PC0},
    {&DDRC, PC1},
};

static char NUMS[10][7] = {
  {'a', 'b', 'c', 'd', 'e', 'f'},
  {'b', 'c'},
  {'a', 'b', 'd', 'e', 'g'},
  {'a', 'b', 'c', 'd', 'g'},
  {'b', 'c', 'f', 'g'},
  {'a', 'c', 'd', 'f', 'g'},
  {'a', 'c', 'd', 'e', 'f', 'g'},
  {'a', 'b', 'c'},
  {'a', 'b', 'c', 'd', 'e', 'f', 'g'},
  {'a', 'b', 'c', 'd', 'f', 'g'},
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

// INTERFACES
void set_n_bit(uint8_t *bits, int bit, int n){
   *bits = (*bits & ~(1<<n)) | (bit<<n);
};

//
void show_stick(char n) {
    struct RP *stick = get_stick_by_name(n);
    set_n_bit(stick->registry, 1, stick->pin);

    if (BASE_ANOD == 1) {
      uint8_t * port;
      if (stick->registry == &DDRB) port = &PORTB;
      if (stick->registry == &DDRC) port = &PORTC;
      if (stick->registry == &DDRD) port = &PORTD;
      set_n_bit(port, 1, stick->pin);
    }

};

//
void hide_stick(char n) {
    struct RP *stick = get_stick_by_name(n);
    set_n_bit(stick->registry, 0, stick->pin);

    if (BASE_ANOD == 1) {
      uint8_t * port;
      if (stick->registry == &DDRB) port = &PORTB;
      if (stick->registry == &DDRC) port = &PORTC;
      if (stick->registry == &DDRD) port = &PORTD;
      set_n_bit(port, 0, stick->pin);
    }

};

//
void activate_segment(uint8_t n) {
    struct RP &seg = SEGMENTS[n];
    set_n_bit(seg.registry, 1, seg.pin);

    if (BASE_ANOD == 0) {
      uint8_t * port;
      if (seg.registry == &DDRB) port = &PORTB;
      if (seg.registry == &DDRC) port = &PORTC;
      if (seg.registry == &DDRD) port = &PORTD;
      set_n_bit(port, 1, seg.pin);
    }
};

//
void deactivate_segment(uint8_t n) {
    struct RP &seg = SEGMENTS[n];
    set_n_bit(seg.registry, 0, seg.pin);

    if (BASE_ANOD == 0) {
      uint8_t * port;
      if (seg.registry == &DDRB) port = &PORTB;
      if (seg.registry == &DDRC) port = &PORTC;
      if (seg.registry == &DDRD) port = &PORTD;
      set_n_bit(port, 0, seg.pin);
    }
};

void deactivate_all_segments(){
  uint8_t i;
  for (i=0; i<SEGMENTS_NUM; i++){
    deactivate_segment(i);
  }
};

void clear_segment() {
    uint8_t i;
    for (i=0; i<sizeof(STICKS)/sizeof(STICKS[0]); i++) {
      struct RP *stick = &STICKS[i];
      set_n_bit(stick->registry, 0, stick->pin);

      if (BASE_ANOD == 1) {
        uint8_t * port;
        if (stick->registry == &DDRB) port = &PORTB;
        if (stick->registry == &DDRC) port = &PORTC;
        if (stick->registry == &DDRD) port = &PORTD;
        set_n_bit(port, 0, stick->pin);
      }
    }
};

void show_num(uint8_t n, uint8_t sn) {
  clear_segment();
  deactivate_all_segments();
  activate_segment(sn);
  uint8_t i;
  for (i=0; i<sizeof(NUMS[n])/sizeof(NUMS[n][0]); i++) {
    show_stick(NUMS[n][i]);
  }
};

int main() {
    
    deactivate_segment(0);
    deactivate_segment(1);
    deactivate_segment(2);
    deactivate_segment(3);

    while (1) {
      show_num(2, 3);
      show_num(8, 2);
      show_num(1, 1);
      show_num(0, 0);
    }
    
    return 0;
}
