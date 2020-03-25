#include <iostream>

#include <ros/ros.h>
#include <gazebo_msgs/ContactsState.h>
#include <geometry_msgs/Wrench.h>

gazebo_msgs::ContactsState s1,s2,s3,s4;
geometry_msgs::Wrench calforce,force1,force2,force3,force4;


void Sensor1CB(const gazebo_msgs::ContactsState::ConstPtr msg)
{
    if(msg->states.size()>0)
    {
        s1.states = msg->states;

        // Gazeboから得られるデータを格納
        force1.force.x = s1.states[0].total_wrench.force.x;
        force1.force.y = s1.states[0].total_wrench.force.y;
        force1.force.z = s1.states[0].total_wrench.force.z;
    }
    
}

void Sensor2CB(const gazebo_msgs::ContactsState::ConstPtr msg)
{
    if(msg->states.size()>0)
    {
        s2.states = msg->states;

        // Gazeboから得られるデータを格納
        force2.force.x = s2.states[0].total_wrench.force.x;
        force2.force.y = s2.states[0].total_wrench.force.y;
        force2.force.z = s2.states[0].total_wrench.force.z;
    }
}

void Sensor3CB(const gazebo_msgs::ContactsState::ConstPtr msg)
{
    if(msg->states.size()>0)
    {
        s3.states = msg->states;

        // Gazeboから得られるデータを格納
        force3.force.x = s3.states[0].total_wrench.force.x;
        force3.force.y = s3.states[0].total_wrench.force.y;
        force3.force.z = s3.states[0].total_wrench.force.z;
    }
}

void Sensor4CB(const gazebo_msgs::ContactsState::ConstPtr msg)
{
    if(msg->states.size()>0)
    {
        s4.states = msg->states;

        // Gazeboから得られるデータを格納
        force4.force.x = s4.states[0].total_wrench.force.x;
        force4.force.y = s4.states[0].total_wrench.force.y;
        force4.force.z = s4.states[0].total_wrench.force.z;
    }
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "cs_plot");
    ros::NodeHandle nh;
    
    s1.states.push_back(*(new gazebo_msgs::ContactState()));
    s2.states.push_back(*(new gazebo_msgs::ContactState()));
    s3.states.push_back(*(new gazebo_msgs::ContactState()));
    s4.states.push_back(*(new gazebo_msgs::ContactState()));

    ros::Publisher cal_pub = nh.advertise<geometry_msgs::Wrench>("cal_pub",1);
    
    // Gazeboからデータをサブスクライブ
    ros::Subscriber sensor1_sub = nh.subscribe("/hako1_state",1,Sensor1CB);
    ros::Subscriber sensor2_sub = nh.subscribe("/hako2_state",1,Sensor2CB);
    ros::Subscriber sensor3_sub = nh.subscribe("/hako3_state",1,Sensor2CB);
    ros::Subscriber sensor4_sub = nh.subscribe("/hako4_state",1,Sensor2CB);


    ros::Rate loop_rate(1000);

    while(ros::ok())
    {
        calforce.force.x = fabs(force1.force.x) + fabs(force2.force.x) + fabs(force3.force.x) + fabs(force4.force.x);
        calforce.force.y = fabs(force1.force.y) + fabs(force2.force.y) + fabs(force3.force.y) + fabs(force4.force.y);
        calforce.force.z = fabs(force1.force.z) + fabs(force2.force.z) + fabs(force3.force.z) + fabs(force4.force.z);
        cal_pub.publish(calforce);
        ros::spinOnce();
        loop_rate.sleep();
    }
}

    
