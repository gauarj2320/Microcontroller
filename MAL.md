## Experiment-1

- Program to store PRN in R register

```
ORG 0H
MOV R0,#22H
MOV R1,#07H
MOV R2,#12H
MOV R3,#34H
MOV R4,#30H
```

- program to add prn digits

```
ORG 0H
MOV R0,#22H
MOV R1,#07H
MOV R2,#12H
MOV R3,#34H
MOV R4,#30H
MOV A,R0
ADD A,R1
ADD A,R2
ADD A,R3
ADD A,R4

```

## Experiment-2 Arithmatic and Logical Operations

- AND

```
ORG 0H
MOV A, #0FH
ANL A,#F0H
```

- OR

```
ORG 0H
MOV A, #0FH
ORL A,#F0H
```

- XOR

```
ORG 0H
MOV A, #0FH
XRL A,#F0H
```

- NOT

```
ORG 0H
MOV A, #0FH
CPL A
```

## Experiment-3 Addressing Modes

1. Immediate addressing

```
ORG 0H
MOV A,#CBH
MOV R0,#ACH
```

2. Register addressing

```
ORG 0H
MOV R0,#AAH
MOV A,R0
```

3. Register Indirect addressing

```
ORG 0H
MOV R0, #20H
MOV 20H,#AAH
MOV A,@R0
```

4. Direct Addressing

```
ORG 0H
MOV 20H,#AAH
MOV A,20H
```

5. Register Bank

```
ORG 0H
SETB PSW.4
SETB PSW.3
MOV R0,#34H
```

6. Port

```
ORG 0H
MOV A,#55H
MOV P1,A
END
```

## Experiment-5

```
ORG 0H
MOV A,#55H
MOV R0,#0AH
LOOP:
    MOV R1,#70
    ACALL INNER_LOOP
    DJNZ R0,LOOP
INNER_LOOP:
    CPL A
    DJNZ R1,INNER_LOOP
    RET
```

```
ORG OH
START: SET B P1.0
       ACALL DELAY;
       CPL P1.0
       SJMP START
DELAY: MOV R2,#OFFH
       DJNZ R2,NEXT
       NEXT: NOP
             RET
             END
```

## Experiment-6

```

```

# Experiment -8 LED Blinking

- Theory:
- I/O ports in PiC18

  - PIC18 has 5 I/O ports PORTX(X=A,B,C,D,E)---> 8bit in size
  - This ports are controlled by register which control it's direction ,value etc.
  - TRISX
    - Controls direction of port whether to use it as input or output
    - TRISX=0 port is used as output
    - TRISX=1 port is used as input
  - LATX
    - Used to set output value of port
  - PORTX
    - Used to read the current state of port

- 1. Program to blink all 8 leds of PORTB
- Code:

```C
#include<pic18f4520.h>
#pragma config OSC=HS
#pragma config WDT=OFF
#pragma config LVP=OFF
#pragma config DEBUG=OFF
#pragma config IESO=OFF
#pragma config FCMEN=OFF

void delay(int a);
void main()
{
    TRISB=0x00;
    while(1){
        LATB=0xFF;
        delay(100);
        LATB=0x00;
        delay(100);
    }

}
void delay(int a){
    for(int i=0;i<a;i++>){
        for(int j=0;j<1275;j++);
    }
}
```

- program to turn on alternal leds

```C
#include<pic18f4520.h>
#pragma config OSC=HS
#pragma config WDT=OFF
#pragma config LVP=OFF
#pragma config DEBUG=OFF
#pragma config IESO=OFF
#pragma config FCMEN=OFF

void delay(int a);
void main()
{
    TRISB=0x00;
    while(1){
        LATB=0xAA;
        delay(100);
        LATB=0X55;
        delay(100);
    }

}
void delay(int a){
    for(int i=0;i<a;i++>){
        for(int j=0;j<1275;j++);
    }
}
```

## Experiment-9 Led and switch

```C
#include<pic18f4520.h>
#pragma config OSC=HS
#pragma config WDT=OFF
#pragma config LVP=OFF
#pragma config DEBUG=OFF
#pragma config IESO=OFF
#pragma config FCMEN=OFF

void delay(int a);
void main()
{
    TRISB=0x00;
    TRISC=0xFF;
    LATB=0x00;
    while(1){
        if(PORTCbits.RC0==1){
            LATBbits.LATB0=1;
        }
        else{
            LATBbits.LATB0=0;
        }
        delay(100);
    }


}
void delay(int a){
    for(int i=0;i<a;i++){
        for(int j=0;j<1275;j++);
    }
}
```

- program to control leds

