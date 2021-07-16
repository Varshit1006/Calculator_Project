#include <avr/io.h> 
#include <util/delay.h> 
#include <stdlib.h> 
#include <string.h>

#define alloc(T,len)(T*)malloc((len)*sizeof(T))

// TYPEDEFS
typedef uint8_t byte; // changed the name


// ------------------
//LCD DRIVER ROUTINES
//
// Routines:
// LCD_Init initializes the LCD controller
// LCD_Cmd sends LCD controller command
// LCD_Char sends single ascii character to display
// LCD_Clear clears the LCD display & homes cursor
// LCD_Integer displays an integer value
// LCD_Message displays a string
// PortB is used for data communications with the HD44780-controlled LCD.
// The following defines specify which port pins connect to the controller:
#define ClearBit(x,y) x &= ~_BV(y) // equivalent to cbi(x,y)
#define SetBit(x,y) x |= _BV(y) // equivalent to sbi(x,y)
#define LCD_RS 0 // pin for LCD R/S (eg PB0)
#define LCD_E 1 // pin for LCD enable
#define DAT4 2 // pin for d4
#define DAT5 3 // pin for d5
#define DAT6 4 // pin for d6
#define DAT7 5 // pin for d7
//// The following defines are controller commands
#define CLEARDISPLAY 0x01

void PulseEnableLine ()
{
 SetBit(PORTB,LCD_E); // take LCD enable line high
 _delay_us(40); // wait 40 microseconds
 ClearBit(PORTB,LCD_E); // take LCD enable line low
}
void SendNibble(byte data)
{
 PORTB &= 0xC3; // 1100.0011 = clear 4 data lines
 if (data & _BV(4)) SetBit(PORTB,DAT4);
 if (data & _BV(5)) SetBit(PORTB,DAT5);
 if (data & _BV(6)) SetBit(PORTB,DAT6);
 if (data & _BV(7)) SetBit(PORTB,DAT7);
 PulseEnableLine(); // clock 4 bits into controller
}
void SendByte (byte data)
{
 SendNibble(data); // send upper 4 bits
 SendNibble(data<<4); // send lower 4 bits
 ClearBit(PORTB,5); // turn off boarduino LED
}
void LCD_Cmd (byte cmd)
{
 ClearBit(PORTB,LCD_RS); // R/S line 0 = command data
 SendByte(cmd); // send it
}
void LCD_Char (byte ch)
{
 SetBit(PORTB,LCD_RS); // R/S line 1 = character data
 SendByte(ch); // send it
}
void LCD_Init()
{
 LCD_Cmd(0x33); // initialize controller
 LCD_Cmd(0x32); // set to 4-bit input mode
 LCD_Cmd(0x28); // 2 line, 5x7 matrix
 LCD_Cmd(0x0C); // turn cursor off (0x0E to enable)
 LCD_Cmd(0x06); // cursor direction = right
 LCD_Cmd(0x01); // start with clear display
 _delay_ms(3); // wait for LCD to initialize
}
void LCD_Clear() // clear the LCD display
{
 LCD_Cmd(CLEARDISPLAY);
 _delay_ms(3); // wait for LCD to process command
}

void LCD_Message(const char *text) // display string on LCD
{
 while (*text) // do until /0 character
 LCD_Char(*text++); // send char & update char pointer
}

void LCD_Integer(int data)
// displays the integer value of DATA at current LCD cursor position
{
 char st[8] = ""; // save enough space for result
 itoa(data,st,10); // 
 LCD_Message(st); // display in on LCD
}

int toint(char str[])
{
    int len = strlen(str);
    int i, num = 0;
 
    for (i = 0; i < len; i++)
    {
        num = num + ((str[len - (i + 1)] - '0') * pow(10, i));
    }
 
   return num;
}



char* DoubleToStr(double num){
 int start = num >= 0 ? 0 : 1;
 if (start == 1) num = -num;
 int bdp = 0, adp = 0;
 int n = num;
 do {
        bdp++;
        n /= 10;
    } while (n != 0);
    int temp = 10000;
 n = (int)((num+10e-5 - (int)num)*temp);
 while (n % temp != 0) { temp /= 10; adp++; }
 
 n = (int)num;
 char* str = (char*)malloc((bdp+(start==0 ? 1 : 2))*sizeof(char));
 if (start == 1) str[0] = '-';
 str[bdp+start] = adp == 0 ? '\0' : '.';
 
 for (int i = 0; i < bdp; i++){
        str[start + bdp - (i + 1)] = ((n % 10) + '0');
        n = n / 10;
    }
    if (adp == 0) return str;
    temp = 1;
    for (int i=0; i<adp; i++) temp *= 10;
    n = (int)((num+10e-5 - (int)num)*temp);
   
    for (int i = 0; i < adp; i++){
        str[start + (bdp+1) + adp - (i + 1)] = ((n % 10) + '0');
        n = n / 10;
    }
    str[start+bdp+adp+1] = '\0';
 return str;
}
int isDigit(char c){ return '0' <= c && c <= '9'; }
double readNum(const char* str, int *index){
 int mul = 1;
 if (str[*index] == '-'){ (*index)++; mul = -1; }
 double num = 0;
 while (str[*index] != 0){
  if (!isDigit(str[*index])) break;
  num *= 10.0;
  num += str[(*index)++] - '0';
 }
 if (str[*index] != '.') return mul*num;
 (*index)++; double m10 = 10;
 while (str[*index] != 0){
  if (!isDigit(str[*index])) break;
  num += (str[(*index)++] - '0')/m10; m10 *= 10;
 }
 return mul*num;
}
void LCD_Double(double data)
// displays the Double value of DATA at current LCD cursor position
{
 char* st = DoubleToStr(data); // save enough space for result // 
 LCD_Message(st); // display in on LCD
}
