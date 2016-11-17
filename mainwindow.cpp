#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

//    float ganho_base;
//    float ganho_ombro;
//    float ganho_cotovelo;
//    float ganho_punho;
//    int coord_x;
//    int coord_y;
//    int coord_z;

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::set_minimuns_maximuns(void)
{
//    ui->doubleSpinBox_coordenada_x->setMinimum(0);
//    ui->doubleSpinBox_coordenada_x->setMaximum(30);
//    ui->doubleSpinBox_coordenada_y->setMinimum(0);
//    ui->doubleSpinBox_coordenada_y->setMaximum(30);
//    ui->doubleSpinBox_coordenada_z->setMinimum(0);
//    ui->doubleSpinBox_coordenada_z->setMaximum(30);


    ui->doubleSpinBox_Base->setMinimum(BAS_MIN);
    ui->doubleSpinBox_Base->setMaximum(BAS_MAX);
    ui->doubleSpinBox_graus_base->setMinimum(0);
    ui->doubleSpinBox_graus_base->setMaximum(190);
    ui->horizontalSlider_base->setMinimum(BAS_MIN);
    ui->horizontalSlider_base->setMaximum(BAS_MAX);

    ui->doubleSpinBox_Ombro->setMinimum(SHL_MIN);
    ui->doubleSpinBox_Ombro->setMaximum(SHL_MAX);
    ui->doubleSpinBox_graus_ombro->setMinimum(0);
    ui->doubleSpinBox_graus_ombro->setMaximum(135);
    ui->horizontalSlider_ombro->setMinimum(SHL_MIN);
    ui->horizontalSlider_ombro->setMaximum(SHL_MAX);

    ui->doubleSpinBox_Cotovelo->setMinimum(ELB_MIN);
    ui->doubleSpinBox_Cotovelo->setMaximum(ELB_MAX);
    ui->doubleSpinBox_graus_cotovelo->setMinimum(0);
    ui->doubleSpinBox_graus_cotovelo->setMaximum(140);
    ui->horizontalSlider_cotovelo->setMinimum(ELB_MIN);
    ui->horizontalSlider_cotovelo->setMaximum(ELB_MAX);

    ui->doubleSpinBox_Punho->setMinimum(WRI_MIN);
    ui->doubleSpinBox_Punho->setMaximum(WRI_MAX);
    ui->doubleSpinBox_graus_punho->setMinimum(0);
    ui->doubleSpinBox_graus_punho->setMaximum(195);
    ui->horizontalSlider_punho->setMinimum(WRI_MIN);
    ui->horizontalSlider_punho->setMaximum(WRI_MAX);

    ui->doubleSpinBox_Garra->setMinimum(GRI_MIN);
    ui->doubleSpinBox_Garra->setMaximum(GRI_MAX);
    ui->horizontalSlider_garra->setMinimum(GRI_MIN);
    ui->horizontalSlider_garra->setMaximum(GRI_MAX);
    ui->doubleSpinBox__cm_garra->setMinimum(0);
    ui->doubleSpinBox__cm_garra->setMaximum(30);

}

void MainWindow::on_pushButton_home_clicked()
{
    //#define HOME_POS "#0P1500#1P1500#2P1500#3P1500#4P1500T10000" //Instruções no manual, página 5.
    communicator->goToHome();
    window_base=1500;
    window_ombro=1500;
    window_cotovelo=1500;
    window_punho=1500;
    window_garra=1500;
    window_control =7;

    ui->doubleSpinBox_Base->setValue(1500);
    ui->horizontalSlider_base->setValue(1500);
    ui->doubleSpinBox_graus_base->setValue(88.94);


    ui->doubleSpinBox_Ombro->setValue(1500);
    ui->horizontalSlider_ombro->setValue(1500);
    ui->doubleSpinBox_graus_ombro->setValue(56.2500);


    ui->doubleSpinBox_Cotovelo->setValue(1500);
    ui->horizontalSlider_cotovelo->setValue(1500);
    ui->doubleSpinBox_graus_cotovelo->setValue(64.6154);

    ui->doubleSpinBox_Punho->setValue(1500);
    ui->horizontalSlider_punho->setValue(1500);
    ui->doubleSpinBox_graus_punho->setValue(97.50);

    ui->doubleSpinBox_Garra->setValue(1500);
    ui->horizontalSlider_garra->setValue(1500);
    ui->doubleSpinBox__cm_garra->setValue(24.5459);
}

