#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/point_cloud2.hpp>
#include <livox_ros_driver2/msg/custom_msg.hpp>
#include <tf2_ros/transform_broadcaster.h>
#include <pcl/point_types.h>
#include <pcl_conversions/pcl_conversions.h>

// Point type definition (assuming PointXYZINormal is preferred)
typedef pcl::PointXYZINormal PointType;

class LivoxRepub : public rclcpp::Node {
public:
    LivoxRepub() : Node("livox_repub") {
        // Initialize subscriber and publisher
        sub_livox_msg_ = create_subscription<livox_ros_driver2::msg::CustomMsg>(
                "/livox/lidar", 10,
                std::bind(&LivoxRepub::LivoxMsgCbk, this, std::placeholders::_1));
        pub_pcl_out_ = create_publisher<sensor_msgs::msg::PointCloud2>(
                "/livox_pcl", 10);

        // Initialize transform broadcaster
        broadcaster_ = std::make_shared<tf2_ros::TransformBroadcaster>(*this);
    }

private:
    rclcpp::Time get_ros_time(double timestamp) {
        int32_t sec = std::floor(timestamp);
        auto nanosec_d = (timestamp - std::floor(timestamp)) * 1e9;
        uint32_t nanosec = nanosec_d;
        return rclcpp::Time(sec, nanosec);
    }

    void LivoxMsgCbk(const livox_ros_driver2::msg::CustomMsg::SharedPtr livox_msg) {
        RCLCPP_INFO_ONCE(this->get_logger(), "Received first LiDAR message");
        // Collect all LiDAR scans for merging (if applicable)
        // ... (replace with appropriate merging logic if needed)

        // Create an empty PointCloud
        pcl::PointCloud<PointType>::Ptr pcl_in(new pcl::PointCloud<PointType>());

        // Process each LiDAR scan
        for (unsigned int i = 0; i < livox_msg->point_num; ++i) {
            PointType pt;
            pt.x = livox_msg->points[i].x;
            pt.y = livox_msg->points[i].y;
            pt.z = livox_msg->points[i].z;

            // Calculate intensity combining line number and reflectivity
            float s = livox_msg->points[i].offset_time / (float) livox_msg->points.back().offset_time;
            pt.intensity = livox_msg->points[i].line + livox_msg->points[i].reflectivity / 10000.0;

            // Calculate curvature (adjust calculation as needed)
            pt.curvature = s * 0.1;

            pcl_in->push_back(pt);
        }

        // Convert PointCloud to ROS message
        sensor_msgs::msg::PointCloud2 pcl_ros_msg;
        pcl::toROSMsg(*pcl_in, pcl_ros_msg);

        // Set timestamp based on LiDAR message
        //pcl_ros_msg.header.stamp = get_ros_time(livox_msg->timebase);
        pcl_ros_msg.header.stamp = this->get_clock()->now();

        // Set frame_id (adjust if needed)
        pcl_ros_msg.header.frame_id = livox_msg->header.frame_id;

        // Publish the converted PointCloud
        pub_pcl_out_->publish(pcl_ros_msg);

        // Optionally, broadcast a TF transform (replace with appropriate logic)
        // ...
    }

    rclcpp::Subscription<livox_ros_driver2::msg::CustomMsg>::SharedPtr sub_livox_msg_;
    rclcpp::Publisher<sensor_msgs::msg::PointCloud2>::SharedPtr pub_pcl_out_;
    std::shared_ptr<tf2_ros::TransformBroadcaster> broadcaster_;
};

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<LivoxRepub>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}