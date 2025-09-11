/*******************************************************
This program was created by the
CodeWizardAVR V3.12 Advanced
Automatic Program Generator
© Copyright 1998-2014 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : 
Version : 
Date    : 26.02.2025
Author  : 
Company : 
Comments: 


Chip type               : ATmega168PA
Program type            : Application
AVR Core Clock frequency: 20,000000 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 256
*******************************************************/

#include <mega168a.h>
#include <delay.h>
#include <stdio.h>
unsigned int  ECU_TEMP,ECU_CURRENT,BUS_5V,VCC,ADC6,ADC7;
unsigned int  AIN0,AIN1,AIN2,AIN3,AIN4,AIN5,AIN6,AIN7;
unsigned int  DOUT0_CURR,DOUT1_CURR,DOUT2_CURR,DOUT3_CURR,DOUT4_CURR;
bit DOUT56STATE,DOUT78STATE,DIN6,DIN7,DIN8,INTBTN,ST;
char D0,D6,RS232,CNT2;       
bit LED1,QP6,QP5,QP4,QP3,QP2,QP1,QP0;
int CNT1,CNT3;



       //Входа скоростные прямые  10-32В  6 штук
       
#define  DIN0 PINC.0
#define  DIN1 PINC.1
#define  DIN2 PINC.2
#define  DIN3 PINC.3
#define  DIN4 PINC.4
#define  DIN5 PINC.5

       //Выхода цифровые Обычные\ШИМ\Безопасность 
       
       
#define  AUX_Safe PORTD.4      //      Выход безопасности,общий на все выхода 10А,10-32В.
#define  DOUT0    PORTD.6      //      Выход Цифровой/ШИМ 3А,10-32В. 
#define  DOUT1    PORTD.5      //      Выход Цифровой/ШИМ 3А,10-32В. 
#define  DOUT2    PORTB.1      //      Выход Цифровой/ШИМ 3А,10-32В. 
#define  DOUT3    PORTB.2      //      Выход Цифровой/ШИМ 3А,10-32В. 
#define  DOUT4    PORTB.3      //      Выход Цифровой/ШИМ 3А,10-32В. 
#define  DOUT5    PORTD.3      //      Выход Цифровой/ШИМ 1А,10-32В. 
#define  DOUT6    QP3          //      Выход Цифровой     1А,10-32В. 
#define  DOUT7    QP4          //      Выход Цифровой     1А,10-32В.
#define  DOUT8    QP5          //      Выход Цифровой     1А,10-32В.

#define  ErrRESET    QP6       //     сброс варии кз.


#define  LOGIC_EN PORTB.0      // Биты управление регистром расширителем U13.
#define  DATA_SPI PORTB.4                                                   
#define  CLK_SPI  PORTB.5 
#define  SRB_SPI  PORTD.7 


#define  DINMUX  PIND.2        // Общий вход цифровой  мультиплексора U17.

interrupt [PC_INT1] void pin_change_isr1(void)
{
// Place your code here

}

// Timer2 overflow interrupt service routine
interrupt [TIM2_OVF] void timer2_ovf_isr(void)
{
// Place your code here

}     

// Timer1 overflow interrupt service routine
interrupt [TIM0_OVF] void timer0_ovf_isr(void)
{ 
CNT3++;

if (CNT3>=AIN7/50&CNT2!=255&ST==0) CNT3=0,CNT2++;
if (CNT2==255) ST=1;
if (CNT3>=AIN7/50&CNT2!=0&ST==1) CNT3=0,CNT2--; 
if (CNT2==0) ST=0;

OCR0A=CNT2;
OCR0B=~CNT2;



DOUT7=DIN7;

if (DIN6==1) D6++;
      if (D6>10&&DIN6==0) D6=0,DOUT6=!DOUT6;
if (DIN8==1) D0++;
      if (D0>10&&DIN8==0) D0=0,AUX_Safe=!AUX_Safe; 
      
ErrRESET=DIN1;



}

