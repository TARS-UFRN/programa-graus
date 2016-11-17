#include "messenger.h"
#include "ufrn_al5d.h"
#include <stdlib.h>

#include <QDebug>

#define HOME_POS "#0P1500#1P1500#2P1500#3P1500#4P1500T3000" //Instruções no manual, página 5.

messenger::messenger()
{



}

void messenger::setParameters(int control, double base, double ombro, double cotovelo, double punho, double garra)
{
    mes_control=control;
    mes_base=base;
    mes_ombro=ombro;
    mes_cotovelo=cotovelo;
    mes_punho=punho;
    mes_garra=garra;
}

void messenger::connect()
{
    //    ufrn_al5d arm = new ufrn_al5d();


    serial_fd = arm.abrir_porta(); // Instacia o objeto serial_fd

     // qDebug() << "Erro:"
      //qDebug() << arm.abrir_porta();


    if(serial_fd == -1) // -1 indica erro
    {
        printf("Erro abrindo a porta serial /dev/ttyS0\nAbortando o programa...");
    }
    else
    {
        printf("Porta serial /dev/ttyS0 aberta com sucesso\n");

        if(arm.configurar_porta(serial_fd) == -1)
        {
            printf("Erro inicializando a porta\n");
            close(serial_fd);
        }

    }

}

void messenger::send()
{

    comando = (char*) malloc(sizeof(char)*BUFSIZE); //BUFSIZE Declarado como 1024 no header ufrn_al5d.h

    double value_to_send;

    switch (mes_control) {
    case 0:
         value_to_send=mes_base;
        break;
    case 1:
         value_to_send=mes_ombro;
        break;
    case 2:
        value_to_send=mes_cotovelo;
        break;
    case 3:
         value_to_send=mes_punho;
        break;
    case 4:
         value_to_send=mes_garra;
        break;
    case 7:
        printf("Servo não selecionado");
        break;
    }


    memset(comando, 0, BUFSIZE);
    sprintf(comando,"#%dP%dS300",mes_control,arm.trava(mes_control,value_to_send)); //trava é uma função do ufrn_al5d.h

    arm.enviar_comando(comando,serial_fd);

    printf("%s\n",comando);

}

void messenger::goToHome()
{
    comando = (char*) malloc(sizeof(char)*BUFSIZE); //BUFSIZE Declarado como 1024 no header ufrn_al5d.h

    sprintf(comando,"%s",HOME_POS); //Imprimi a posição inicial

    //Escrevendo com teste de escrita
    if(arm.enviar_comando(comando,serial_fd)!=-1)
    {
        printf("Envio de comando com teste de envio: %s\n",HOME_POS);
    }
    else
    {
        printf("Problema no envio do comando\nAbortando o programa...");
    }
}

void messenger::desconnect()
{
    // FIM DO PROGRAMA DEMO //
    arm.fechar_porta(serial_fd);
    printf("\nAcesso a porta serial /dev/ttyS0 finalizado\n");
}

