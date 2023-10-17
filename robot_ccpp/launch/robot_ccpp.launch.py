import os
import yaml
from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node
from launch.actions import IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource



def generate_launch_description():
    use_sim_time = LaunchConfiguration('use_sim_time', default=True)

    param_file_name = 'robot_ccpp.yaml'
    param_dir = LaunchConfiguration(
        'params_file',
        default=os.path.join(
            get_package_share_directory('robot_ccpp'),
            'config'))    
    
    # 全覆盖路径规划算法
    path_planning_node = Node(package='robot_ccpp',
                            executable='path_planning_node',
                            parameters=[{'use_sim_time': use_sim_time}],
                            arguments=['-configuration_directory', param_dir,
                                        '-configuration_basename', param_file_name],
                            output = 'screen'
                            )
    
    return LaunchDescription([
        DeclareLaunchArgument(
            'use_sim_time',
            default_value='true',
            description='Use simulation (Gazebo) clock if true'),

        DeclareLaunchArgument(
            'params_file',
            default_value=param_dir,
            description='Full path to param file to load'),
        
        # voxel_visualizer_node,
        path_planning_node,
    ])
