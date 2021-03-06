/**
* @mainpage ZumoBot Project
* @brief    You can make your own ZumoBot with various sensors.
* @details  <br><br>
    <p>
    <B>General</B><br>
    You will use Pololu Zumo Shields for your robot project with CY8CKIT-059(PSoC 5LP) from Cypress semiconductor.This 
    library has basic methods of various sensors and communications so that you can make what you want with them. <br> 
    <br><br>
    </p>
    
    <p>
    <B>Sensors</B><br>
    &nbsp;Included: <br>
        &nbsp;&nbsp;&nbsp;&nbsp;LSM303D: Accelerometer & Magnetometer<br>
        &nbsp;&nbsp;&nbsp;&nbsp;L3GD20H: Gyroscope<br>
        &nbsp;&nbsp;&nbsp;&nbsp;Reflectance sensor<br>
        &nbsp;&nbsp;&nbsp;&nbsp;Motors
    &nbsp;Wii nunchuck<br>
    &nbsp;TSOP-2236: IR Receiver<br>
    &nbsp;HC-SR04: Ultrasonic sensor<br>
    &nbsp;APDS-9301: Ambient light sensor<br>
    &nbsp;IR LED <br><br><br>
    </p>
    
    <p>
    <B>Communication</B><br>
    I2C, UART, Serial<br>
    </p>
*/

#include <project.h>
#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"
#include "Motor.h"
#include "Ultra.h"
#include "Nunchuk.h"
#include "Reflectance.h"
#include "Gyro.h"
#include "Accel_magnet.h"
#include "LSM303D.h"
#include "IR.h"
#include "Beep.h"
#include "mqtt_sender.h"
#include <time.h>
#include <sys/time.h>
#include "serial1.h"
#include <unistd.h>
#include <stdlib.h>


/**
 * @file    main.c
 * @brief   
 * @details  ** Enable global interrupt since Zumo library uses interrupts. **<br>&nbsp;&nbsp;&nbsp;CyGlobalIntEnable;<br>
*/

// testiohjelma käännöksille 

#if 0

    void zmain(void){
    void tankTurnLeft();
    void tankTurnRight();    
    void oneHundreadEightyDegreeTurnRight();
    void fourtyFiveDegreeTurnRight();
    void ninetyDegreeTurnRight();
    void oneHundreadTwentyDegreeTurnRight();
    void oneHundreadEightyDegreeTurnLeft();
    void fourtyFiveDegreeTurnLeft();
    void ninetyDegreeTurnLeft();
    void oneHundreadTwentyDegreeTurnLeft();
    
    motor_start();
    ninetyDegreeTurnRight();
    motor_stop();
    
    }
    
    
    void oneHundreadEightyDegreeTurnRight(){
    MotorDirLeft_Write(0);      // set LeftMotor backward mode
    MotorDirRight_Write(1);     // set RightMotor forward mode
    PWM_WriteCompare1(255); 
    PWM_WriteCompare2(255); 
    vTaskDelay(390);
    MotorDirRight_Write(0);
}

    void fourtyFiveDegreeTurnRight(){
    MotorDirLeft_Write(0);      // set LeftMotor backward mode
    MotorDirRight_Write(1);     // set RightMotor forward mode
    PWM_WriteCompare1(255); 
    PWM_WriteCompare2(255); 
    vTaskDelay(120);
    MotorDirRight_Write(0);
}
    void ninetyDegreeTurnRight(){
    MotorDirLeft_Write(0);      // set LeftMotor backward mode
    MotorDirRight_Write(1);     // set RightMotor forward mode
    PWM_WriteCompare1(255); 
    PWM_WriteCompare2(255); 
    vTaskDelay(205);
    MotorDirRight_Write(0);
}
    void oneHundreadTwentyDegreeTurnRight(){
    MotorDirLeft_Write(0);      // set LeftMotor backward mode
    MotorDirRight_Write(1);     // set RightMotor forward mode
    PWM_WriteCompare1(255); 
    PWM_WriteCompare2(255); 
    vTaskDelay(330);
    MotorDirRight_Write(0);
}
    
    void oneHundreadEightyDegreeTurnLeft(){
    MotorDirLeft_Write(1);      // set LeftMotor backward mode
    MotorDirRight_Write(0);     // set RightMotor forward mode
    PWM_WriteCompare1(255); 
    PWM_WriteCompare2(255); 
    vTaskDelay(390);
    MotorDirRight_Write(0);
}

    void fourtyFiveDegreeTurnLeft(){
    MotorDirLeft_Write(1);      // set LeftMotor backward mode
    MotorDirRight_Write(0);     // set RightMotor forward mode
    PWM_WriteCompare1(255); 
    PWM_WriteCompare2(255); 
    vTaskDelay(120);
    MotorDirRight_Write(0);
}
    void ninetyDegreeTurnLeft(){
    MotorDirLeft_Write(1);      // set LeftMotor backward mode
    MotorDirRight_Write(0);     // set RightMotor forward mode
    PWM_WriteCompare1(255); 
    PWM_WriteCompare2(255); 
    vTaskDelay(205);
    MotorDirRight_Write(0);
}
    void oneHundreadTwentyDegreeTurnLeft(){
    MotorDirLeft_Write(1);      // set LeftMotor backward mode
    MotorDirRight_Write(0);     // set RightMotor forward mode
    PWM_WriteCompare1(255); 
    PWM_WriteCompare2(255); 
    vTaskDelay(330);
    MotorDirRight_Write(0);
}
    



    
    
#endif

#if 0

    
    void zmain(void){
    

        struct accData_ data;
        
        
        if(!LSM303D_Start()){
             printf("LSM303D failed to initialize!!! Program is Ending!!!\n");
            while(1) vTaskDelay(10); 
        }else{
             printf("Device Ok...\n"); 
        }
        
        while(true){
            LSM303D_Read_Acc(&data); 
            printf("x %10d y %10d\n",data.accX, data.accY);
            vTaskDelay(100);
            
            if(data.accX <= -800 && data.accX >= -2400){
                printf("Hit from the back\n");
            }else if(data.accX >= 800 && data.accX <= 2400){
                printf("Hit from the front\n");
            }else if(data.accY <= -1200 && data.accY >= -2000){
                printf("Hit from the right");
            }else if(data.accY >= 200 && data.accY <= 2000){
                printf("Hit from the left");
            }
            
        }
        
    }
    
#endif


