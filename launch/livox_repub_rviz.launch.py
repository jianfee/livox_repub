from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import ThisLaunchFileDir, Command
from launch_ros.actions import Node


def generate_launch_description():
    return LaunchDescription([
        # 包含另一个launch文件
        IncludeLaunchDescription(
            PythonLaunchDescriptionSource([ThisLaunchFileDir(), '/livox_repub.launch.py'])
        ),

        # 启动RViz节点
        Node(
            package='rviz2',  # 注意在ROS2中，rviz的包名变为了rviz2
            executable='rviz2',  # 在ROS2中，执行文件名称变为了rviz2
            name='rviz',
            arguments=['-d', Command(['find', 'livox_repub', '/launch/livox_repub.rviz'])],
        ),
    ])
