import datetime
import argparse
import serial

import wiotp.sdk.device as wiotpgw

def commandProcessor(cmd):
    print(f"Command received: {cmd.data}")


def onPublishCallback():
    print(f"Confirmed event received by WIoTP\n")

    
deviceOptions = wiotpgw.parseConfigFile("config.cfg")
deviceCli = wiotpgw.DeviceClient(config=deviceOptions, logHandlers=None)
deviceCli.commandCallback = commandProcessor
csuccess = deviceCli.connect()


parser = argparse.ArgumentParser()
parser.add_argument("-E", "--event", required=False, default="event", help="type of event to send")
parser.add_argument("-N", "--nummsgs", required=False, type=int, default=1, help="send this many messages before disconnecting")
parser.add_argument("-D", "--delay", required=False, type=float, default=5, help="number of seconds between msgs")
args, unknown = parser.parse_known_args()

while (True):
    stream = serial.Serial(port, baudrate=115200)
    data = [int(float(item)) for item in stream.readline().decode('utf-8').split(',')[:-1]]

    if (len(data) > 0):
        output = {
            'sp_sv': data[1],
            'sp_bv': data[2],
            'sp_lv': data[3],
            'sp_c': data[4],
            'sp_p': power
            'time': datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S") 
        }

    success = deviceCli.publishEvent(args.event, "json", data, qos=0, onPublish=onPublishCallback)
    if not success:
        print("Not connected to WIoTP")

    time.sleep(10)   
