#include <webots/supervisor.h>
#include <webots/robot.h>
#include <webots/distance_sensor.h>
#include <stdio.h>

#define TIME_STEP 8

//WbNodeRef wb_supervisor_node_get_from_device("");

//void wb_supervisor_field_enable_sf_tracking(WbFieldRef field, int sampling_period);

void move(WbNodeRef object, double *p0, double *p, double velocity)
{
    WbFieldRef object_translation = wb_supervisor_node_get_field(object, "translation");
    double pos[3] = {p0[0], p0[1], p0[2]};
    double k = 0.001;

    while (wb_robot_step(TIME_STEP) != -1) 
    {
        if (pos[0] < p[0])
        {
            pos[0] += (k*velocity);
        } else
        {
            pos[0] -= (k*velocity);
        }
        /*if (pos[1] < p[1])
        {
            pos[1] += (k*velocity);
        } else
        {
            pos[1] -= (k*velocity);
        }*/
        if (pos[2] < p[2])
        {
            pos[2] += (k*velocity);
        } else
        {
            pos[2] -= (k*velocity);
        }

        wb_supervisor_field_set_sf_vec3f(object_translation, pos);

        if((pos[0]-p[0] < k) && (pos[1]-p[1] < k) && (pos[2]-p[2] < k))
        {
          break;           
        }

        if((pos[0]-p[0] < (k*velocity)) && (pos[1]-p[1] < (k*velocity)) && (pos[2]-p[2] < (k*velocity)))
        {
          velocity--;            
        }  
    }        
}

int main()
{
    wb_robot_init();

    WbDeviceTag ds1 = wb_robot_get_device("ds1");
    WbDeviceTag ds2 = wb_robot_get_device("ds2");
    wb_distance_sensor_enable(ds1, TIME_STEP);
    wb_distance_sensor_enable(ds2, TIME_STEP);
    double posin[3] = {-0.125, 0, 0.178};
    double posfin[3] = {0.159, 0, -0.106};    
    WbNodeRef block = wb_supervisor_node_get_from_def("Moving_Block");    
    double l1, l2;

    while (wb_robot_step(TIME_STEP) != -1) 
    {
        l1 = wb_distance_sensor_get_value(ds1);
        l2 = wb_distance_sensor_get_value(ds2);
        if((l1 != 1000) || (l2 != 1000))
        {
            move(block, posin, posfin, 10.0);
            break;
        }        
    }

    wb_robot_cleanup();

    return 0;
}

