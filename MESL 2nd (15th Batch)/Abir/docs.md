# Project Line Follower Robot
This project started with a simple idea of some curious minds & a long wished dream of perfect LFR. 

But let's not rush. Let's all calm down & start from the very beginning. After all enthusiasts gather around it's time for figuring out necessary equipments.

#### What do you need to make a LFR?
- a development board (arduino, esp32 etc.)
- sensor 
- motor 
- battery
- motor driver
- wheels
- wires (^-^)

## Phase 1: Initial Prototype (7 Dec-11 Dec)
Our target was to build a minimalistic bot which do nothing but follow a simple line (that means no sharp edges, no zigzag patter, no mind wobbling track).

We decided to stick with esp32 rather than arduino (reason? its capabilities). Some notable instruments would be:
- buck converter
- boost converter
- L289N motor driver
- esp32
- 10 array sensor
- n20 motor 

### Learnings
> Q. Can vin port of esp provide 5v?

As far as we all know vin port only took input voltage to turn on esp32. While uploading code to esp, we noticed an unusual phenomena. Buck converter , motor driver & boost converter all somehow turned on. When we measured the voltage at each point, we got 5v at both point of buck converter. The motor driver started operating the motor also.

`Gist`: Vin port also supply 5v not only it takes input

> Esp32 doesnot have `analogWrite()` rather `ledcWrite()` 
## Next steps??
- a more polished circuit
- better motor & wheel
- test on real track