#if 1
    // Sumo botti
    void zmain(void)
    {
        
    //methods and booleans
        bool objectAhead();
        bool isLineIntersection();
        bool isThereLine();
        bool isLineLittleLeft();
        bool isLineLittleRight();
        bool isLineLeft();
        bool isLineRight();
        bool isLineLeftEdge();
        bool isLineRightEdge();
        void stopMovement();
        void moveBack();
        void moveForward();
        void hunt();
        void oneHundreadEightyDegreeTurnRight();
        void oneHundreadTwentyDegreeTurnRight();
        void oneHundreadEightyDegreeTurnLeft();
        void oneHundreadTwentyDegreeTurnLeft();
        void backToMiddle();
        
        // Structures
        
        struct accData_ data;        
        struct sensors_ ref;
        uint8 SW1_Read(void);
        TickType_t start;
        TickType_t end;
        
        
        //start everything
        
        reflectance_start();
        motor_start();
        IR_Start();
        Ultra_Start();
        LSM303D_Start();
        
        
        
      while(true){
        
            if(SW1_Read() == 0){
                
        // Loop to the first intersectio waiting for IR Signal!
                while(true){
                    reflectance_read(&ref);
                    motor_forward(50, 10);
                    if(isLineIntersection(ref)){                        
                        stopMovement();
                        IR_flush();
                        print_mqtt("Zumo045/ready ", "zumo");
                        IR_wait();
                        motor_forward(255,800);
                        motor_forward(0,0);
                        break;
                    }
                    
                }
                

        // Printing out the start time
        start = xTaskGetTickCount();
        print_mqtt("Zumo045/start ", "%d", start);
        
        //sumo loop
        while(true){
        // reading the sensors for data.
                LSM303D_Read_Acc(&data);
                reflectance_read(&ref);
                hunt();
            
                if(objectAhead()){  
                    moveForward();   
        //checkups if the robot is one the line and turns               
                }else if (isLineLittleLeft(ref)) {
                    backToMiddle();
                    oneHundreadEightyDegreeTurnRight();
                    
                }if (isLineLittleRight(ref)){
                    backToMiddle();
                    oneHundreadEightyDegreeTurnLeft();
                    
                }else if (isLineLeft(ref)){
                    backToMiddle();
                    oneHundreadEightyDegreeTurnRight();
                    
                }if (isLineRight(ref)){
                    backToMiddle();
                    oneHundreadEightyDegreeTurnLeft();
                   
                }else if(isLineLeftEdge(ref)){
                    backToMiddle();
                    oneHundreadTwentyDegreeTurnRight();
                    
                }if (isLineRightEdge(ref)){
                    backToMiddle();
                    oneHundreadTwentyDegreeTurnLeft();
                    
                }else if(isThereLine()){
                    backToMiddle();
                    oneHundreadEightyDegreeTurnRight();
                    
                    }
                

                
                // Stoping the shit and print mqtt time
                if(SW1_Read() == 0){
                    end = xTaskGetTickCount();
                    print_mqtt("Zumo045/stop ", "%d", end);
                    print_mqtt("Zumo045/time ", "%d", end - start);
                    break;
                    }
                
                }
            }
        }
    }
        

         
        
        
        
        
        
        
        
        
        // methods
    
    void hunt(){
        motor_turn(255, 0, 0);
        
    }
    
    void moveForward(){
        motor_forward(255,0);
        
    }
    
    void moveBack(){
        MotorDirLeft_Write(0);      // set LeftMotor backward mode
        MotorDirRight_Write(1);     // set RightMotor forward mode
        PWM_WriteCompare1(250); 
        PWM_WriteCompare2(250); 
        motor_forward(255,0);
        
    }
    
        void stopMovement(){
        motor_forward(0, 0);
        
    }
    
        // All turn methods
        void oneHundreadEightyDegreeTurnRight(){
        MotorDirLeft_Write(0);      // set LeftMotor backward mode
        MotorDirRight_Write(1);     // set RightMotor forward mode
        PWM_WriteCompare1(255); 
        PWM_WriteCompare2(255); 
        vTaskDelay(390);
        MotorDirRight_Write(0);

    }
 
    void oneHundreadTwentyDegreeTurnRight(){
        MotorDirLeft_Write(0);      // set LeftMotor backward mode
        MotorDirRight_Write(1);     // set RightMotor forward mode
        PWM_WriteCompare1(255); 
        PWM_WriteCompare2(255); 
        vTaskDelay(330);
        MotorDirRight_Write(0);
        
    }   
    
    void oneHundreadEightyDegreeTurnLeft(){
        MotorDirLeft_Write(1);      // set LeftMotor backward mode
        MotorDirRight_Write(0);     // set RightMotor forward mode
        PWM_WriteCompare1(255); 
        PWM_WriteCompare2(255); 
        vTaskDelay(390);
        MotorDirRight_Write(0);

    }
    
    void oneHundreadTwentyDegreeTurnLeft(){
        MotorDirLeft_Write(1);      // set LeftMotor backward mode
        MotorDirRight_Write(0);     // set RightMotor forward mode
        PWM_WriteCompare1(255); 
        PWM_WriteCompare2(255); 
        vTaskDelay(330);
        MotorDirRight_Write(0);
    }
    
    void backToMiddle(){  
        motor_forward(0,0);
        motor_backward(255,200);
        motor_forward(255, 800);
    }
        // all  checks if the robot is on the black line.
    
    bool objectAhead(){
    
    if(Ultra_GetDistance() <= 20){
    return true;
    }
    return false;  
    }
    
    bool isLineIntersection(struct sensors_ ref){
    
    int average = (ref.l1 + ref.l2 + ref.l3 + ref.r1 + ref.r2 + ref.r3) / 6;
    
    if(average >= 18000){
        return true;
    printf("%d/n",average);
    }
    
    return false;
    }
    bool isThereLine(struct sensors_ ref){
    
    if(ref.r1 >= 10000 && ref.r2 >= 10000 && ref.l1 >= 10000 && ref.l2 >= 10000 && ref.l3 >= 10000 && ref.r3 >= 10000 ){
        return true;
    } return false;}
    
    
    bool isLineLittleLeft(struct sensors_ ref){
    
    if(ref.l1 >= 10000 && ref.l2 >= 10000 && ref.l3 >= 10000 && ref.r1 < 10000 && ref.r2 < 10000 && ref.r3 < 10000 ){
        return true;
    } return false;}
    
    
    bool isLineLittleRight(struct sensors_ ref){
    
    if(ref.l1 < 10000 && ref.l2 < 10000 && ref.l3 < 10000 && ref.r1 >= 10000 && ref.r2 >= 10000 && ref.r3 >= 10000 ){
        return true;
    } return false;}
    
    
    bool isLineLeft(struct sensors_ ref){
    
    if(ref.l1 >= 10000 && ref.l2 >= 10000 && ref.l3 < 10000 && ref.r1 < 10000 && ref.r2 < 10000 && ref.r3 < 10000 ){
        return true;
    } return false;}
    
    
    bool isLineRight(struct sensors_ ref){
    
    if(ref.l1 < 10000 && ref.l2 < 10000 && ref.l3 < 10000 && ref.r1 >= 10000 && ref.r2 >= 10000 && ref.r3 < 10000 ){
        return true;
    } return false;}
    
    
    bool isLineLeftEdge(struct sensors_ ref){
    
    if(ref.l1 >= 10000 && ref.l2 < 10000 && ref.l3 < 10000 && ref.r1 < 10000 && ref.r2 < 10000 && ref.r3 < 10000 ){
        return true;
    } return false;}
    
    
    bool isLineRightEdge(struct sensors_ ref){
    
    if(ref.l1 < 10000 && ref.l2 < 10000 && ref.l3 < 10000 && ref.r1 >= 10000 && ref.r2 < 10000 && ref.r3 < 10000 ){
        return true;
    } return false;}
    
    
#endif