void TR4094(void) {

 DATA_SPI=LED1;
  CLK_SPI=1,CLK_SPI=0;    
    DATA_SPI=QP6;    
  CLK_SPI=1,CLK_SPI=0;
    DATA_SPI=QP5;
  CLK_SPI=1,CLK_SPI=0;    
    DATA_SPI=QP4;    
  CLK_SPI=1,CLK_SPI=0; 
    DATA_SPI=QP3;
  CLK_SPI=1,CLK_SPI=0;    
    DATA_SPI=QP2;    
  CLK_SPI=1,CLK_SPI=0; 
    DATA_SPI=QP1;
  CLK_SPI=1,CLK_SPI=0;    
    DATA_SPI=QP0;    
  CLK_SPI=1,CLK_SPI=0;   
  SRB_SPI=1,SRB_SPI=0; 
}

void ADC_READ(void) {

ADMUX=0xC6;
delay_us(46);
ADCSRA|=0x40;
delay_us(46);
ADC6=ADCW;

ADMUX=0xC7;
delay_us(46);
ADCSRA|=0x40;
delay_us(46);
ADC7=ADCW;

}



void main(void)
{
// Declare your local variables here

// Crystal Oscillator division factor: 1
#pragma optsize-
CLKPR=(1<<CLKPCE);
CLKPR=(0<<CLKPCE) | (0<<CLKPS3) | (0<<CLKPS2) | (0<<CLKPS1) | (0<<CLKPS0);
#ifdef _OPTIMIZE_SIZE_
#pragma optsize+
#endif

// Input/Output Ports initialization
// Port B initialization
// Function: Bit7=In Bit6=In Bit5=Out Bit4=Out Bit3=In Bit2=In Bit1=In Bit0=Out 
DDRB=(1<<DDB7) | (0<<DDB6) | (1<<DDB5) | (1<<DDB4) | (1<<DDB3) | (1<<DDB2) | (1<<DDB1) | (1<<DDB0);
// State: Bit7=T Bit6=T Bit5=0 Bit4=0 Bit3=T Bit2=T Bit1=T Bit0=0 
PORTB=(0<<PORTB7) | (0<<PORTB6) | (0<<PORTB5) | (0<<PORTB4) | (0<<PORTB3) | (0<<PORTB2) | (0<<PORTB1) | (0<<PORTB0);

// Port C initialization
// Function: Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In 
DDRC=(0<<DDC6) | (0<<DDC5) | (0<<DDC4) | (0<<DDC3) | (0<<DDC2) | (0<<DDC1) | (0<<DDC0);
// State: Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T 
PORTC=(0<<PORTC6) | (0<<PORTC5) | (0<<PORTC4) | (0<<PORTC3) | (0<<PORTC2) | (0<<PORTC1) | (0<<PORTC0);

// Port D initialization
// Function: Bit7=Out Bit6=In Bit5=In Bit4=In Bit3=Out Bit2=In Bit1=In Bit0=In 
DDRD=(1<<DDD7) | (1<<DDD6) | (1<<DDD5) | (1<<DDD4) | (1<<DDD3) | (0<<DDD2) | (0<<DDD1) | (0<<DDD0);
// State: Bit7=0 Bit6=T Bit5=T Bit4=T Bit3=1 Bit2=T Bit1=T Bit0=T 
PORTD=(0<<PORTD7) | (0<<PORTD6) | (0<<PORTD5) | (0<<PORTD4) | (0<<PORTD3) | (0<<PORTD2) | (0<<PORTD1) | (0<<PORTD0);

// Timer/Counter 0 initialization
// Clock source: System Clock
// Clock value: 78,125 kHz
// Mode: Fast PWM top=0xFF
// OC0A output: Non-Inverted PWM
// OC0B output: Non-Inverted PWM
// Timer Period: 3,2768 ms
// Output Pulse(s):
// OC0A Period: 3,2768 ms Width: 0 us
// OC0B Period: 3,2768 ms Width: 0 us
TCCR0A=(1<<COM0A1) | (0<<COM0A0) | (1<<COM0B1) | (0<<COM0B0) | (1<<WGM01) | (1<<WGM00);
TCCR0B=(0<<WGM02) | (1<<CS02) | (0<<CS01) | (0<<CS00);
TCNT0=0x00;
OCR0A=0x00;
OCR0B=0x00;

// Timer/Counter 1 initialization
// Clock source: System Clock
// Clock value: 78,125 kHz
// Mode: Fast PWM top=0x00FF
// OC1A output: Non-Inverted PWM
// OC1B output: Non-Inverted PWM
// Noise Canceler: Off
// Input Capture on Falling Edge
// Timer Period: 3,2768 ms
// Output Pulse(s):
// OC1A Period: 3,2768 ms Width: 0 us
// OC1B Period: 3,2768 ms Width: 0 us
// Timer1 Overflow Interrupt: Off
// Input Capture Interrupt: Off
// Compare A Match Interrupt: Off
// Compare B Match Interrupt: Off
TCCR1A=(1<<COM1A1) | (0<<COM1A0) | (1<<COM1B1) | (0<<COM1B0) | (0<<WGM11) | (1<<WGM10);
TCCR1B=(0<<ICNC1) | (0<<ICES1) | (0<<WGM13) | (1<<WGM12) | (1<<CS12) | (0<<CS11) | (0<<CS10);
TCNT1H=0x00;
TCNT1L=0x00;
ICR1H=0x00;
ICR1L=0x00;
OCR1AH=0x00;
OCR1AL=0x00;
OCR1BH=0x00;
OCR1BL=0x00;

//// Timer/Counter 2 initialization
//// Clock source: System Clock
//// Clock value: 78,125 kHz
//// Mode: Fast PWM top=0xFF
//// OC2A output: Non-Inverted PWM
//// OC2B output: Non-Inverted PWM
//// Timer Period: 3,2768 ms
//// Output Pulse(s):
//// OC2A Period: 3,2768 ms Width: 0 us
//// OC2B Period: 3,2768 ms Width: 0 us
//ASSR=(0<<EXCLK) | (0<<AS2);
//TCCR2A=(1<<COM2A1) | (0<<COM2A0) | (1<<COM2B1) | (0<<COM2B0) | (1<<WGM21) | (1<<WGM20);
//TCCR2B=(0<<WGM22) | (1<<CS22) | (1<<CS21) | (0<<CS20);
//TCNT2=0x00;
//OCR2A=0x00;
//OCR2B=0x00;
// Timer/Counter 2 initialization
// Clock source: System Clock
// Clock value: 20000,000 kHz
// Mode: Fast PWM top=0xFF
// OC2A output: Disconnected
// OC2B output: Disconnected
// Timer Period: 0,0128 ms
ASSR=(0<<EXCLK) | (0<<AS2);
TCCR2A=(0<<COM2A1) | (0<<COM2A0) | (0<<COM2B1) | (0<<COM2B0) | (1<<WGM21) | (1<<WGM20);
TCCR2B=(0<<WGM22) | (0<<CS22) | (0<<CS21) | (1<<CS20);
TCNT2=0x00;
OCR2A=0x00;
OCR2B=0x00;

// Timer/Counter 0 Interrupt(s) initialization
TIMSK0=(0<<OCIE0B) | (0<<OCIE0A) | (1<<TOIE0);

// Timer/Counter 1 Interrupt(s) initialization
TIMSK1=(0<<ICIE1) | (0<<OCIE1B) | (0<<OCIE1A) | (0<<TOIE1);

// Timer/Counter 2 Interrupt(s) initialization
TIMSK2=(0<<OCIE2B) | (0<<OCIE2A) | (1<<TOIE2);


// External Interrupt(s) initialization
// INT0: Off
// INT1: Off
// Interrupt on any change on pins PCINT0-7: Off
// Interrupt on any change on pins PCINT8-14: On
// Interrupt on any change on pins PCINT16-23: Off
EICRA=(0<<ISC11) | (0<<ISC10) | (0<<ISC01) | (0<<ISC00);
EIMSK=(0<<INT1) | (0<<INT0);
PCICR=(0<<PCIE2) | (1<<PCIE1) | (0<<PCIE0);
PCMSK1=(0<<PCINT14) | (0<<PCINT13) | (0<<PCINT12) | (0<<PCINT11) | (0<<PCINT10) | (0<<PCINT9) | (1<<PCINT8);
PCIFR=(0<<PCIF2) | (1<<PCIF1) | (0<<PCIF0);

// USART initialization for ATmega168A/P
// External crystal: 20 MHz
// Baud Rate: 9600
// Communication Parameters: 8 Data, 1 Stop, No Parity

UCSR0A = (0<<RXC0) | (0<<TXC0) | (0<<UDRE0) | (0<<FE0) | (0<<DOR0) | (0<<UPE0) | (0<<U2X0) | (0<<MPCM0);
UCSR0B = (0<<RXCIE0) | (0<<TXCIE0) | (0<<UDRIE0) | (1<<RXEN0) | (1<<TXEN0) | (0<<UCSZ02) | (0<<RXB80) | (0<<TXB80);
UCSR0C = (0<<UMSEL01) | (0<<UMSEL00) | (0<<UPM01) | (0<<UPM00) | (0<<USBS0) | (1<<UCSZ01) | (1<<UCSZ00) | (0<<UCPOL0);

// Baud Rate calculation for 9600 baud at 20MHz
// UBRR = (F_CPU / (16 * BAUD)) - 1
// UBRR = (20000000 / (16 * 9600)) - 1 = (20000000 / 153600) - 1 = 130.208 - 1 = 129.208  129

UBRR0H = 0x00;
UBRR0L = 0x81; // 129 decimal = 0x81 hexadecimal

// Analog Comparator initialization
// Analog Comparator: Off
// The Analog Comparator's positive input is
// connected to the AIN0 pin
// The Analog Comparator's negative input is
// connected to the AIN1 pin
ACSR=(1<<ACD) | (0<<ACBG) | (0<<ACO) | (0<<ACI) | (0<<ACIE) | (0<<ACIC) | (0<<ACIS1) | (0<<ACIS0);
ADCSRB=(0<<ACME);
// Digital input buffer on AIN0: On
// Digital input buffer on AIN1: On
DIDR1=(0<<AIN0D) | (0<<AIN1D);

// ADC initialization
// ADC disabled
//ADCSRA=(0<<ADEN) | (0<<ADSC) | (0<<ADATE) | (0<<ADIF) | (0<<ADIE) | (0<<ADPS2) | (0<<ADPS1) | (0<<ADPS0);
ADCSRA=0x86;
//10000110

ADCSRB=(0<<ADTS2) | (0<<ADTS1) | (0<<ADTS0);
//ADMUX=0xC8;  // Temp sensor,ref 1.1v 0b11001000; ADC6=0b11000110  0xC6;  ADC7=0b11000111  0xC7;

// SPI initialization
// SPI disabled
SPCR=(0<<SPIE) | (0<<SPE) | (0<<DORD) | (0<<MSTR) | (0<<CPOL) | (0<<CPHA) | (0<<SPR1) | (0<<SPR0);

// TWI initialization
// TWI disabled
TWCR=(0<<TWEA) | (0<<TWSTA) | (0<<TWSTO) | (0<<TWEN) | (0<<TWIE);

LOGIC_EN=1;

#asm("sei")
while (1)
      {  
      
          
RS232++;
////////////////////////MUX0
QP2=0,QP1=0,QP0=0;    
TR4094(); 
ADMUX=0xC8;
delay_us(46);
ADCSRA|=0x40;
delay_us(46);
ECU_TEMP=(ADCW)-330;
ADC_READ();
ECU_CURRENT=(ADC6/1.475);
AIN0=ADC7;
 DOUT56STATE=PIND.2;

////////////////////////MUX1
QP2=0,QP1=0,QP0=1;    
TR4094();
ADC_READ();
DOUT0_CURR=(ADC6/3.76);
AIN1=ADC7;    
DOUT78STATE=PIND.2;
////////////////////////MUX2
 QP2=0,QP1=1,QP0=0;    
TR4094();    
ADC_READ();
DOUT1_CURR=(ADC6/3.76);
AIN2=ADC7;
DIN6=PIND.2;
////////////////////////MUX3
QP2=0,QP1=1,QP0=1;    
TR4094();
ADC_READ();    
DOUT2_CURR=(ADC6/3.76);
AIN3=ADC7;
DIN7=PIND.2;
////////////////////////MUX4
QP2=1,QP1=0,QP0=0;    
TR4094();    
ADC_READ();
DOUT3_CURR=(ADC6/3.76);
AIN4=ADC7;
DIN8=PIND.2;
////////////////////////MUX5
QP2=1,QP1=0,QP0=1;    
TR4094();    
ADC_READ();
DOUT4_CURR=(ADC6/3.76);
AIN5=ADC7;
INTBTN=PIND.2;
////////////////////////MUX6
QP2=1,QP1=1,QP0=0;    
TR4094();    
ADC_READ();
BUS_5V=(ADC6/1.86);
AIN6=ADC7;
////////////////////////MUX7      
QP2=1,QP1=1,QP0=1;    
TR4094();    
ADC_READ();
VCC=(ADC6/2.71);
AIN7=ADC7;




CNT1++;      
if (RS232==250) {
    RS232=0;
    
    // ECU temp
    printf("t4.txt=\"%i\"\xFF\xFF\xFF", ECU_TEMP);
    
    // ECU curr
    printf("t1.txt=\"%i\"\xFF\xFF\xFF", ECU_CURRENT);
    
    // 5v
    printf("t6.txt=\"%i\"\xFF\xFF\xFF", BUS_5V);
    
    // VCC
    printf("t8.txt=\"%i\"\xFF\xFF\xFF", VCC);
    
    // DIN0-DIN8 checkbox c0-c8
    printf("c0.val=%i\xFF\xFF\xFF", DIN0);
    printf("c1.val=%i\xFF\xFF\xFF", DIN1);
    printf("c2.val=%i\xFF\xFF\xFF", DIN2);
    printf("c3.val=%i\xFF\xFF\xFF", DIN3);
    printf("c4.val=%i\xFF\xFF\xFF", DIN4);
    printf("c5.val=%i\xFF\xFF\xFF", DIN5);
    printf("c6.val=%i\xFF\xFF\xFF", DIN6);
    printf("c7.val=%i\xFF\xFF\xFF", DIN7);
    printf("c8.val=%i\xFF\xFF\xFF", DIN8);
    
    // analog inp
    printf("c9.val=%i\xFF\xFF\xFF", DOUT0_CURR > 0 ? 1 : 0);
    printf("c10.val=%i\xFF\xFF\xFF", DOUT1_CURR > 0 ? 1 : 0);
    printf("c11.val=%i\xFF\xFF\xFF", DOUT2_CURR > 0 ? 1 : 0);
    printf("c12.val=%i\xFF\xFF\xFF", DOUT3_CURR > 0 ? 1 : 0);
    printf("c13.val=%i\xFF\xFF\xFF", DOUT4_CURR > 0 ? 1 : 0);
    printf("c14.val=%i\xFF\xFF\xFF", DOUT56STATE);
    printf("c15.val=%i\xFF\xFF\xFF", DOUT78STATE);
    printf("c16.val=%i\xFF\xFF\xFF", INTBTN);
    
    // temp
    //printf("add s0,%i,255\xFF\xFF\xFF", ECU_TEMP);
                
    LED1=!LED1;
}
}}