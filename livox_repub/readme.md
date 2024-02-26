官方livox_driver驱动livox雷达发出的点云topic有两种，一种是大疆览沃定制的格式CustomMsg格式，另一种是将CustomMsg格式
转换过的pointcloud2格式，参见
Livox雷达驱动程序发布点云格式CustomMsg、PointCloud2、pcl::PointXYZI、pcl::PointXYZINormal解析
现在将转换这部分的代码提取出来，方便 随时使用

1. 创建ros功能包
   mkdir -p livox_repub/src
   cd livox_repub/src
   catkin_init_workspace
   cd ..
   catkin_make
2. livox_repub.cpp
   cd src
   mkdir livox_repub
   cd livox_repub
   vi package.xml

vi CMakeLists.txt

vi livox_repub.cpp

3. 编译运行
   cd ../../
   catkin_make
   source devel/setup.bash
   roslaunch livox_repub livox_repub.launch
   注意：这个包是要先订阅CustomMsg的话题/livox/lidar，然后发布PointCloud2格式的"/livox_pcl0"
   话题，所以不论是实时驱动livox-driver还是通过bag包发布/livox/lidar，都需要确保有/livox/lidar才能有转换结果
   转换后的PointCloud2点云可以通过rviz显示，终端输
   rviz
   Fixed Frame设置为livox，点云设置为/livox_pcl0
   /home/geely/图片/2022-07-25 16-19-37 的屏幕截图.png
   ros graph
   /home/geely/图片/rosgraph.png

