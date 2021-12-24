#include <HCSR04.h> // substituir por newping
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
#define enb_pin 3 
#define in3_pin 4 
#define in4_pin 5 
//------------------------ DECLARE FUNCTIONS ----------------------------------------------
void Motor(int Pulse_Width1, int motorPinInput1, int motorPinInput2);
void MotorTest(int Pulse_Width1, int pwmpin);
void motors_init();
void messageCb( const geometry_msgs::Twist& msg);
//------------------------ VARIABLES ------------------------------------------------------
double w_r = 0, w_l = 0;
//RADIUS AND SEPARATION WHEELS
double wheel_rad = 0.07/5, wheel_sep = 0.17; 
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
  speed_lin = msg.linear.x * 80;
  speed_ang = msg.angular.z * 80;

  w_r = (speed_lin / wheel_rad) + ((speed_ang * wheel_sep)/(2.0 * wheel_rad));
  w_l = (speed_lin / wheel_rad) - ((speed_ang * wheel_sep)/(2.0 * wheel_rad));
}

// UltraSonicDistanceSensor distanceSensor(4, 2);

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
    // unsigned long tempoAtual = millis();
    // if (tempoAtual - tempoAnterior >= PERIODO) {
    //   tempoAnterior = tempoAtual;
    //   distancia.data = distanceSensor.measureDistanceCm();
    //   pub_dist.publish(&distancia);
    // } 
    
    if (abs(w_l) < 15)
    {
        w_l = 0;
    }
    if (abs(w_r)<15)
    {
        w_r = 0;
    }
    if (w_l>25) // Consertar o sinal, para contemplar os valores negativos.
    {
        w_l = 25;    
    }
    if (w_r>25)
    {
        w_r = 25;    
    }
    if (w_l<-25) // Consertar o sinal, para contemplar os valores negativos.
    {
        w_l = -25;    
    }
    if (w_r<-25)
    {
        w_r = -25;    
    }

    // Motor(w_l * 10, in1_pin, in2_pin);
    // Motor(w_r * 10, RIGHT_MOTOR_PWM_PIN_1, RIGHT_MOTOR_PWM_PIN_2);
    MotorTest(w_r * 10, ena_pin);
    
    // left.data = (w_l * 10 / 250) * 5;
    // right.data = (w_r * 10 / 250) * 5;

    // pub_left.publish(&left);
    // pub_right.publish(&right);
    
    nh.spinOnce();
    
    // Every 500 miliseconds, do a measurement using the sensor and print the distance in centimeters.
    //Serial.println(distanceSensor.measureDistanceCm());
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

void MotorTest(int Pulse_Width1, int pwmpin){
 if (Pulse_Width1 > 0){
    analogWrite(pwmpin, 255);
 }
 else
 {
    analogWrite(pwmpin, 0);
 }
 
 
}


void Motor(int Pulse_Width1, int motorPinInput1, int motorPinInput2){
 if (Pulse_Width1 > 0){
    analogWrite(motorPinInput1,Pulse_Width1);
    analogWrite(motorPinInput2,LOW);
 }
 if (Pulse_Width1 < 0){
    Pulse_Width1 = abs(Pulse_Width1);
    analogWrite(motorPinInput1,LOW);
    analogWrite(motorPinInput2,Pulse_Width1);
 }
  if (Pulse_Width1 == 0){
     digitalWrite(motorPinInput1, LOW);
     digitalWrite(motorPinInput2, LOW);
 }
}