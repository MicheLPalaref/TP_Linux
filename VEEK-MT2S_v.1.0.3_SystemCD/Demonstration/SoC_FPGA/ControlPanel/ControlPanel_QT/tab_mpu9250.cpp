#include "dialog.h"
#include "ui_dialog.h"
#include <stdio.h>
#include <QPainter>
#include <QtCore>


// QRect: http://qt-project.org/doc/qt-5.0/qtcore/qrect.html
// QPoint: http://qt-project.org/doc/qt-5.0/qtcore/qpoint.html





void Dialog::TabMpu9250Polling(FPGA *fpag){

    float ax, ay, az, gx, gy, gz, mx, my, mz;
    char szText[64];


    fpga->getMotion9(&ax, &ay, &az, &gx, &gy, &gz, &mx, &my, &mz);


    // accelerometer x,y,z
    sprintf(szText, "%.3f\r\n", ax);
    ui->label_AX->setText(szText);
    sprintf(szText, "%.3f\r\n", ay);
    ui->label_AY->setText(szText);
    sprintf(szText, "%.3f\r\n", az);
    ui->label_AZ->setText(szText);

    // gyroscopes x,y,z
    sprintf(szText, "%.3f\r\n", gx);
    ui->label_GX->setText(szText);
    sprintf(szText, "%.3f\r\n", gy);
    ui->label_GY->setText(szText);
    sprintf(szText, "%.3f\r\n", gz);
    ui->label_GZ->setText(szText);

    // magnetometer x,y,z
    sprintf(szText, "%.3f\r\n", mx);
    ui->label_MX->setText(szText);
    sprintf(szText, "%.3f\r\n", my);
    ui->label_MY->setText(szText);
    sprintf(szText, "%.3f\r\n", mz);
    ui->label_MZ->setText(szText);

}
