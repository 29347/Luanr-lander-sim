# Lunar Lander Autopilot Simulator

A physics-based simulation of a lunar module landing on the Moon using PID-controlled autopilot, written in C++.
## Inspiration 
I saw a guy on youtube simulate an entire solar system using C++. That was the inspiration and the goal for me.

## Overview

This project simulates a spacecraft landing on the Moon using realistic physics and an automated PID (Proportional-Integral-Derivative) controller. It demonstrates fundamental concepts in aerospace engineering, control systems, and real-time simulation.

**Built for learning:**
- Gravitational physics
- PID feedback control systems
- Real-time physics simulation
- Systems engineering principles

## Features

-  **Real-time ASCII visualization** - Watch the lander descend with dynamic engine flames
-  **Physically accurate simulation** - Uses Newton's laws with lunar gravity (1.625 m/s²)
-  **PID autopilot controller** - Maintains safe descent velocity automatically
-  **Dynamic throttle control** - Variable thrust based on current state
-  **Fuel consumption modeling** - Realistic fuel burn rates
-  **Landing quality assessment** - Evaluates touchdown performance

##  Demo

```
     /\
    /  \
   | LM |  <- 45m
   |____|
    |  |
   /|  |\
  / |  | \     MAX BURN
 <  *  *  >
  \ | * | /
   \|**|/


_____________________________________________________________[ Moon Surface]
 Status Dashboard 
Time: 5.2s | Alt: 45m | Vel: -2.3 m/s | Fuel: 82% | Thr: 78%
```

## Installation & Usage

### Prerequisites
- C++ compiler with C++11 support (g++, clang++)
- Terminal/Command Prompt

### Compile & Run

```bash
# Clone the repository
git clone https://github.com/29347/Luanr-lander-sim.git
cd Luanr-lander-sim

# Compile
g++ -std=c++11 engine.cpp -o lunar_lander -pthread

# Run
./lunar_lander
```

**Windows users:** Use `g++` from MinGW or compile with Visual Studio.

##  How It Works

The autopilot engages automatically and attempts to land safely. Watch as the PID controller:
1. Monitors current descent velocity
2. Compares it to target velocity (0.5 m/s)
3. Adjusts throttle in real-time to maintain safe descent
4. Manages fuel consumption
5. Achieves soft touchdown

After landing, you'll see a mission report with your touchdown velocity and landing quality.

##  Physics Model

### Lunar Gravity
```
g_moon = 1.625 m/s² (16.6% of Earth's gravity)
```

### Force Calculations
```
F_thrust = throttle × max_thrust (0-4500 N)
F_gravity = mass × g_moon
F_net = F_thrust + F_gravity
```

### Kinematics (Euler Integration)
```
acceleration = F_net / mass
velocity = velocity + acceleration × dt
altitude = altitude + velocity × dt
```

### Initial Conditions
- **Starting altitude**: 50 meters
- **Starting velocity**: -10 m/s (descending)
- **Lander mass**: 1000 kg
- **Maximum thrust**: 4500 N
- **Fuel capacity**: 100%
- **Fuel burn rate**: 1.5% per second at full throttle

##  PID Controller

The autopilot uses a **PID (Proportional-Integral-Derivative) controller** - the same type of control system used in real spacecraft.

### Control Algorithm
```
throttle = base_hover + Kp×error + Ki×∫error×dt + Kd×(derror/dt)
```

### Tuned Parameters
- **Kp = 0.02**: Responds to current velocity error
- **Ki = 0.005**: Eliminates accumulated error over time
- **Kd = 0.2**: Dampens oscillations and prevents overshoot

### Base Hover Throttle
```
base_hover = (mass × |g_moon|) / max_thrust
           = (1000 × 1.625) / 4500
           ≈ 0.361 (36.1%)
```
This is the throttle needed to maintain constant altitude (hover).

## Landing Performance

The simulation evaluates your landing based on touchdown velocity:

| Velocity Range | Result | Status |
|----------------|--------|--------|
| > -2.0 m/s |  **Perfect Landing** | Crew safe, mission successful |
| -2.0 to -5.0 m/s |  **Rough Landing** | Survivable, minor damage |
| < -5.0 m/s |  **Crash** | Catastrophic failure |

*Real Apollo missions aimed for 1-2 m/s touchdown velocity*

## Technical Implementation

### Code Structure
- **`LanderPhysics` class**: Handles all physics calculations (forces, motion, fuel)
- **`PIDcontroller` class**: Implements autopilot control logic
- **`drawLander()` function**: Real-time ASCII visualization
- **`main()` function**: Simulation loop orchestrating everything

### Key Design Decisions
1. **Separation of concerns**: Physics engine independent from control system
2. **Time-step integration**: Simple Euler method (dt = 0.1s)
3. **Cross-platform**: Works on Windows, macOS, and Linux
4. **Real-time visualization**: Uses `std::this_thread::sleep_for()` for smooth display

## What I Learned

This project taught me:
- How PID controllers work in practice (not just theory)
- Physics simulation using numerical integration
- Real-time systems programming
- Object-oriented design for separating concerns
- The challenges faced by real spacecraft guidance systems

##  Comparison to Real Apollo Missions

### What We Got Right 
- Control theory (PID similar to Apollo's Digital Autopilot)
- Variable thrust control (like the real descent engine)
- Accurate lunar gravity
- Safe landing speed targets

### Simplifications 
- 1D vertical motion (real spacecraft: 3-axis)
- Perfect sensors (real spacecraft: noisy radar/IMU)
- Constant mass (real spacecraft: mass decreases as fuel burns)
- Terminal descent only (real missions: full powered descent from orbit)

*Despite simplifications, this captures the fundamental challenge of closed-loop descent control*

## Future Enhancements

Potential improvements:
- [ ] 2D/3D motion with horizontal velocity
- [ ] Terrain generation and obstacle avoidance
- [ ] Manual control mode for comparison
- [ ] Multiple celestial bodies (Mars, Earth, Europa)
- [ ] Advanced integration (Runge-Kutta 4th order)
- [ ] Sensor noise and communication delays
- [ ] Data logging to CSV for analysis
- [ ] Graphical UI using SFML/SDL

## 👨‍💻 Author

**Thant Kyi Thu (Alex)**
- GitHub: [@29347](https://github.com/29347)
- Project: [Lunar Lander Simulator](https://github.com/29347/Luanr-lander-sim)

---

## 💡 Why I Built This

I'm fascinated by space exploration and wanted to understand how spacecraft guidance systems work. This project combines my interests in computer science, physics, and aerospace engineering. Building this taught me the fundamentals of control systems that scale to real missions like JPL's Mars landers.

---

*"That's one small step for code, one giant leap for simulations." 🌙*

