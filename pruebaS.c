#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <ctype.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdarg.h>
#include <libpq-fe.h>

// Alejandro Paez Perez UNACH

PGconn *conexion_db();
void comprobar_estadodb();
void do_exit(PGconn *conexion);
static PGconn *conexion;

void main()
{
    // fifos
    int ffilas, fcolumnas;
    int fconsulta;
    int fconsulta2;

    int filasint;
    int columnasint;

    char filasq[10]= {0};
    char columnasq[10]= {0};

    char consulta [1000];
    char consulta2 [1000];
    char querys [1000];
    char filas[100];

    do
    {
//PARA CONSULTAR DATOS
     fconsulta = open("FIFOCONSULTA", O_RDONLY);
     read(fconsulta,consulta, sizeof(consulta));
     printf("la consulta es:\n  %s\n",consulta);


     //if (consulta == NULL){
        //printf("no trae nada la consulta\n");
     //}else{
        conexion = conexion_db();
        PGresult * respC = PQexec(conexion, consulta);       
        
//SACAR EL DATO DE FILAS Y COLUMNAS
        filasint = PQntuples(respC);
        columnasint = PQnfields (respC);

//CONVERTIMOS A CHAR LOS DATOS ENTEROS

    sprintf(filasq, "%d", filasint);
    sprintf(columnasq, "%d", columnasint);

        printf("esta son las filas : %s \n",filasq);
        printf("este es el la columnas con pnfield: %s \n",columnasq);

    
//IMPRIMIR DATOS 
    fconsulta2 = open ("FIFOCONSULTABACK",O_WRONLY);
            for (int i = 0; i < PQntuples(respC); i++){ //filas
               for (int j = 0; j < PQnfields(respC); j++){//columnas

                        sprintf(querys,(PQgetvalue(respC,i,j)));
                        printf("%s | ",querys);
                        write(fconsulta2,querys,sizeof(querys));
                        
                  }
                  printf("\n");
            //}
                  close(fconsulta2);


     }


   ffilas = open("FIFOFILAS",O_WRONLY);
    write(ffilas,filasq,sizeof(filasq));
    close(ffilas);


    fcolumnas = open("FIFOCOLUMNAS",O_WRONLY);
    write(fcolumnas,columnasq,sizeof(columnasq));
    close(fcolumnas); 
     



        // validacion si la inserccion es correcta
        if (PQstatus(conexion) != CONNECTION_OK)
        {
            sprintf(consulta2, "Error de consulta valores invalido\n");
        }
        else
        {
            sprintf(consulta2, "Query exitoso\n");
        }

        fconsulta2 = open("FIFO2", O_WRONLY);
        write(fconsulta2, consulta2, sizeof(consulta2));
        close(fconsulta2);

        // limpiar la cadena para que no tires basura
        for (int i = 0; i < 100; i++)
        {
            consulta[i] = '\0';
            consulta2[i] = '\0';
        }

    } while (1);

    printf("SALIR\n");

    return 0;
}

// metodo conexion
PGconn *conexion_db()
{

    if (conexion == NULL)
    {
        conexion = PQconnectdb("host=127.0.0.1 port=5432 dbname=tienda user = postgres password=1234");
        printf("conexion exitosa\n");
    }
    comprobar_estadodb(conexion);
    return conexion;
}

void comprobar_estadodb()
{
    if (PQstatus(conexion) == CONNECTION_BAD)
    {
        fprintf(stderr, "Falló la conexión a la base de datos:%s \n", PQerrorMessage(conexion));
    }
}

void do_exit(PGconn *conexion)
{
    PQfinish(conexion);
    exit(1);
}
