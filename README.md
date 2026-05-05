
<img width="3200" height="800" alt="github-header-banner" src="https://github.com/user-attachments/assets/7d7d103f-fef3-466b-b249-434fcb38ebec" />

# ecoSMRT
![Arduino](https://img.shields.io/badge/Arduino-00979D?style=for-the-badge&logo=arduino&logoColor=white)
![Edge Impulse](https://img.shields.io/badge/Edge%20Impulse-000000?style=for-the-badge)
![ESP32](https://img.shields.io/badge/ESP32-E7352C?style=for-the-badge)
## Overview
(this is my second README for this project -- I accidentally deleted the first one)
ecoSMRT is an edge AI project which determines if an article of trash is a recyclable (bottle) or not and sorts it accordingly.
It uses a refined version of MobileNetV2's CNN (convolutional neural networks) specifically for this task to make quality inferences. The model is around 60-70% accuracy when it comes to strong confidences over the 90% threshold.
I have logged nearly 45+ hours working on ecoSMRT as part of Hackclub's program, STASIS. Journal entries after every work session are also posted on the repository. 

## Incentive
 
## Hardware 
- MCU - Xiao ESP32S3-Sense w/ built-in camera module:
The Xiao ESP32 felt like the suitable choice because of its dual-core processors and built-in camera, which allowed the classification model to run smoothly locally, along with its GPIO capabilities.
Camera - OV2640 
- MG90 Microservo:
I have had my fair share of bad experience with the SG90 on multiple accounts, so I opted for its counterpart with metal-geared teeth, which seemed to be a good idea for tourque.
These two components are connected with jumper wires which pass through a diode and capacitor to prevent spikes and browning out.

## Software & Dependencies
- Arduino IDE
- Edge Impulse CLI
- ESP32 Arduino Core 2.0.8+
- `bottleclassifications_inferencing` (included in `/lib`) (refined w/ Edge Impulse)
- servo/webserver libraries used for testing/deployment

## Dataset
- Trained on [Edge Impulse](https://edgeimpulse.com)
- Dataset available at `SMRTcan-dataset`

## How It Works & Usage
Frames are fed into the CNN, which returns inferences for classifications in real time. If an inference exceeds the 90% confidence threshold, the servo adjusts lid in one direction or another, 'sorting' the article of trash. 

To use, place the trash on the lid in front of the camera and in any orientation and wait for the bin to sort before placing the second article of trash down. 

## Future Improvements
- Improving vision model by manually training on pytorch or by expanding dataset
- adding feet to the bin to stabilize and prevent shaking from disturbing classifications 💀
- adaptability
