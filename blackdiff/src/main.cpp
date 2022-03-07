#include <NewPing.h>
#include <ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Float64.h>
#include <std_msgs/Int64.h>
#include <Arduino.h>
#include <geometry_msgs/Twist.h>

//------------------------ DECLARE PINS ---------------------------------------------------
//RIGHT MOTOR
#define ena_pin 5 
#define in1_pin 9 
#define in2_pin 8 
//LEFT MOTOR
#define enb_pin 6 
#define in3_pin 4 
#define in4_pin 3
// SONAR SENSOR
#define trigger  2
#define echo  7
//Declare functions
void MotorTest(float percent1, float percent2, int pwmpin1, int pwmpin2);
void motors_init();
void messageCb( const geometry_msgs::Twist& msg);
//Variables and objects
double max_speed = 0.47;
double left_speed = 0, right_speed = 0;
double left_speed_percent = 0, right_speed_percent = 0;
//RADIUS AND SEPARATION WHEELS
double wheel_rad = 0.034, wheel_sep = 0.156; 
double speed_ang = 0, speed_lin = 0;
int max_distance = 500;
NewPing Sonar(trigger, echo, max_distance);
//ROS objects
ros::NodeHandle nh;
std_msgs::Float64 distance;
std_msgs::Int64 left;
std_msgs::Int64 right;
//Publisher
ros::Publisher pub_dist("distance", &distance);
ros::Publisher pub_left("left", &left);
ros::Publisher pub_right("right", &right);
//SUbscribers
ros::Subscriber<geometry_msgs::Twist> sub("cmd_vel", &messageCb );
//Callback
void messageCb( const geometry_msgs::Twist& msg){
  speed_lin = msg.linear.x;
  speed_ang = msg.angular.z;

  left_speed = speed_lin - (speed_ang * wheel_sep / 2);
  right_speed = speed_lin + (speed_ang * wheel_sep / 2);

  left_speed_percent = left_speed / max_speed;
  right_speed_percent = right_speed / max_speed;
}

void setup () {
    Serial.begin(9600);

    motors_init();
    nh.initNode();
    nh.advertise(pub_dist);
    nh.advertise(pub_left);
    nh.advertise(pub_right);
    nh.subscribe(sub);
}

void loop () {
    MotorTest(left_speed_percent, right_speed_percent, ena_pin, enb_pin);

    distance.data = Sonar.ping_cm();
    pub_dist.publish(&distance);

    nh.spinOnce();
}


//Functions

void motors_init(){
    // LEFT MOTOR
    pinMode(ena_pin, OUTPUT);
    pinMode(in1_pin, OUTPUT);
    pinMode(in2_pin, OUTPUT);

    pinMode(enb_pin, OUTPUT);
    pinMode(in3_pin, OUTPUT);
    pinMode(in4_pin, OUTPUT);

    digitalWrite(in1_pin, HIGH);
    digitalWrite(in2_pin, LOW);

    digitalWrite(in3_pin, HIGH);
    digitalWrite(in4_pin, LOW);

}

void MotorTest(float percent1, float percent2, int pwmpin1, int pwmpin2)
{
  if (speed_lin > 0)
  {
    digitalWrite(in1_pin, HIGH);
    digitalWrite(in2_pin, LOW);

    digitalWrite(in3_pin, HIGH);
    digitalWrite(in4_pin, LOW);

    analogWrite(pwmpin1, percent1 * 200);
    analogWrite(pwmpin2, percent2 * 200);
    /* code */
  }
  if (speed_lin < 0)
  {
    digitalWrite(in1_pin, LOW);
    digitalWrite(in2_pin, HIGH);

    digitalWrite(in3_pin, LOW);
    digitalWrite(in4_pin, HIGH);

    analogWrite(pwmpin1, round(abs(percent1) * 200));
    analogWrite(pwmpin2, round(abs(percent2) * 200));
  }
}