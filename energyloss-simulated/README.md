# Send csv data to IBM Maximo Monitor with IoT Platform SDK & Cloud Pak For Data 
## [From Drone to Fix - Solar Farm Inspection - Energy Loss Story (Simulated)]

**Last Updated:** 18 November 2024 **Authors:** <a href="https://www.linkedin.com/in/christophe-lucas-a5abab28/" target="_blank">Christophe Lucas</a> & <a href="https://www.linkedin.com/in/jamesppetrie/" target="_blank">James Petrie</a><br>
**Disclaimer:** This code is delivered as-is and is NOT formal IBM documentation in any way.


# Table of Contents
- [Introduction](#intro)
- [Get ready](#ready)
    - [Get your MAS Monitor IoT Tool details & certificate](#credentials)
    - [Download Notebook & solar-panel-readings.csv](#download)
    - [Create Project in Cloud Pak For Data & import certificate, Notebook and csv](#cp4d)
- [Understand & run the Notebook](#notebook)
    - [Notebook Explained](#notebookexplained)
    - [Notebook - GO !](#notebookgo) 

<a id='intro'> </a>
# Introduction
The objective of this recipe is to enable you to reproduce the `Energy Loss` story of the [From Drone to Fix – Solar Farm Inspection using IBM Maximo & Watsonx](../README.md) demo system - without the need to buy the hardware, and using demo data that was recorded live with a real solar panel IoT setup. **Note**: If you wish to reproduce the `Energy Loss` story including the hardware, follow this alternative [Create solar panel IoT circuit & send data to IBM Maximo Monitor](../energyloss-circuit/README.md) recipe.

In this recipe, you will:
1. Get your required MAS Monitor IoT Tool details & certificate, download the csv file containing the simulated readings & the Notebook. 
2. Setup a Cloud Pak For Data (CP4) Project and upload the certificate, the csv file and the Notebook to it.
3. Understand & run the Notebook in CP4D to:
   - visualize the csv solar panel data.
   - send the 5,720 rows of simulated data to Monitor as (a) either real-time or (b) past & future data.
   - create dashboard, anomaly function, alerts & alert-based service requests - play the end-to-end `Energy Loss` story !

**Products Used**: <a href="https://www.ibm.com/docs/en/maximo-monitor/continuous-delivery" target="_blank">IBM Maximo Monitor</a> version `8.11.11` & <a href="https://www.ibm.com/products/cloud-pak-for-data" target="_blank">IBM Cloud Pak for Data</a> `4.6`, part of the <a href="https://www.ibm.com/products/maximo" target="_blank">IBM Maximo Application Suite</a> `8.11.15`.

**Expected Duration**: 45 minutes.<br>

![image](/images/Simulated-000.jpg)

<a id='ready'> </a>
# Get ready

<a id='credentials'> </a>
## Get your MAS Monitor IoT Tool details & certificate
To send data to Monitor's IoT Tool using the Notebook, you will use the <a href="https://ibm-watson-iot.github.io/iot-python/application/mqtt/events/#publishing-device-events" target="_blank">Publishing Device Events</a> command of Monitor's <a href="https://ibm-watson-iot.github.io/iot-python/" target="_blank">IBM Watson IoT Platform Python SDK</a>. To connect, you will need a `myConfig` <a href="https://ibm-watson-iot.github.io/iot-python/device/config/" target="_blank">Configuration</a> cell, including your IoT Tool's `"orgId"` & `"domain"` values, as well as its `"caFile"` certifcate. 

Here is how to get `"orgId"` & `"domain"`:

1. `"orgId"`: from Monitor's home menu, click `Open the IoT tool`. On the top-right of the screen just below your user name, copy the `ID` - that is the value of `"orgId"`.
2. `"domain"`: observe the URL of your IoT Tool home screen. As per the image example, if your IoT Tool URL =
`https://yourgeo.iot.yourgeomas.xyz.com/`, then your `"domain"` = `iot.yourgeomas.xyz.com`.

To get the `"caFile"` certificate, use Firefox (not Chrome) and:
1. In the Watson IoT Platform browser bar, click the Security icon just next to the URL. Click the `Connection Secure` line. Then click the `More information` line. That will open a pop-up window.
2. On the popped-up window, click `View Certificate`. That will open a new tab on your browser.
On the opened Certificate browser tab, click the `ISRG Root X1` tab. In the `Miscellaneous` section, click the `PEM (chain)` link. That will download a `certificate.pem` file which name should look like: `iot-yourgeomas-xyz-com.pem`. Save it locally. 

![image](/images/Simulated-001.jpg)

<a id='download'> </a>
## Download Notebook & solar-panel-readings.csv
Download:
1. the [solar-panel-readings.csv](./files/solar-panel-readings.csv) file containing the 5,720 rows of simulated data , save it locally.
2. the [cl-energy-loss-simulated.ipynb](./files/cl-energy-loss-simulated.ipynb) Notebook, save it locally.

<a id='cp4d'> </a>
## Create Project in Cloud Pak For Data & import certificate, Notebook and csv
Following the blue arrows in the below picture, do:
1. In CP4D, go to `Projects`-`All Projects` menu and click `New project`. Name it `xy-energy-loss-simulated`, click `Create`.
2. From the Project `Assets` tab, click `New Asset`, select `Jupyter notebook editor`. Go to the `From file` tab and drag and drop the `cl-energy-loss-simulated.ipynb` you just downloaded, select `Runtime 22.2 on Python 3.10 (1vCPU, 2 GB RAM)` option. Click `Create`. This should open the Notebook.
3. Click the data waffle (top-right) and drag and drop both the [solar-panel-readings.csv](./files/solar-panel-readings.csv) and that `certificate.pem` e.g. `iot-yourgeomas-xyz-com.pem` you just downloaded.


![image](/images/Simulated-002.jpg)

<a id='notebook'> </a>
# Understand & run the Notebook

<a id='notebookexplained'> </a>
## Notebook Explained    
The [cl-energy-loss-simulated.ipynb](./files/cl-energy-loss-simulated.ipynb) Notebook provides all instructions to complete this recipe. Using the Notebook, you will:
1. Transform the csv into a pandas data frame and visualize it with an interactive Bokeh plot
2. Have 2 options to send the 5,720 rows of data to Monitor:
    - **Option A**: send data real-time at your chosen frequency (e.g. 1 reading every second, minute, 10 minutes etc)
    - **Option B**: send past & future data choosing your own `start_date`, `frequency_type` (minute, hour) and `frequency`.
2. create an anomaly score for `power`, anomaly-based alerts and a dashboard to ultimately create a Service Request for a visual drone inspection whenever a power drop or anomaly is observed.

![image](/images/Simulated-003.jpg)
<a id='notebookgo'> </a>
## Notebook - GO !  
Open the `cl-energy-loss-simulated.ipynb` notebook in the CP4D Project, click the pencil `Edit` button and run the cells one by one.
