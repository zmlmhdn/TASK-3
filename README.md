# Project flowchart
## Simulation (Cartographer mapping)

1. Launching Gazebo
   $ export TURTLEBOT3_MODEL=waffle
   $ ros2 launch turtlebot3_gazebo turtlebot3_world.launch.py

2. Teleop for movement of the robot in simulation
   $ ros2 run turtlebot3_teleop teleop_keyboard

4. Mapping in Cartographer
   $ ros2 launch turtlebot3_cartographer cartographer.launch.py use_sim_time:=True

5. Teleop twist keyboard
   $ ros2 run turtlebot3_teleop teleop_keyboard

6. Drive the robot inside simulation, mapping the environment
7. Save the map
   $ ros2 run nav2_map_server map_saver_cli -f ~/sim_map

## Custom robot (real environment mapping)

1. 