void MainWindow::on_pushButton_connect_clicked()
{
    communicator->connect();
    set_minimuns_maximuns();
    on_pushButton_home_clicked();
}



void MainWindow::on_pushButton_desconnect_clicked()
{
    communicator->goToHome();
    communicator->desconnect();
}


void MainWindow::on_doubleSpinBox_Garra_valueChanged(double arg1)
{

    // GRI_MIN=1300=30mm=aberto    GRI_MAX=2400=0mm=fechado
    double mm=((GRI_MAX-arg1)/GANHO_GARRA);
//    qDebug() <<"_Garra doubleSpinBox";
//    qDebug() <<"mm: "<< mm;
//    qDebug() <<"pwm: "<< arg1;
//    qDebug() <<"";
    ui->doubleSpinBox__cm_garra->setValue(mm);
    ui->horizontalSlider_garra->setValue(arg1);
    window_garra=arg1;
    window_control=4;
    communicator->setParameters(window_control, window_base, window_ombro, window_cotovelo,
                                window_punho, window_garra);
    communicator->send();

}
void MainWindow::on_horizontalSlider_garra_sliderMoved(int position)
{
    double mm=((GRI_MAX-position)/GANHO_GARRA);
//    qDebug() <<"_Garra horizontalSlider";
//    qDebug() <<"mm: "<< mm;
//    qDebug() <<"pwm: "<< position;
//    qDebug() <<"";
    ui->doubleSpinBox__cm_garra->setValue(mm);
    ui->doubleSpinBox_Garra->setValue(position);
    window_garra=position;
    window_control=4;
    communicator->setParameters(window_control, window_base, window_ombro, window_cotovelo,
                                window_punho, window_garra);
    communicator->send();
}
void MainWindow::on_doubleSpinBox__cm_garra_valueChanged(double arg1)
{
    double pwm;
    pwm = (GRI_MAX-(GANHO_GARRA*arg1));
//    qDebug() <<"_Garra doubleSpinBox__cm";
//    qDebug() <<"mm: "<< arg1;
//    qDebug() <<"pwm: "<< pwm;
//    qDebug() <<"";
    window_garra=pwm;
    ui->horizontalSlider_garra->setValue(pwm);
    ui->doubleSpinBox_Garra->setValue(pwm);
    window_control=4;
    communicator->setParameters(window_control, window_base, window_ombro, window_cotovelo,
                                window_punho, window_garra);
    communicator->send();

}

void MainWindow::on_doubleSpinBox_Punho_valueChanged(double arg1)
{
    double graus=((WRI_MAX-arg1)/GANHO_PUNHO);
    if((arg1-window_punho)>5 || (arg1-window_punho)<-5){
//        qDebug() <<"Punho doubleSpinBox";
//        qDebug() <<"graus: "<< graus;
//        qDebug() <<"pwm: "<< arg1;
//        qDebug() <<"";
        ui->doubleSpinBox_graus_punho->setValue(graus);
        ui->horizontalSlider_punho->setValue(arg1);
        window_punho=arg1;
        window_control=3;
        communicator->setParameters(window_control, window_base, window_ombro, window_cotovelo,
                                     window_punho, window_garra);
        communicator->send();
    }

}

void MainWindow::on_horizontalSlider_punho_sliderMoved(int position)
{
    double graus=((WRI_MAX-position)/GANHO_PUNHO);
    if((position-window_punho)>5 || (position-window_punho)<-5){
//        qDebug() <<"Punho horizontalSlider";
//        qDebug() <<"graus: "<< graus;
//        qDebug() <<"pwm: "<< position;
//        qDebug() <<"";
        ui->doubleSpinBox_graus_punho->setValue(graus);
        ui->doubleSpinBox_Punho->setValue(position);
        window_punho=position;
        window_control=3;
        communicator->setParameters(window_control, window_base, window_ombro, window_cotovelo,
                                    window_punho, window_garra);
        communicator->send();
    }

}

