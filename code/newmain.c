#include <xc.h>
#include <stdio.h>

#define _XTAL_FREQ 20000000

// CONFIG BITS
#pragma config FOSC = HS
#pragma config WDTE = OFF
#pragma config PWRTE = OFF
#pragma config BOREN = ON
#pragma config LVP = OFF
#pragma config CPD = OFF
#pragma config WRT = OFF
#pragma config CP = OFF

// ================= LCD CONFIG =================
#define RS PORTCbits.RC0
#define RW PORTCbits.RC1
#define EN PORTCbits.RC3

// ================= FUNCTION DECLARATIONS =================
void ADC_Init();
unsigned int ADC_Read(unsigned char channel);
void PWM_Init();
void set_PWM_duty(unsigned int duty);

void LCD_Init();
void LCD_Command(unsigned char cmd);
void LCD_Char(unsigned char data);
void LCD_String(const char *str);
void LCD_Clear();

// ================= MAIN =================
void main() {
    unsigned int adc;
    float temp;
    char buffer[16];

    TRISA = 0xFF;
    TRISC = 0x00;
    TRISD = 0x00;

    PORTC = 0x00;
    PORTD = 0x00;

    ADC_Init();
    PWM_Init();
    LCD_Init();

    while(1) {
        adc = ADC_Read(0);
        temp = (adc * 5.0 * 100.0) / 1023.0;

        LCD_Clear();
        sprintf(buffer, "Temp: %.1f C", temp);
        LCD_String(buffer);

        LCD_Command(0xC0);

        if(temp < 30) {
            set_PWM_duty(0);
            LCD_String("Fan OFF ");
        }
        else if(temp < 35) {
            set_PWM_duty(250);
            LCD_String("Fan LOW ");
        }
        else if(temp < 40) {
            set_PWM_duty(600);
            LCD_String("Fan MED ");
        }
        else {
            set_PWM_duty(1023);
            LCD_String("Fan HIGH");
        }

        __delay_ms(500);
    }
}

// ================= ADC =================
void ADC_Init() {
    ADCON0 = 0x41;
    ADCON1 = 0x80;
}

unsigned int ADC_Read(unsigned char channel) {
    ADCON0 &= 0xC5;
    ADCON0 |= (channel << 3);

    __delay_ms(2);

    GO_nDONE = 1;
    while(GO_nDONE);

    return ((ADRESH << 8) + ADRESL);
}

// ================= PWM =================
void PWM_Init() {
    TRISC2 = 0;
    CCP1CON = 0x0C;
    PR2 = 255;
    T2CON = 0x07;   // Timer2 ON
}

void set_PWM_duty(unsigned int duty) {
    if(duty > 1023) duty = 1023;

    CCPR1L = duty >> 2;
    CCP1CON &= 0xCF;
    CCP1CON |= (duty & 0x03) << 4;
}

// ================= LCD =================
void LCD_Command(unsigned char cmd) {
    PORTD = cmd;
    RS = 0;
    RW = 0;
    EN = 1; __delay_ms(2); EN = 0;
}

void LCD_Char(unsigned char data) {
    PORTD = data;
    RS = 1;
    RW = 0;
    EN = 1; __delay_ms(2); EN = 0;
}

void LCD_Init() {
    __delay_ms(20);
    LCD_Command(0x38); // 8-bit mode
    LCD_Command(0x0C); // display ON
    LCD_Command(0x06); // cursor move
    LCD_Command(0x01); // clear
    __delay_ms(5);
}

void LCD_String(const char *str) {
    while(*str) {
        LCD_Char(*str++);
    }
}

void LCD_Clear() {
    LCD_Command(0x01);
    __delay_ms(2);
}
