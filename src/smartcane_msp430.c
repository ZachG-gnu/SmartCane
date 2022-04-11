#include <msp430.h> 

volatile int temp[2];
volatile float diff;
volatile float distance;
volatile unsigned int i=0;
int wsFlag = 0, flag = 0;

void main(void) {
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    P1DIR = BIT7 | BIT3 | BIT6;    // Set P1.3 and P1.6 as OUTPUT
    P1IFG &= (~BIT4);       // Clear interrupt flag for P1.4
    P1IE |= BIT4;           // Enable interrupt for P1.4
    P1OUT = 0;

    P2IFG &= ~BIT3; // Clear interrupt flag for P2.3
    P2IE |= BIT3;   // Enable interrupt for P2.3

    BCSCTL1 = CALBC1_1MHZ;     // Set MCLK = SMCLK = 1MHz
    DCOCTL = CALDCO_1MHZ;      // Set MCLK = SMCLK = 1MHz
    P2SEL = BIT1;
    P1SEL = BIT1 | BIT2 | BIT6;
    P1SEL2 = BIT1 | BIT2;
    TA0CTL = TASSEL_2 | MC_1;
    TA0CCR0 = 0xFFFF;
    TA0CCR1 = 0x000A;
    TA0CCTL1 = OUTMOD_7;
    TA1CTL = TASSEL_2 | MC_2;
    TA1CCTL1 = CAP | CCIE | CCIS_0 | CM_3 | SCS ; // Setup for capture mode
    _enable_interrupts();

    while(1){
        distance = abs(diff/58);

        if (distance > 20 && distance < 35) {}  // Deadzone of 20-30cm
        else {
            if (distance <= 20) {
                P1OUT |= BIT3;     // TURN VIBRATION MOTOR ON
            }
            else {
                P1OUT &= ~BIT3;    // TURN VIBRATION MOTOR OFF
            }
        }

        __delay_cycles(500);  //0.5 second delay
    }
}

#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void) {
    if (wsFlag) {
        P1IES &= ~BIT4; // Switch to rising edge on P1.4
        P1OUT &= ~BIT7; // Turn speaker off
        wsFlag = 0;
    }
    else {
        P1IES |= BIT4;  // Switch to falling edge on P1.4
        P1OUT |= BIT7;  // Turn speaker on
        wsFlag = 1;
    }

    P1IFG &= (~BIT4);   // Clear interrupt flag for P1.4
}

#pragma vector=PORT2_VECTOR
__interrupt void Port_2(void) {
    P2IFG &= (~BIT3);   // Clear interrupt flag for P2.3

    P2IES ^= BIT3; // Flip between rising or falling edge

    if (flag) {
        flag = 0;
    }
    else {
        flag = 1;
        P1OUT = 0;  // Turn off all peripherals on P1 before going into LPM0
        __bis_SR_register(LPM0_bits + GIE);    // Enter LPM0 w/ interrupts
    }

    __bic_SR_register_on_exit(LPM0_bits); // Exit LPM0
}

#pragma vector = TIMER1_A1_VECTOR
__interrupt void Timer_A(void) {
    temp[i] = TA1CCR1;
    i += 1;
    TA1CCTL1 &= ~CCIFG ;
    if (i==2) {
        diff = temp[i-1]-temp[i-2];
        i=0;
    }
}