#if 0
    // Maze
    void zmain(void)
    {
        
        
    // methods
    bool isLineMiddle();
    bool isLineIntersection();
    bool isLineLittleRight();
    bool isLineLittleLeft();
    bool objectAhead();
    bool isLineMoreRight();
    bool isLineMoreLeft();
    bool endOfTheLine();
    void backToMiddleLineRight();
    void backToMiddleLineLeft();
    void hardTurnLeft();
    void hardTurnRight();
    void tankTurnLeft();
    void tankTurnRight();
    void moveForward();
    void goBack();
    void skip();
    void stopMovement();
    void mazeTurnRight();
    void mazeTurnLeft();
    void goToLeft();
    void goToRight();
    void startLineSkip();
    
    
    
    
    //variables
    struct sensors_ ref;
    uint8 SW1_Read(void);
    int xcount = 0;
    int ycount = 0;
    TickType_t start;
    TickType_t end;
    
    
    //starting sensors
    reflectance_start();
    motor_start();
    IR_Start();
    Ultra_Start();
    
    
    
    //main while loop
    while(true){
            if(SW1_Read() == 0){
                
                // Loop to the first intersection waiting for IR Signal!
                while(true){
                    reflectance_read(&ref);
                    motor_forward(50, 10);
                    if(isLineIntersection(ref)){
                        startLineSkip();
                        stopMovement();
                        print_mqtt("Zumo045:/Ready","Maze");
                        IR_flush();
                        IR_wait();
                        start = xTaskGetTickCount();
                        break;
                    }
                }
            
            
        
                // Main loop
                while(true){
                    
                    reflectance_read(&ref);
                    
                    if(isLineIntersection(ref)){
                        print_mqtt("Zumo045:", "X:%d    Y:%d",xcount,ycount );
                        skip();
                        ycount++;
                        //Try avoiding obstacle going right if X= 0-3
                        if(objectAhead() && xcount>=0 && xcount<4){
                            
                            if(xcount==3){
                                print_mqtt("Zumo045:", "X:%d    Y:%d",xcount,ycount );
                                while(true){
                                    //Going to left side just to be sure
                                    
                                    if (xcount>=0){ 
                                        
                                        mazeTurnLeft();
                                        xcount--;
                                        print_mqtt("Zumo045:", "X:%d    Y:%d",xcount,ycount );
                                    }else{
                                           
                                        break;
                                    }
                                    }
                                }else if(objectAhead() && xcount<3){
                                    
                                    mazeTurnRight();
                                    xcount++; 
                                    print_mqtt("Zumo045:", "X:%d    Y:%d",xcount,ycount );
                                    //Checking that there is no object after the movement and reacting if there is
                                    if(objectAhead()&& xcount<3){
                                        mazeTurnRight();
                                        xcount++; 
                                        print_mqtt("Zumo045:", "X:%d    Y:%d",xcount,ycount );
                                    }
                                }
                        //Try to avoid obstacle going left if X= -1 to -3
                                }else if(objectAhead() && xcount<0 ){
                                    if(xcount==-3){
                                        print_mqtt("Zumo045:", "X:%d    Y:%d",xcount,ycount );
                                //Going to right side just to be sure
                                        while(true){
                                        print_mqtt("Zumo045:", "X:%d    Y:%d",xcount,ycount );
                                        if (xcount < 0){
                                        mazeTurnRight();
                                        xcount++;
                                    }else{
                                        break;
                                    }
                                    }
                            }else{
                                print_mqtt("Zumo045:", "X:%d    Y:%d",xcount,ycount );
                                mazeTurnLeft();
                                xcount--;
                                //Checking if there is an object ahead after the turn and reacting
                                if(objectAhead()&& xcount<
                                3){
                                print_mqtt("Zumo045:", "X:%d    Y:%d",xcount,ycount );
                                mazeTurnLeft();
                                xcount--;
                            }
                            }
                            
                        
                            
                        }else if(ycount>=11){
                            //No more obstacles get to middle line
                            if(xcount!=0){
                            while(true){                                
                                if(xcount>0){
                                    mazeTurnLeft();
                                    xcount--;
                                    print_mqtt("Zumo045:", "X:%d    Y:%d",xcount,ycount );
                                }else if(xcount<0){
                                    mazeTurnRight();
                                    xcount++;
                                    print_mqtt("Zumo045:", "X:%d    Y:%d",xcount,ycount );
                                }else if(xcount==0){
                                    print_mqtt("Zumo045:", "X:%d    Y:%d",xcount,ycount );
                                    break;
                                }
                            }
                            }else{
                                while(true){
                                if(ycount==13){
                                    moveForward();
                                    //Delay just to make sure it gets over the last line since not sure when it has to stop
                                    vTaskDelay(2000);
                                    motor_forward(0,0);
                                    motor_stop();
                                    end = xTaskGetTickCount();
                                    int time= end - start;
                                    print_mqtt("Zumo045:","Time:%d",time);
                                    
                                }else if(isLineMiddle(ref)){
                                    moveForward();
                                }else if(isLineLittleRight(ref)){
                                    backToMiddleLineRight();
                                }else if(isLineLittleLeft(ref)){
                                    backToMiddleLineLeft();
                                }else if(isLineMoreLeft(ref)){
                                    hardTurnLeft();
                                }else if(isLineMoreRight(ref)){
                                    hardTurnRight();
                                }
                                //Just to make sure it doesn't go outside the maze after finishing
                                else if(endOfTheLine(ref)){
                                    stopMovement();
                                    motor_stop();
                                }else if(isLineIntersection(ref)){
                                    ycount++;
                                    //Delay to not count the same intersection twice
                                    vTaskDelay(200);
                                print_mqtt("Zumo045:", "X:%d    Y:%d",xcount,ycount );}                                    
                                }
                            }
                            }
                        
                        
                        
 

                    
                    
                    }else{
                
                    // Basic Midlle Line following
                        if(isLineMiddle(ref)){
                            moveForward();
                        }else if(isLineLittleRight(ref)){
                            backToMiddleLineRight();
                        }else if(isLineLittleLeft(ref)){
                            backToMiddleLineLeft();
                        }else if(isLineMoreLeft(ref)){
                            hardTurnLeft();
                        }else if(isLineMoreRight(ref)){
                            hardTurnRight();
                        }else if(endOfTheLine(ref)){
                            stopMovement();
                            motor_stop();
                        }
                    }
                
                }
            }
        }
    }
    
    //Checking for object
    bool objectAhead(){
    
    if(Ultra_GetDistance() <= 15){
        return true;
    }
        return false;  
    }
    
    
    
    //Checking for intersection
    bool isLineIntersection(struct sensors_ ref){
    
    int average = (ref.l1 + ref.l2 + ref.l3 + ref.r1 + ref.r2 + ref.r3) / 6;
    
    if(average >= 14000){
        return true;
    }
    
    return false;
}
    //Checking if there is still a line
    bool endOfTheLine(struct sensors_ ref){
            if(ref.l1 < 12000 && ref.r1 < 12000 && ref.l2 < 12000 && ref.l3 < 12000 && ref.r2 < 12000 && ref.r3 < 12000){
        return true;
    }
    
    return false;
    
    }
    
    //Boolean values for the checking where the line is.
    bool isLineMiddle(struct sensors_ ref){

     
    if(ref.l1 >= 10000 && ref.r1 >= 10000 && ref.l2 < 10000 && ref.l3 < 10000 && ref.r2 < 10000 && ref.r3 < 10000){
        return true;
    }
    
    return false;
}

    
    bool isLineLittleRight(struct sensors_ ref){
    
    
    if(ref.r1 >= 10000 && ref.r2 >= 10000 && ref.l1 < 10000 && ref.l2 < 10000 && ref.l3 < 10000 && ref.r3 < 10000 ){
        return true;
    }
    
    return false;
}

    bool isLineLittleLeft(struct sensors_ ref){
    
    
    if(ref.l1 >= 10000 && ref.l2 >= 10000 && ref.l3 < 10000 && ref.r1 < 10000 && ref.r2 < 10000 && ref.r3 < 10000 ){
        return true;
    }
    
    return false;
}
    bool isLineMoreRight(struct sensors_ ref){
    
     
    if(ref.r2 >= 10000 && ref.r3 >= 10000 && ref.r1 < 10000 && ref.l2 < 10000 && ref.l3 < 10000 && ref.l1 < 10000){
        return true;
    }
    return false;
}

bool isLineMoreLeft(struct sensors_ ref){
    
     
    if(ref.l2 >= 10000 && ref.l3 >= 10000 && ref.r1 < 10000 && ref.r2 < 10000 && ref.r3 < 10000 && ref.l1 < 10000){
        return true;
    }
    return false;
}
    //Moving methods
    void moveForward(){
        motor_forward(80, 0);
    }
    
    void hardTurnLeft(){
        motor_turn(30, 100, 0);
    }
    
    void hardTurnRight(){
        motor_turn(100, 30, 0);
    }
    
    void backToMiddleLineRight(){
        motor_turn(80, 40, 0);
    }
    
    void backToMiddleLineLeft(){
        motor_turn(80, 40, 0);
    }
    
    void goBack(){
        motor_backward(100, 0);                        
    }
    void startLineSkip(){
    motor_forward(60,400);
    }
    void skip(){
    motor_forward(60, 350);
    }
    
    void stopMovement(){
    motor_forward(0, 0);
    }

    void tankTurnLeft(){
    MotorDirLeft_Write(1);      // set LeftMotor backward mode
    MotorDirRight_Write(0);     // set RightMotor forward mode
    PWM_WriteCompare1(100); 
    PWM_WriteCompare2(100); 
    vTaskDelay(600);
    MotorDirLeft_Write(0);
}

void tankTurnRight(){
    MotorDirLeft_Write(0);      // set LeftMotor backward mode
    MotorDirRight_Write(1);     // set RightMotor forward mode
    PWM_WriteCompare1(100); 
    PWM_WriteCompare2(100); 
    vTaskDelay(600);
    MotorDirRight_Write(0);
}



