<p align="center">
  <img src="https://user-images.githubusercontent.com/3983762/226071344-ee43eaa5-1fc4-49ac-9c41-0afcf9a6d8e3.png" width="20%"/>
</p>



<h1 align="center">Pippo</h1>


## CONGRATULATIONS DAVI!!!
### Welcome to the nerd club (again).
When Moni suggested getting you a present for your gradution (well done btw 🤓) I thought I'd make one instead and open up another super awesome world of nerdiness/coolness (to us... not them 🤫)!

The code below controls an [ESP8266](https://www.wemos.cc/en/latest/d1/d1_mini.html) (an [Arduino](https://www.arduino.cc/) compatible microcontroller) thats written in C++ (kinda... they made thier own language to make things easier but its very C++ like).

To run it, follow these steps:

1. It should start by initialising as an access point for you to give it your wifi credentials (it should be called Pippo or what ever is #define NAME).
2. You need to use the Alexa app to connect the device to your network (it should be called Pippo or what ever is #define ID_RELAY)
3. Then say "Alexa, pippo on/off" and hope it doesn't blow up 💣💥

Well done for graduating good sir!! I know from experience how hard it is to get there and I don't doubt there is a lot of awesome projects to come!

Disclaimer: this shouldn't burn down your lovely new house 🤭

### Edit the Code 

To edit the code you need to download the [Arduino IDE](https://www.arduino.cc/en/software). If you want to explore more advanced tools, look into [PlatformIO](https://platformio.org/). It runs in Visual Studio and allows for a lot more project structure. 

The libraries needed include: [fauxmo](https://github.com/n8henrie/fauxmo) and [wifiManager](https://github.com/tzapu/WiFiManager)