void MainWindow::on_doubleSpinBox_graus_punho_valueChanged(double arg1)
{
    double pwm;
    pwm = (WRI_MAX-(GANHO_PUNHO*arg1));
    if((pwm-window_punho)>5 || (pwm-window_punho)<-5){
//        qDebug() <<"Punho doubleSpinBox";
//        qDebug() <<"graus: "<< arg1;
//        qDebug() <<"pwm: "<< pwm;
//        qDebug() <<"";
        window_punho=pwm;
        ui->horizontalSlider_punho->setValue(pwm);
        ui->doubleSpinBox_Punho->setValue(pwm);
        window_control=3;
        communicator->setParameters(window_control, window_base, window_ombro, window_cotovelo,
                                    window_punho, window_garra);
        communicator->send();
    }

}


void MainWindow::on_doubleSpinBox_Cotovelo_valueChanged(double arg1)
{
    double graus=((ELB_MAX-arg1)/GANHO_COTOVELO);
    if((arg1-window_cotovelo)>5 || (arg1-window_cotovelo)<-5){
//        qDebug() <<"Cotovelo doubleSpinBox";
//        qDebug() <<"graus: "<< graus;
//        qDebug() <<"pwm: "<< arg1;
//        qDebug() <<"";
        ui->doubleSpinBox_graus_cotovelo->setValue(graus);
        ui->horizontalSlider_cotovelo->setValue(arg1);
        window_cotovelo=arg1;
        window_control=2;
        communicator->setParameters(window_control, window_base, window_ombro, window_cotovelo,
                                    window_punho, window_garra);
        communicator->send();
    }


}

void MainWindow::on_horizontalSlider_cotovelo_sliderMoved(int position)
{
    double graus=((ELB_MAX-position)/GANHO_COTOVELO);
    if((position-window_cotovelo)>5 || (position-window_cotovelo)<-5){
//        qDebug() <<"Cotovelo horizontalSlider";
//        qDebug() <<"graus: "<< graus;
//        qDebug() <<"pwm: "<< position;
//        qDebug() <<"";
        window_cotovelo=position;
        ui->doubleSpinBox_Cotovelo->setValue(position);
        ui->doubleSpinBox_graus_cotovelo->setValue(graus);
        window_control=2;
        communicator->setParameters(window_control, window_base, window_ombro, window_cotovelo,
                                    window_punho, window_garra);
        communicator->send();
    }

}

void MainWindow::on_doubleSpinBox_graus_cotovelo_valueChanged(double arg1)
{
    double pwm;
    pwm = (ELB_MAX-(GANHO_COTOVELO*arg1));
    if((pwm-window_cotovelo)>5 || (pwm-window_cotovelo)<-5){
//        qDebug() <<"Punho doubleSpinBox graus";
//        qDebug() <<"graus: "<< arg1;
//        qDebug() <<"pwm: "<< pwm;
//        qDebug() <<"";
        window_cotovelo=pwm;
        ui->horizontalSlider_cotovelo->setValue(pwm);
        ui->doubleSpinBox_Cotovelo->setValue(pwm);
        window_control=2;
        communicator->setParameters(window_control, window_base, window_ombro, window_cotovelo,
                                    window_punho, window_garra);
        communicator->send();
    }
}


void MainWindow::on_doubleSpinBox_Ombro_valueChanged(double arg1)
{
    double graus=((SHL_MAX-arg1)/GANHO_OMBRO);
    if((arg1-window_ombro)>5 || (arg1-window_ombro)<-5){
//        qDebug() <<"Ombro doubleSpinBox";
//        qDebug() <<"graus: "<< graus;
//        qDebug() <<"pwm: "<< arg1;
//        qDebug() <<"";
        window_ombro=arg1;
        ui->horizontalSlider_ombro->setValue(arg1);
        ui->doubleSpinBox_graus_ombro->setValue(graus);
        window_control=1;
        communicator->setParameters(window_control, window_base, window_ombro, window_cotovelo,
                                    window_punho, window_garra);
        communicator->send();
    }

}