void mazeTurnRight(){
    
    struct sensors_ ref;
    
    tankTurnRight();        
    while(true){
        reflectance_read(&ref);
        if(isLineMiddle(ref)){
             moveForward();
        }else if(isLineLittleRight(ref)){
            backToMiddleLineRight();
        }else if(isLineLittleLeft(ref)){
            backToMiddleLineLeft();
        }else if(isLineMoreLeft(ref)){
            hardTurnLeft();
        }else if(isLineMoreRight(ref)){
                         hardTurnRight();
        }
        else if(isLineIntersection(ref)){
            
            skip();
            break;
        }
    }
    
    
    tankTurnLeft();
    

}
void mazeTurnLeft(){
    
    struct sensors_ ref;
    
    tankTurnLeft();

    while(true){       
        reflectance_read(&ref);
        if(isLineMiddle(ref)){
                moveForward();
            }else if(isLineLittleRight(ref)){
                backToMiddleLineRight();
            }else if(isLineLittleLeft(ref)){
                backToMiddleLineLeft();
            }else if(isLineMoreLeft(ref)){
                hardTurnLeft();
            }else if(isLineMoreRight(ref)){
                hardTurnRight();
        }else if(isLineIntersection(ref)){
            skip();
            break;
        }  
        
    }
    tankTurnRight();        

}



#endif

#if 0
    
    void zmain(void)
    {
    
    // methods
    bool isLineMiddle();
    bool isLineIntersection();
    bool isLineLittleRight();
    bool isLineLittleLeft();
    bool objectAhead();
    void backToMiddleLineRight();
    void backToMiddleLineLeft();
    void hardTurnLeft();
    void hardTurnRight();
    void tankTurnLeft();
    void tankTurnRight();
    void moveForward();
    void goBack();
    void skip();
    void stopMovement();
    void mazeTurnRight();
    void mazeTurnLeft();
    void tankTurnLeftExtreme();
    
    
    
    //variables
    struct sensors_ ref;
    uint8 SW1_Read(void);
    //int xcount = 0;
    //int ycount = 0;
    
    
    //starting sensors
    reflectance_start();
    motor_start();
    IR_Start();
    Ultra_Start();
    
    while(true){
        if(SW1_Read() == 0){
            break;
        }
    }
    
    while(true){
        reflectance_read(&ref);
        motor_forward(50, 0);
        if(isLineIntersection(ref)){
            skip();
            stopMovement();
            IR_flush();
            IR_wait();
            break;
        }
    }
    
    // Main place
    while(true){
        reflectance_read(&ref);
        motor_forward(50, 0);
        
        if(objectAhead()){
            while(true){
                reflectance_read(&ref);
                motor_forward(50, 0);
                if(isLineIntersection(ref)){
                    skip();
                    mazeTurnLeft();
                    break;
                }
            }
        }


        
    }
    
    
    
}
        
    
     bool objectAhead(){
    
    if(Ultra_GetDistance() <= 15){
        return true;
    }
        return false;  
    }
    
    
    

    bool isLineIntersection(struct sensors_ ref){
    
    int average = (ref.l1 + ref.l2 + ref.l3 + ref.r1 + ref.r2 + ref.r3) / 6;
    
    if(average >= 14000){
        return true;
    }
    
    return false;
}
    
    bool isLineMiddle(struct sensors_ ref){

    // Lisää lisä ehto jos vain jompi kumpi palaa 
    if(ref.l1 >= 10000 && ref.r1 >= 10000 && ref.l2 < 10000 && ref.l3 < 10000 && ref.r2 < 10000 && ref.r3 < 10000){
        return true;
    }
    
    return false;
}


    bool isLineLittleRight(struct sensors_ ref){
    
    // Lisää lisä ehto jos vain jompi kumpi palaa 
    if(ref.r1 >= 10000 && ref.r2 >= 10000 && ref.l1 < 10000 && ref.l2 < 10000 && ref.l3 < 10000 && ref.r3 < 10000 ){
        return true;
    }
    
    return false;
}

    bool isLineLittleLeft(struct sensors_ ref){
    
    // Lisää lisä ehto jos vain jompi kumpi palaa 
    if(ref.l1 >= 10000 && ref.l2 >= 10000 && ref.l3 < 10000 && ref.r1 < 10000 && ref.r2 < 10000 && ref.r3 < 10000 ){
        return true;
    }
    
    return false;
}
    
    void moveForward(){
        motor_forward(50, 0);
    }
    
    void hardTurnLeft(){
        motor_turn(0, 240, 0);
    }
    
    void hardTurnRight(){
        motor_turn(240, 0, 0);
    }
    
    void backToMiddleLineRight(){
        motor_turn(50, 30, 0);
    }
    
    void backToMiddleLineLeft(){
        motor_turn(30, 50, 0);
    }
    
    void goBack(){
        motor_backward(100, 0);                        
    }
    
    void skip(){
    motor_forward(60, 300);
    }
    
    void stopMovement(){
    motor_forward(0, 0);
    }

    void tankTurnLeft(){
    MotorDirLeft_Write(1);      // set LeftMotor backward mode
    MotorDirRight_Write(0);     // set RightMotor forward mode
    PWM_WriteCompare1(100); 
    PWM_WriteCompare2(100); 
    vTaskDelay(710);
    MotorDirLeft_Write(0);
}

void tankTurnRight(){
    MotorDirLeft_Write(0);      // set LeftMotor backward mode
    MotorDirRight_Write(1);     // set RightMotor forward mode
    PWM_WriteCompare1(100); 
    PWM_WriteCompare2(100); 
    vTaskDelay(710);
    MotorDirRight_Write(0);
}

void checkForObstacle(){
    

}

void tankTurnLeftExtreme(){
    MotorDirLeft_Write(1);      // set LeftMotor backward mode
    MotorDirRight_Write(0);     // set RightMotor forward mode
    PWM_WriteCompare1(250); 
    PWM_WriteCompare2(250); 
    vTaskDelay(250);
}

void mazeTurnRight(){
    
    struct sensors_ ref;
    
    tankTurnRight();
    while(true){
        reflectance_read(&ref);
        moveForward();
        if(isLineIntersection(ref)){
            skip();
            break;
        }
    }
    tankTurnLeft();
    skip();
}

void mazeTurnLeft(){
    
    struct sensors_ ref;
    
    tankTurnLeft();
    while(true){
        reflectance_read(&ref);
        moveForward();
        if(isLineIntersection(ref)){
            skip();
            break;
        }   
    }
    tankTurnRight();
    skip();
}
    
#endif

