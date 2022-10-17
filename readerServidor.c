#include <fcntl.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <libpq-fe.h>
// Alejandro Paez Perez UNACH

PGconn * conexion_db();
void comprobar_estadodb();
void do_exit(PGconn * conexion) ;

static PGconn * conexion;

void main()
{
    int fd, fd2, i;
    char salir;

   do    {
        char cadena[100];
        char cadena2[100];

        //empieza a recibir el mensaje.
        fd = open("FIFO1", O_RDONLY);
        read(fd, cadena, sizeof(cadena));
        if (strcmp(cadena, "offline") == 0)
        {
            puts("\n\n\nUsuario 1 --offline--");
            exit(-1);
        }
        printf("\ncliente hace: %s ", cadena);
//empieza sentencia sql        
        
        conexion = conexion_db();

        conexion = PQexec(conexion, cadena);

        close(fd);



        // proceso de mensaje enviado

        if (PQstatus(conexion) != CONNECTION_OK)
        {
            sprintf(cadena2, "Error de consulta");
        }    else {
            sprintf(cadena2, "Exitosa de consulta");
        }
       
        fd2 = open("FIFO2", O_WRONLY);
       
        
        write(fd2, cadena2, sizeof(cadena2));
        close(fd2);

        if (strcmp(cadena2, "salir") == 0)
        {
            printf("\n\nSalir del programa [s/n]:  ");
            scanf("%c", &salir);
            if (salir == 's' || salir == 'S')
            {
                write(fd2, "offline", 13);
                puts("\n\n\n--ofline--");
                exit(-1);
            }
            else if (salir == 'n' || salir == 'N')
            {
                fflush(stdin);
            }
            else
            {
                fflush(stdin);
                puts("\n\n\n\t-INVALIDO-");
            }
        }
        

        for (i = 0; i < 100; i++)
        {
            cadena[i] = '\0';
            cadena2[i] = '\0';
        }
        
   } while (1);

   printf("SALIR\n");
   return 0;
}

PGconn * conexion_db() {

    if (conexion == NULL) {
        conexion = PQconnectdb("host=127.0.0.1 port=5432 dbname=tienda user = postgres password=1234");
        printf("conexion exitosa\n");
    }

    comprobar_estadodb(conexion);

    return conexion;
}

void comprobar_estadodb() {

    if (PQstatus (conexion) == CONNECTION_BAD) {
        fprintf (stderr, "Falló la conexión a la base de datos:%s \n", PQerrorMessage (conexion));
    }

}


void do_exit(PGconn * conexion) {
    PQfinish(conexion);
    exit(1);
}