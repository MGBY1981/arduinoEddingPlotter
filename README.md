Welcome to the 'arduinoEddingPlotter'

Ever thought about creating a printing machine using LEGO parts and Arduino Uno components?
To realize the project you will need:

- Arduino Uno R3 or R4
- 2 stepper motors
- 1 servo motor
- 1 LEGO rail vehicle which runs on LEGO rails
- 50 centimeters of LEGO rails for the pen vehicle to run on the X axis
- 1 conveyor belt for pulling the pen vehicle on the X axis from left to right
- 2 cardboard tubes for holding and spinning the paper
- 2 timing belts for turning the cardboard tubes
- a lot of cables :)
- a breadboard for connections between Arduinon and controllers
- an edding that can be fixed on the vehicle

The code can paint 2 color bitmap images in the "0" and "1" format, where "0" paints a black dot and "1" leaves a white dot
printer can paint images with a maximum sitze of 400 pixels (width) and 250 pixels (height) maybe even a little more.

--> How can I convert .jpg oder .png pictures into textual bitpam files?
I recommend this simple browser tool:
https://www.dcode.fr/binary-image

pick a file, select 'custom width' (400 for example) and press 'convert' to get the result.
Then use an editor like Notepad+ or Vim to remove all blanks and transfer the file that all content is in 1 single line (important!)
The copy the (very long) line of '0' and '1' elements and insert it into the graphics PROGMEM arrays. 
Adjust the parameters width so it fits to the actual width of your image.
You might also have to adjust 'lineBackLength' in order to have the pen travellinig back to the initial position.
The initial pen position on the rails needs to be same for every line, otherwise the lines get shifted and the image will look like crap.


painting bitmaps can take a lot of time (between 1 and 3 hours depending on size and complexity).
Parameters need fine-tuning (pen distance, lines, with, speeds). You can experiment with

For questions don't hesitatie to ask: martin.grabsch@gmail.com

Have fun!
