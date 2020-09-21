/*  Engine rpm pulse  */
#include <Arduino.h>
#include <FlexiTimer2.h>

/// plse Plate tooth num
int roundDeg = 360;
int cycleDeg = 720;

/// crank pulse plate profile. true is active, false is negative.
bool pulsePlateTbl[] = {
 /* 0     1     2     3     4     5     6     7     8     9     */
    true, true, true, true, true, true, true, true, true, true, 
 /* 10     11     12    */ 
    false, false, false, 
 /* 13    14    15    16    17    18    19    20    21    22    23    24    */
    true, true, true, true, true, true, true, true, true, true, true, true, 
 /* 25    26    27    28    29    30    31    32    33    34    35 */
    true, true, true, true, true, true, true, true, true, true, true
};

/// crank plate tooth number
int pulsePerRound = sizeof(pulsePlateTbl)/sizeof(pulsePlateTbl[0]);

/// pulse width of crank angle sensor
int pulseWidthus = 74;

/// index counter of pulsePlateTbl
int crankCounter = 0;



void setup() 
{
    // put your setup code here, to run once:
    DDRB |= _BV(PB5) | _BV(PB4);
    setPulseIntv(1600);
}

void loop() 
{
    // put your main code here, to run repeatedly:

}

void setPulseIntv(int rpm)
{
    int t = 1.0 / rpm / 60 / pulsePerRound;
    FlexiTimer2::stop();
    FlexiTimer2::set(t, 1.0/1000000, pulseIntr);
    FlexiTimer2::start();
}

void pulseIntr(void)
{
    if (pulsePlateTbl[crankCounter])
    {
        noInterrupts();    
        digitalWrite(13, LOW);
        PORTB &= ~(_BV(PB5) | _BV(PB4));
        delayMicroseconds(pulseWidthus);
        PORTB |= _BV(PB5) | _BV(PB4);
        interrupts();
    }
    else
    {
        PORTB &= ~(_BV(PB5) | _BV(PB4));
    }
    crankCounter = (crankCounter + 1) % pulsePerRound;
    
}
