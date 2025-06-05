#include <pic18f4520.h>
#pragma config OSC=HS
#pragma config PWRT = OFF
#pragma config WDT = OFF
#pragma config DEBUG = OFF, LVP = OFF

#define RS PORTDbits.RD3
#define RW PORTDbits.RD4
#define EN PORTDbits.RD5
#define dataport PORTC

void delay(int k);
void lcddata(char c);
void lcdcmd(char val);  
void displayTime(int minutes, int seconds);
void intToString(int num, char* str);
void delayOneSecond();

void main(void)
{
    TRISC = 0x00;  // Set PORTC as output for LCD
    TRISD = 0x00;  // Set PORTD as output for LCD control
    EN = 0;

    // Initialize the LCD
    lcdcmd(0x38); // 2-line mode
    delay(1000);
    lcdcmd(0x01); // Clear display
    delay(100);
    lcdcmd(0x0E); // Display ON, Cursor ON
    delay(100);
    lcdcmd(0x80); // Set cursor to the first line
    delay(100);

    // Display initial label
    lcddata('T');
    lcddata('i');
    lcddata('m');
    lcddata('e');
    lcddata(':');
    lcddata(' ');

    int seconds = 0;  // Seconds counter
    int minutes = 0;  // Minutes counter
    int running = 1;  // Timer state (1 = running)

    while (1)  // Infinite loop for continuous counting
    {
        if (running) {
            displayTime(minutes, seconds);  // Display current time
            delayOneSecond();  // Delay for approximately 1 second
            seconds++;  // Increment the seconds counter
            
            if (seconds >= 60) {
                seconds = 0;  // Reset seconds
                minutes++;  // Increment minutes
            }
            if (minutes >= 60) {
                minutes = 0;
                seconds = 0;
            }
        }
    }
} 

void lcdcmd(char val)
{
    dataport = val;
    RS = 0;  // Command mode
    RW = 0;  // Write mode
    EN = 1;  // Enable high
    delay(10);
    EN = 0;  // Enable low
}

void lcddata(char c)
{
    dataport = c;
    RS = 1;  // Data mode
    RW = 0;  // Write mode
    EN = 1;  // Enable high
    delay(10);
    EN = 0;  // Enable low
}

void displayTime(int minutes, int seconds)
{
    char minStr[3], secStr[3];  // Buffers for minutes and seconds

    // Ensure both minutes and seconds are padded to two digits
    intToString(minutes, minStr);
    if (minutes < 10) {
        minStr[1] = minStr[0];  // Shift digit to the right
        minStr[0] = '0';        // Add leading zero
        minStr[2] = '\0';       // Null-terminate
    }

    intToString(seconds, secStr);
    if (seconds < 10) {
        secStr[1] = secStr[0];  // Shift digit to the right
        secStr[0] = '0';        // Add leading zero
        secStr[2] = '\0';       // Null-terminate
    }

    // Move the cursor back to the correct position
    lcdcmd(0xC0);  // Set cursor to the second line, first position
    delay(100);

    // Display minutes and seconds
    lcddata('M'); lcddata('i'); lcddata('n'); lcddata(':'); lcddata(' ');
    for (int i = 0; minStr[i] != '\0'; i++) {
        lcddata(minStr[i]);  // Send each character to LCD
    }
    
    lcddata(' ');  // Space between minutes and seconds
    lcddata('S'); lcddata('e'); lcddata('c'); lcddata('s'); lcddata(':'); lcddata(' ');

    for (int i = 0; secStr[i] != '\0'; i++) {
        lcddata(secStr[i]);  // Send each character to LCD
    }
}


void intToString(int num, char* str)
{
    int i = 0;

    // Handle 0 explicitly
    if (num == 0) {
        str[i++] = '0';
        str[i] = '\0';
        return;
    }

    // Process individual digits
    while (num > 0) {
        str[i++] = (num % 10) + '0';  // Convert digit to character
        num /= 10;  // Remove last digit
    }

    str[i] = '\0';  // Null-terminate the string

    // Reverse the string since we added digits in reverse order
    for (int j = 0; j < i / 2; j++) {
        char temp = str[j];
        str[j] = str[i - j - 1];
        str[i - j - 1] = temp;
    }
}

void delayOneSecond()
{
    for (int i = 0; i < 1; i++)  // Adjust to create a delay of 1 second
    {
        delay(100);  // Each call to delay(100) gives about 1000 ms
    }
}

void delay(int k)
{
    int i, j;
    for (i = 0; i < k; i++) {
        for (j = 0; j < 1275; j++);  // Simple delay loop
    }
}