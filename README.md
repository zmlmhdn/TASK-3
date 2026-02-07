# Project flowchart
## Simulation (Cartographer mapping)

1. Launching Gazebo

   $ export TURTLEBOT3_MODEL=waffle
   $ ros2 launch turtlebot3_gazebo turtlebot3_world.launch.py

2. Teleop for movement of the robot in simulation
   
   $ ros2 run turtlebot3_teleop teleop_keyboard

3. Mapping in Cartographer

   $ ros2 launch turtlebot3_cartographer cartographer.launch.py use_sim_time:=True

4. Teleop twist keyboard

   $ ros2 run turtlebot3_teleop teleop_keyboard

5. Drive the robot inside simulation, mapping the environment

6. Save the map

   $ ros2 run nav2_map_server map_saver_cli -f ~/sim_map

## Builing packages inside the custom robot

Before mapping, the custom robot model was chosen. Instead of Turtlebot3, the custom robot was the Bveeta Mini model. Hence, relevant packages must be installed first. The project flowchart is as follows:

1. Installing Ubuntu and ROS2 (Humble), and necessary packages needed for the ROS into the Pi.

2. SSH connection into robot
   - After the robot is turned on, the laptop is connected using ssh connection into the Pi

   $ ssh ubuntu@<robot ip address> = $ ssh ubuntu@

3. Creating the package inside the Pi

   $ mkdir -p ~/robot_ws2/src
   $ cd ~/robot_ws2
   $ ros2 pkg create --build-type ament_python serial_motor_controller --dependencies rclpy geometry_msgs
   
4. Installing pyserial

   $ cd ~/robot_ws
   $ sudo apt install python3-serial
   
5. Creating the python serial bridge script

   $ cd ~/robot_ws/src/serial_motor_controller/serial_motor_controller
   $ nano serial_bridge.py

   - The coding of the serial_bridge.py was uploaded above.

6. Updating setup,py file

   $ cd ~/robot_ws/src/serial_motor_controller
   $ nano setup.py

   - The coding of the setup.py was uploaded above.

7. Building the package and sourcing it

   $ cd ~/robot_ws2
   $ source /opt/ros/humble/setup.bash
   $ colcon build --symlink-install
   $ source install/setup.bash

8. Uploading the Arduino code into Pi (the code file is uploaded above)

9. Connecting Arduino cable to Pi

## Mapping using the custom robot (Real environment)

1. Inside the robot terminal 1, run the serial_motor_controller
   
   $ cd ~/robot_ws2
   $ source install/setup.bash
   $ ros2 run serial_motor_controller serial_bridge

2. In robot terminal 2, run the teleop inside the same file as terminal 1 (/robot_ws2)

   $ ros2 run teleop_twist_keyboard teleop_twist_keyboard

## Problems encountered in this Task