#if 0
    // Line following part
    void zmain(void)
    {
        // Initializing methods
        bool isLineMiddle();
        bool isLineIntersection();
        bool isLineLittleRight();
        bool isLineLittleLeft();
        bool isLineMoreRight();
        bool isLineMoreLeft();
        bool isLineOnRightEdge();
        bool isLineOnLeftEdge();
        bool endOfTheLineRight();
        bool endOfTheLineLeft();
        void moveForward();
        void turnLeft();
        void turnRight();
        void hardTurnLeft();
        void hardTurnRight();
        void stopMovement();
        void tankTurnLeft();
        void tankTurnRight();
        void skip();
        void backToMiddleLineRight();
        void backToMiddleLineLeft();
        
        
        

        
        // Creating variables
        struct sensors_ ref;
        int count = 0;
        uint8 SW1_Read(void);
        TickType_t start;
        TickType_t end;
        

        // Starting needed sensors
        reflectance_start();
        motor_start();
        IR_Start();
        

        // Main while loop
        while(true){
        
            if(SW1_Read() == 0){
                
                // Loop to the first intersectio waiting for IR Signal!
                while(true){
                    reflectance_read(&ref);
                    motor_forward(50, 10);
                    if(isLineIntersection(ref)){
                        skip();
                        stopMovement();
                        IR_flush();
                        print_mqtt("Zumo045/ready","line");
                        start = xTaskGetTickCount();
                        IR_wait();
                        print_mqtt("Zumo045/start", "%d", start);
                        break;
                    }
                }
                
                // Main line following part
                // Start of the line following
                while(true){                    
                    reflectance_read(&ref);
                    printf(" _||_ %d, %d, %d, %d, %d, %d\n", ref.l3, ref.l2, ref.l1, ref.r1, ref.r2, ref.r3);
                    if(isLineIntersection(ref)){
                        // Adding to count when crossing lines. When it gets higher than 10 it makes the stop
                        if(count>=10){
                            motor_forward(0,0);
                            motor_stop();
                            end = xTaskGetTickCount();
                            
                            // Calculating the time that it took to run the course
                            print_mqtt("Zumo045/stop","%d", end);
                            print_mqtt("Zmo045u/time","%d", end-start);
                            break;
                        }else{
                            moveForward();
                            count++;
                        }
                    // This is the line following algorith    
                    }else if(isLineMiddle(ref)){
                        moveForward();
                    }else if(isLineLittleRight(ref)){
                        backToMiddleLineRight();
                    }else if(isLineLittleLeft(ref)){
                        backToMiddleLineLeft();
                    }else if(isLineMoreRight(ref)){
                        turnRight();
                    }else if(isLineMoreLeft(ref)){
                        turnLeft();
                    }else if(isLineOnLeftEdge(ref)){
                        hardTurnLeft();
                    }else if(isLineOnRightEdge(ref)){
                        hardTurnRight();
                    }else if(endOfTheLineLeft(ref)){
                        hardTurnLeft();
                    }else if(endOfTheLineRight(ref)){
                        hardTurnRight();
                    }
                
                }
                
                // Catching code here. So it dosen't give error
                while(true){
                    vTaskDelay(100); // sleep (in an infinite loop)
                }
                
            }
        }
    }
    
//Takes sensor data as parameter. Check if the parameters indicates it being at middle. If middle returns true.    
bool isLineMiddle(struct sensors_ ref){

    // Lisää lisä ehto jos vain jompi kumpi palaa 
    if(ref.l1 >= 10000 && ref.r1 >= 10000 && ref.l2 < 10000 && ref.l3 < 10000 && ref.r2 < 10000 && ref.r3 < 10000){
        return true;
    }
    
    return false;
}

//Takes sensor data as parameter. Check if the parameters indicates it being at right edge. If right edge returns true.
bool isLineOnRightEdge(struct sensors_ ref){

    // Lisää lisä ehto jos vain jompi kumpi palaa 
    if(ref.r3 >= 10000 && ref.r1 < 10000 && ref.l2 < 10000 && ref.l3 < 10000 && ref.r2 < 10000 && ref.l1 < 10000){
        return true;
    }
    
    return false;
}

//Takes sensor data as parameter. Check if the parameters indicates it being at left edge. If left edge returns true.
bool isLineOnLeftEdge(struct sensors_ ref){

    // Lisää lisä ehto jos vain jompi kumpi palaa 
    if(ref.l3 >= 10000 && ref.r1 < 10000 && ref.l2 < 10000 && ref.l1 < 10000 && ref.r2 < 10000 && ref.r3 < 10000){
        return true;
    }
    
    return false;
}

//Takes sensor data as parameter. Check if the parameters indicates it being a intersection. If intersection returns true.
bool isLineIntersection(struct sensors_ ref){
    
    int average = (ref.l1 + ref.l2 + ref.l3 + ref.r1 + ref.r2 + ref.r3) / 6;
    
    if(average >= 23000){
        return true;
    }
    
    return false;
}

//Takes sensor data as parameter. Check if the parameters indicates it being a little to right. If little right returns true.
bool isLineLittleRight(struct sensors_ ref){
    
    // Lisää lisä ehto jos vain jompi kumpi palaa 
    if(ref.r1 >= 10000 && ref.r2 >= 10000 && ref.l1 < 10000 && ref.l2 < 10000 && ref.l3 < 10000 && ref.r3 < 10000 ){
        return true;
    }
    
    return false;
}

//Takes sensor data as parameter. Check if the parameters indicates it being little left. If little left returns true.
bool isLineLittleLeft(struct sensors_ ref){
    
    // Lisää lisä ehto jos vain jompi kumpi palaa 
    if(ref.l1 >= 10000 && ref.l2 >= 10000 && ref.l3 < 10000 && ref.r1 < 10000 && ref.r2 < 10000 && ref.r3 < 10000 ){
        return true;
    }
    
    return false;
}

//Takes sensor data as parameter. Check if the parameters indicates it being at rigt. If right returns true.
bool isLineMoreRight(struct sensors_ ref){
    
    // Lisää lisä ehto jos vain jompi kumpi palaa 
    if(ref.r2 >= 10000 && ref.r3 >= 10000 && ref.r1 < 10000 && ref.l2 < 10000 && ref.l3 < 10000 && ref.l1 < 10000){
        return true;
    }
    return false;
}

//Takes sensor data as parameter. Check if the parameters indicates it being at left. If left returns true.
bool isLineMoreLeft(struct sensors_ ref){
    
    // Lisää lisä ehto jos vain jompi kumpi palaa 
    if(ref.l2 >= 10000 && ref.l3 >= 10000 && ref.r1 < 10000 && ref.r2 < 10000 && ref.r3 < 10000 && ref.l1 < 10000){
        return true;
    }
    return false;
}

//Takes sensor data as parameter. Check if the parameters indicates it being at . If left returns true.
bool endOfTheLineLeft(struct sensors_ ref){
if(ref.l2 >= 10000 && ref.l3 >= 10000 && ref.r3 < 10000 && ref.l1 >= 10000){
        return true;
    }
    return false;

}

//Takes sensor data as parameter. Check if the parameters indicates it being at . If left returns true.
bool endOfTheLineRight(struct sensors_ ref){
    
    // Lisää lisä ehto jos vain jompi kumpi palaa 
    if(ref.r2 >= 10000 && ref.r3 >= 10000 && ref.r1 >= 10000 && ref.l3 < 10000){
        return true;
    }
    return false;
}

// Here we have motor turns

void turnLeft(){
    motor_turn(40, 200, 0);
}

void hardTurnLeft(){
    motor_turn(0, 255, 0);
}

void skip(){
    motor_forward(80, 200);
}


void turnRight(){
    motor_turn(200, 40, 0);
}

void hardTurnRight(){
    motor_turn(255, 0, 0);
}

void backToMiddleLineRight(){
    motor_turn(180, 120, 0);
}

// 120, 180
void backToMiddleLineLeft(){
    motor_turn(120, 180, 0);
}
// 160
void moveForward(){
    motor_forward(160, 0);
}

void stopMovement(){
    motor_forward(0, 0);
}


void tankTurnLeft(){
    MotorDirLeft_Write(1);      // set LeftMotor backward mode
    MotorDirRight_Write(0);     // set RightMotor forward mode
    PWM_WriteCompare1(100); 
    PWM_WriteCompare2(100); 
    vTaskDelay(800);
    MotorDirLeft_Write(0);
}

void tankTurnRight(){
    MotorDirLeft_Write(0);      // set LeftMotor backward mode
    MotorDirRight_Write(1);     // set RightMotor forward mode
    PWM_WriteCompare1(100); 
    PWM_WriteCompare2(100); 
    vTaskDelay(800);
    MotorDirRight_Write(0);
}
void tankTurnLeftExtreme(){
    MotorDirLeft_Write(1);      // set LeftMotor backward mode
    MotorDirRight_Write(0);     // set RightMotor forward mode
    PWM_WriteCompare1(250); 
    PWM_WriteCompare2(250); 
    vTaskDelay(250);
}

void tankTurnRightExtreme(){
    MotorDirLeft_Write(0);      // set LeftMotor backward mode
    MotorDirRight_Write(1);     // set RightMotor forward mode
    PWM_WriteCompare1(250); 
    PWM_WriteCompare2(250); 
    vTaskDelay(250);
}


// Function for setting the real time
void setRealTime(int hours, int minutes, int seconds){

    RTC_Start();
    
    RTC_TIME_DATE now;
    now.DayOfYear = 2019;
    now.DayOfMonth = 12;
    now.DayOfWeek = 51;
    now.Hour = hours;
    now.Min = minutes;
    now.Sec = seconds;
    
    RTC_WriteTime(&now);
    
}

