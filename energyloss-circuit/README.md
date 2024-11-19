# Create solar panel IoT circuit & send data to IBM Maximo Monitor
## [From Drone to Fix - Solar Farm Inspection - Energy Loss Story (Circuit)]

**Last Updated:** 19 November 2024 **Authors:** <a href="https://www.linkedin.com/in/jamesppetrie/" target="_blank">James Petrie</a> & <a href="https://www.linkedin.com/in/christophe-lucas-a5abab28/" target="_blank">Christophe Lucas</a><br>
**Disclaimer:** This code is delivered as-is and is NOT formal IBM documentation in any way.<br>

## Table of Contents
- [Introduction](#intro)
- [Prereqs & hardware ingredients](#overview)
    - [Prerequisites & system used](#prereq)
    - [Hardware Buy List](#hwbuy)
- [Create device](#creating-device)
    - [Create device_type in Monitor](#create-device-type-in-mas)
    - [Create device in Monitor IoT Tool](#create-device-in-iot-platform)
- [Set up hardware](#setting-up-hardware)
    - [Create circuit](#create-circuit)
    - [Create config](#credentials)
    - [Create code](#implement-code)
- [Play the 'Energy Loss' story end-to-end](#play)
    - [Create Anomaly Function & Dashboard](#anomaly)
    - [Create Alerts & Service Request](#dashboard)

<a id='intro'> </a>
# Introduction
The objective of this recipe is to enable you to fully reproduce the `Energy Loss` story of the [From Drone to Fix – Solar Farm Inspection using IBM Maximo & Watsonx](../README.md) demo system - from buying the IoT circuit to sending live data to Monitor, to creating a service request for a drone inspection based on a power drop or anomaly. **Note**: If you wish to reproduce the `Energy Loss` story without having to purchase the hardware, follow this alternative [Send csv data to IBM Maximo Monitor with IoT Platform SDK & Cloud Pak For Data ](../energyloss-simulated/README.md) recipe.

In this recipe, you will:
1. get the list of hardware elements to buy to reproduce the IoT solar panel system.
2. set up the IoT solar panel (hardware & code parts), create a device in Monitor and send data to it.
3. create an anomaly function on the power reading, create alerts and a dashboard in Monitor to visualize the solar panel readings. Re-play the whole `Energy Loss` story by submitting a service request based on an alert.

**Products Used**: <a href="https://www.ibm.com/docs/en/maximo-monitor/continuous-delivery" target="_blank">IBM Maximo Monitor</a> version `8.11.11`, part of the <a href="https://www.ibm.com/products/maximo" target="_blank">IBM Maximo Application Suite</a> `8.11.15`.

![image](/images/Circuit-000.jpg)

<a id='overview'> </a>
## Prereqs & hardware ingredients

<a id='prereq'></a>
## Prerequisites & system used
In order to run this recipe, you need a Maximo Application Suite (MAS) ID with, at the minimun, `Application Entitlement - Base` & `Administration entitlement - Base` entitlements, as well as `Administrator` access to `Monitor` and `IoT` applications.

**System Used**: All below code was implemented using a Windows 11 Enterprise x64 laptop.


<a id='hwbuy'></a>
## Hardware Buy List
This table lists the components that were bought to build this system.
Please note that the sample buy links are just provided as examples and to show the item images, but you can purchase those at your preferred vendor site.

| #  | Item                   | Item Description                                          | Sample Buy Link |
|----|------------------------|----------------------------------------------------------|------------------|
| 1  | Atem Solar Panel       | 12v 10W Solar Panel. Note that any similar panel with red and black 'crocodile clips' to connect to should do.  | <a href="https://atempower.com/collections/solar-panels/products/12v-10w-mono-solar-panel" target="_blank">12V 10W Mono Solar Panel</a>             |
| 2  | Arduino R3            | Arduino microcontroller                                   | <a href="https://www.amazon.com.au/Arduino-A000066-ARDUINO-UNO-R3/dp/B008GRTSV6/ref=sr_1_6?dib=eyJ2IjoiMSJ9.3aUwJiF6fH5R-jBpquxxputPvpgTU2bFSuO01LH2UM7KE-yUVh7HFetTzhYgfMu6YuYN1R_nyUgn0jifA34xgblGsJKqByy6om91ume6aKkuDXyvaIDMGn7OYEXbdU_vb-W_sTUTxbT0DQwSKfBoCUc9jfObgMHRGPBuE8R4Kga3GoPrnQNtHJiZjL6mGyb_JiUEwm0GBBDUv6NEoKK-zVXzc1k8NdhTVrW10yBozvbzymilFbcpoib9QHcnMUrIC39DtPIQWOqqINtvlJprIVA7vvwpi2MBMS3ActGUums.JFc_TtzluffB6hd4ZXEjrqHFn8cErYKqIuf9tb1Ovwg&dib_tag=se&keywords=arduino%2Buno%2Br3&qid=1720654653&sr=8-6&th=1" target="_blank">Arduino Uno REV3</a>            |
| 3  | INA219                 | 5 x DC current sensor for reading solar panel power output | <a href="https://www.amazon.com.au/INA219-Bi-Directional-Current-Supply-Breakout/dp/B0CJMV4Q38/ref=sr_1_4?crid=17EWT3WQ1DICR&dib=eyJ2IjoiMSJ9._BqhQ_kPZlgWRuR4KBEpVcgHsVA3x3WAvkcurLParmI3tc_CuUNojodsy90y52-x847lswhIQkBm0SUHwsp4fhMJxJLzslt68yjh6OA39aV_iVNyEUezk6Ezj3fgu3Wokod7YuZF_xMun4e3ViE15PJAR-AZ1lbg7PF4RpNWJn-4qTXRyj8FA1zAUC-NE7aU6b8j9Zp_8KJbmUKvXiyLJAzrapc6H04qmGvg2dXXHeRVt55tzD5FjgXdyJPq40DV4cbb_KjrdPxqvSF2ojzpU3k-Bdw3oLYkn2NFP0xTfeA.CzNVi_OXczhfKNLXPw3nr6R4v_v3eoJXbe2m4IZARE4&dib_tag=se&keywords=ina219&qid=1720414949&s=electronics&sprefix=ina219%2Celectronics%2C234&sr=1-4" target="_blank">5 x INA219 DC Current Power</a>             |
| 4  | Jumper wires           | For connecting up circuit                                 | <a href="https://www.amazon.com.au/KICHOUSE-Jumper-Connecting-Cables-Breadboard/dp/B0CC4H2JDV/ref=sr_1_12?crid=1AAPFECNFB1YG&dib=eyJ2IjoiMSJ9.RZuN3DWp909Wy1xwoQhY358TbrYX8LBQq80Qgj7hrHivMulqtLBDET-PKWI8Dk4CIdsus3qolC--FDHbYOSyBbKaYl20ot6y4zm9K4ffK7gba49OqxdPP7TUtJ6ic4f3Yem0taAZ_IxaSj2Wkaq9KVs0-9MtXfVk4ceCHDWmdf3WnBQn4oMCgV1pSmbxMXjTi3WCLqAz053__h0nVssoSCGX9Gu4TiGizMyU2OMA6DL5NzL8M8wfEuKhtyhyZBDKPRfjO1cW0FHHT98BFcclEEKNu8wHMUlaN0KBmdZ2cxs.9wNJ5NUGZ5PMt8ZntmrtGVH8jzwmvJu74SV97r6wnpM&dib_tag=se&keywords=jumper+male+to+male+cable+breadboard&qid=1720058582&sprefix=jumper+male+to+malecable+breadboard%2Caps%2C211&sr=8-12" target="_blank">Jump Cable 40pcs</a>            |
| 5  | LED                    | Light Emitting Diodes for excess load consumption        | <a href="https://www.amazon.com.au/DiCUNO-450pcs-colors-Emitting-Assorted/dp/B073QMYKDM/ref=sr_1_32?dib=eyJ2IjoiMSJ9.pHXQF3skQg3jz54p0J8fn16b_mAj8ErP3cUud97PX6aRDGnwn9oiTgqyF2vgkma-RvyMS4KWqic2QFDNu4zMfg_1ZrVcVCFtWyqiAQCNv6Svvd77T-nDj90D2nR4nA6JBy92X6bDr69wStNkl7oEVHJOVL7jCo2f-exRqvKeXCjZ6rPNnKth57145lLhlpzBC2Gs5jyF3yU1ZJPiyBSJpq75Razfj5PGEtNWYm88p0RHVF5hv-Q3Eu_fa4Qfc8m9o8gtEVCnRCcnjd19hG159Xa273rB12egST6MYktvm_w.lwtFaKqnHDl859yZwdXrgms3Ucn5hV9hPHAYS9phGJM&dib_tag=se&keywords=arduino+led&qid=1720654966&sr=8-32">5mm Light Emitting Diodes</a>            |
| 6  | Display case           | 20x30x20cm box for circuit                               | <a href="https://www.amazon.com.au/ACRLIE-Collectibles-Protection-20x30x20cm-7-9x11-8x7-9inch/dp/B094HQ7PR4/ref=sr_1_1?crid=7RW3P48FGH45&dib=eyJ2IjoiMSJ9.F0H4Ctbzc-CWyOajwGVMQEe4-BUUMdy_-YEHDJV1lggni3Z6L2z7E-7GxpY8fWKauKg4719Q4aW0QEMxgI2nCWWNF3KOQ6frN4e2vawKvQ2wwf1HjOWnemCQKJiyLcYwEVibYTCU4WpDvB45n3YEk30xHu7I_VIw3mZJxveZ5XiThc0_Nkb2sCjwKnEeRH2Nlimt71x1SDDcpy8GEQ-Da6uWhr0E4IzdJeO3hg1Oaav3nBcpMF1ON01xhXQ_L0oyIgov0lpTEdthOLNJd381GFSp05-sHQdGVhN6QL_SeUE.GAT723S_wESl-e5hOgQpD0zpU7_dO1swGE4FIQQh7CU&dib_tag=se&keywords=transparent%2Bcasing%2B30x20x15&qid=1724048334&sprefix=transparent%2Bcasing%2B30x20x1%2Caps%2C269&sr=8-1&th=1" target="_blank">Acrylic Display Case</a>            |
| 7  | USB-A to USB-B Cable       | For connecting Arduino to laptop                          | <a href="https://www.amazon.com.au/UGREEN-Printer-Scanner-Lexmark-Samsung/dp/B00P0FO1P0/ref=sr_1_5?adgrpid=1232552855489479&dib=eyJ2IjoiMSJ9.vdYLo19k8qmDlRune2-G9eimj4tkjjOmtCnVfijlYx1xy4ZdubC_8NB6xzxm195lTQrxupDNVAXZFEQ0qPInk8pIrOz_GlqEJPzTO0KIorOidtrHnn8uKxTBSt_Vnza-I749iuGHw2wILGCAMD16CO2PxLvyXGgYsdaHcyxo0zhWB2jY2BOf92VM85IfLK-oEBA9M6-F-lLBsISbwuFP7um9Qb1c5s2KMu8jUuhAxRCEs1PB-6bspGwwu11_RYIG0s1fRiQ-qMKcW55D1WHWg3wCPhBw1qA3DDaUlyhAfcs.caAU8CyClghm76NdRGJNG92kh_C-Mgn_AW8ABAXlEpM&dib_tag=se&hvadid=77034726595754&hvbmt=be&hvdev=c&hvlocphy=123941&hvnetw=o&hvqmt=e&hvtargid=kwd-77034800348468%3Aloc-9&hydadcr=19768_524983&keywords=usb%2Ba%2Bto%2Busb%2Bb%2Bcable&msclkid=c16cb9a5c1e812b174d1df635df704d7&qid=1724292130&sr=8-5&th=1" target="_blank">USB-A to USB-B Cable</a>             |
| 8  | [Optional] Desk Lamp     | To have consistent light source over the panel           | <a href="https://www.amazon.com.au/Flexible-Painted-Classical-Bedside-Studying/dp/B07T3GGWP9/ref=sr_1_2_sspa?crid=29LKRHSVLEST4&dib=eyJ2IjoiMSJ9.UF8NM7pqojjBoD_D56UhL6XXgKnPXe6LJ417enKIeySnjLLTgtfPcZKZ5Th7tI8iPXTJEvPbzOoyugv3MBU-0j-2W5X-SKKu9AjRofIhtLBvRFDCn9yrhMrG0L7jspTC-ZnU0zDX7CnR_XS8ru922vfh15KVK92a_GAl2wIxTIv-gJvZHZ1IbmPCIBcqivhIbdf3-TQSy4DXuM0F77tUeYxBpmhaNCs-CM0okmvzzrAoEVrkeWnaE12w3fYRHe7ZhJvx1bl-xbemlNZUSAy4dnLpRe3l51jVg18gT1rQgac.kbf_fSHMt2CWIcbxgKXNPqZ_hh4NQaFtvuyjkXmqavQ&dib_tag=se&keywords=desk+lamp+e27+holder&qid=1724049567&sprefix=desk+lamp+e27+hold%2Caps%2C264&sr=8-2-spons&sp_csd=d2lkZ2V0TmFtZT1zcF9hdGY&psc=1" target="_blank">Swing Arm Desk Lamp</a>             |
| 9  | [Optional] Light Bulb    | To have consistent light source                           | <a href="https://lightingsuperstore.com.au/collections/e27-es-led/products/8-7w-edison-screw-es-e27-led-cool-white-gls-frosted-dimmable" target="_blank">9.8w Light Buld</a>             |


<a id='creating-device'> </a>
# Create device

<a id='create-device-type-in-mas'></a>
## Create device type in Monitor
1.	Open MAS > Monitor > Create a device type 
2.	Choose **basic template** and select **Next**
3.	Name the **device type** in the format- `<Initials>_<Device>` e.g. `JP_SolarPanel` – then select **Create**
4.  In the **Metrics** tab, select **Add metric +** and add the following metrics:
    | Metric | Display name | Event | Type | Unit |
    | ----------- | ----------- | ----------- |  ----------- |  ----------- | 
    | sp_p | SolarPanel_Power | event | NUMBER | mW | 
    | sp_bv | SolarPanel_BusVoltage | event | NUMBER | v | 
    | sp_sv | SolarPanel_ShuntVoltage | event | NUMBER | mV | 
    | sp_c | SolarPanel_current | event | NUMBER | mA | 


<a id='create-device-in-iot-platform'></a>
## Create device in Monitor IoT Tool
1.	Move back to MAS suite navigator > Tools > IoT
2.	Select **Add Device** in top right
3.	Enter previously created `device_type` into **device type** field
4.	Name the **device** in the format - `<Device type>_<Identifier>` e.g. `JP_SolarPanel_001` – then select Next
5.	Enter any relevant device information (Optional)
6.	Select **Next** through Device information, gateway and security tabs, and finally Finish on summary tab
7.	Record `Authentication token` on next screen as this will be used later

This picture highlights the steps you just completed:
![image](/images/Circuit-002.jpg)

<a id='setting-up-hardware'></a>
# Set up hardware

<a id='Create circuit'></a>
## Create circuit
1.	Establish the following connections on the board:
    -	Solar Panel Positive -> Sensor Power In
    -	Sensor Power out -> LED (3 were used in sequence to consume enough power)
    -	LED output -> Solar Panel Negative
    -	Sensor 5V Power -> Microcontroller 5V Power source
    -	Sensor GND -> Microcontroller GND
    -	Sensor SDA -> Microcontroller pin A5
    -	Sensor SDL -> Microcontroller pin A4
2. At this stage, observe how the LED lights react to you covering and uncovering the panel by getting less or more bright - that brightness relates to that power production which we will later see in Monitor
3.	**Connect** Arduino to laptop using USB cable

![image](/images/Circuit-001.jpg)


<a id='credentials'> </a>
## Create config - Get your MAS Monitor IoT Tool details & certificate
To send data to Monitor's IoT Tool, you will use the <a href="https://ibm-watson-iot.github.io/iot-python/application/mqtt/events/#publishing-device-events" target="_blank">Publishing Device Events</a> command of Monitor's <a href="https://ibm-watson-iot.github.io/iot-python/" target="_blank">IBM Watson IoT Platform Python SDK</a>. To connect, you will need a `myConfig` <a href="https://ibm-watson-iot.github.io/iot-python/device/config/" target="_blank">Configuration</a> cell, including your IoT Tool's `"orgId"` & `"domain"` values, as well as its `"caFile"` certifcate. 

Here is how to get `"orgId"` & `"domain"`:

1. `"orgId"`: from Monitor's home menu, click `Open the IoT tool`. On the top-right of the screen just below your user name, copy the `ID` - that is the value of `"orgId"`.
2. `"domain"`: observe the URL of your IoT Tool home screen. As per the image example, if your IoT Tool URL =
`https://yourgeo.iot.yourgeomas.xyz.com/`, then your `"domain"` = `iot.yourgeomas.xyz.com`.

To get the `"caFile"` certificate, use Firefox (not Chrome) and:
1. In the Watson IoT Platform browser bar, click the Security icon just next to the URL. Click the `Connection Secure` line. Then click the `More information` line. That will open a pop-up window.
2. On the popped-up window, click `View Certificate`. That will open a new tab on your browser.
On the opened Certificate browser tab, click the `ISRG Root X1` tab. In the `Miscellaneous` section, click the `PEM (chain)` link. That will download a `certificate.pem` file which name should look like: `iot-yourgeomas-xyz-com.pem`. Save it locally.

<a id='implement-code'></a>
## Implement code
1.  Download and install Arduino IDE: `https://www.arduino.cc/en/software`
2.  With the Arduino plugged into your device, select the COM port that shows `Arduino Uno` as per below
    ![image](/images/Arduino-ide.png)
3.  Copy the below code into a new file and **upload** to arduino, noting the baud rate of `115200`.
    This will output 1 line to serial every second with the format:
    `<sp_sv>,<sp_bv>,<sp_v>,<sp_c>,<sp_p>\n`

    **Note:** Full file is saved here: [arduino_reading.ino](/energyloss-circuit/files/arduino_reading.ino)

    -------------- 
    ```cpp
    #include <Adafruit_INA219.h>

    Adafruit_INA219 ina219;

    void setup(void) 
    {
    Serial.begin(115200); // This is the baud rate and will be used in python code
    while (!Serial) {
        delay(1);
    }

    auto connected = false;
    while (!connected) {   
        if (ina219.begin()) {
            connected = true;
        }
        Serial.println("Connecting...");
        delay(1000);
    }
    
    ina219.setCalibration_16V_400mA();

    Serial.println("Measuring voltage and current with INA219 ...");
    }

    void loop(void) 
    {
        float shuntVoltage = ina219.getShuntVoltage_mV();
        float busVoltage = ina219.getBusVoltage_V(); 
        float current = ina219.getCurrent_mA();
        float power_mW = ina219.getPower_mW();
        float voltage = busVoltage + (shuntVoltage / 1000);

        Serial.print(shuntVoltage); Serial.print(',');
        Serial.print(busVoltage);Serial.print(',');
        Serial.print(voltage);Serial.print(',');
        Serial.print(current);Serial.print(',');
        Serial.print(power_mW);Serial.print(',');
        Serial.println("");

        delay(1000);
    }
    ```

4. On VSCode or any other IDE that supports python, copy the below python code to pick up the line output from arduino and send to IoT:

    **Note:** Full file is saved here: [relay.py](/energyloss-circuit/files/relay.py)


    ```python
    
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
                'sp_sv': data[0],
                'sp_bv': data[1],
                'sp_lv': data[2],
                'sp_c': data[3],
                'sp_p': data[4],
                'time': datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S") 
            }

        success = deviceCli.publishEvent(args.event, "json", data, qos=0, onPublish=onPublishCallback)
        if not success:
            print("Not connected to WIoTP")

        time.sleep(10)

    ```
<a id='play'></a>
# Play the 'Energy Loss' story end-to-end
Now that the data is flowing, let's visualize it in Monitor and play the `Energy Loss` story end-to-end.

<a id='anomaly'></a>
## Create Anomaly Function & Dashboard
Create the `power_anomaly` data item:
1. From the `Monitor` left menu, `Devices` tab, select your Device Type e.g. `JP_SolarPanel` and click `Setup device type`.
2. In the `Data Items` menu, click `Create metric` under the `Batch data metric (calculated)` section. Select `KMeansAnomalyScore` function. Click `Next`. In the `input_item` field, select `sp_p` (the power reading) and set `windowsize` to `12`. Click `Next`. On final screen, untick `Auto schedule` and set `Executing every` to `5 Minutes` and `Calculating the last` to `30 Days`. Name you data item `power_anomaly` and click `Create`. Wait 5 minutes for the `power_anomaly` to be calculated.

Create a Dashboard:
1. From the Monitor `Setup` menu, `Devices` tab, select your Device (NOT the Device Type) e.g. `JP_SolarPanel_001` and click the `+` buttom next to the `Metrics Dashboard` tab. Name it `Overview`.
2. Reproduce a Dashboard similar to the one in below picture i.e. (a) create a `Image` card and add a nice picture to it, (b) create a `Value/KPI` card and select the `sp_c`, `sp_bv`, `sp_p` data items, call it `Last Readings`, (c) create a `Value/KPI` with , (d) importantly create a `Time Series` and display all readings on it, including the `power_anomaly` data item you just created.

<a id='dashboard'></a>
## Create Alert & Service Request
On the `Time Series` plot of the dashboard, select `sp_p` and `power_anomaly` only and notice the spikes of the `power_anomaly` whenever there's a power drop. Observe the value of those spikes and  take note e.g. you will likely notice that the `power_anomaly` score spikes to values above `16` each time there is a drop.

Create the `alert_power_anomaly` data item and add it to the dashboard :
1. From the `Data Items` menu, click `Create metric` under the `Batch data metric (calculated)` section. Select `AlertHighValue` and click `Select`.
2. Click `Next`. Select `power_anomaly` in `input_item`, in `upper_threshold` enter the 'spike' value just mentionned e.g. `16`. Select `High` in `Severity` and `New` in `Status`. Click next and on last screen. Click `Create`.
3. Back to the dashboard, click `Edit dashboard` (top right) and add an `Alert table` as per image below.

Finally, you can now create a `Service Request` for a visual drone inspection from the Alert table.

![image](/images/Circuit-003.jpg)
Well done - you made it !


