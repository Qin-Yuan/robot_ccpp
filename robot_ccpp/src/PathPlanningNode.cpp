#include "CleaningPathPlanner.h"
#include <boost/shared_ptr.hpp>
#include "nav2_costmap_2d/costmap_2d_ros.hpp"

namespace cm = nav2_costmap_2d;
namespace rm = geometry_msgs::msg;

using std::vector;
using rm::PoseStamped;
using std::string;
using cm::Costmap2D;
using cm::Costmap2DROS;


int main(int argc, char** argv) {
    rclcpp::init(argc, argv) ;
    nav2_costmap_2d::Costmap2DROS lcr("cleaning_costmap");
    rclcpp::sleep_for(std::chrono::seconds(5));

    auto clr_node = std::make_shared<CleaningPathPlanning>(&lcr);
    
    RCLCPP_INFO(clr_node->get_logger(),"Process") ;

    tf2_ros::Buffer tf(clr_node->get_clock()) ;
    tf2_ros::TransformListener tf2_listener(tf) ;
    
    clr_node->GetPathInROS() ;
    //clr_node.GetBorderTrackingPathInROS() ;   
    rclcpp::Rate rate(1) ;  // 1 Hz
    while(rclcpp::ok()) {
        RCLCPP_INFO(clr_node->get_logger(),"Process") ;
        clr_node->PublishCoveragePath();
        rclcpp::spin_some(clr_node) ;
        rate.sleep() ;
    }
    rclcpp::shutdown() ;   
    return 0 ;
}

