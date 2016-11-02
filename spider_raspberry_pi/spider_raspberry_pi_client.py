import urllib2
import time

info_url = "http://cpeg498-spider-mbetters.c9users.io/info"

while True:
    latest_info = urllib2.urlopen(info_url).read()
    print latest_info
    time.sleep(3)
