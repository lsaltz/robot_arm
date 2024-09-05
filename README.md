# robot_arm
[Junior Design Webpage](https://eecs.engineering.oregonstate.edu/project-showcase/projects/?id=5xJAjyhgneRR1Nk8)

## Project Goals
- The system must draw with a speed of at least 4 inches per second.
Status: Met
- The system must draw a 10 inch straight line  +/- .25 inches in each direction.
Status: Unmet
- The robotic arm will use a SCARA topology, with two rotating joints to control arm actuation.
Status: Met
- Controlling commands will be input as G-code commands. These commands must be available within the Python or MATLAB GUI: G0, G1, G90, G91, G20, G21, M2, M6, M72.
Status: Met
- Upon receiving an M6 command the machine operator must mount a crayon, pen, or pencil within 15 seconds.
Status: Met
- The system must accept an image and replicate it so it is identifiable by 9 out of 10 individuals.
Status: Unmet


## Responsibilities
Marshall Saltz:
 - Design and print robot arm body
 - Arduino code
   - GUI communication
   - Motor controls
   - Matlab simulation verification
   - G-Code command execution

     
Chandler Donahey:
 - Voltage regulator PCB design, ordering, and assembly
 - Electrical design


Reuben De Souza:
 - GUI interface
 - Image processing for replication

## Notes
After completing the majority of the requirements for Junior Design, I assumed the task of implementing the remainder of the requirements in my free time. This involves adjusting the GUI interface and image processing code as well as the arduino code.

## TODO
- Image replication
- Straight line
