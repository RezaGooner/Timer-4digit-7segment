# Display Time on a 4-Digit 7-Segment Display Using ATmega32 and BCD to 7-Segment Decoder (IC 7447)

This project is a simple digital clock that displays time on a 4-digit 7-segment display. It is implemented using the **ATmega32** microcontroller, a **BCD to 7-Segment Decoder (IC 7447)**, and the **Multiplexing** technique.

---

## Table of Contents
- [Introduction](#introduction)
- [Components Required](#components-required)
- [How It Works](#how-it-works)
- [Hardware Connections](#hardware-connections)
- [How to Run the Project](#how-to-run-the-project)
- [Programming](#programming)


---

## Introduction

This project is a simple digital clock that displays minutes and seconds on a 4-digit 7-segment display. The **ATmega32** microcontroller generates BCD (Binary-Coded Decimal) values, which are then converted to the appropriate signals for the 7-segment display using the **BCD to 7-Segment Decoder (IC 7447)**. The **Multiplexing** technique is employed to display all digits simultaneously.

---

## Components Required

- **ATmega32** microcontroller
- 4-digit 7-segment display (Common Cathode)
- BCD to 7-Segment Decoder (IC 7447)
- NPN transistors (e.g., 2N2222 or BC547) (4 pieces)
- 5V power supply

---

## How It Works

![ezgif-2ca358baa20250](https://github.com/user-attachments/assets/ce49f578-de18-416c-88c3-9d5308b665e8)

In this project, time is calculated in minutes and seconds and displayed on the 7-segment display. The **ATmega32** generates BCD values for each digit, which are then sent to the **BCD to 7-Segment Decoder (IC 7447)**. The decoder converts the BCD values into the appropriate signals to drive the 7-segment display.

Each digit is activated one by one and quickly turned on and off to create the illusion that all digits are lit simultaneously. This process is achieved using the **Multiplexing** technique.

The time increments every second, and after reaching 60 seconds, the minutes increase. If the minutes reach 60, they reset to zero.

---

## Hardware Connections

![Untitled](https://github.com/user-attachments/assets/d4d270d4-0642-4630-af11-df8734856a1c)


### Port C (PORTC):
- Port C is used to send BCD values to the **BCD to 7-Segment Decoder (IC 7447)**.
- Each BCD value corresponds to a digit (0-9).

| 7448 Pin | Microcontroller Port |
|---------|----------------------|
| A       | PC0                  |
| B       | PC1                  |
| C       | PC2                  |
| D       | PC3                  |

### Port D (PORTD):
- Port D is used to control the common cathodes of each digit.
- Each pin of Port D is connected to the base of an NPN transistor.
- The collector of the transistor is connected to the common cathode of a digit on the 7-segment display.
- The emitter of the transistor is connected to ground (GND).

| input Not Gates | Microcontroller Port |
|-------------------|----------------------|
| Gate 1   | PD0                  |
| Gate 2   | PD1                  |
| Gate 3   | PD2                  |
| Gate 4   | PD3                  |


| 7-Segment Cathode | output Not Gates |
|-------------------|----------------------|
| Digit 1 Cathode   | Gate 1                  |
| Digit 2 Cathode   | Gate 2                  |
| Digit 3 Cathode   | Gate 3                  |
| Digit 4 Cathode   | Gate 4                  |

### BCD to 7-Segment Decoder (IC 7447):
- The BCD inputs (A, B, C, D) are connected to Port C of the microcontroller.
- The 7-segment outputs (a, b, c, d, e, f, g) are connected to the corresponding segments of the 7-segment display.

| IC 7447 Pin | 7-Segment Pin |
|-------------|---------------|
| QA           | A             |
| QB           | B             |
| QC           | C             |
| QD           | D             |
| QE           | E             |
| QF           | F             |
| QG           | G             |


| IC 7447 Pin | Connected to |
|-------------|---------------|
| LT           | VCC             |
| RBI           | VCC             |
| BI/RBO           | VCC             |



---

## How to Run the Project

1. **Hardware Connections**: Connect the components as per the tables above.
2. Compile the project code in a suitable programming environment (e.g., CodeVision or Atmel Studio).
3. Program the generated HEX file onto the ATmega32 microcontroller.
4. Power on the circuit and observe the time displayed on the 7-segment display.

![bandicam2025-03-1123-31-47-335-ezgif com-video-to-gif-converter](https://github.com/user-attachments/assets/63f7eec3-4477-42bf-b7cb-46672a03548d)


---

## Programming

The code for this project is written in C and uses the `<mega32.h>` and `<delay.h>` libraries. In this code, time is calculated in minutes and seconds, and BCD values are generated for each digit. These BCD values are sent to the **BCD to 7-Segment Decoder (IC 7447)**.

```c
#include <mega32.h>
#include <delay.h>

void main(void){
    int i, j;
    int seconds = 0;
    int minutes = 0;
    int s[4] = {0, 0, 0, 0};
    DDRD = 0x0f;
    DDRC = 0x0f;
    
    while(1){
        s[0] = minutes / 10;
        s[1] = minutes % 10;
        s[2] = seconds / 10;
        s[3] = seconds % 10;

        for (j = 0; j < 250; j++) {
            for (i = 0; i < 4; i++) {
                PORTD = ~(1 << i);
                PORTC = s[i];
                delay_ms(1);
                PORTC = 0;
                PORTD = 0;
            }
        }

        seconds++;
        if (seconds >= 60) {
            seconds = 0;
            minutes++;
            if (minutes >= 60) {
                minutes = 0;
            }
        }
    }
}
```

---

## License

This project is licensed under the [MIT License](LICENSE).

