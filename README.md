# Elster_A1100
Arduino sketch to decode IR data from the IRDA port in the Elster electicity meter

Photo of my setup https://drive.google.com/open?id=0B73QqrlATOVmOV9iQktmT0NuSVU

Using this IR receiver:
http://www.jaycar.com.au/Active-Components/Optoelectronics/Optocouplers/5mm-Infrared-Receiver/p/ZD1952
 actually the spec sheet is found as RPM7138-R
 
And these parts:

 http://www.ebay.com.au/itm/WeMos-D1-R2-Latest-ESP-12E-WiFi-ESP8266-Board-Arduino-IDE-Uno-SYDNEY/272385909659?ssPageName=STRK%3AMEBIDX%3AIT&_trksid=p2060353.m2749.l2649
 
  This project is based on https://pedrosnotes.wordpress.com/ which uses an Arduino UNO.
  
  This project uses a Wemos ESP8266 D1R2 which is Arduino compatible and has WIFI which can be used to
  upload the Elster A1100 data to www.pvoutput.org. Also uses an RTC and a light sensitive switch device. 
  
  http://www.ebay.com.au/itm/Photosensitive-Detector-Light-Photo-Sensitive-Switch-Sensor-Module-Arduino-Part/161869818445?ssPageName=STRK%3AMEBIDX%3AIT&_trksid=p2060353.m1438.l2649
  
  http://www.ebay.com.au/itm/ZS042-DS3231-AT24C32-IIC-module-precision-Real-time-clock-quare-memory-Arduino/221549752451?ssPageName=STRK%3AMEBIDX%3AIT&_trksid=p2060353.m2749.l2649
 
some info here :
http://forums.whirlpool.net.au/forum-replies.cfm?t=2291936&p=2

Notes on the project here:
https://pedrosnotes.wordpress.com/2015/09/26/decoding-electricity-meter-elster-a1100-first-steps/

Thanks David and Pedro.

