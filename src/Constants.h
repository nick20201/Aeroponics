#ifndef __CONSTANTS__H__
#define __CONSTANTS__H__

#define PUMP_OUTPUT                     11
#define SOLENOID_OUTPUT                 12
#define PURGE_OUTPUT                    13
#define PRESSURE_SENSOR                 A6 
#define OK_BUTTON       6
#define LEFT_BUTTON     7
#define RIGHT_BUTTON    8
#define UP_BUTTON       9
#define DOWN_BUTTON     10
#define DEBOUNCE_TIME   50

#define PRESSURE_OFFSET             0.483
#define DIVISOR_MPA_TO_PSI          6.895
/*#define LCD_RS      12
#define LCD_EN      11
#define LCD_D4       5
#define LCD_D5       4
#define LCD_D6       3
#define LCD_D7       2*/ 

#define DISPLAY_STATE       0
#define SYSTEM_STATE        1
#define PRESSURE_ON_STATE   2
#define PRESSURE_OFF_STATE  3
#define ON_TIME_STATE       4
#define OFF_TIME_STATE      5
#define PURGE_STATE         6
#define SOLENOID_STATE      7
#define MAX_PUMP_STATE      8
#define PUMP_ERROR_STATE    9
#define PUMP_STATS_STATE   10
#define STATE_COUNT         (PUMP_STATS_STATE + 1)     

#define DISPLAY_UPDATE_EVERY_X_MILLI    500

#define MAX_SPRAY_ON                    10
#define MAX_SPRAY_OFF                   500

#define SPRAY_ON_INC_VALUE              1
#define SPRAY_OFF_INC_VALUE             10

#define MIN_PUMP_ON_PRESSURE            20
#define MAX_PUMP_OFF_PRESSURE           120

#define MAGIC_NUMBER                    113
#define MAGIC_NUMBER_ADDR               0
#define PRESSURE_OFF_ADDR               1
#define PRESSURE_ON_ADDR                2
#define SYSTEM_ADDR                     3
#define SPRAY_ON_ADDR                   4
#define SPRAY_OFF_ADDR_HIGH_BYTE        5
#define SPRAY_OFF_ADDR_LOW_BYTE         6
#define MAX_PUMP_ON_ADDR                7

#define DEFAULT_VALUE_SYSTEM_STATE          true
#define DEFAULT_VALUE_SPRAY_ON              1
#define DEFAULT_VALUE_SPRAY_OFF             300
#define DEFAULT_VALUE_PRESSURE_ON           80
#define DEFAULT_VALUE_PRESSURE_OFF          100
#define DEFAULT_MAX_PUMP_ON_TIME_IN_SECONDS 15
#endif  //!__CONSTANTS__H__