void MainWindow::on_horizontalSlider_ombro_sliderMoved(int position)
{

    double graus=((SHL_MAX-position)/GANHO_OMBRO);
    if((position-window_ombro)>5 || (position-window_ombro)<-5){
//        qDebug() <<"Ombro horizontalSlider";
//        qDebug() <<"graus: "<< graus;
//        qDebug() <<"pwm: "<< position;
//        qDebug() <<"";
        window_ombro=position;
        ui->doubleSpinBox_Ombro->setValue(position);
        ui->doubleSpinBox_graus_ombro->setValue(graus);
        window_control=1;
        communicator->setParameters(window_control, window_base, window_ombro, window_cotovelo,
                                    window_punho, window_garra);
        communicator->send();
    }

}

void MainWindow::on_doubleSpinBox_graus_ombro_valueChanged(double arg1)
{
    double pwm;
    pwm = (SHL_MAX-(GANHO_OMBRO*arg1));
    if((pwm-window_ombro)>5 || (pwm-window_ombro)<-5){
//        qDebug() <<"Ombro doubleSpinBox_graus";
//        qDebug() <<"graus: "<< arg1;
//        qDebug() <<"pwm: "<< pwm;
//        qDebug() <<"";
        window_ombro=arg1;
        ui->doubleSpinBox_Ombro->setValue(pwm);
        ui->horizontalSlider_ombro->setValue(pwm);
        window_control=1;
        communicator->setParameters(window_control, window_base, window_ombro, window_cotovelo,
                                    window_punho, window_garra);
        communicator->send();
    }

}


void MainWindow::on_doubleSpinBox_Base_valueChanged(double arg1)
{
    double graus=((BAS_MAX-arg1)/GANHO_BASE);
    if((arg1-window_base)>5 || (arg1-window_base)<-5){
        qDebug() <<"Base doubleSpinBox";
        qDebug() <<"graus: "<< graus;
        qDebug() <<"pwm: "<< arg1;
        qDebug() <<"";
        window_base=arg1;
        ui->horizontalSlider_base->setValue(arg1);
        ui->doubleSpinBox_graus_base->setValue(graus);
        window_control=0;
        communicator->setParameters(window_control, window_base, window_ombro, window_cotovelo,
                                    window_punho, window_garra);
        communicator->send();
    }
}


void MainWindow::on_horizontalSlider_base_sliderMoved(int position)
{
 double graus=((BAS_MAX-position)/GANHO_BASE);
    if((position-window_base)>5 || (position-window_base)<-5){
        qDebug() <<"Base doubleSpinBox";
        qDebug() <<"graus: "<< graus;
        qDebug() <<"pwm: "<< position;
        qDebug() <<"";
        window_base=position;
        ui->doubleSpinBox_Base->setValue(position);
        ui->doubleSpinBox_graus_base->setValue(graus);
        window_control=0;
        communicator->setParameters(window_control, window_base, window_ombro, window_cotovelo,
                                    window_punho, window_garra);
        communicator->send();
    }

}

void MainWindow::on_doubleSpinBox_graus_base_valueChanged(double arg1)
{
    double pwm;
    pwm = (BAS_MAX-(GANHO_BASE*arg1));
    if((pwm-window_ombro)>5 || (pwm-window_ombro)<-5){
        qDebug() <<"Base doubleSpinBox";
        qDebug() <<"graus: "<< arg1;
        qDebug() <<"pwm: "<< pwm;
        qDebug() <<"";
        window_base=pwm;
        ui->doubleSpinBox_Base->setValue(pwm);
        ui->horizontalSlider_base->setValue(pwm);
        window_control=0;
        communicator->setParameters(window_control, window_base, window_ombro, window_cotovelo,
                                    window_punho, window_garra);
        communicator->send();

    }

}



void MainWindow::on_doubleSpinBox_coordenadas_x_valueChanged(double arg1)
{
    int i=arg1;
    i=i+i;
}

void MainWindow::on_doubleSpinBox_coordenadas_y_valueChanged(double arg1)
{
    int i=arg1;
    i=i+i;
}

void MainWindow::on_doubleSpinBox_coordenadas_z_valueChanged(double arg1)
{
    int i=arg1;
    i=i+i;
}






