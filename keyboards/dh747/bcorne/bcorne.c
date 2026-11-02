#include "quantum.h"

#ifdef RGB_MATRIX_ENABLE

led_config_t g_led_config = {
    {

         // matrix rows 0-4 = left half, rows 5-9 = right half (sequential, not paired)
         // chain order (left): top(0-5) > Q row(6-11) > PgUp(12) > home row(13-18) > Mute(19) > Z row(20-25) > thumbs(26-28)
         // PgDn (matrix 2,6) has no under-key LED. right half mirrored.
         { 0,      1,      2,      3,      4,      5,      NO_LED },                // matrix row 0: L top row (Esc/1/2/3/4/5)
         { 6,      7,      8,      9,      10,     11,     12 },                    // matrix row 1: L Q row + PgUp (LED 12 at (1,6))
         { 13,     14,     15,     16,     17,     18,     19 },                    // matrix row 2: L home row + PgDn (LED 19 at (2,6))
         { 20,     21,     22,     23,     24,     25,     NO_LED },                // matrix row 3: L Z row, Mute no LED (no LED at (3,6))
         { NO_LED, NO_LED, NO_LED, 26,     27,     28,     NO_LED },                // matrix row 4: L thumbs - Del=26, MO(1)=27, Space=28
         { NO_LED, 29,     30,     31,     32,     33,     34 },                    // matrix row 5: R top row (cols ascending)
         { 35,     36,     37,     38,     39,     40,     41 },                    // matrix row 6: R Q row + "{[" (cols 0-6 ascending, all align matrix col)
         { 42,     43,     44,     45,     46,     47,     48 },                    // matrix row 7: R home row + MediaPlay (cols 0-6 ascending)
         { NO_LED, 49,     50,     51,     52,     53,     54 },                    // matrix row 8: R Z row, "}]" no LED (col 0 silent, cols 1-6 ascending)
         { NO_LED, 55,     56,     57,     NO_LED, NO_LED, NO_LED },                // matrix row 9: R thumbs - Enter=55, MO(3)=56, Bksp=57 (mirror)

    },

  {
        // LED Index to Physical Position
         {0,12},   {16,12}, {32,12}, {48,12}, {64,12},{80,12},              //             {128,12}, {144,12}, {160,12}, {178,12},{194,12}, {210,12},
         {0,25},   {16,25}, {32,25}, {48,25}, {64,25},{80,25},     {96,25}, // {112,25},   {128,25}, {144,25}, {160,25}, {178,25},{194,25}, {210,25},
         {0,38},   {16,38}, {32,38}, {48,38}, {64,38},{80,38},     {96,38}, // {112,38},   {128,38}, {144,38}, {160,38}, {178,38},{194,38}, {210,38},
         {0,51},   {16,51}, {32,51}, {48,51}, {64,51},{80,51},               //            {128,51}, {144,51}, {160,51}, {178,51},{194,51}, {210,51},
                            {32,63}, {48,63}, {64,63},              // {112,63},   {128,63}, {144,63}, {160,63}, {178,63},

                     {128,12}, {144,12}, {160,12}, {178,12},{194,12}, {210,12},
         {112,25},   {128,25}, {144,25}, {160,25}, {178,25},{194,25}, {210,25},
         {112,38},   {128,38}, {144,38}, {160,38}, {178,38},{194,38}, {210,38},
                     {128,51}, {144,51}, {160,51}, {178,51},{194,51}, {210,51},
                     {112,63}, {128,63}, {144,63},
     },

 {
      // LED Index to Flag
      4,4,4,4,4,4,\
      4,4,4,4,4,4,4,\
      4,4,4,4,4,4,4,\
      4,4,4,4,4,4,\
         4,4,4,\
        4,4,4,4,4,4,\
      4,4,4,4,4,4,4,\
      4,4,4,4,4,4,4,\
        4,4,4,4,4,4,\
     4,4,4,
    }
};

#endif

// Soft entry to the PlumBL bootloader
void bootloader_jump(void) {
    *(volatile uint32_t *)0x2000FC00UL = 0xC220B134UL;
    NVIC_SystemReset();
}
