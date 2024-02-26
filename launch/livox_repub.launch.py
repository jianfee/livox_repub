from launch import LaunchDescription
from launch_ros.actions import Node


def generate_launch_description():
    return LaunchDescription([
        Node(
            package='livox_repub',
            executable='livox_repub',
            name='livox_repub',
            output='screen',
            remappings=[
                ('/livox/lidar', '/livox/lidar'),
            ],
        ),
    ])
