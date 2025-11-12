# Advanced-Robotic-Arm-PID-Control-Project
In progess
# Advanced Robotic Arm with PID Control

This project demonstrates a 5-DOF robotic arm designed and built from scratch with a custom planetary gearbox and integrated PID feedback control system.  
Developed using Arduino and C++, the system uses rotary encoders and pressure sensors for precise joint positioning and adaptive grip control.

---

**Goal**
To design a modular robotic arm capable of accurate motion and real-time feedback using closed-loop PID control, serving as a foundation for future ROS2-based autonomous operation.

---

**Features**
- 5-DOF robotic arm designed in Fusion 360
- Custom 16:1 planetary gearbox for improved torque
- PID control for position feedback and stability
- Pressure sensing system for adaptive grip control
- Encoder-based position tracking
- Modular 3D-printed components

---

**Hardware:** Arduino Uno, MG996R Servos, Rotary Encoders, Voltage Sensors  
**Software:** C++, Arduino IDE, Altium Designer, Fusion 360, ROS2 (in progress)

---

**Control Overview**
![System Diagram](images/wiring_layout.png)

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

**Gallery**
| Assembly | Electronics | Testing |
|-----------|-------------|---------|
| ![Arm](images/arm_photo1.jpg) | ![PCB](images/wiring_layout.png) | ![Testing](images/oscilloscope_feedback.png) |

---

**Author**
**Tenzin Lobsang Phelgyal**  
Computer Engineering Student – Robotics & Embedded Systems  
[LinkedIn](https://linkedin.com/in/tenlobphelgyal)
