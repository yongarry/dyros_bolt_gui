#ifndef dyros_gui__RqtDyrosPlugin_H
#define dyros_gui__RqtDyrosPlugin_H

#include <rqt_gui_cpp/plugin.h>
#include <dyros_bolt_gui/ui_dyros_gui.h>
#include <QWidget>
#include <QKeyEvent>
#include <std_msgs/Float64.h>
#include <std_msgs/Bool.h>
#include <std_msgs/Int16.h>
#include <std_msgs/Int16MultiArray.h>
#include <sensor_msgs/JointState.h>
#include <dyros_bolt_msgs/JointCommand.h>
#include <dyros_bolt_msgs/CustomCommand.h>
#include <iostream>
#include <ros/ros.h>

namespace dyros_gui {

class RqtDyrosPlugin
    : public rqt_gui_cpp::Plugin
{
    Q_OBJECT
public:
    RqtDyrosPlugin();
    virtual void initPlugin(qt_gui_cpp::PluginContext& context);
    virtual void shutdownPlugin();
    virtual void saveSettings(qt_gui_cpp::Settings& plugin_settings, qt_gui_cpp::Settings& instance_settings) const;
    virtual void restoreSettings(const qt_gui_cpp::Settings& plugin_settings, const qt_gui_cpp::Settings& instance_settings);

    ros::Publisher axis_state_pub;
    ros::Publisher joint_ctrl_pub;
    ros::Publisher custom_ctrl_pub;

    ros::Subscriber axis_current_state_sub;
    ros::Subscriber joint_state_sub;
    
    std_msgs::Int16 axis_state_msgs;
    dyros_bolt_msgs::JointCommand joint_cmd_msgs;
    dyros_bolt_msgs::CustomCommand custom_cmd_msgs;

    const char* jointName[8] = {"FL_HAA", "FL_HFE", "FL_KFE", "FL_ANKLE", "FR_HAA", "FR_HFE", "FR_KFE", "FR_ANKLE"};

    void send_joint_ctrl(int id, double q_);
    void jointStateCallback(const sensor_msgs::JointStateConstPtr &msg);
    void axisStateCallback(const std_msgs::Int16MultiArrayConstPtr &msg);

protected slots:
    virtual void motorcalibutton();
    virtual void encodercalibutton();
    virtual void clbutton();
    virtual void idlebutton();
    virtual void estopbutton();
    virtual void rebootbutton();
    virtual void encoderbutton();
    virtual void jointCommandClicked();
    virtual void ccCmdbutton();
    virtual void gravCmdbutton();
    // virtual void tqbutton1();
    // virtual void tqbutton2();
    // virtual void tqbutton3();
    // virtual void tqbutton4();
    // virtual void tqbutton5();
    // virtual void tqbutton6();

signals:

private:
    Ui::DyrosGui ui_;
    QWidget* widget_;
    std::vector<QLabel*> jointStates;
};
}

#endif // my_namespace__my_plugin_H