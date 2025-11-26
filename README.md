Developed an embedded application with the following requirements:

Reaction Game

1. The application runs as an Autosar Application.
2. Upon startup, the program will show a welcome message via the serial port.
3. After pressing one of the two white buttons, the program will wait for a random time. After waiting for 1s to 3s a random value (1 or 2) will be displayed on both 7 segment displays.
4. The user has to press the right button in case a ‘1’ is displayed and the left button in case a ‘2’ is displayed.
5. In case the correct button is being pressed, the measured reaction time in [ms] will be shown and the game can be started again by pressing one of the two buttons.
6. In case a wrong button is pressed, an error message will be displayed and the game can be started again by pressing one of the two buttons.
7. In case the user does not press a button within 1 s, the message “Too slow” will appear and the game can be started again by pressing one of the two buttons.
8. One game consists out of 10 rounds
9. At the end of a game, print the score (i.e. correct number of button pressed), the total time and the average time.

Arcadian Style

1. In a first step, create a fading traveling light. The three LED’s are glowing like the 80ies Knightraider pattern. (Fader)
2. Using the RGB LED, implement an easily configurable glowing function. Using a const - table (pseudo code) which creates a specific sequence and runs permanently. (glower)
