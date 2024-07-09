# esp8266-oled-0.96-inch
dự án nghịch vui cho esp8266 oled
Installing with Boards Manager
Starting with 1.6.4, Arduino allows installation of third-party platform packages using Boards Manager. We have packages available for Windows, Mac OS, and Linux (32 and 64 bit).

Download and install Arduino IDE 1.x or 2.x
Start Arduino and open the Preferences window
Enter https://arduino.esp8266.com/stable/package_esp8266com_index.json into the File>Preferences>Additional Boards Manager URLs field of the Arduino IDE. You can add multiple URLs, separating them with commas.
Open Boards Manager from Tools > Board menu and install esp8266 platform (and don't forget to select your ESP8266 board from Tools > Board menu after installation).
Latest release Latest release
Boards manager link: https://arduino.esp8266.com/stable/package_esp8266com_index.json
Go to Tools > Board > Board Manager, search for esp8266 and install
Download eyes: git clone https://github.com/nguyenthehoang29th122009/esp8266-oled-0.96-inch/tree/main
If you can't find the COM port of ESP8266 board, then you're probably missing the right drivers. Here are links to drivers of the 2 most used UART chips on ESP8266 development boards
CP2102: https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers
CH304: https://sparks.gogo.co.nz/ch340.html
Flash 
1 Open eyse.ino with the Arduino IDE.
2 Under Tools > Board in the Deauther esp8266 Board, section, select your board. For example NodeMCU
4 Connect the ESP8266 board via USB and select its port under Tools > Port.
5 Press Upload.
