<div align="center">    
 <img src="https://img.shields.io/github/license/create1st/esp32-matter-airbase-xiao.svg" align="left" />
 <img src="https://img.shields.io/badge/matter-blue.svg" align="left" />
 <img src="https://img.shields.io/badge/PRs-welcome-green.svg" align="left" />
</div>

# Daikin Airbase BRP15B61 bridge for Matter

### Disclaimer
All product and company names or logos are trademarks™ or registered® trademarks of their respective holders.
Their use does not imply affiliation with or endorsement by them or any associated subsidiaries!
**Daikin** is a trademark of **Daikin Industries, Ltd**.

This personal project has an educational context, is developed as a proof of concept, and has no business goal.
The author is not responsible for the harm or damage caused by using this software. You may use it at your own risk and responsibility only.

### Resources
https://github.com/ael-code/daikin-control
https://github.com/Apollon77/daikin-controller
https://en.wikipedia.org/wiki/Matter_(standard)

### Installation
This project is intended as a replacement to https://github.com/create1st/smartthings-daikin-airbase It takes advantage of Matter standard and as such can be used with any home automation platform.  
[IMPORTANT] Please be aware that this is still under development and implementation progress is dependent on
https://github.com/espressif/arduino-esp32/issues/7432

# You need to create a file with your WiFi credentials
airbase/credentials.h

```c++
#ifndef CREDENTIALS_H_
#define CREDENTIALS_H_
const char ssid[] = "ssid";
const char pass[] = "pass";

#endif

```
