#include <bsp/bsp_cpu.h>
#ifndef __CPU_ATMEGA32U4_H
#error "This app is only for ATmega32u4!"
#endif
#include <io.h>

void mimosa_app_run(void)
{
  writeb(DDRD, 0b100000);

  while(1)
    {
      writeb(PORTD, 0b100000);
      _delay_ms(1000);
      writeb(PORTD, 0);
      _delay_ms(1000);
    }
}