```C
#include<pic18f4520.h>
#pragma config OSC=HS
#pragma config WDT=OFF
#pragma config LVP=OFF
#pragma config DEBUG=OFF
#pragma config IESO=OFF
#pragma config FCMEN=OFF

void delay(int a);
void main()
{
    TRISB=0x00;
    TRISC=0xFF;
    LATB=0x00;
    while(1){
       LATB=PORTC;
       delay(100);
    }


}
void delay(int a){
    for(int i=0;i<a;i++){
        for(int j=0;j<1275;j++);
    }
}
```

- task-3:

```C
#include<pic18f4520.h>
#pragma config OSC=HS
#pragma config WDT=OFF
#pragma config LVP=OFF
#pragma config DEBUG=OFF
#pragma config IESO=OFF
#pragma config FCMEN=OFF

void delay(int a);
void main()
{
    TRISB=0x00;
    TRISC=0xFF;
    LATB=0x00;
    while(1){
        LATBbits.LATB0=POTRCbits.RC4;
        LATBbits.LATB1=POTRCbits.RC5;
        LATBbits.LATB2=POTRCbits.RC6;
        LATBbits.LATB3=POTRCbits.RC7;
        LATBbits.LATB4=POTRCbits.RC0;
        LATBbits.LATB5=POTRCbits.RC1;
        LATBbits.LATB6=POTRCbits.RC2;
        LATBbits.LATB7=POTRCbits.RC3;
        delay(100);
    }


}
void delay(int a){
    for(int i=0;i<a;i++){
        for(int j=0;j<1275;j++);
    }
}
```

## Experiment-10 LCD

### RS, RW, and EN: LCD Control Lines

- **RS**: Register Select pin, set to `0` for command mode and `1` for data mode.
- **RW**: Read/Write pin, set to `0` for writing to the LCD.
- **EN**: Enable pin, used to latch data into the LCD.

### LCD Initialization Commands

- `lcdcmd(0x38);`: Sets the LCD to 8-bit, 2-line mode.
- `lcdcmd(0x01);`: Clears the display.
- `lcdcmd(0x0E);`: Turns on the display with the cursor on.
- `lcdcmd(0x83);`: Moves the cursor to the desired position (column 3, row 1)

```C
#include<stdio.h>
#pragma OSC=HS
#pragma WDT=OFF
#pragma LVP=OFF
#pragma DEBUG=OFF
#pragma PWRT=OFF
#define RS PORTDbits.RD3
#define RW PORTDbits.RD4
#define EN PORTDbits.RD5
void delay(int a);
void lcddata(char c);
void lcdcmd(char val);
void main()
{
    int b;
    char a[8]="SIT E&TC";
    TRISC=0x00;
    TRISD=0x00;
    EN=0;
    lcdcmd(0x38);
    delay(1000);
    lcdcmd(0x01);
    delay(100);
    lcdcmd(0x0E);
    delay(100);
    lcdcmd(0x83);
    delay(100);
    for(b=0;b<8;b++){
        lcddata(a[b]);
        delay(10);
    }
}
void lcdcmd(char val){
    dataport=val;
    RS=0;
    RW=0;
    EN=1;
    delay(10);
    EN=0;
}
void lcddata(char c){
    dataport=c;
    RS=1;
    RW=0;
    EN=1;
    delay(10);
    EN=0
}
void delay(int a){
    for(int i=0;i<a;i++){
        for(int j=0;j<1275;j++)
        {}
    }
}
```

## Experiment-10 7 Segment

```c
#include<pic18f4520>
#pragma config OSC=HS
#pragma config WDT=OFF
#pragma config PWRT=OFF
#pragma config DEBUG=OFF
#pragma config LVP=OFF
void delay(int a){
    for(int i=0;i<a;i++){
        for(int j=0;j<1275;j++)
        {}
    }
}
void main()
{
    TRISC=0x00;
    TRISD=0x00;
    LATD=0x0F;
    char c[]={0xC0,0xF9.....}
    while(1){
        for(int i=0;i<16;i++){
            LATC=c[i];
            delay(100);
        }
    }
}
```
```c
#include<pic18f4520>
#pragma config OSC=HS
#pragma config WDT=OFF
#pragma config PWRT=OFF
#pragma config DEBUG=OFF
#pragma config LVP=OFF
void delay(int a){
    for(int i=0;i<a;i++){
        for(int j=0;j<1275;j++)
        {}
    }
}
void chardisplay(int a){
    char c[]={0xC0,0xF9.....}
    LATD=0x00;
    LATC=c[a];
    LATD=0x01;
    delay(100);

}
void main()
{
    TRISC=0x00;
    TRISD=0x00;
    LATD=0x00;
    LATC=0x00;
    
    while(1){
        for(int i=0;i<16;i++){
            chardisplay(i);
            delay(1000);
        }
    }
}
```