unsigned int pot_value=0;
unsigned int t=1023;

void software_pwm(int);
void conf_delay(int);

void main() {
trisa=0x01;
trisd=0x00;
while(1)
        {
         pot_value = ADC_Read(0);
         portd.f0=1;
         portd.f1=0;
         software_pwm(pot_value);
        }
}

void software_pwm(int duty)
{
 portd.f2=1;
 conf_delay(duty);
 portd.f2=0;
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