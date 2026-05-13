
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
Often times, managing waste can be overwhelming and done incorrectly. At the recycling level, nearly 76% of recyclables are lost at the household level (https://recyclingpartnership.org/residential-recycling-report/), and even those which are put into the recycling bin can be wrongly classified. As these wrongly-sorted articles of trash add up, the recycling process loses its efficiency, inflating unnecessary costs to over $3.5 billion yearly for the US (https://www.federalrecycling.com/industry-insights/common-recycling-mistakes-and-how-to-avoid-them/). As a direct result, recycling becomes more of a burden than a tool. Human error is exacerbating what recycling aims to fix: bettering the environment. Instead of looking towards refining the system, we should look to fix the root of the cause, our inaccuracies, by removing ourselves from the equation. AI is better than humans probably so like make a trash sorter ig 🤷‍♂️.

## How ecoSMRT was made
I had originally settled for a more complex mechanical sorter, but the AI proved to be a challenge, so I simplified its design down to focus on firmware. The AI and curating a dataset which could yield decent results was also hard: At first, I was taking pre-existing datasets online, but the models were terrible. I did a lot of research and realized that I should probably use the native camera and setup for the training data, which turned out to work much better. Also, I switched from FOMO to MobileNet because like a month in I realized that image detection and classification were completely different (explanation found in journal). Everything else was relatively smooth sailing.

## Hardware 
- MCU - Xiao ESP32S3-Sense w/ built-in camera module:
The Xiao ESP32 felt like the suitable choice because of its dual-core processors and built-in camera, which allowed the classification model to run smoothly locally, along with its GPIO capabilities.
Camera - OV2640 
- MG90 Microservo:
I have had my fair share of bad experience with the SG90 on multiple accounts, so I opted for its counterpart with metal-geared teeth, which seemed to be a good idea for tourque.

## Electronic Framework
I used a perfboard for this prototype to organize electronics. 
The servo's jumper wires connect to sockets and pass through a diode and capacitor in order to prevent spikes and browning out. These go to terminals where the Xiao's jumper wires are connected. Schematic for wiring on perfboard:

<img width="406" height="380" alt="image" src="https://github.com/user-attachments/assets/87bba609-41c8-49c5-919e-325569f664a4" />

## CAD / 3d Printed Parts
<img width="1520" height="680" alt="SMRTCAN--exploded2" src="https://github.com/user-attachments/assets/87e8d460-363f-445a-8450-bfc745447585" />

Parts are printed in PLA, amounting to around 300 grams of filament (although all my prototypes summed up to a kg spool)
These consist of the bin's lid, which revolves on small axis extensions. These pass through bores that connect to the edges of the lid, and, when connected to the servo, keep the lid at the set position. The mount for the ESP32 slides around the servo's housing and attach to its walls. Additionally, I have modeled small attachments to connect the two halves of the lid if it cannot be printed as one part. 

## Software & Dependencies
- Arduino IDE
- Edge Impulse CLI
- ESP32 Arduino Core 2.0.8+
- `bottleclassifications_inferencing` (included in `/lib`) (refined w/ Edge Impulse)
- servo/webserver libraries used for testing/deployment
  
here are some crappy inferences from my first few models:

<img width="583" height="777" alt="image" src="https://github.com/user-attachments/assets/8f3c499e-f5ab-4f76-8893-ca2cdb620fc6" />

### Image Classification VS Object Detection (written in a journal entry)
Classification observes the image as a whole and returns a confidence score; its only question to ask is: What is this thing in front of me? Detection has to decide three things: Are there multiple objects? What are the objects? Where are the objects? In this case, the model has to consider spatial data when moving forwards for its confidence, which takes a lot more computing power and is way too overkill for my project.

### How Image Classification Works
Image classification is tuning a pre-trained model for a specific need. My model, MobileNetV2 has already been trained on ImageNet with millions of classification data – its weights have already adjusted to finding curves, textures, and colors within an image. What the refining does is simply re-run these weights over the image (or vector with the image data) – there is a series of these filters (matricies which are averaged out to make smaller maps) that alter the feature map that compound on one another, so they take the last feature’s map, instead of the old image. In this way the filters are able to distinguish curves, then textures, then shapes, then the image itself – again stacking over itself. The result is a confidence score that can be achieved even with little data.

## Dataset
- Trained on [Edge Impulse](https://edgeimpulse.com)

## How It Works & Usage
Frames are fed into the CNN, which returns inferences for classifications in real time. If an inference exceeds the 90% confidence threshold, the servo adjusts lid in one direction or another, 'sorting' the article of trash. 

To use, place the trash on the lid in front of the camera and in any orientation and wait for the bin to sort before placing the second article of trash down. 

## Future Improvements
- Improving vision model by manually training on pytorch or by expanding dataset
- adding feet to the bin to stabilize and prevent shaking from disturbing classifications 💀
- adaptability
