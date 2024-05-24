# TP_Linux

Preparation de la carte SD:

Preparation effectuee par M. Fiack sur Linux.

Preparation de l'environnement de developpement:

Installation d'ORACLE VM VirtualBox:
![alt text](image.png)

/!\ Ne pas oublier de changer le chemin d'accès pour ne pas se retrouver dans les dossiers partages de M.BARES:
![alt text](image-1.png)

Parametrer la connection ethernet:
Au demarage de la carte, on a :
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

suivi de la commande
```C
sudo reboot
```