// Function for getting the real time. Houers and minutes
void getRealTime(){
    RTC_TIME_DATE now;
    RTC_DisableInt();
    now = *RTC_ReadTime();
    RTC_EnableInt();
    
    //print the current time
    printf("%2d:%02d.%02d\n", now.Hour, now.Min, now.Sec);
    
}

#endif

#if 0
// Hello World!
void zmain(void)
{
//    uint8 SW1_Read(void); 
//    //printf("\nHello, World!\n");
//    
//    if(SW1_Read() == 0){
//    printf("You pressed button\n");
//    vTaskDelay(200);
//    
//    for(int i = 0; i < 3; i++){
//        BatteryLed_Write(1);
//        vTaskDelay(500);
//        BatteryLed_Write(0);
//        vTaskDelay(500);
//    }
//    
//    for(int i = 0; i < 3; i++){
//        BatteryLed_Write(1);
//        vTaskDelay(1500);
//        BatteryLed_Write(0);
//        vTaskDelay(500);
//    }
//    
//    for(int i = 0; i < 3; i++){
//        BatteryLed_Write(1);
//        vTaskDelay(500);
//        BatteryLed_Write(0);
//        vTaskDelay(500);
//    }
//    
//}
    
    
    // ------------------------------ Tästä eteenpäin on omia testejä! ----------------------------------
    
        // 360 ang small circle turn
        //motor_turn(94, 10, 5400);
        
        // 90 ang left turn
        //motor_turn(0, 94, 1000);
        
        // 90 ang right turn
        //motor_turn(94, 0, 1000);
    
    // Ikuinen looppi. Lopettaa toiston napin painon jälkeen.
    
    //TickType_t time;
    
    while(true){
    
        if(SW1_Read() == 0){
        motor_start();
        Ultra_Start();
        //time = xTaskGetTickCount();
        
        
        while(true){
            //time = xTaskGetTickCount();
            //motor_forward(100, 100);
            int x = Ultra_GetDistance();
            printf("U_distance: %d\n", x);  
            vTaskDelay(500);
            
            
            if(Ultra_GetDistance() <= 20){
                //motor_turn(0, 94, 2000);
                printf("You are now closer than 20 cm!\n");
            }
//            if(time > 10000){
//                motor_forward(0, 0);
//                break;
//            }
        }
        
        

        // Fail safe to motor stop
        motor_forward(0, 0);
        motor_stop();
        break;
        }
    }
    
    
    while(true)
    {
        vTaskDelay(100); // sleep (in an infinite loop)
    }
 }   
#endif

#if 0
// Name and age
void zmain(void)
{
    //char name[32];
    int age, time;
    TickType_t start;
    TickType_t stop;
    
    
    
    
    
    //printf("Enter your name: ");
    //fflush(stdout);
    //scanf("%s", name);
    printf("Enter your age: ");
    start = xTaskGetTickCount();
    //fflush(stdout);
    scanf("%d", &age);
    stop = xTaskGetTickCount();

    time = stop - start;
    
    printf("Time is value &time\n");
    
    if(age < 21){
        if(time < 3000){
            printf("Super fast dude!\n");
        }else if(time >= 3000 && time <= 5000){
            printf("So mediocre.\n");
        }else{
            printf("My granny is faster than you!\n");
        }
    }else if(age >= 22 && age <= 50){
        if(time < 3000){
            printf("Be quick or be dead\n");
        }else if(time >= 3000 && time <= 5000){
            printf("You're so average.\n");
        }else{
            printf("Have you been smoking something illegal?\n");
        }
    }else{
        if(time < 3000){
            printf("Still going strong\n");
        }else if(time >= 3000 && time <= 5000){
            printf("You're doing okay for your age.\n");
        }else{
            printf("Do they still allow you to drive?\n");
        }
    }
    
    while(true)
    {
        BatteryLed_Write(!SW1_Read());
        vTaskDelay(100);
    }
 }   
#endif


#if 0
//battery level//
void zmain(void)
{
    ADC_Battery_Start();        

    int16 adcresult =0;
    float volts = 0.0;

    printf("\nBoot\n");

    //BatteryLed_Write(1); // Switch led on 
    //BatteryLed_Write(0); // Switch led off 
    //uint8 button;
    //button = SW1_Read(); // read SW1 on pSoC board
    // SW1_Read() returns zero when button is pressed
    // SW1_Read() returns one when button is not pressed

    while(true)
    {
        //char msg[80];
        ADC_Battery_StartConvert(); // start sampling
        if(ADC_Battery_IsEndConversion(ADC_Battery_WAIT_FOR_RESULT)) {   // wait for ADC converted value
            adcresult = ADC_Battery_GetResult16(); // get the ADC value (0 - 4095)
            // convert value to Volts
            // you need to implement the conversion
            volts = ((adcresult / 4095.0) * 1.5 * 5.0);
            
            //printf("button state %d\n", button);
            if(volts < 4){
                
                while(SW1_Read() == 1){
                    BatteryLed_Write(1);
                    vTaskDelay(500);
                    BatteryLed_Write(0);
                    vTaskDelay(500);
//                    if(SW1_Read() == 0){
//                        break;
//                    }
                }
                
            }
            
            // Print both ADC results and converted value
            printf("%d %.2f\r\n",adcresult, volts);
        }
        vTaskDelay(1000);
    }
 }   
#endif

#if 0
// button
void zmain(void)
{
    while(true) {
        printf("Press button within 5 seconds!\n");
        int i = 50;
        while(i > 0) {
            if(SW1_Read() == 0) {
                break;
            }
            vTaskDelay(100);
            --i;
        }
        if(i > 0) {
            printf("Good work\n");
            while(SW1_Read() == 0) vTaskDelay(10); // wait until button is released
            motor_start();
            // suorat
            motor_forward(200, 1850);
            motor_turn(96, 0, 1400);
            motor_forward(200, 1500);
            motor_turn(96, 0, 1400);
            motor_forward(200, 1550);
            motor_turn(96, 0, 1750);
            // Kaari
            motor_turn(110, 50, 4000);
            motor_forward(200,700);
            
            motor_forward(0, 0);
            motor_stop();
        }
        else {
            printf("You didn't press the button\n");
        }
    }
}
#endif

#if 0
// button
void zmain(void)
{
    printf("\nBoot\n");

    //BatteryLed_Write(1); // Switch led on 
    BatteryLed_Write(0); // Switch led off 
    
    //uint8 button;
    //button = SW1_Read(); // read SW1 on pSoC board
    // SW1_Read() returns zero when button is pressed
    // SW1_Read() returns one when button is not pressed
        while(true){
    
        if(SW1_Read() == 0){
        motor_start();
        Ultra_Start();
        
        
        while(true){
            motor_forward(50, 100);
            //int x = Ultra_GetDistance();
            //printf("U_distance: %d\n", x);  
            //vTaskDelay(500);
            
            
            if(Ultra_GetDistance() <= 10){
                // kun lähempänä kuin 10 cm
                motor_forward(0, 0);
                Beep(1000, 100);
                motor_backward(100, 2000);
                motor_turn(0, 94, 2000);
            }
//            if(time > 10000){
//                motor_forward(0, 0);
//                break;
//            }
        }
        
        

        // Fail safe to motor stop
        motor_forward(0, 0);
        motor_stop();
        break;
        }
    }
 }   
#endif


