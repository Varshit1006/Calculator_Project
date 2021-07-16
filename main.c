#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <LCD.h>
#include <math.h>
#include <stdio.h>



typedef enum { false, true } bool;
double Number = 0;
double Num1;
double Num2;
char action;
char op;
char key;
int k =0;
int count=0;
int nc = 0;
int num=0;
int q=0;
double dnum=0;
int a =0;

 
void Circ_Init(void)
{

// Use PB pins for LCD interface
// Use PD pins for rows
// Use PC pins for coloumns
 
DDRB = 0xFF; // 1111.1111; set PB0-PB7 as outputs
DDRD=0b00000000; // Set PD4-PD7 as i/p
DDRC=0xFF;// Set PC0-PC5 as o/p
PORTD = 0xFF;    //enable all internal pull-ups  
return;

}

char READ_SWITCHES()
{
PORTC = 0b00000000;// Turn all rows to LOW
PORTD = 0b11111000;// Enable Pull-ups

if (!(PIND & (1<<PD3)))
{
// Change corresponding rows and check the i/p
PORTC=0b00001110;
PORTC=PORTC;
if (!(PIND & (1<<PD3)))
return '.';
PORTC=0b00001101;
PORTC=PORTC;
if (!(PIND & (1<<PD3)))
return 's';
PORTC=0b00001011;
PORTC=PORTC;
if (!(PIND & (1<<PD3)))
return 'o';
PORTC=0b00000111;
PORTC=PORTC;
if (!(PIND & (1<<PD3)))
return 'r';
}
//Check which coloumn has LOW i/p
if (!(PIND & (1<<PD4)))
{
// Change corresponding rows and check the i/p
PORTC=0b00001110;
PORTC=PORTC;
if (!(PIND & (1<<PD4)))
return '1';
PORTC=0b00001101;
PORTC=PORTC;
if (!(PIND & (1<<PD4)))
return '2';
PORTC=0b00001011;
PORTC=PORTC;
if (!(PIND & (1<<PD4)))
return '3';
PORTC=0b00000111;
PORTC=PORTC;
if (!(PIND & (1<<PD4)))
return '+';
}
else if (!(PIND & (1<<PD5)))
{
PORTC=0b00001110;
PORTC=PORTC;
if (!(PIND & (1<<PD5)))
return '4';
PORTC=0b00001101;
PORTC=PORTC;
if (!(PIND & (1<<PD5)))
return '5';
PORTC=0b00001011;
PORTC=PORTC;
if (!(PIND & (1<<PD5)))
return '6';
PORTC=0b00000111;
PORTC=PORTC;
if (!(PIND & (1<<PD5)))
return '-';
}

else if (!(PIND & (1<<PD6)))
{
PORTC=0b00001110;
PORTC=PORTC;
if (!(PIND & (1<<PD6)))
return '7';
PORTC=0b00001101;
PORTC=PORTC;
if (!(PIND & (1<<PD6)))
return '8';
PORTC=0b00001011;
PORTC=PORTC;
if (!(PIND & (1<<PD6)))
return '9';
PORTC=0b00000111;
PORTC=PORTC;
if (!(PIND & (1<<PD6)))
return '*';
}

else if (!(PIND & (1<<PD7)))
{
PORTC=0b00001110;
PORTC=PORTC;
if (!(PIND & (1<<PD7)))
return '=';

PORTC=0b00001101;
PORTC=PORTC;
if (!(PIND & (1<<PD7)))
return '0';
PORTC=0b00001011;
PORTC=PORTC;
if (!(PIND & (1<<PD7)))
return 'c';
PORTC=0b00000111;
PORTC=PORTC;
if (!(PIND & (1<<PD7)))
return '/';
}



return 'n';           // Means no key has been pressed
}




