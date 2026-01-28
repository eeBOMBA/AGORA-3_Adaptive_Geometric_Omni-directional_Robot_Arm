# Advanced-Robotic-Arm-PID-Control-Project
In progess

This project demonstrates a 6-DOF robotic arm designed and built from scratch with a custom planetary gearbox and integrated PID feedback control system.  
Developed using Arduino and C++, the system uses rotary encoders and pressure sensors for precise joint positioning and adaptive grip control.

---

**Goal**
To design a modular robotic arm capable of accurate motion and real-time feedback using closed-loop PID control, serving as a foundation for future ROS2-based/Matlab Simulink autonomous operation.

---

**Features**
- 6-DOF robotic arm designed in Fusion 360
- Custom 48:1 planetary gearbox for improved torque
- PID control for position feedback and stability
- Pressure sensing system for adaptive grip control
- Encoder-based position tracking
- Modular 3D-printed components

---

**Hardware:** Arduino Uno R4, MG996R Servos, Rotary Encoders, Voltage Sensors, AS5600 encoders, CNC sheild, TMC-2209 drivers  
**Software:** C++, Arduino IDE, Altium Designer, Fusion 360, ROS2 (in progress)

---

**Control Overview**

The PID controller continuously adjusts motor signals based on encoder feedback to maintain target joint angles with minimal overshoot and steady-state error.

---

**3D Models**
All CAD and STL files for mechanical components are available under the `/3d_models` folder.  
You can view them directly in GitHub or download them for 3D printing.

---

**Future Work**
- Implementing the PID system via the rotary encoders and servos
- Implement ROS2 simulation and path planning  
- Add inverse kinematics and trajectory generation  
- Integrate computer vision for object tracking

---

**Images**
Displays all videos and pictures of progress on robot

---

**Author**
**Tenzin Lobsang Phelgyal**  
Computer Engineering Student – Robotics & Embedded Systems  
[LinkedIn](https://linkedin.com/in/tenlobphelgyal)