#if 0
//ultrasonic sensor//
void zmain(void)
{
    struct accData_ data;
    

        while(true){
    
        if(SW1_Read() == 0){
        motor_start();
        //Ultra_Start();
        LSM303D_Start();
        //TickType_t time;
        //time = xTaskGetTickCount();
        //TickType_t runningtime;
        
        int count = 0;
        //int data_average_x = 0;
        //int data_average_y = 0;
        //int keskiarvo = 0;
        
        while(true){
            
            motor_forward(100, 0);
            
            LSM303D_Read_Acc(&data);
            
            /*
            time = xTaskGetTickCount();
            runningtime= time % 3000;
            */
            
            //time = xTaskGetTickCount();
            
            //data_average_x += data.accX;
            //data_average_y += data.accY;
            
            count++;
            
//            printf("X : %10d Y : %10d Z : %10d\n", data.accX, data.accY, data.accZ);
//            printf("X kesiarvo on: %d\n", (data_average_x / count));
            //printf("TickType_t = %lu\n", time);
            //printf("Y kesiarvo on: %d\n", (data_average_y / count));
//            printf("%d \n", count);
//            vTaskDelay(10);
//            
            if(count > 1600){
                //time = 0;
                count = 0;
                satunnais_kaannos();
            }

            //keskiarvo = data_average_x / count;
            
            if((data.accX) <  -2500){
                motor_forward(0, 0);
//                vTaskDelay(100);
                motor_backward(100, 2000);
                satunnais_kaannos();
                count = 0;
            }

        }
        
        

        // Fail safe to motor stop
        motor_forward(0, 0);
        motor_stop();
        break;
        }
    }

}

void satunnais_kaannos(){
    
                int random_n = rand() % 2;
                
                if(random_n == 1){
                    motor_turn(0,200, 400);
                }else{
                    motor_turn(200, 0, 400);
                }
                
//                switch(random_n){
//
//                    case 0:
//                    motor_turn(0, 90, 1000);
//                    break;
//
//                    case 1:
//                    motor_turn(90, 0, 1000);
//                    break;
//
//                    default:
//                    printf("Nyt meni päin helvettiä!\n");
//                }
}


#endif





#if 0
//IR receiver - read raw data
void zmain(void)
{
    int intersectionStop();
    // Startting needed sensor and motoros
    motor_start();
    reflectance_start();
    uint8 SW1_Read(void);
    IR_Start();
    
    // Initializing variables
    struct sensors_ ref;
    int count = 0;
    
    while(true){
    
    if(SW1_Read() == 0){
        
        while(true)
        {
            motor_forward(50, 50);
            reflectance_read(&ref);
            if(intersectionStop(ref) == 1){
                break;
            }
            
        }
        
        
        motor_start();
        IR_wait(); 
        
        while(true){
        
            motor_forward(50, 10);
            count++;
            printf("count : %d\n", count);
            reflectance_read(&ref);

            if(count > 250){
                intersectionStop(ref);
            }
        }
        
    }
}

}



int intersectionStop(struct sensors_ ref){
    
    int average;
    
    average = (ref.l1 + ref.l2 + ref.l3 + ref.r1 + ref.r2 + ref.r3) / 6;
    
    printf("averaga is_ %d\n", average);
    
    if(average >= 12000){
        motor_forward(100,100);
        motor_forward(0, 0);
        motor_stop();
        printf("inside %d\n", average);
        return 1;
    }
    
    return 0;
    
}


int lineCount(struct sensors_ ref){

    int average;
    average = (ref.l1 + ref.l2 + ref.l3 + ref.r1 + ref.r2 + ref.r3) / 6;
    
    if(average >= 12000){
        motor_forward(100, 200);
        return 1;
    }
    
    return 0;
}

#endif

#if 0
    void zmain(void)
    {
        // Initializing methods
        bool isLineMiddle();
        bool isLineIntersection();
        bool isLineLittleRight();
        bool isLineLittleLeft();
        bool isLineMoreRight();
        bool isLineMoreLeft();
        void moveForward();
        void turnLeft();
        void turnRight();
        void stopMovement();
        void tankTurnLeft();
        void tankTurnRight();
        void skip();
        void backToMiddleLineRight();
        void backToMiddleLineLeft();

        
        // Creating variables
        struct sensors_ ref;
        uint8 SW1_Read(void);
        int count = 1;

        // Starting needed sensors
        reflectance_start();
        motor_start();
        IR_Start();
        

        // Main while loop
        while(true){
        
            if(SW1_Read() == 0){
                
                // Loop to the first intersectio waiting for IR Signal!
                while(true){
                    reflectance_read(&ref);
                    motor_forward(50, 10);
                    if(isLineIntersection(ref)){
                        skip();
                        stopMovement();
                        IR_flush();
                        IR_wait();
                        break;
                    }
                }
                
                // Start of the line following
                while(true){
                
                    reflectance_read(&ref);
                    printf(" _||_ %d, %d, %d, %d, %d, %d\n", ref.l3, ref.l2, ref.l1, ref.r1, ref.r2, ref.r3);
                    
                    if(isLineMiddle(ref)){
                        moveForward();
                    }else if(isLineIntersection(ref)){
                        if(count == 1){
                            skip();
                            tankTurnLeft();
                            count++;
                        }else if(count == 2){
                            printf("vitun valtteri/n");
                            skip();
                            tankTurnRight();
                            count++;
                        }else if(count == 3){
                            skip();
                            tankTurnRight();
                            count++;
                        }else{
                            motor_stop();
                        }
                    }else if(isLineLittleRight(ref)){
                        backToMiddleLineRight();
                    }else if(isLineLittleLeft(ref)){
                        backToMiddleLineLeft();
                    }else if(isLineMoreRight(ref)){
                        turnRight();
                    }else if(isLineMoreLeft(ref)){
                        turnLeft();
                    }
                
                }
                
            }
        }
    }
    
bool isLineMiddle(struct sensors_ ref){

    if(ref.l1 >= 10000 && ref.r1 >= 10000 && ref.l2 < 10000 && ref.l3 < 10000 && ref.r2 < 10000 && ref.r3 < 10000){
        return true;
    }
    
    return false;
}

bool isLineIntersection(struct sensors_ ref){
    
    int average = (ref.l1 + ref.l2 + ref.l3 + ref.r1 + ref.r2 + ref.r3) / 6;
    
    if(average >= 14000){
        return true;
    }
    
    return false;
}

bool isLineLittleRight(struct sensors_ ref){
    
    if(ref.r1 >= 10000 && ref.r2 >= 10000 && ref.l1 < 10000 && ref.l2 < 10000 && ref.l3 < 10000 && ref.r3 < 10000 ){
        return true;
    }
    
    return false;
}

bool isLineLittleLeft(struct sensors_ ref){
    
    if(ref.l1 >= 10000 && ref.l2 >= 10000 && ref.l3 < 10000 && ref.r1 < 10000 && ref.r2 < 10000 && ref.r3 < 10000 ){
        return true;
    }
    
    return false;
}

bool isLineMoreRight(struct sensors_ ref){
    
    if(ref.r2 >= 10000 && ref.r3 >= 10000 && ref.r1 < 10000 && ref.l2 < 10000 && ref.l3 < 10000 && ref.l1 < 10000){
        return true;
    }
    return false;
}

bool isLineMoreLeft(struct sensors_ ref){
    
    if(ref.l2 >= 10000 && ref.l3 >= 10000 && ref.r1 < 10000 && ref.r2 < 10000 && ref.r3 < 10000 && ref.l1 < 10000){
        return true;
    }
    return false;
}

void turnLeft(){
    motor_turn(20, 200, 0);
}

void skip(){
    motor_forward(60, 300);
}

void turnRight(){
    motor_turn(200, 20, 0);
}

void moveForward(){
    motor_forward(40, 0);
}

void stopMovement(){
    motor_forward(0, 0);
}


void tankTurnLeft(){
    MotorDirLeft_Write(1);      // set LeftMotor backward mode
    MotorDirRight_Write(0);     // set RightMotor forward mode
    PWM_WriteCompare1(100); 
    PWM_WriteCompare2(100); 
    vTaskDelay(800);
    MotorDirLeft_Write(0);
}

void tankTurnRight(){
    MotorDirLeft_Write(0);      // set LeftMotor backward mode
    MotorDirRight_Write(1);     // set RightMotor forward mode
    PWM_WriteCompare1(100); 
    PWM_WriteCompare2(100); 
    vTaskDelay(800);
    MotorDirRight_Write(0);
}
void tankTurnLeftExtreme(){
    MotorDirLeft_Write(1);      // set LeftMotor backward mode
    MotorDirRight_Write(0);     // set RightMotor forward mode
    PWM_WriteCompare1(250); 
    PWM_WriteCompare2(250); 
    vTaskDelay(250);
}