char get_key(void)
{
key = 'n';
while(key=='n')
{
key=READ_SWITCHES();
}
return key;
}
int x=0;
float i=1;
void DetectButtons()
{
char key=get_key();


   if(x==0)
   {
     if (key == '1') //If Button 1 is pressed
    {
nc++;
    if (Number==0)
    Number=1;
    else
    Number = (Number*10) + 1; //Pressed twice
    }
   
     if (key == '4') //If Button 4 is pressed
    {nc++;
    if (Number==0)
    Number=4;
    else
    Number = (Number*10) + 4; //Pressed twice
    }
   
     if (key == '7') //If Button 7 is pressed
    {nc++;
    if (Number==0)
    Number=7;
    else
    Number = (Number*10) + 7; //Pressed twice
    }
   
    if (key == '0')
    { nc++;//Button 0 is Pressed
    if (Number==0)
    Number=0;
    else
    Number = (Number*10) + 0; //Pressed twice
    }
   
     if (key == '2') //Button 2 is Pressed
    {nc++;
     if (Number==0)
    Number=2;
    else
    Number = (Number*10) + 2; //Pressed twice
    }
   
     if (key == '5')
    {nc++;
     if (Number==0)
    Number=5;
    else
    Number = (Number*10) + 5; //Pressed twice
    }
   
     if (key == '8')
    {nc++;
     if (Number==0)
    Number=8;
    else
    Number = (Number*10) + 8; //Pressed twice
    }  
   
     if (key == '3')
    {nc++;
     if (Number==0)
    Number=3;
    else
    Number = (Number*10) + 3; //Pressed twice
    }
   
     if (key == '6')
    {nc++;
    if (Number==0)
    Number=6;
    else
    Number = (Number*10) + 6; //Pressed twice
    }
   
     if (key == '9')
    {nc++;
    if (Number==0)
    Number=9;
    else
    Number = (Number*10) + 9; //Pressed twice
    }
}
     if (key == '.')
     {  
x++;
q=0;

}

if(x!=0)
{

if(key == '1')
{
Number=Number+0.1*i;
i*=0.1;
q++;
}
if(key == '2')
{
Number=Number+0.2*i;
i*=0.1;
q++;
}
if(key == '3')
{
Number=Number+0.3*i;
i*=0.1;
q++;
}
if(key == '4')
{
Number=Number+0.4*i;
i*=0.1;
q++;
}
if(key == '5')
{
Number=Number+0.5*i;
i*=0.1;
q++;
}
if(key == '6')
{
Number=Number+0.6*i;
i*=0.1;
q++;
}
if(key == '7')
{
Number=Number+0.7*i;
i*=0.1;
q++;
}
if(key == '8')
{
Number=Number+0.8*i;
i*=0.1;
q++;
}
if(key == '9')
{
Number=Number+0.9*i;
i*=0.1;
q++;
}
if(key == '0')
{
i*=0.1;
q++;
}
if (key == '=')
    {
    Num2=Number;
    }
}


if(key == 's'){
  if(count==0){
LCD_Clear();
    Num1 = Number;
    LCD_Char('S');
    LCD_Char('i');
    LCD_Char('n');
    LCD_Char('(');
    LCD_Message(DoubleToStr(Number));
    LCD_Char(')');
    Number = sin(Num1*M_PI/180);
}
  if(count==1){
backspace();
if(x==0){
for(int j=0;j<nc;j++){
backspace();
}
}
else{
for(int j=0;j<nc+q+1;j++){   //+1 because of the decial point
backspace();
}
}

    Num2 = Number;  
    LCD_Char('S');
    LCD_Char('i');
    LCD_Char('n');
    LCD_Char('(');
    LCD_Message(DoubleToStr(Number));
    LCD_Char(')');
    Number = sin(Num2*M_PI/180);
    count=0;
}
}

if(key == 'o'){
  if(count==0){
LCD_Clear();
    Num1 = Number;  
    LCD_Char('C');
    LCD_Char('o');
    LCD_Char('s');
    LCD_Char('(');
    LCD_Message(DoubleToStr(Number));
    LCD_Char(')');
    Number = cos(Num1*M_PI/180);
}
if(count==1){
backspace();
if(x==0){
for(int j=0;j<nc;j++){
backspace();
}
}
else{
for(int j=0;j<nc+q+1;j++){   //+1 because of the decial point
backspace();
}
}
    Num2 = Number;  
    LCD_Char('C');
    LCD_Char('o');
    LCD_Char('s');
    LCD_Char('(');
    LCD_Message(DoubleToStr(Number));
    LCD_Char(')');
    Number = cos(Num2*M_PI/180);
    count=0;
}
}

if(key == 'r'){
if(count==0){
LCD_Clear();
    Num1 = Number;  
    LCD_Char('S');
    LCD_Char('q');
    LCD_Char('r');
    LCD_Char('t');
    LCD_Char('(');
    LCD_Message(DoubleToStr(Number));
    LCD_Char(')');
    Number = sqrt(Num1);
}
if(count==1){
backspace();
if(x==0){
for(int j=0;j<nc;j++){
backspace();
}
}
else{
for(int j=0;j<nc+q+1;j++){   //+1 because of the decial point
backspace();
}
}
    Num2 = Number;  
    LCD_Char('S');
    LCD_Char('q');
    LCD_Char('r');
    LCD_Char('t');
    LCD_Char('(');
    LCD_Message(DoubleToStr(Number));
    LCD_Char(')');
    Number = sqrt(Num2);
    count=0;
}
}


 
  if (key == '+' || key == '-' || key == '*' || key == '/') //Detecting Buttons on Column 4
  {
x=0;
i=1;
count=1;
a=0;
nc=0;

    if (key == '+')
    {action = '+';}
     if (key == '-')
    {action = '-'; }
     if (key == '*')
    {action = '*';}
     if (key == '/')
    {action = '/';}
    if(k == 0){
    Num1 = Number;    
    Number =0;
    k = 1;
    op = key;
}

else{
Num2 = Number;
  if (op=='+')
    Number = Num1+Num2;

  if (op=='-')
    Number = Num1-Num2;

  if (op=='*')
    Number = Num1*Num2;

  if (op=='/')
    Number = Num1/Num2;
LCD_Clear();
LCD_Message(DoubleToStr(Number));
LCD_Char(key);
Num1 = Number;
op = key;

}
Number = 0;
}

if(key == '='){
Num2=Number;
LCD_Cmd(0xC0);
CalculateResult();
LCD_Message(DoubleToStr(Number));
_delay_ms(700);
key = get_key();
LCD_Clear();
init_var();
if (key != 'b' && key !='c' )  
{
LCD_Char(key);
}

DetectButtons();
}

}

