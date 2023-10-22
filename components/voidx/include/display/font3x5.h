#ifdef __cplusplus
extern "C" {
#endif

#ifndef FONT_H
#define FONT_H

#define glcd_font_length 3
#define glcd_font_height 5

#define glcd_font_num  0
#define glcd_font_lett 10
#define glcd_font_spec 36

static const unsigned char glcd_font[] = {
248,136,248, // 0
136,248,128, // 1
232,168,184, // 2
168,168,248, // 3
56,32,248,   // 4
184,168,232, // 5
248,168,232, // 6
8,8,248,     // 7
248,168,248, // 8
184,168,248, // 9
240,40,240,  // A
248,168,80,  // B
112,136,136, // C
248,136,112, // D
248,168,136, // E
248,40,8,    // F
248,168,232, // G
248,32,248,  // H
136,248,136, // I
200,136,120, // J
248,32,216,  // K
248,128,128, // L
248,48,248,  // M
248,112,248, // N
112,136,112, // O
248,40,16,   // P
112,200,240, // Q
248,40,208,  // R
176,168,104, // S
8,248,8,     // T
120,128,248, // U
24,96,248,   // V
248,96,248,  // W
216,32,216,  // X
56,224,56,   // Y
200,168,152, // Z
0,0,0,       // (space)
128,128,128, // _
32,32,32,    // -
0,80,0,      // :
0,128,0,     // .
32,112,32    // +
};

int getFontAddress(char);
char isValue(char car);

#ifdef __cplusplus
}
#endif

#endif
