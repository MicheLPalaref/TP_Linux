#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdint.h>
#include <unistd.h>


int main (void)
{
    uint32_t * p;
    int i;
    int fd = open("/dev/mem", O_RDWR);
    p = (uint32_t*)mmap(NULL, 4, PROT_WRITE|PROT_READ, MAP_SHARED,fd, 0xFF203000);
    //*p = (1<<9);//Allume la 8ieme led
    //*p = 8; //Allume (1000) la 4ieme led
    while(1)
    {
    for(i=1;i<10;i++)
    {
        *p=(1<<i);
        usleep(100000);
    }
    }

}