void init_var(){
Number =0;
Num1=0;
Num2=0;
k=0;
i=1;
x=0;
count=0;
num=0;
dnum=0;
q=0;
a=0;
nc=0;
}

void CalculateResult()
{
  if (action=='+')
    Number = Num1+Num2;

  if (action=='-')
    Number = Num1-Num2;

  if (action=='*')
    Number = Num1*Num2;

  if (action=='/')
    Number = Num1/Num2;

}

void backspace(){
LCD_Cmd(0x10);
LCD_Char(' ');
LCD_Cmd(0x10);
}

int no_digits(double no){
int co;
if(x==0){
int numb=no;
while( numb!= 0)
     {
        co++;
        numb/= 10;
     }
 }
     else{
while(no<0){
no=no*10;
}

int numb=(int)no;
while( numb!= 0)
      {
        co++;
        numb/= 10;
      }
}

return co;
}

int main(void)
{
Circ_Init(); // Initialize the circuit
LCD_Init(); // initialize LCD controller

while(1)
{
key=get_key();
if(key=='1' ||key=='2' ||key=='3' ||key=='4' ||key=='5' ||key=='6' ||key=='7' ||key=='8' ||key=='9' ||key=='0' ){
if(x==0){
num = atoi(&key);
}
else{
dnum = atoi(&key);
for(int j=0;j<=q;j++){
dnum = dnum * 0.1;
}
}
}

if(key == 'c'){

if(a==0){
if(x==0){
backspace();
Number = (Number-num)/10;
nc--;
}
else{
backspace();
Number = Number-dnum;
q=q-1;
}
a=1;
}
_delay_ms(1000);
key = READ_SWITCHES();
if(key=='c'){
LCD_Clear();
init_var();
}
}

if (key != 'b' && key!='c' && key!='n')  
{
LCD_Char(key);
}

DetectButtons();

_delay_ms(500);
}
}
