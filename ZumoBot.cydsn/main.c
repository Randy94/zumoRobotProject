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

void satunnais_kaannos();

/**
 * @file    main.c
 * @brief   
 * @details  ** Enable global interrupt since Zumo library uses interrupts. **<br>&nbsp;&nbsp;&nbsp;CyGlobalIntEnable;<br>
*/


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
            motor_forward(200, 1750);
            motor_turn(94, 0, 1400);
            motor_forward(200, 1500);
            motor_turn(94, 0, 1400);
            motor_forward(200, 1550);
            motor_turn(94, 0, 1750);
            // Kaari
            motor_turn(110, 50, 6000);
            
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


#if 1
//ultrasonic sensor//
void zmain(void)
{
    struct accData_ data;

        while(true){
    
        if(SW1_Read() == 0){
        motor_start();
        //Ultra_Start();
        LSM303D_Start();
        TickType_t time;
        time = xTaskGetTickCount();
        TickType_t runningtime;
        
        int count = 0;
        int data_average_x = 0;
        int data_average_y = 0;
        int keskiarvo = 0;
        
        while(true){
            
            motor_forward(100, 100);
            LSM303D_Read_Acc(&data);
            time = xTaskGetTickCount();
            runningtime= time % 3000;
            
            data_average_x += data.accX;
            data_average_y += data.accY;
            
            count++;
            
            printf("X : %10d Y : %10d Z : %10d\n", data.accX, data.accY, data.accZ);
            printf("X kesiarvo on: %d\n", (data_average_x / count));
            //printf("Y kesiarvo on: %d\n", (data_average_y / count));
            //printf("%d ", random_n);
            vTaskDelay(1);
            if(runningtime == 0){
                satunnais_kaannos();
            }

            keskiarvo = data_average_x / count;
            
            if((keskiarvo - data.accX) <  -2000){
                motor_forward(0, 0);
                vTaskDelay(100);
                motor_backward(100, 2000);
                satunnais_kaannos();
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
                
                switch(random_n){

                    case 0:
                    motor_turn(0, 90, 1000);
                    break;

                    case 1:
                    motor_turn(90, 0, 1000);
                    break;

                    default:
                    printf("Nyt meni päin helvettiä!\n");
                }
}


#endif





#if 0
//IR receiver - read raw data
void zmain(void)
{
    IR_Start();
    
    uint32_t IR_val; 
    
    printf("\n\nIR test\n");
    
    IR_flush(); // clear IR receive buffer
    printf("Buffer cleared\n");
    
    // print received IR pulses and their lengths
    while(true)
    {
        if(IR_get(&IR_val, portMAX_DELAY)) {
            int l = IR_val & IR_SIGNAL_MASK; // get pulse length
            int b = 0;
            if((IR_val & IR_SIGNAL_HIGH) != 0) b = 1; // get pulse state (0/1)
            printf("%d %d\r\n",b, l);
        }
    }    
 }   
#endif


#if 0
//reflectance
void zmain(void)
{
    struct sensors_ ref;
    struct sensors_ dig;

    reflectance_start();
    reflectance_set_threshold(9000, 9000, 11000, 11000, 9000, 9000); // set center sensor threshold to 11000 and others to 9000
    

    while(true)
    {
        // read raw sensor values
        reflectance_read(&ref);
        // print out each period of reflectance sensors
        printf("%5d %5d %5d %5d %5d %5d\r\n", ref.l3, ref.l2, ref.l1, ref.r1, ref.r2, ref.r3);       
        
        // read digital values that are based on threshold. 0 = white, 1 = black
        // when blackness value is over threshold the sensors reads 1, otherwise 0
        reflectance_digital(&dig); 
        //print out 0 or 1 according to results of reflectance period
        printf("%5d %5d %5d %5d %5d %5d \r\n", dig.l3, dig.l2, dig.l1, dig.r1, dig.r2, dig.r3);        
        
        vTaskDelay(200);
    }
}   
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
// MQTT test
void zmain(void)
{
    int ctr = 0;

    printf("\nBoot\n");
    send_mqtt("Zumo01/debug", "Boot");

    //BatteryLed_Write(1); // Switch led on 
    BatteryLed_Write(0); // Switch led off 

    while(true)
    {
        printf("Ctr: %d, Button: %d\n", ctr, SW1_Read());
        print_mqtt("Zumo01/debug", "Ctr: %d, Button: %d", ctr, SW1_Read());

        vTaskDelay(1000);
        ctr++;
    }
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
