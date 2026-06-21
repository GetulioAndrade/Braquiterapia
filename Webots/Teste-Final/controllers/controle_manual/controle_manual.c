#include <stdio.h>
#include <stdlib.h>
#include <webots/robot.h>
#include <webots/motor.h>
#include <webots/keyboard.h>
#include <webots/led.h>
#include <webots/distance_sensor.h>

#define TIME_STEP 48

WbDeviceTag MTD, MTE, led, s1, s2, s3, s4, s5;
float d, la1=0, la2=0, la3=0, la4=0, la5=0;

int main() 
{
  wb_robot_init();

  wb_robot_step(TIME_STEP);

  MTD = wb_robot_get_device("roda_direita");
  MTE = wb_robot_get_device("roda_esquerda");
  wb_motor_set_position(MTD, INFINITY);
  wb_motor_set_position(MTE, INFINITY);
  wb_motor_set_velocity(MTD, 0.0);
  wb_motor_set_velocity(MTE, 0.0);
  
  s1 = wb_robot_get_device("seguidor_de_linha1");
  s2 = wb_robot_get_device("seguidor_de_linha2");
  s3 = wb_robot_get_device("seguidor_de_linha3");
  s4 = wb_robot_get_device("seguidor_de_linha4");
  s5 = wb_robot_get_device("seguidor_de_linha5");
  
  wb_distance_sensor_enable(s1, TIME_STEP);
  wb_distance_sensor_enable(s2, TIME_STEP);
  wb_distance_sensor_enable(s3, TIME_STEP);
  wb_distance_sensor_enable(s4, TIME_STEP);
  wb_distance_sensor_enable(s5, TIME_STEP);

  wb_keyboard_enable(TIME_STEP);
  
  led = wb_robot_get_device("LED");

  int ledcolor;

  while (wb_robot_step(TIME_STEP) != -1) 
  {
    int comando = wb_keyboard_get_key();

    if ((ledcolor % 3) == 0)
    {
      wb_led_set(led, 1);
    } else
    {
      if ((ledcolor % 2) == 0)
      {
        wb_led_set(led, 2);
      } else
      {
        wb_led_set(led, 3);
      }      
    }
    ledcolor++;
    

    switch (comando)
    {
    case 315:
      //frente
      wb_motor_set_position(MTD, INFINITY);
      wb_motor_set_position(MTE, INFINITY);
      wb_motor_set_velocity(MTD, 10.0);
      wb_motor_set_velocity(MTE, 10.0);
    break;
    case 317:
      //tr�s
      wb_motor_set_position(MTD, INFINITY);
      wb_motor_set_position(MTE, INFINITY);
      wb_motor_set_velocity(MTD, -10.0);
      wb_motor_set_velocity(MTE, -10.0);
    break;
    case 316:
      //direita
      wb_motor_set_position(MTD, INFINITY);
      wb_motor_set_position(MTE, INFINITY);
      wb_motor_set_velocity(MTD, -10.0);
      wb_motor_set_velocity(MTE, 10.0);
    break;
    case 314:
      //esquerda
      wb_motor_set_position(MTD, INFINITY);
      wb_motor_set_position(MTE, INFINITY);
      wb_motor_set_velocity(MTD, 10.0);
      wb_motor_set_velocity(MTE, -10.0);
    break;

    default:
      //nenhuma tecla acionada
      wb_motor_set_position(MTD, INFINITY);
      wb_motor_set_position(MTE, INFINITY);
      wb_motor_set_velocity(MTD, 0.0);
      wb_motor_set_velocity(MTE, 0.0);
    break;
    }
    
    /*d = wb_distance_sensor_get_value(s1);
    if(abs(d-la1) > 0.5)
    {
      printf("\n\nS1: %.2f", d);
      la1 = d;
    }
    d = wb_distance_sensor_get_value(s2);
    if(abs(d-la2) > 0.5)
    {
      printf("\n\nS2: %.2f", d);
      la2 = d;
    }
    d = wb_distance_sensor_get_value(s3);
    if(abs(d-la3) > 0.5)
    {
      printf("\n\nS3: %.2f", d);
      la3 = d;
    }
    d = wb_distance_sensor_get_value(s4);
    if(abs(d-la4) > 0.5)
    {
      printf("\n\nS4: %.2f", d);
      la4 = d;
    }
    d = wb_distance_sensor_get_value(s5);
    if(abs(d-la5) > 0.5)
    {
      printf("\n\nS5: %.2f", d);
      la5 = d;
    }
    
    printf("\n\n%lf", wb_robot_get_time());*/
    
    
  };
    
  wb_robot_cleanup();

  return 0;
}
