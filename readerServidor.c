#include <fcntl.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <libpq-fe.h>
// Alejandro Paez Perez UNACH

PGconn *conexion_db();
void comprobar_estadodb();
void do_exit(PGconn *conexion);

static PGconn *conexion;

void main()
{
    
    int fd, fd2, i, fdOpcion;
    int filas,columnas;
    char salir;
    int opcionhear;
    char opcionf[10];
    int opcioncase;
    PGresult *resultado;

    do
    {
        char cadena[100];
        char cadena2[100];

        // empieza a recibir el mensaje.
        fd = open("FIFO1", O_RDONLY);
        read(fd, cadena, sizeof(cadena));
        printf("\nSentencia sql es:\n %s \n", cadena);
        // empieza sentencia sql
        conexion = conexion_db();
        conexion = PQexec(conexion, cadena);

/* 
            resultado=PQexec(conexion,cadena);
        printf("Filas:%d, Columnas:%d \n",PQntuples(resultado),PQnfields(resultado));
        if(resultado != NULL){
            printf("Imprimiendo los valores de la tabla Estudiante\n");
            for (i = 0; i < PQntuples(resultado); i++){ //filas
               for (int j = 0; j < PQnfields(resultado); j++){//columnas
                    printf("%s\t",PQgetvalue(resultado,i,j));
                        fd2 = open("FIFO2", O_WRONLY);
                        write(fd2, filc, sizeof(filc));
                        write(fd2, colc, sizeof(colc));
                        close(fd2);
                  }
                  printf("\n");
              }
          }
 */
        close(fd);
        // validacion si la inserccion es correcta
        if (PQstatus(conexion) != CONNECTION_OK)
        {
            sprintf(cadena2, "Error de consulta valores invalido\n");
        }
        else
        {
            sprintf(cadena2, "Query exitoso\n");
        }

        fd2 = open("FIFO2", O_WRONLY);
        write(fd2, cadena2, sizeof(cadena2));
        close(fd2);

        // limpiar la cadena para que no tires basura
        for (i = 0; i < 100; i++)
        {
            cadena[i] = '\0';
            cadena2[i] = '\0';
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