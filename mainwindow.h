#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "messenger.h"

#define GANHO_GARRA 36.6666666
#define GANHO_PUNHO 10.25641026
#define GANHO_COTOVELO 9.285714
#define GANHO_OMBRO 8.888888
#define GANHO_BASE 9.894736

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    messenger *communicator;

private slots:
    void on_pushButton_home_clicked();

    void on_doubleSpinBox_Garra_valueChanged(double arg1);

    void on_doubleSpinBox_Punho_valueChanged(double arg1);

    void on_doubleSpinBox_Cotovelo_valueChanged(double arg1);

    void on_doubleSpinBox_Ombro_valueChanged(double arg1);

    void on_doubleSpinBox_Base_valueChanged(double arg1);

    void on_pushButton_connect_clicked();

    void on_pushButton_desconnect_clicked();

    void on_horizontalSlider_garra_sliderMoved(int position);

    void on_horizontalSlider_punho_sliderMoved(int position);

    void on_horizontalSlider_ombro_sliderMoved(int position);

    void on_horizontalSlider_cotovelo_sliderMoved(int position);

    void on_horizontalSlider_base_sliderMoved(int position);  

    void on_doubleSpinBox_coordenadas_x_valueChanged(double arg1);

    void on_doubleSpinBox_coordenadas_y_valueChanged(double arg1);

    void on_doubleSpinBox_coordenadas_z_valueChanged(double arg1);

    void on_doubleSpinBox__cm_garra_valueChanged(double arg1);

    void on_doubleSpinBox_graus_punho_valueChanged(double arg1);

    void on_doubleSpinBox_graus_cotovelo_valueChanged(double arg1);

    void on_doubleSpinBox_graus_ombro_valueChanged(double arg1);

    void on_doubleSpinBox_graus_base_valueChanged(double arg1);

private:
    Ui::MainWindow *ui;
    void set_minimuns_maximuns(void);
    double window_base;
    double window_ombro;
    double window_cotovelo;
    double window_punho;
    double window_garra;
    int window_control;





};

#endif // MAINWINDOW_H
