#ifdef __cplusplus
extern "C" {
#endif

#include "font3x5.h"
#include "font5x8.h"
#include "fonts/allfonts.h"

#ifndef GLCD_H
#define GLCD_H

//data
/*
#define KS0108_0_OUT    PLIB_PORTS_PinDirectionOutputSet(PORTS_ID_0, GLCD_DB0_PORT, GLCD_DB0_PIN)
#define KS0108_1_OUT    PLIB_PORTS_PinDirectionOutputSet(PORTS_ID_0, GLCD_DB1_PORT, GLCD_DB1_PIN)
#define KS0108_2_OUT    PLIB_PORTS_PinDirectionOutputSet(PORTS_ID_0, GLCD_DB2_PORT, GLCD_DB2_PIN)
#define KS0108_3_OUT    PLIB_PORTS_PinDirectionOutputSet(PORTS_ID_0, GLCD_DB3_PORT, GLCD_DB3_PIN)
#define KS0108_4_OUT    PLIB_PORTS_PinDirectionOutputSet(PORTS_ID_0, GLCD_DB4_PORT, GLCD_DB4_PIN)
#define KS0108_5_OUT    PLIB_PORTS_PinDirectionOutputSet(PORTS_ID_0, GLCD_DB5_PORT, GLCD_DB5_PIN)
#define KS0108_6_OUT    PLIB_PORTS_PinDirectionOutputSet(PORTS_ID_0, GLCD_DB6_PORT, GLCD_DB6_PIN)
#define KS0108_7_OUT    PLIB_PORTS_PinDirectionOutputSet(PORTS_ID_0, GLCD_DB7_PORT, GLCD_DB7_PIN)
#define KS0108_D_OUT    KS0108_0_OUT; KS0108_1_OUT; KS0108_2_OUT; KS0108_3_OUT; KS0108_4_OUT; KS0108_5_OUT; KS0108_6_OUT; KS0108_7_OUT

#define KS0108_0_IN     PLIB_PORTS_PinDirectionInputSet(PORTS_ID_0, GLCD_DB0_PORT, GLCD_DB0_PIN)
#define KS0108_1_IN     PLIB_PORTS_PinDirectionInputSet(PORTS_ID_0, GLCD_DB1_PORT, GLCD_DB1_PIN)
#define KS0108_2_IN     PLIB_PORTS_PinDirectionInputSet(PORTS_ID_0, GLCD_DB2_PORT, GLCD_DB2_PIN)
#define KS0108_3_IN     PLIB_PORTS_PinDirectionInputSet(PORTS_ID_0, GLCD_DB3_PORT, GLCD_DB3_PIN)
#define KS0108_4_IN     PLIB_PORTS_PinDirectionInputSet(PORTS_ID_0, GLCD_DB4_PORT, GLCD_DB4_PIN)
#define KS0108_5_IN     PLIB_PORTS_PinDirectionInputSet(PORTS_ID_0, GLCD_DB5_PORT, GLCD_DB5_PIN)
#define KS0108_6_IN     PLIB_PORTS_PinDirectionInputSet(PORTS_ID_0, GLCD_DB6_PORT, GLCD_DB6_PIN)
#define KS0108_7_IN     PLIB_PORTS_PinDirectionInputSet(PORTS_ID_0, GLCD_DB7_PORT, GLCD_DB7_PIN)
#define KS0108_D_IN     KS0108_0_IN; KS0108_1_IN; KS0108_2_IN; KS0108_3_IN; KS0108_4_IN; KS0108_5_IN; KS0108_6_IN; KS0108_7_IN
#define KS0108_D_READ   PLIB_PORTS_PinGet(PORTS_ID_0, GLCD_DB0_PORT, GLCD_DB0_PIN) + (PLIB_PORTS_PinGet(PORTS_ID_0, GLCD_DB1_PORT, GLCD_DB1_PIN) << 1) +  (PLIB_PORTS_PinGet(PORTS_ID_0, GLCD_DB2_PORT, GLCD_DB2_PIN) << 2) + (PLIB_PORTS_PinGet(PORTS_ID_0, GLCD_DB3_PORT, GLCD_DB3_PIN) << 3) + (PLIB_PORTS_PinGet(PORTS_ID_0, GLCD_DB4_PORT, GLCD_DB4_PIN) << 4) + (PLIB_PORTS_PinGet(PORTS_ID_0, GLCD_DB5_PORT, GLCD_DB5_PIN) << 5) + (PLIB_PORTS_PinGet(PORTS_ID_0, GLCD_DB6_PORT, GLCD_DB6_PIN) << 6) + (PLIB_PORTS_PinGet(PORTS_ID_0, GLCD_DB7_PORT, GLCD_DB7_PIN) << 7)
*/
//control
//#define glcd_control_dir_0  TRISC
//#define glcd_control_dir_1  TRISB
/*#define glcd_RST RB5
#define glcd_CSB RC7
#define glcd_CSA RC6
#define glcd_RS  RC0
#define glcd_RW  RC1
#define glcd_E   RC2 */

//definitions
#define glcd_OFF 0
#define glcd_ON  1
#define glcd_COMMAND 0
#define glcd_BYTE    1

#define GLCD_DOUBLE_DELAY 1000000
#define GLCD_DELAY        4

#define GLCD_INVERT_X
#define GLCD_INVERT_Y

#define GLCD_HEIGHT 64
#define GLCD_WIDTH  128
#define GLCD_PAGES  8

static const signed char glcd_pot_15_x[33] = {-4,-5,-6,-6,-7,-7,-7,-7,-7,-6,-6,-5,-4,-3,-2,-1,0,1,2,3,4,5,6,6,7,7,7,7,7,6,6,5,4};
static const signed char glcd_pot_15_y[33] = {-6,-5,-4,-3,-2,-1,0,1,2,3,4,5,6,6,7,7,7,7,7,6,6,5,4,3,2,1,0,-1,-2,-3,-4,-5,-6};

//#define TMS_PLATFORM

//functions phisical layer
void glcd_flushPage(void);
void glcd_flushAll(void);
void glcd_initialize(void);
//void glcd_setController(char, char);
void glcd_writeBus(char);
void glcd_write(char, char);
char glcd_read(char);
//void glcd_writeByteAt(char, char, char);
void glcd_writeByteBufferedAt(char, char, char, char);
//functions user layer
void glcd_clear(char);
void glcd_drawPixel(unsigned char, unsigned char, char);
void glcd_drawLine(unsigned char, unsigned char, unsigned char, unsigned char, char);
void glcd_drawCircle(unsigned char, unsigned char, unsigned char, char);
void glcd_fillCircle(unsigned char, unsigned char, unsigned char, char);
void glcd_drawRect(unsigned char, unsigned char, unsigned char, unsigned char, char);
int glcd_drawChar2(int, int, char, const unsigned char * font, char);
int glcd_drawCharLimited(int, int, int, int, char, const unsigned char * font, char);
void glcd_fillRect(unsigned char, unsigned char, unsigned char, unsigned char, char);
void glcd_drawChar(unsigned char, unsigned char, char, char);
void glcd_drawBigChar(unsigned char, unsigned char, char, char);
void glcd_drawString(unsigned char, unsigned char, char*, char);
int glcd_drawStringFont(unsigned char x, unsigned char y, char *string, const unsigned char * font, char color);
int glcd_drawStringFontLimited(int x, int y, int max_x, int offset, char * string, const unsigned char * font, char color);
void glcd_drawStringFontCentered(unsigned char x, unsigned char y, unsigned char count, char *string, const unsigned char * font, char color);
int glcd_drawStringFontRightAligned(unsigned char x, unsigned char y, char * string, const unsigned char * font, char color);
int glcd_drawStringFontRightAlignedTrim(unsigned char x, unsigned char y, int trim, int pos, char * string, const unsigned char * font, char color);
void glcd_drawBigString(unsigned char, unsigned char, char*, char);
void glcd_drawStringCentered(unsigned char, unsigned char, unsigned char, char*, char);
void glcd_drawBigStringCentered(unsigned char, unsigned char, unsigned char, char*, char);
void glcd_drawInt(unsigned char, unsigned char, int, char);
void glcd_drawHex(unsigned char, unsigned char, unsigned int, char);
void glcd_drawCharInt(unsigned char, unsigned char, unsigned char, char);
void glcd_drawFloat(unsigned char, unsigned char, float, char);
void glcd_drawPot(unsigned char, unsigned char, unsigned char, float, float, float, char);
void glcd_drawPotLog(unsigned char, unsigned char, unsigned char, float, float, float, char);
void glcd_drawBar1(unsigned char, unsigned char, unsigned char, unsigned char, unsigned char, unsigned char, float, float, float, char);
void glcd_drawVu(unsigned char, unsigned char, unsigned char, unsigned char, float, float, float, char);
void glcd_drawSmallArrow(unsigned char x, unsigned char y, unsigned char dir, unsigned char color);
void glcd_drawArrow(unsigned char, unsigned char, unsigned char, unsigned char);
void glcd_drawIcon(unsigned char, unsigned char, unsigned char[], unsigned char, unsigned char);
void glcd_drawFullImage(const unsigned char * image);
void glcd_drawScrollBar(unsigned char, unsigned char, unsigned char, int, int);
void glcd_drawFullImageOffset(const unsigned char * image, char offset);
//void glcd_drawSpectrum(unsigned char x, unsigned char y, unsigned char spectrumWidth, unsigned char spectrumHeigth, float * IR, unsigned int NTaps);
void glcd_drawImage(const unsigned char * image, unsigned char x, unsigned char y, unsigned char rows, unsigned char columns, unsigned char type); //rows e columns multipli di 8!

#endif

#ifdef __cplusplus
}
#endif