void tankTurnRightExtreme(){
    MotorDirLeft_Write(0);      // set LeftMotor backward mode
    MotorDirRight_Write(1);     // set RightMotor forward mode
    PWM_WriteCompare1(250); 
    PWM_WriteCompare2(250); 
    vTaskDelay(250);
}

void backToMiddleLineRight(){
    motor_turn(150, 50, 0);
}

void backToMiddleLineLeft(){
    motor_turn(50, 150, 0);
}



// some debug prints
// printf(" _||_ %d", );
    
#endif


#if 0
//motor
void zmain(void)
{
    motor_start();              // enable motor controller
    motor_forward(0,0);         // set speed to zero to stop motors

    vTaskDelay(3000);
    
    motor_forward(100,2000);     // moving forward
    motor_turn(200,50,2000);     // turn
    motor_turn(50,200,2000);     // turn
    motor_backward(100,2000);    // moving backward
     
    motor_forward(0,0);         // stop motors

    motor_stop();               // disable motor controller
    
    while(true)
    {
        vTaskDelay(100);
    }
}
#endif

#if 0
/* Example of how to use te Accelerometer!!!*/
void zmain(void)
{
    struct accData_ data;
    
    printf("Accelerometer test...\n");

    if(!LSM303D_Start()){
        printf("LSM303D failed to initialize!!! Program is Ending!!!\n");
        vTaskSuspend(NULL);
    }
    else {
        printf("Device Ok...\n");
    }
    
    while(true)
    {
        LSM303D_Read_Acc(&data);
        printf("%8d %8d %8d\n",data.accX, data.accY, data.accZ);
        vTaskDelay(50);
    }
 }   
#endif    

#if 0
// 5.1 Assignment
void zmain(void)
{

    RTC_TIME_DATE setRealTime();
    RTC_Start();
    
    int hours, minutes;
    uint8 SW1_Read(void);
    RTC_TIME_DATE now;
    
    vTaskDelay(10000);
    printf("Give current time.\n");
    printf("Hours: \n");
    scanf("%d", &hours);
    printf("Minutes: \n");
    scanf("%d", &minutes);

    now.Hour = hours;
    now.Min = minutes;
    
    RTC_WriteTime(&now);
    
    while(true)
    {

        if(SW1_Read() == 0){
            
            RTC_DisableInt(); /* Disable Interrupt of RTC Component */
            now = *RTC_ReadTime(); /* copy the current time to a local variable */
            RTC_EnableInt(); /* Enable Interrupt of RTC Component */
            
            print_mqtt("Zumo045/"," Time is %d:%d\n", now.Hour, now.Min);
            
             // wait until button is released
            while(SW1_Read() == 0) vTaskDelay(50);
        }
        

    }
 }



#endif

#if 0
// 5.2 Assigment
void zmain(void)
{
    void satunnais_kaannos();
    motor_start();
    Ultra_Start();
    
    while(true){
    
        while(true){
            if(SW1_Read() == 0){
                break;
            }
        }
        
        while(true){

            motor_forward(100, 0);
            
            if(Ultra_GetDistance() <= 20){
                motor_backward(200, 1000);
                satunnais_kaannos();
            }  

        }

        // Fail safe to motor stop
        motor_forward(0, 0);
        motor_stop();
        break;
        
    }
        while(true){
            vTaskDelay(100); // sleep (in an infinite loop)
        }
    
}

void satunnais_kaannos(){
    
                int random_n = rand() % 2;
                
                if(random_n == 1){
                    motor_turn(0, 200, 400);
                    print_mqtt("Zumo045/ ","turn right");
                }else{
                    motor_turn(200, 0, 400);
                    print_mqtt("Zumo045/ ","turn left");
                }
                

}

#endif

#if 0
    // Assignment 5.3
    void zmain(){
    
        // Aloitus statementit
        motor_start();
        IR_Start();
        reflectance_start();
        
        struct sensors_ ref;
        TickType_t start;
        TickType_t end;
        
        bool isLineIntersection();
        
        // Start shit at button press
        while(true){
            if(SW1_Read() == 0){
                break;
            }
        }
        
        while(true){
            reflectance_read(&ref);
            motor_forward(100, 0);
            printf("%5d %5d %5d %5d %5d %5d\r\n", ref.l3, ref.l2, ref.l1, ref.r1, ref.r2, ref.r3); 
            if(isLineIntersection(ref)){
                motor_forward(60, 300);
                motor_forward(0, 0);
                IR_flush();
                IR_wait();
                // Tähän tickcoutn start
                start = xTaskGetTickCount();
                break;
            }
            
        }
        
        // Main loop
        while(true){
            reflectance_read(&ref);
            motor_forward(100, 0);
            
            if(isLineIntersection(ref)){
                // Tähän tickount stop
                end = xTaskGetTickCount();
                motor_forward(0, 0);
                motor_stop();
                print_mqtt("Zumo045/","lap %d", end - start);
                break;
            }
            
        }
        
        while(true){
            vTaskDelay(100); // sleep (in an infinite loop)
        }
    
    }
    
    bool isLineIntersection(struct sensors_ ref){
    
    int average = (ref.l1 + ref.l2 + ref.l3 + ref.r1 + ref.r2 + ref.r3) / 6;
    if(average >= 14000){
        return true;
    }
    
    return false;
}
    
#endif

#if 0
void zmain(void)
{    
    struct accData_ data;
    struct sensors_ ref;
    struct sensors_ dig;
    
    printf("MQTT and sensor test...\n");

    if(!LSM303D_Start()){
        printf("LSM303D failed to initialize!!! Program is Ending!!!\n");
        vTaskSuspend(NULL);
    }
    else {
        printf("Accelerometer Ok...\n");
    }
    
    int ctr = 0;
    reflectance_start();
    while(true)
    {
        LSM303D_Read_Acc(&data);
        // send data when we detect a hit and at 10 second intervals
        if(data.accX > 1500 || ++ctr > 1000) {
            printf("Acc: %8d %8d %8d\n",data.accX, data.accY, data.accZ);
            print_mqtt("Zumo01/acc", "%d,%d,%d", data.accX, data.accY, data.accZ);
            reflectance_read(&ref);
            printf("Ref: %8d %8d %8d %8d %8d %8d\n", ref.l3, ref.l2, ref.l1, ref.r1, ref.r2, ref.r3);       
            print_mqtt("Zumo01/ref", "%d,%d,%d,%d,%d,%d", ref.l3, ref.l2, ref.l1, ref.r1, ref.r2, ref.r3);
            reflectance_digital(&dig);
            printf("Dig: %8d %8d %8d %8d %8d %8d\n", dig.l3, dig.l2, dig.l1, dig.r1, dig.r2, dig.r3);
            print_mqtt("Zumo01/dig", "%d,%d,%d,%d,%d,%d", dig.l3, dig.l2, dig.l1, dig.r1, dig.r2, dig.r3);
            ctr = 0;
        }
        vTaskDelay(10);
    }
 }   

#endif

#if 0
void zmain(void)
{    
    RTC_Start(); // start real time clock
    
    RTC_TIME_DATE now;

    // set current time
    now.Hour = 12;
    now.Min = 34;
    now.Sec = 56;
    now.DayOfMonth = 25;
    now.Month = 9;
    now.Year = 2018;
    RTC_WriteTime(&now); // write the time to real time clock

    while(true)
    {
        if(SW1_Read() == 0) {
            // read the current time
            RTC_DisableInt(); /* Disable Interrupt of RTC Component */
            now = *RTC_ReadTime(); /* copy the current time to a local variable */
            RTC_EnableInt(); /* Enable Interrupt of RTC Component */

            // print the current time
            printf("%2d:%02d.%02d\n", now.Hour, now.Min, now.Sec);
            
            // wait until button is released
            while(SW1_Read() == 0) vTaskDelay(50);
        }
        vTaskDelay(50);
    }
 }   
#endif

/* [] END OF FILE */
