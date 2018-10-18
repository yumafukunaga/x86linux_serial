#include "init.h"
#include <stdio.h>
#include <string.h>
// open
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
// close
#include <unistd.h>
// Interface
#include <termios.h>
#include <sys/ioctl.h>

int main(int argc, char **argv){
    int fd_dev;
    struct termios config; // serial
    int baud_rate_value;
    int i, len;
    char buf[255];

    memset(&config, 0, sizeof(config));
    // 受信を有効化, ローカルライン
    config.c_cflag |= CREAD | CLOCAL;

    // パラメーターチェック
    fd_dev = select_device(argv[1]);
    if(fd_dev < 0){
        fprintf(stderr, "open error\n");
        return -1;
    }
    baud_rate_value = select_baud_rate(argv[2]);
    cfsetispeed(&config, baud_rate_value);
    cfsetospeed(&config, baud_rate_value);

    config.c_cflag |= select_data_size(argv[3]);
    config.c_cflag |= select_parity_bit(argv[4]);
    config.c_cflag |= select_stop_bit(argv[5]);

    // パラーメーター設定
    tcsetattr(fd_dev, TCSANOW, &config);
    // ポートの設定を有効にする
    ioctl(fd_dev, TCSETS, &config);

    /* シリアルポートから文字列をリードし、
     * アルファベットの小文字があれば大文字に変換して
     * シリアルポートに変換した文字列をライトする。
     */
    while(1){
        len = read(fd_dev, buf, sizeof(buf));
        if(0 < len){
            for(i = 0; i < len; i++){
                //printf("%x", buf[i]);
                printf("%c", buf[i]);
                if(0x61 <= buf[i] && buf[i] <= 0x7a){
                    buf[i] = buf[i] - 0x20;
                }
            }
            printf("\n");
        }
        write(fd_dev, buf, len);
    } 
    close(fd_dev);
    return 0;
}

