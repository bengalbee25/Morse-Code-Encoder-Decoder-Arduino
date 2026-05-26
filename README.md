
# Morse Code Encoder and Decoder Using Arduino

## Overview

This project is an Arduino-based Morse Code Encoder and Decoder system. It converts normal text into Morse code using an LED and buzzer, and it can also decode Morse code input entered through a push button.

The project is built using an Arduino Uno and basic electronic components. It is useful for learning Morse code, Arduino programming, digital input/output, timing logic, and serial communication.

## Features

- Converts text input into Morse code
- Displays Morse code through LED blinking
- Produces Morse code sound using a buzzer
- Decodes button presses into readable characters
- Supports letters A-Z and numbers 0-9
- Uses Arduino Serial Monitor for input and output
- Beginner-friendly embedded system project

## Components Required

| Component | Quantity |
|---|---:|
| Arduino Uno | 1 |
| LED | 1 |
| Buzzer | 1 |
| Push Button | 1 |
| Resistors | As required |
| Breadboard | 1 |
| Jumper Wires | As required |

## Pin Configuration

| Component | Arduino Pin |
|---|---|
| LED | Digital Pin 13 |
| Buzzer | Digital Pin 12 |
| Push Button | Digital Pin 2 |

> Note: The button uses `INPUT_PULLUP`, so it should be connected between Digital Pin 2 and GND.

## Main File

```text
morse_code_encoder_decoder.ino
````

## How It Works

### Encoding

1. The user types a message in the Arduino Serial Monitor.
2. The Arduino reads each character.
3. The character is converted into Morse code.
4. The LED and buzzer produce dot and dash signals.

### Decoding

1. The user enters Morse code using the push button.
2. A short press is detected as a dot.
3. A long press is detected as a dash.
4. The Arduino compares the input sequence with the Morse code table.
5. The decoded character is printed on the Serial Monitor.

## Timing Logic

| Signal Type |                  Duration |
| ----------- | ------------------------: |
| Dot         | Short press / short blink |
| Dash        |   Long press / long blink |
| Symbol Gap  |               Small delay |
| Letter Gap  |              Medium delay |
| Word Gap    |              Longer delay |

## How to Run the Project

1. Connect the circuit according to the pin configuration.
2. Open `morse_code_encoder_decoder.ino` in the Arduino IDE.
3. Select the correct board:

   * `Arduino Uno`
4. Select the correct COM port.
5. Upload the code to the Arduino board.
6. Open the Serial Monitor.
7. Set the baud rate to:

```text
9600
```

8. Type text in the Serial Monitor to encode it into Morse code.
9. Use the push button to enter Morse code for decoding.

## Example

Input:

```text
HELLO
```

Output:

```text
H: ....
E: .
L: .-..
L: .-..
O: ---
```

The LED and buzzer will also generate the Morse code signals.

## Applications

* Morse code learning
* Arduino practice project
* Embedded systems education
* Emergency signal demonstration
* Basic assistive communication prototype
* Digital input/output practice

## Limitations

* Supports only letters A-Z and numbers 0-9
* Does not support punctuation or special characters
* Button-based decoding depends on accurate timing
* No wireless communication is included

## Future Improvements

* Add LCD display output
* Add Bluetooth or Wi-Fi communication
* Add message storage
* Improve button debounce handling
* Support punctuation and special characters
* Build two-way wireless Morse communication between two Arduino boards
