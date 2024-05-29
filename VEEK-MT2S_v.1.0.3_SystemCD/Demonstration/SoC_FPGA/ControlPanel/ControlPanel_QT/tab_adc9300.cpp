#include "dialog.h"
#include "ui_dialog.h"
#include <stdio.h>
#include <QPainter>
#include <QtCore>


void Dialog::TabAdc9300Polling(FPGA *fpag){

    uint16_t light0, light1;
    char szText[64];


    if (fpga->getLight(&light0, &light1)){
        sprintf(szText, "%d\r\n", light0);
        ui->label_VISIBLE_IR->setText(szText);
        sprintf(szText, "%d\r\n", light1);
        ui->label_IR->setText(szText);
    }else{
        sprintf(szText, "NA\r\n");
        ui->label_VISIBLE_IR->setText(szText);
        ui->label_IR->setText(szText);
    }


}
