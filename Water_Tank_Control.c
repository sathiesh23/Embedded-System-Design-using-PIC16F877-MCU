void water_inlet()
{
portc.f0=1;
portc.f1=0;
}

void water_outlet()
{
portc.f6=1;
portc.f7=0;
}

void inlet_stop()
{
portc.f0=0;
portc.f1=0;
}

void outlet_stop()
{
portc.f6=0;
portc.f7=0;
}

unsigned char in=0, out=0;

void main() {
 trisc=0x00;
 trisb=0x03;
 intcon=0x00;
 while(1)
 {
  while(portb.f0==0 && portb.f1==0 && in==0 && out==0)
     {
       water_inlet();
       outlet_stop();
       if(portb.f0==1 && portb.f1==0 && in==0 && out==0)
         {
          in=1;
         }
     }
  while(portb.f0==1 && portb.f1==0 && in==1 && out==0)
     {
      water_inlet();
      outlet_stop();
      if(portb.f0==1 && portb.f1==1 && in==1 && out==0)
         {
          in=0;
         }
     }
  while(portb.f0==1 && portb.f1==1 && in==0 && out==0)
     {
      water_outlet();
      inlet_stop();
      if(portb.f0==1 && portb.f1==0 && in==0 && out==0)
         {
          out=1;
         }
     }
  while(portb.f0==1 && portb.f1==0 && in==0 && out==1)
     {
      water_outlet();
      inlet_stop();
      if(portb.f0==0 && portb.f1==0 && in==0 && out==1)
         {
          out=0;
         }
     }
 }
}