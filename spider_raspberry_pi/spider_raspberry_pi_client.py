import urllib2
import time

#A c9.io server is used to send signals to the Raspberry Pi
info_url = "http://cpeg498-spider-mbetters.c9users.io/info"

while True:
    latest_info = urllib2.urlopen(info_url).read()
    print latest_info
    #TODO: Here, parse latest_info and then pass the relevant info along a serial line
    #      to the Arduino, which will then act according to that info
    time.sleep(3)
