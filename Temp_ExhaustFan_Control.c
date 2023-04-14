// LCD module connections
sbit LCD_RS at RD2_bit;
sbit LCD_EN at RD3_bit;
sbit LCD_D4 at RD4_bit;
sbit LCD_D5 at RD5_bit;
sbit LCD_D6 at RD6_bit;
sbit LCD_D7 at RD7_bit;

sbit LCD_RS_Direction at TRISD2_bit;
sbit LCD_EN_Direction at TRISD3_bit;
sbit LCD_D4_Direction at TRISD4_bit;
sbit LCD_D5_Direction at TRISD5_bit;
sbit LCD_D6_Direction at TRISD6_bit;
sbit LCD_D7_Direction at TRISD7_bit;
// End LCD module connections

unsigned int temp_value=0;
unsigned int t=1023;
char *text, *text1;
char temperature[5];
long temp;

void software_pwm(int);
void conf_delay(int);

void main() {
trisa=0x01;            // LM35 -> AN0
trisc=0x00;            // PORTC.F0 , PORTC.F1 -> Exhaust DC Fan
trisd=0x00;            // PORTD -> 16x2 LCD in 4-bit mode
adcon1=0x80;           // PORTA -> Analog port, ADC Vref = 5V
intcon=0x00;           // Disable interrupts

Lcd_Init();                      // LCD display initialization
Lcd_Cmd(_LCD_CURSOR_OFF);        // LCD command (cursor off)
Lcd_Cmd(_LCD_CLEAR);             // LCD command (clear LCD)

text = "Temp based";             // Define the first message
text1 = "Fan - Control";         // Define the second message
Lcd_Out(1,1,text);               // Write the first message in the first line
Lcd_Out(2,1,text1);              // Write the second message in the second line
delay_ms(2000);

while(1)
        {
         temp_value = ADC_Read(0);
         temp = temp_value*4.88;      // Convert it into Voltage value, ADC Resolution = 4.88 mV
         temp = temp/10;              // Voltage Value/10 mV to get the temperature
         IntToStr(temp, temperature); // Convert the Temperature value to string
         Lcd_Cmd(_LCD_CLEAR);         // LCD command (clear LCD)
         Lcd_Out(1,1,"Temperature:"); // Write result in LCD
         Lcd_Out(2,1,"In C=");
         Lcd_Out_CP(temperature);
         //delay_ms(2000);
        
         portc.f0=1;                  //
         portc.f1=0;
         software_pwm(temp_value*10); // To adjust PWM for Temp = 0 to 50 deg
        }
}

void software_pwm(int duty)
{
 portc.f2=1;
 conf_delay(duty);
 portc.f2=0;
 conf_delay(t-duty);
}

void conf_delay(int duty)
{
 unsigned int i;
 for (i=0; i<duty; i++)
     {
      delay_us(1);
     }
}