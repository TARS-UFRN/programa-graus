#ifndef MESSENGER_H
#define MESSENGER_H
#include "ufrn_al5d.h"


class messenger
{
public:
    messenger();
    void setParameters(int control, double base, double ombro, double cotovelo, double punho, double garra);
    void connect(void);
    void desconnect(void);
    void send(void);
    void goToHome(void);

    float ganho_base;
    float ganho_ombro;
    float ganho_cotovelo;
    float ganho_punho;
    float ganho_garra;
    float coord_x;
    float coord_y;
    float coord_z;

private:

    ufrn_al5d arm;
    int serial_fd;
    char *comando;
    double mes_base;
    double mes_ombro;
    double mes_cotovelo;
    double mes_punho;
    double mes_garra;
    int mes_control; // nada=7, base=0,ombro=1, contovelo=2, punho=3, garra=4

};

#endif // MESSENGER_H
