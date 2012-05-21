
/****************************************************************/
/* WARNING this file is automatically generated DO NOT EDIT IT! */
/*                                                              */
/* This file provides an interface between eTPU code and CPU    */
/* code. All references to the CAM function should be made   */
/* with information in this file. This allows only symbolic     */
/* information to be referenced which allows the eTPU code to be*/
/* optimized without effecting the CPU code.                    */
/****************************************************************/
#ifndef _ETPU_CAM_AUTO_H_
#define _ETPU_CAM_AUTO_H_

/****************************************************************
* Function Configuration Information.
****************************************************************/
#define FS_ETPU_CAM_FUNCTION_NUMBER  13 
#define FS_ETPU_CAM_TABLE_SELECT    0 
#define FS_ETPU_CAM_NUM_PARMS       0x0030 

/****************************************************************
* Host Service Request Definitions.
****************************************************************/
#define FS_ETPU_CAM_INIT        7 
#define FS_ETPU_CAM_UPDATE_WINDOW             4

/****************************************************************
* Parameter Definitions.
****************************************************************/
#define FS_ETPU_CAM_STATE_OFFSET                           0x0000
#define FS_ETPU_CAM_STATE_OLD_OFFSET                       0x000C
#define FS_ETPU_CAM_CRANK_CHANNEL_OFFSET                   0x0008
#define FS_ETPU_CAM_ANGLE_WINDOW_START_NEW_OFFSET          0x0009
#define FS_ETPU_CAM_ANGLE_WINDOW_START_HOST_OFFSET         0x000D
#define FS_ETPU_CAM_ANGLE_WINDOW_START_OFFSET              0x0011
#define FS_ETPU_CAM_ANGLE_WINDOW_WIDTH_NEW_OFFSET          0x0015
#define FS_ETPU_CAM_ANGLE_WINDOW_WIDTH_HOST_OFFSET         0x0019
#define FS_ETPU_CAM_ANGLE_WINDOW_WIDTH_OFFSET              0x001D
#define FS_ETPU_CAM_EDGE_TIME_OFFSET                       0x0005
#define FS_ETPU_CAM_EDGE_ANGLE_OFFSET                      0x0001
#define FS_ETPU_CAM_TCR2_COUNTS_PER_ENGINE_CYCLE_OFFSET    0x0021
#define FS_ETPU_CAM_ERROR_STATUS_OFFSET                    0x0004
#define FS_ETPU_CAM_ENGINE_CYCLE_0_COUNT_OFFSET            0x0025
#define FS_ETPU_CAM_ANGLE_START_COUNT_OFFSET            0x0029

/* cam_edge_polarity options */
#define FS_ETPU_CAM_FM0_RISING_EDGE 1 
#define FS_ETPU_CAM_FM0_FALLING_EDGE 0 

/* CAM Sync States */
#define FS_ETPU_CAM_SYNC_SEEK_OR_START_ANGLE       0
#define FS_ETPU_CAM_SYNC_ANGLE 1
#define FS_ETPU_CAM_SYNC_LOST  2
/* Error codes */
#define FS_ETPU_CAM_NO_ERROR         0 
#define FS_ETPU_CAM_INVALID_M1       1 
#define FS_ETPU_CAM_INVALID_M2       2 

/* cam_priority options ; required for GCT */
#define FS_ETPU_CAM_PRIORITY_DISABLE  FS_ETPU_PRIORITY_DISABLE  /* Disable */
#define FS_ETPU_CAM_PRIORITY_HIGH     FS_ETPU_PRIORITY_HIGH     /* High*/
#define FS_ETPU_CAM_PRIORITY_MIDDLE   FS_ETPU_PRIORITY_MIDDLE   /* Middle*/
#define FS_ETPU_CAM_PRIORITY_LOW      FS_ETPU_PRIORITY_LOW      /* Low*/
#endif
