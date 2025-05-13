# Send csv data to IBM Maximo Monitor with IoT Platform SDK
## [From Drone to Fix - Solar Farm Inspection - Energy Loss Story (Simulated)]

**Last Updated:** 12 May 2025 **Authors:** <a href="https://www.linkedin.com/in/christophe-lucas-a5abab28/" target="_blank">Christophe Lucas</a> & <a href="https://www.linkedin.com/in/jamesppetrie/" target="_blank">James Petrie</a><br>
**Disclaimer:** This code is delivered as-is and is NOT formal IBM documentation in any way.

# Table of Contents
- [Introduction](#intro)
- [Get ready](#ready)
    - [Get your MAS Monitor IoT Tool details & certificate](#credentials)
    - [Download csv, create Project, import certificate & Notebook](#import)
        - [Download solar-panel-readings.csv](#download)
        - [OPTION A - using Local Jupyter Env](#local)      
        - [OPTION B - using Cloud Pak for Data](#cp4d)      
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
On the opened Certificate browser tab, click the `ISRG Root X1` tab. In the `Miscellaneous` section, click the `PEM (chain)` link. That will download a `certificate.pem` file which name should look like: `iot-yourgeomas-xyz-com-chain.pem`. Save it locally. 

![image](/images/Simulated-001.jpg)


<a id='import'> </a>
## Create Project & import certificate, Notebook and csv

<a id='download'> </a>
### Download solar-panel-readings.csv
Download the [solar-panel-readings.csv](./files/solar-panel-readings.csv) file containing the 5,720 rows of simulated data , save it locally.

<a id='local'> </a>
### OPTION A - using Local Jupyter Env
Download this Notebook locally [cl-energy-loss-simulated-local.ipynb](./files/cl-energy-loss-simulated-local.ipynb). 

In order to run this recipe, all we need is a Python `virtual environment` within which we'll install `Jupyter Lab` to run the Notebook.
The steps below were executed with Python 3.12.7 on a Mac but similar steps can be used on a PC (refer to documentation links below).

Open your Mac `Terminal` and follow these steps to install and activate the Python `venv`:
1.  Run `mkdir cl-energy-loss-simulated` to create a `cl-energy-loss-simulated` folder (refer to Python documentation <a href="https://docs.python.org/3/library/venv.html" target="_blank">venv — Creation of virtual environments </a> for non-Mac user and/or more info)
2. Run `cd cl-energy-loss-simulated` to move to your folder
3. Run `python3 -m venv venv` to create a virtual environment called `venv`. Once done, check that you have a `venv` folder under and that it contains the subfolders `bin`, `include`, `lib` and a file `pyvenv.cfg`.
4. Run `source venv/bin/activate` to activate the venv. Note that once this command is done, a `(venv)` should appear on the left of your Terminal command line e.g. `(venv) christophelucasibm@MacBook cl-energy-loss-simulated-test %`. That means your venv is activated successfully.
5. Run `pip list` and note that only e.g. `pip 24.2` is returned i.e. your venv has no other python package installed yet.

Let's now install `Jupyter Lab` in the `venv`:
1. Run `pip install jupyterlab` to Install Jupyter Lab (see <a href="https://jupyter.org/install" target="_blank">Installing Jupyter </a> documentation)
2. Run `pip list` and notice that many packages have been installed that Jupyter Lab uses.
3. Run `jupyter lab`. This should ultimately invite you to open a `http://localhost:8888/lab` link in your browser.
4. Drag and drop the [solar-panel-readings.csv](./files/solar-panel-readings.csv) and that `certificate.pem` e.g. `iot-yourgeomas-xyz-com-chain.pem` you just downloaded from your local folder to the Jupyter Lab window on your browser.
5. Similarly, drag and drop the [cl-energy-loss-simulated-local.ipynb](./files/cl-energy-loss-simulated-local.ipynb) you just downloaded. Open it - you are ready to go !

<a id='cp4d'> </a>
### OPTION B - using Cloud Pak for Data
Download this Notebook locally [cl-energy-loss-simulated-cp4d.ipynb](./files/cl-energy-loss-simulated-cp4d.ipynb).

Following the blue arrows in the below picture, do:
1. In CP4D, go to `Projects`-`All Projects` menu and click `New project`. Name it `xy-energy-loss-simulated`, click `Create`.
2. From the Project `Assets` tab, click `New Asset`, select `Jupyter notebook editor`. Go to the `From file` tab and drag and drop the `cl-energy-loss-simulated.ipynb` you just downloaded, select `Runtime 22.2 on Python 3.10 (1vCPU, 2 GB RAM)` option. Click `Create`. This should open the Notebook.
3. Click the data waffle (top-right) and drag and drop both the [solar-panel-readings.csv](./files/solar-panel-readings.csv) and that `certificate.pem` e.g. `iot-yourgeomas-xyz-com-chain.pem` you just downloaded.

![image](/images/Simulated-002.jpg)


<a id='notebook'> </a>
# Understand & run the Notebook

<a id='notebookexplained'> </a>
## Notebook Explained    
Both the [cl-energy-loss-simulated-local.ipynb](./files/cl-energy-loss-simulated.ipynb) and [cl-energy-loss-simulated-cp4d.ipynb](./files/cl-energy-loss-simulated-cp4d.ipynb) Notebooks provide all instructions to complete this recipe. Using the Notebook, you will:
1. Transform the csv into a pandas data frame and visualize it with an interactive Bokeh plot
2. Have 2 options to send the 5,720 rows of data to Monitor:
    - **Option A**: send data real-time at your chosen frequency (e.g. 1 reading every second, minute, 10 minutes etc)
    - **Option B**: send past & future data choosing your own `start_date`, `frequency_type` (minute, hour) and `frequency`.
2. create an anomaly score for `power`, anomaly-based alerts and a dashboard to ultimately create a Service Request for a visual drone inspection whenever a power drop or anomaly is observed.

![image](/images/Simulated-003.jpg)
<a id='notebookgo'> </a>
## Notebook - GO !  
Open the [cl-energy-loss-simulated-local.ipynb](./files/cl-energy-loss-simulated.ipynb) (OPTIONN A) or [cl-energy-loss-simulated-cp4d.ipynb](./files/cl-energy-loss-simulated-cp4d.ipynb) (OPTION B) notebook, and simply run the cells one by one.
