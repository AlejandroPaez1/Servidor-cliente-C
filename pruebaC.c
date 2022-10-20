#include <fcntl.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
// Alejandro Paez Perez UNACH

void menu_clientes();
void inicio();
void menu_facturas();
void menu_articulos();
void altacliente();
void consultaClient();
void eliminarCliente();
void modifyCliente();

    // fifos
     // fifos
    int ffilas, fcolumnas;
    int fconsulta;
    int fconsulta2;

    int filasint;
    int columnasint;

    char filasq[10];
    char columnasq[10];

    char consulta [1000];
    char consulta2 [1000];
    char querys [1000];

     char id_cliente[20];
   

void main()
{
    mkfifo("FIFOFILAS", 0666);
    mkfifo("FIFOCOLUMNAS", 0666);
    mkfifo("FIFOCONSULTA", 0666);
    mkfifo("FIFOCONSULTABACK", 0666);
    consultaClient();

}


void consultaClient()
{

    do
    {
     // se envia el mensaje.
         fflush(stdin);
        fconsulta = open("FIFOCONSULTA",O_WRONLY);

        printf("\n escribe el id del cliente que quieres mostrar:\n");
        scanf("%s",&id_cliente);

        //sprintf(consulta, "SELECT * FROM clientes WHERE id_cliente = %s;", id_cliente);
        sprintf(consulta, "SELECT * FROM clientes;");

        write(fconsulta, consulta, sizeof(consulta));
        close(fconsulta);

        //recibimos mensaje del server
        fconsulta2 = open("FIFOCONSULTABACK",O_RDONLY);
        //leemos
        read(fconsulta2,querys,sizeof(querys));
        //imprimimos
     
        printf("\n la respuesta es del server: %s\n",querys);


        //checamos las cantidad de filas y columnas
    ffilas = open("FIFOFILAS",O_RDONLY);
        read(ffilas,filasq,sizeof(filasq));
    printf("el tamano de las filas son %s \n",filasq);
    close(ffilas);

    fcolumnas = open("FIFOCOLUMNAS",O_RDONLY);
        read(fcolumnas,columnasq,sizeof(columnasq));
    printf("el tamano de las columnas son %s \n",columnasq);
    close(fcolumnas);


        close(fconsulta2);


        for (int i = 0; i < 100; i++)
        {
            // reiniciar la cadena a 0
            consulta[i] = '\0';
            consulta2[i] = '\0';
        }
        fflush(stdin);

menu_clientes();
    } while (1);
}


void menu_clientes(){
    printf("\n-----menu cliente");
}