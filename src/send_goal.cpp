    #include <ros/ros.h>  
    #include <move_base_msgs/MoveBaseAction.h>  
    #include <actionlib/client/simple_action_client.h>  
    #include "geometry_msgs/PoseWithCovarianceStamped.h"    
    #include "std_msgs/String.h"
    #include <sstream> 

    typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;  
      typedef struct _POSE
{
  double X;
  double Y;
  double Z;
  double or_x;
  double or_y;
  double or_z;
  double or_w;
} POSE;

  void setHome( ros::Publisher pub,POSE pose)
{
    geometry_msgs::PoseWithCovarianceStamped msg_poseinit;
    msg_poseinit.header.frame_id = "map";
    msg_poseinit.header.stamp = ros::Time::now();
  /*  nh.param<double>("amcl_pose_position.x", msg_poseinit.pose.pose.position.x,1.959);
    nh.param<double>("amcl_pose_position.y", msg_poseinit.pose.pose.position.y,3.170);
    nh.param<double>("amcl_pose_position.z", msg_poseinit.pose.pose.position.z,0);
    nh.param<double>("amcl_pose_orientation.x", msg_poseinit.pose.pose.orientation.x,0.0);
    nh.param<double>("amcl_pose_orientation.y", msg_poseinit.pose.pose.orientation.y,0.0);
    nh.param<double>("amcl_pose_orientation.z", msg_poseinit.pose.pose.orientation.z,0.961);
    nh.param<double>("amcl_pose_orientation.w", msg_poseinit.pose.pose.orientation.w,-0.278); */
    msg_poseinit.pose.pose.position.x = pose.X;
    msg_poseinit.pose.pose.position.y = pose.Y;
    msg_poseinit.pose.pose.position.z = pose.Z;
    msg_poseinit.pose.pose.orientation.x = pose.or_x;
    msg_poseinit.pose.pose.orientation.y = pose.or_y;
    msg_poseinit.pose.pose.orientation.z = pose.or_z;
    msg_poseinit.pose.pose.orientation.w = pose.or_w;
//因为ros话题原理本身的问题，Setting pose 需要按照以下发送
    pub.publish(msg_poseinit);
    ros::Duration(1.0).sleep();
    pub.publish(msg_poseinit);
    ros::Duration(1.0).sleep();
    pub.publish(msg_poseinit);
    ros::Duration(1.0).sleep();
}


    int main(int argc, char** argv){  
      ros::init(argc, argv, "simple_navigation_goals");
      ros::NodeHandle nh;
      ros::Publisher pub_initialpose = nh.advertise<geometry_msgs::PoseWithCovarianceStamped>("/initialpose", 10);
      ros::Publisher xfer_pub = nh.advertise<std_msgs::String>("xfwords", 1);
    
      //tell the action client that we want to spin a thread by default  
      MoveBaseClient ac("move_base", true);  
      
      //wait for the action server to come up  
      while(!ac.waitForServer(ros::Duration(5.0))){  
        ROS_INFO("Waiting for the move_base action server to come up");  
      }  
     // POSE pose_AMCL = {0.0, 0.0, 0.0,  0.0, 0.0, 0.0, 0.0};

      double AMCL_Point_x,AMCL_Point_y,AMCL_Point_z,AMCL_orientation_x,
      AMCL_orientation_y,AMCL_orientation_z,AMCL_orientation_w; 
    // nh.param<double>("~AMCL_Point_x", AMCL_Point_x, 2.0);
    // nh.param<double>("~AMCL_Point_y", AMCL_Point_y, 2.25);
    // nh.param<double>("AMCL_Point_z", AMCL_Point_z, 0.0);
     //nh.param<double>("AMCL_orientation_x", AMCL_orientation_x, 0.0);
     //nh.param<double>("AMCL_orientation_y", AMCL_orientation_y, 0.0);
     //nh.param<double>("AMCL_orientation_z", AMCL_orientation_z, 2.5);
     //nh.param<double>("AMCL_orientation_w", AMCL_orientation_w, 2.5); 

     ros::param::get("~AMCL_Point_x",AMCL_Point_x);
     ros::param::get("~AMCL_Point_y",AMCL_Point_y);
     ros::param::get("~AMCL_Point_z",AMCL_Point_z);
     ros::param::get("~AMCL_orientation_x",AMCL_orientation_x);
     ros::param::get("~AMCL_orientation_y",AMCL_orientation_y);
     ros::param::get("~AMCL_orientation_z",AMCL_orientation_z);
     ros::param::get("~AMCL_orientation_w",AMCL_orientation_w);
     POSE pose_AMCL = {AMCL_Point_x,AMCL_Point_y, AMCL_Point_z,  AMCL_orientation_x,
     AMCL_orientation_y,AMCL_orientation_z, AMCL_orientation_w
     }; 

  //    setHome(pub_initialpose,pose_AMCL);


      POSE pose_GOAL_1,pose_GOAL_2,pose_GOAL_3;
     /* nh.param<double>("GOAL_1_Point_x", pose_GOAL_1.X, 0.0);
      nh.param<double>("GOAL_1_Point_y", pose_GOAL_1.Y, 0.0);
      nh.param<double>("GOAL_1_Point_z", pose_GOAL_1.Z, 0.0);
      nh.param<double>("GOAL_1_orientation_x", pose_GOAL_1.or_x, 0.0);
      nh.param<double>("GOAL_1_orientation_y", pose_GOAL_1.or_y, 0.0);
      nh.param<double>("GOAL_1_orientation_z", pose_GOAL_1.or_z, 2.5);
      nh.param<double>("GOAL_1_orientation_w", pose_GOAL_1.or_w, 2.5);
       
      nh.param<double>("GOAL_2_Point_x", pose_GOAL_2.X, 0.48);
      nh.param<double>("GOAL_2_Point_y", pose_GOAL_2.Y, 4.348);
      nh.param<double>("GOAL_2_Point_z", pose_GOAL_2.Z, 0.0);
      nh.param<double>("GOAL_2_orientation_x", pose_GOAL_2.or_x, 0.0);
      nh.param<double>("GOAL_2_orientation_y", pose_GOAL_2.or_y, 0.0);
      nh.param<double>("GOAL_2_orientation_z", pose_GOAL_2.or_z, 1.0);
      nh.param<double>("GOAL_2_orientation_w", pose_GOAL_2.or_w, 0.02);  */

     ros::param::get("~GOAL_1_Point_x",pose_GOAL_1.X);
     ros::param::get("~GOAL_1_Point_y",pose_GOAL_1.Y);
     ros::param::get("~GOAL_1_Point_z",pose_GOAL_1.Z);
     ros::param::get("~GOAL_1_orientation_x",pose_GOAL_1.or_x);
     ros::param::get("~GOAL_1_orientation_y",pose_GOAL_1.or_y);
     ros::param::get("~GOAL_1_orientation_z",pose_GOAL_1.or_z);
     ros::param::get("~GOAL_1_orientation_w",pose_GOAL_1.or_w);

     ros::param::get("~GOAL_2_Point_x",pose_GOAL_2.X);
     ros::param::get("~GOAL_2_Point_y",pose_GOAL_2.Y);
     ros::param::get("~GOAL_2_Point_z",pose_GOAL_2.Z);
     ros::param::get("~GOAL_2_orientation_x",pose_GOAL_2.or_x);
     ros::param::get("~GOAL_2_orientation_y",pose_GOAL_2.or_y);
     ros::param::get("~GOAL_2_orientation_z",pose_GOAL_2.or_z);
     ros::param::get("~GOAL_2_orientation_w",pose_GOAL_2.or_w);


      move_base_msgs::MoveBaseGoal goal;  
      
      //we'll send a goal to the robot to move 1 meter forward  
      goal.target_pose.header.frame_id = "map";  
      goal.target_pose.header.stamp = ros::Time::now();  
      
     // goal.target_pose.pose.position.x = 1.0;  
      //goal.target_pose.pose.orientation.w = 1.0;  

      goal.target_pose.pose.position.x = pose_GOAL_1.X;
      goal.target_pose.pose.position.y = pose_GOAL_1.Y;
      goal.target_pose.pose.position.z = pose_GOAL_1.Z;
      goal.target_pose.pose.orientation.x = pose_GOAL_1.or_x;
      goal.target_pose.pose.orientation.y = pose_GOAL_1.or_y;
      goal.target_pose.pose.orientation.z = pose_GOAL_1.or_z;
      goal.target_pose.pose.orientation.w = pose_GOAL_1.or_w;
      ROS_INFO("Sending goal");  
      ac.sendGoal(goal);  
      
      ac.waitForResult(); 
   
      
      if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)  
      {  ROS_INFO("Hooray, the base moved 1 meter forward");  


    std_msgs::String msg,msg2;  
    std::stringstream ss;  
    std::stringstream ss2;  
    ss << "到达目的地，正在去往下一目的地";  
    ss2 << "到达目的地,导航结束";  
    msg.data = ss.str(); 
    msg2.data = ss2.str(); 
    ROS_INFO("%s", msg.data.c_str());  
    xfer_pub.publish(msg);  
  
    ros::spinOnce();
      goal.target_pose.pose.position.x = pose_GOAL_2.X;
      goal.target_pose.pose.position.y = pose_GOAL_2.Y;
      goal.target_pose.pose.position.z = pose_GOAL_2.Z;
      goal.target_pose.pose.orientation.x = pose_GOAL_2.or_x;
      goal.target_pose.pose.orientation.y = pose_GOAL_2.or_y;
      goal.target_pose.pose.orientation.z = pose_GOAL_2.or_z;
      goal.target_pose.pose.orientation.w = pose_GOAL_2.or_w;
      ROS_INFO("Sending goal 2");   
  
    ros::spinOnce();
      ac.sendGoal(goal);  
      
      ac.waitForResult();  

 
        if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)  
        {
        ROS_INFO("Hooray, the base moved 2 meter forward"); 
        xfer_pub.publish(msg2);
        ros::spinOnce();
        }
        else  
        ROS_INFO("The base failed to move forward 1 meter for some reason");  
        }
      else  
        ROS_INFO("The base failed to move forward 1 meter for some reason");  
      
      return 0;  
    }  
