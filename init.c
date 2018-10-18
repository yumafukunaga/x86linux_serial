#include "init.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// open
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
// Interface
#include <termios.h>
#include <sys/ioctl.h>

#define DEV_TTY "/dev/tty"
#define DEFAULT_PATH "/dev/ttyS0"
#define PATH_LENGTH 256
#define STR_MAX 5

/*
 * デバイス
 * デフォルト値 /dev/ttyS0
 * 指定できる値 /dev/tty*
 * /dev/tty* 以降5文字まで
 */
int select_device(char *device_name){
    char path[PATH_LENGTH];

    strncat(path, DEV_TTY, strlen(DEV_TTY));
    if(device_name != NULL){
        strncat(path, device_name, STR_MAX);
    }else{
        memset(path, '\0', strlen(path));
        strcpy(path, DEFAULT_PATH);
    }
    printf("path : %s\n", path);
    return(open(path, O_RDWR));
}


/*
 * ボーレート
 * デフォルト値 115200
 * 指定できる値 9600, 38400, 115200
 */
int select_baud_rate(char *char_value){
    int value;
    if(char_value != NULL){
        value = strtol(char_value, NULL, 10);
        if(value == 9600){
            printf("baud rate : %d\n", value);
            return(B9600);
        }else if(value == 38400){
            printf("baud rate : %d\n", value);
            return(B38400);
        }
    }
    printf("baud rate : 115200\n");
    return(B115200);
}


/*
 * データ幅
 * デフォルト値 8
 * 指定できる値 7, 8
 */
int select_data_size(char *data_size){
    if((data_size != NULL) && !strcmp(data_size, "7")){
        printf("data size : 7\n");
        return(CS7);
    }
    printf("data size : 8\n");
    return(CS8);
}


/*
 * パリティ有無
 * デフォルト値 none
 * 指定できる値 odd, even
 */
int select_parity_bit(char *parity){
    if(parity != NULL){
        if(!strcmp(parity, "even")){
            printf("parity bit : even\n");
            return(PARENB);
        }else if(!strcmp(parity, "odd")){
            printf("parity bit : odd\n");
            return(PARENB | PARODD);
        }
    }
    printf("parity bit : none\n");
    return 0;
}


/* ストップビット幅
 * デフォルト値 1
 * 指定できる値 1, 2
 */
int select_stop_bit(char *stop_bit){
    if(stop_bit != NULL && !strcmp(stop_bit, "2")){
        printf("stop bit : 2\n");
        return(CSTOPB);
    }
    printf("stop bit : 1\n");
    return 0;
}

