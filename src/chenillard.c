//il faut allumer puis supprimer les led1 à led9
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>


int main (void)
{
    char filename[50];
    int fd[10];
    int i;

    for (i=0;i<10;i++)
    {   //ouverture des fichiers brightness pour les leds 1 à 9
        sprintf(filename,"/sys/class/leds/fpga_led%d/brightness",i);
        fd[i] = open(filename,O_WRONLY);
    }
    

    while(1)
    {
        for(i=0;i<10;i++)
        {
            //allume en ecrivant "1" dans le fichier brightness
            write(fd[i],"1",1);
            usleep(100000);
        }
        for(i=0;i<10;i++)
        {
            //eteint en ecrivant "0" dans le fichier brightness
            write(fd[i],"0",1);
            usleep(100000);
        }
    }
    
}

