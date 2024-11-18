# From Drone to Fix - Solar Farm Inspection using IBM Maximo & Watsonx
**Last Updated:** 18 November 2024 **Authors:**  <a href="https://www.linkedin.com/in/christophe-lucas-a5abab28/" target="_blank">Christophe Lucas</a> & <a href="https://www.linkedin.com/in/jamesppetrie/" target="_blank">James Petrie </a><br>
**Disclaimer:** This code is delivered as-is and is NOT formal IBM documentation in any way.<br><br>
**IMPORTANT NOTE:** This repository is still work-in-progress. As of 18 November 2024, this main page & the `Energy Loss` story recipes are complete. The `Visual Inspection` & `GenAI + Q&A` recipes are still to be written (end 2024, early 2025). 

# Table of Contents
- [**Introduction**](#intro)
- [**DEMO Flow Overview & the 3 Stories**](#demo)
- [**The 3 Stories**](#stories)
    - [Energy Loss](#energy)
    - [Visual Inspection](#visual)
    - [GenAI + Q&A](#genaiqa)
- [**Tools Architecture**](#tools)

<a id='intro'></a>
# Introduction
This demo system was created by the IBM Australia team and showcased at several conferences in Australia & New Zealand end of 2024. Its physical setup consists of rows of solar panels, of a drone inspecting the simulated solar farm, and of a little IoT system which measures the power production of one solar panel.

The goal of this GitHub repository is to:
1. provide an overview of what this system is and does
2. provide a collection of recipes to enable you to reproduce the demo


![image](/images/DroneToFix-000.jpg)

<a id='demo'></a>
# DEMO Flow Overview & the 3 Stories
**DEMO Story Pitch**: This demo system shows how the power production of a simulated solar farm is continuously monitored and how an alert then a service request for a drone inspection are triggered when a power drop or anomaly is detected. The drone visual inspection of the farm spots all defects, trends and anomalies are analyzed, and the inspection results are consolidated into health scores for each panel. Furthermore, all the inspection data can be interrogated in plain english and finally, a work order with smart fix recommendations is created using generative AI.<br>

**Products Used**: IBM  <a href="https://www.ibm.com/products/maximo/remote-monitoring" target="_blank">Maximo Monitor</a>, 
<a href="https://www.ibm.com/products/maximo/visual-inspection" target="_blank">Maximo Visual Inspection </a> (including
<a href="https://www.ibm.com/docs/en/mas-cd/maximo-vi/continuous-delivery?topic=integrating-maximo-visual-inspection-edge" target="_blank">MVI Edge</a>), 
<a href="https://www.ibm.com/products/maximo/predictive-maintenance" target="_blank">Maximo Health & Predict</a> and
its underlying <a href="https://www.ibm.com/products/cloud-pak-for-data" target="_blank">IBM Cloud Pak for Data</a>
(all part of the <a href="https://www.ibm.com/products/maximo" target="_blank">IBM Maximo Application Suite</a>)
 +
<a href="https://www.ibm.com/products/watsonx-ai" target="_blank">Watsonx.ai</a>,
<a href="https://www.ibm.com/products/watsonx-assistant" target="_blank">Watsonx Assistant</a> and
<a href="https://www.ibm.com/products/watson-discovery" target="_blank">Watson Discovery</a>.


The demo flow highlighted in below picture follows these 3 sub stories:
1. **Energy Loss**: One solar panel is covered, resulting in a sudden power production drop. 
That drop generates an alert then a service request to launch a drone inspection of the solar farm to identify defects.

2. **Visual Inspection**: The drone automatically detects defects (like Lichen Growth or Bird Drops) as panel images are inferred every 0.x second at the edge. 
All inspection results are sent to Monitor where defect counts, trends, anomalies etc insights are provided via dashboards. 
Furthermore, an overall Health score is calculated for each panel – mix of its power production, defects and number of past fix work orders. Based on the real condition of every asset of the solar farm and other info like criticality, cost or age, decisions can be made on e.g.  which panels to fix first.

3. **GenAI + Q&A**: Ask questions like “*What was the recent farm energy production like ?*” or “*How many defects were found during last inspection ?*” or “*Generate a summary of last inspection*” !
Finally, ask “*Create a Work Order*” and the system generates a work order with a long description providing clear fix instructions, materials required etc.

Two videos that show the whole demo flow can be download here: (1) [DroneToFix - Overview (04'32'') - With Voice.mp4](/images/DroneToFix-WithVoice.mp4), (2) [DroneToFix - Overview & Full DEMO (04'45'') - No Voice.mp4](/images/DroneToFix-NoVoice.mp4).

![image](/images/DroneToFix-001.jpg)

<a id='stories'></a>
# The 3 Stories

<a id='energy'></a>
## Energy Loss
**Story Pitch:** Here we start with [1] a solar panel which is uncovered. We then [2] cover it and that results in [3] a visible power drop in Monitor's IoT tool. That drop is captured by [4] Monitor's functions and [5] an alert is automatically generated. Based on that alert, [6] a service request for [7] a visual drone Inspection is triggered.<br>

**Products Used**: <a href="https://www.ibm.com/docs/en/maximo-monitor/continuous-delivery" target="_blank">IBM Maximo Monitor</a><br>

**Links to Recipe**
Follow 1 of these 2 recipes to be able to reproduce this `Energy Loss` story end-to-end:
1. [Create solar panel IoT circuit & send data to IBM Maximo Monitor](/energyloss-circuit/README.md): In this recipe, you will learn how to physically build the IoT circuit and use it to send power, current and voltage readings to the Monitor IoT tool.
2. [Send csv data to IBM Maximo Monitor with Watson IoT Platform SDK & Cloud Pak For Data](/energyloss-simulated/README.md): In this recipe, you will learn how to use a csv file containing 5,720 demo data readings to (a) send data real-time, (b) bulk-send future & past data to Monitor.

At the end of both recipes, you will create an anomaly score for `power`, anomaly-based alerts and a dashboard to ultimately create a Service Request for a visual drone inspection whenever a power drop or anomaly is observed.
![image](/images/DroneToFix-002.jpg)

<a id='visual'></a>
## Visual Inspection
**Story Pitch:** At the beginning of the project, [1] drone footage was used to [2] train a visual recognition model to detect defects like Lichen Growth & Bird Drops.
That model was then [3] deployed to MVI Edge where [4] new drone footage is monitored and new images are inferred in real time. Those new images can be used to further train and [5] ameliorate the model. 
All Inspection results are [6] sent to Monitor where [7] defect counts, trends, anomalies and so on can be visualised. 
Furthermore, an overall [8] Health score is calculated for each panel – mix of its power production, defects and number of past fix work orders. 
Based on the real condition of every asset of the solar farm and other info like criticality, cost or age, decisions can be made on e.g. which panels to fix first.

**Products Used**: <a href="https://www.ibm.com/products/maximo/remote-monitoring" target="_blank">Maximo Monitor</a>, 
<a href="https://www.ibm.com/products/maximo/visual-inspection" target="_blank">Maximo Visual Inspection </a> (including
<a href="https://www.ibm.com/docs/en/mas-cd/maximo-vi/continuous-delivery?topic=integrating-maximo-visual-inspection-edge" target="_blank">MVI Edge</a>), 
<a href="https://www.ibm.com/products/maximo/predictive-maintenance" target="_blank">Maximo Health & Predict</a>

**Links to Recipe**: The `Visual Inspection` recipe has not been written yet - stay tuned (we hope to write it before end 2024)!

![image](/images/DroneToFix-003.jpg)

<a id='genaiqa'></a>
## GenAI + Q&A
**Story Pitch:** Here we have a chat interface where we can ask questions about the solar farm like [1] *"What was the recent Energy production like?"* or [2] *"When was the last power drop?"* or *"How many Lichen Growth did you find during last inspection?”* ... or just [3] ask for Inspection Summaries. 
All those questions are translated into calls to the Maximo APIs or database and answers are provided by Watsonx Assistant. 
Similarly, we use a call to a watsonx.ai Large language model to [4] generate a fix work order which includes a Long Description detailing steps to fix, equipment and tools to use etc, based on past similar work orders and other historical info.

**Products Used**: <a href="https://www.ibm.com/products/watsonx-ai" target="_blank">Watsonx.ai</a>,
<a href="https://www.ibm.com/products/watsonx-assistant" target="_blank">Watsonx Assistant</a> and
<a href="https://www.ibm.com/products/watson-discovery" target="_blank">Watson Discovery</a>.

**Links to Recipe**: The `GenAI + Q&A` recipe has not been written yet - stay tuned (we hope to write it early 2025)!

![image](/images/DroneToFix-004.jpg)

<a id='tools'></a>
# Tools Architecture
This picture highlights how the following IBM products used to build this demo interact.<br>
<a href="https://www.ibm.com/products/maximo" target="_blank">IBM Maximo Application Suite</a> : 
<a href="https://www.ibm.com/products/maximo/remote-monitoring" target="_blank">Maximo Monitor</a>, 
<a href="https://www.ibm.com/products/maximo/visual-inspection" target="_blank">Maximo Visual Inspection </a> (including
<a href="https://www.ibm.com/docs/en/mas-cd/maximo-vi/continuous-delivery?topic=integrating-maximo-visual-inspection-edge" target="_blank">MVI Edge</a>), 
<a href="https://www.ibm.com/products/maximo/predictive-maintenance" target="_blank">Maximo Health & Predict</a> and
its underlying <a href="https://www.ibm.com/products/cloud-pak-for-data" target="_blank">IBM Cloud Pak for Data</a>
 +
<a href="https://www.ibm.com/products/watsonx-ai" target="_blank">Watsonx.ai</a>,
<a href="https://www.ibm.com/products/watsonx-assistant" target="_blank">Watsonx Assistant</a> and
<a href="https://www.ibm.com/products/watson-discovery" target="_blank">Watson Discovery</a>.<br>

![image](/images/DroneToFix-005.jpg)
