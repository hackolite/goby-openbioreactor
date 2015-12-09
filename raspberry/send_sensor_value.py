import serial
import time
ser = serial.Serial('/dev/ttyACM0',9600, timeout=1000)
while 1==1 :
        time.sleep(2)
        try:
            dic = ser.readline()
            dictionnaire = eval(dic)
            import urllib
            import httplib     
            print dictionnaire
            params = urllib.urlencode({'field1':dictionnaire['temp'],'field2':dictionnaire['density'],'field3':dictionnaire['density'], 'key':'xxxxxxxxxxxxxx'})
            # temp is the data you will be sending to the thingspeak channel for plotting the graph. You can add more than one channel and plot more graphs
            headers = {"Content-typZZe": "application/x-www-form-urlencoded","Accept": "text/plain"}
            conn = httplib.HTTPConnection("api.thingspeak.com")
            conn.request("POST", "/update", params, headers)
            response = conn.getresponse()
            print 'status', response.status, 'response', response.reason
            data = response.read()
            conn.close()
            print 'ok'   
        except Exception, e:  
            print "erre", e

