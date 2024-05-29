# TP_Linux

Preparation de la carte SD:

Preparation effectuee par M. Fiack sur Linux.

Preparation de l'environnement de developpement:

Installation d'ORACLE VM VirtualBox:
![alt text](image.png)

/!\ Ne pas oublier de changer le chemin d'accès pour ne pas se retrouver dans les dossiers partages de M.BARES:
![alt text](image-12.png)

Parametrer la connection ethernet de la carte pour la lier a notre VM:

On utilise TeraTerm lié en serial port pour visualier le Linux de notre carte.
Au demarage de la carte, avec la commande "ls" on a :
![alt text](image-2.png)

on entre la commande 
```C
vim /etc/network/interfaces
```
on supprime le contenu présent puis on écrit 
```C
auto eth0
iface eth0 inet dhcp
allow-hotplug eth0
```

Quand c’est terminé, on appui sur la touche Echap pour revenir en mode command
puis on entre la commande
```C
:wp
``` 
avant d'appuyer sur entrée pour sauvegarder et quitter vim.

suivi de la commande de redémarrage 
```C
sudo reboot
```

Après le reboot, on peut alors récupérer l'IP de la carte avec la commande:
```C
ip a
```
![alt text](image-5.png)

Une fois l'IP de la carte récupérée on peut l'utiliser pour envoyer les programmes developpes depuis notre VM vers la carte : 

![alt text](image-4.png)

Une fois le fichier Hello transféré, si on retappe la commande "ls" on obtient:
![alt text](image-3.png)

le fichier hello a bien été transféré, on peut l'exécuter sur la carte avec la commande TeraTerm
```C
./hello
```
Alors même que le fichier a été créé sur la VM:

![alt text](image-6.png)


# 1.4.4 Accès au matériel

![alt text](image-7.png)

Les commandes suivantes:
Allument la led1,
Eteignent la led1
Allument la led2
Allument la led1

# 1.4.5 Chenillard (Et oui, encore !)

On va créer un fichier Chenillard.c dans la VM:
```C
//il faut allumer puis supprimer les led1 à led9
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main (void)
{
    char filename[50];//Contient le chemin du fichier brightness des leds
    int fd[10];//Tableau de 10 chemins (un chemin pour chaque led de 1 à 9)
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
```

Puis on charge le code dans notre VM et on l'envoi sur notre carte:
![alt text](image-8.png)

Sur TeraTerm (notre carte), on vérifie la présence du nouveau code et on le lance:
![alt text](image-9.png)

# 2  Modules kernel

# 2.1 Accès aux registres

On créé un chenillard en utilisant mmap:
```C
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
```

On met à jour le code sur la VM et on l'envoi sur le SOC:
![alt text](image-11.png)

Sur le SOC:

![alt text](image-10.png)


Pose 2 problèmes:

Pas de possibilité d'interruption.

Pas de portabilité (l'adresse est marquée en dure. Doit rechanger le code en dur si l'adresse change. Exemple : sur un autre appareil l'adresse des GPIO peut etre differente)

# 2.2 Compilation de module noyau sur la VM

Installation linux-headers-amd64:

![alt text](image-13.png)

Installation BC:

![alt text](image-14.png)

En installant le dossier téléchargé depuis Moodle, on obtient:

![alt text](image-16.png)

En appliquant la commande Make on obtient:

![alt text](image-17.png)

on applique 
```C
sudo insmod hello.ko
sudo dmesg
```
![alt text](image-19.png)
```C
sudo rmmod hello
sudo dmesg
```
![alt text](image-20.png)

# 2.3 CrossCompilation de modules noyau

# 2.3.0 Récupération du Noyau Terasic (c’est déjà fait dans la VM !)
Tout est dit dans le titre

# 2.3.1 Préparation de la compilation

Le chemin vers les compilateurs est
```C
/usr/bin/arm-linux-gnueabihf-gcc
```
![alt text](image-21.png)


# 2.3.2 Récupéreation de la configuration actuelle du noyau

Le fichier config.gz du noyau que l'on souhaite récupérer sur trouve sur le SOC à l'adresse /proc/

On désire le copier sur notre VM. Puisque notre VM est cachée on ne peut pas copier depuis le SOC. Il faut donc le copier depuis la VM.


```C
//On commence par se positionner dans le bon dossier de la VM:
cd linux-socfpga/ 

//Puis on recopie le dossier souhaité depuis l'adresse IP de notre SOC vers le dossier de la VM où nous nous trouvons
//scp AdresseIP_SOC: Chemin_Dossier_Souhaité .
scp root@192.168.88.24:/proc.config.gz .

//Après avoir récupérer notre fichier config.gz, on applique la commande pour le dézipper:
gunzip config.gz

//Puis on rename le fichier config en config.config:
mv config .config

//Si on utilise la commande "ls" on ne trouve pas le fichier puisque les .config n'apparaissent pas. On peut en revanche s'assurer de sa présence avec la commande "ls -a"

//On créé des variables d'environnement qui sont propres a notre VM qui se perdent à chaque fois qu'on ferme un terminal sans sauvegarde.
//on termine par un "-" afin de pouvoir compléter les noms par les différents outils de compilation avec par exemple CROSS_COMPILE=/usr/bin/arm-linux-gnueabihf-gcc 
export CROSS_COMPILE=/usr/bin/arm-linux-gnueabihf-
export ARCH=arm

//On prépare les fichiers pour le démarage noyau et on génère les scripts nécessaire au démarage du noyau
make prepare
make scripts
```

# 2.3.3 Hello World

On se place dans :
```C
cd src/Moodle_TP2/

vim Makefile
vim hello.c
ls
make//ne fonctionne pas car dans un dossier partagé
cd ..//On remonte d'un cran
cp -r Moodle_TP2/ .. //on créé un nouveau dossier 
cd ..
cd Moodle_TP2/
ls
make
ls
scp hello.ko root@192.168.88.24://mise a jour du code hello.ko
vim hello.c//version affichée toujours ancienne
cp ../src/Moodle_TP2/hello.c .//on recopie
vim hello.c//version modifée


```

