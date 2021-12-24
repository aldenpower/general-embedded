// #include <HCSR04.h> // substituir por newping
#include <ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Float64.h>
#include <std_msgs/Int64.h>
#include <Arduino.h>
#include <geometry_msgs/Twist.h>

//------------------------ DECLARE PINS ---------------------------------------------------
//LEFT MOTOR
#define ena_pin 3 
#define in1_pin 4 
#define in2_pin 5 
//RIGHT MOTOR
// #define enb_pin 3 
// #define in3_pin 4 
// #define in4_pin 5 
//------------------------ DECLARE FUNCTIONS ----------------------------------------------
void MotorTest(int Pulse_Width1, int pwmpin);
void motors_init();
void messageCb( const geometry_msgs::Twist& msg);
//------------------------ VARIABLES ------------------------------------------------------
//MAX BLACKDIFF VEL IN m/s
double max_speed = 3;
double left_speed = 0, right_speed = 0;
double left_speed_percent = 0, right_speed_percent = 0;
//RADIUS AND SEPARATION WHEELS
double wheel_rad = 0.034, wheel_sep = 0.17; 
double speed_ang = 0, speed_lin = 0;
const long PERIODO = 500;
unsigned long tempoAnterior = 0;
//------------------------ ROS VARIABLES ------------------------------------------------------
ros::NodeHandle nh;
// std_msgs::Float64 distancia;
std_msgs::Int64 left; // PODE SER INTEIRO
std_msgs::Int64 right;
//------------------------ PUBLISHERS ------------------------------------------------------
// ros::Publisher pub_dist("distancia", &distancia);
ros::Publisher pub_left("left", &left);
ros::Publisher pub_right("right", &right);
//------------------------ SUBSCRIBER ------------------------------------------------------
ros::Subscriber<geometry_msgs::Twist> sub("cmd_vel", &messageCb );
//------------------------ CALLBACK ------------------------------------------------------
void messageCb( const geometry_msgs::Twist& msg){
  speed_lin = msg.linear.x;
  speed_ang = msg.angular.z;

  left_speed = speed_lin - (speed_ang * wheel_sep / 2);
  right_speed = speed_lin + (speed_ang * wheel_sep / 2);

  left_speed_percent = 100 * left_speed / max_speed;
  right_speed_percent = 100 * right_speed / max_speed;
}

void setup () {
    Serial.begin(9600);
    motors_init();
    nh.initNode();
    // nh.advertise(pub_dist);
    nh.advertise(pub_left);
    nh.advertise(pub_right);
    nh.subscribe(sub);
}

void loop () {
    MotorTest(left_speed_percent / 100, ena_pin);
    
    nh.spinOnce();
}


// FUNCTIONS

void motors_init(){
    // LEFT MOTOR
    pinMode(in1_pin, OUTPUT);
    pinMode(in2_pin, OUTPUT);
    pinMode(ena_pin, OUTPUT);

    digitalWrite(in1_pin, HIGH);
    digitalWrite(in2_pin, LOW);

}

void MotorTest(int percent, int pwmpin)
{
  analogWrite(pwmpin, percent * 255);
}