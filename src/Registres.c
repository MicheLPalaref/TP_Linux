#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdint.h>


int main (void)
{
    uint32_t * p;
    int fd = open("/dev/mem", O_RDWR);
    p = (uint32_t*)mmap(NULL, 4, PROT_WRITE|PROT_READ, MAP_SHARED,fd, 0xFF203000);
    *p = (1<<8);//Allume la 8ieme led
    //*p = 8; //Allume (1000) la 4ieme led

}