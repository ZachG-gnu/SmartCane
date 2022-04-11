# SmartCane
An embedded system designed to add smart capabilities to a walking cane.

### Background Information
This project involved the design and construction of the SmartCane, with the purpose of enhancing the mobility for the visibly impaired through a smart cane. A normal walking cane requires the user to physically touch an object to detect it. This is great, however what if the user is trying to navigate around a crowd of people? It would be awkward for the user to touch the people around them with a cane. A walking cane also does not have the ability to detect puddles on the ground, which is a hazard for the visually impaired. The SmartCane features onboard sensors to solve all these problems. The vision of the SmartCane is to allow every visually impaired person to have the freedom to go wherever they want to go. 

### Theory Of Operation
An ultrasonic sensor is located on the front of the bottom of the cane. When the sensor detects in object in front of it that is closer than 20cm, it will activate a vibration motor located on the handle of the cane. The vibration will then stop once the object is further than the threshold. The SmartCane also has the ability to detect water at ground-level. When the bottom of the SmartCane encounters enough water, it will active a buzzer. The buzzer will continue to sound until the SmartCane is taken out of the water. When in need of saving battery, the SmartCane can also be put into low-power mode using the capacitive touch sensor. In low-power mode, power consumption is greatly reduced, which allows the battery to last longer.

### Schematic
<img src="https://github.com/ZachG-gnu/SmartCane/blob/master/images/SmartCane_schematic.png" width="800" height="auto">

### Thumbnail
<img src="https://github.com/ZachG-gnu/SmartCane/blob/master/images/SmartCane_thumbnail.png" width="600" height="auto">

