This project uses a Wemos ESP8266 D1R2 from ebay http://www.ebay.com.au/itm/WeMos-D1-R2-Latest-ESP-12E-WiFi-ESP8266-Board-Arduino-IDE-Uno-SYDNEY/272385909659?ssPageName=STRK%3AMEBIDX%3AIT&_trksid=p2060353.m2749.l2649
  This project is based on https://pedrosnotes.wordpress.com/ which uses an Arduino UNO.
  This project uses a Wemos ESP8266 D1R2 which is Arduino compatible and has WIFI which will be used to
  upload the Elster A1100 data to www.pvoutput.org. Also uses an RTC and a light sensitive switch device. 
  http://www.ebay.com.au/itm/Photosensitive-Detector-Light-Photo-Sensitive-Switch-Sensor-Module-Arduino-Part/161869818445?ssPageName=STRK%3AMEBIDX%3AIT&_trksid=p2060353.m1438.l2649
  http://www.ebay.com.au/itm/ZS042-DS3231-AT24C32-IIC-module-precision-Real-time-clock-quare-memory-Arduino/221549752451?ssPageName=STRK%3AMEBIDX%3AIT&_trksid=p2060353.m2749.l2649
  This code has been tested with a Wemos ESP8266 D1R2 wiring a comercial infrared sesor RPM7138-R from Jaycar Cat.No. ZD1952.
  It will print to to the serial port just when it detects a change
  in Total Imports, Total exports or a change in direction (0=Importing , 1=Exporting)
  The code will not work unless 12v is connected to the power jack (9v - 24V) as the serial microUSB cable can
  only supply 3.3v to the Wemos ESP8266 D1R2 and the RPM7138-R is a 5v device.
  I have tried some IR sensors so far the only one working at the moment is the RPM7138-R which is a 5v device.

  Based on Dave's code to read an elter a100c for more info on that vist:
  http://www.rotwang.co.uk/projects/meter.html
  Thanks Dave.

