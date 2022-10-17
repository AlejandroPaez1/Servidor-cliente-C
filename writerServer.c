#include <fcntl.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
// Alejandro Paez Perez UNACH

void main()
{
    printf("\n...esperando");
    int fd, fd2, i;
    char salir;
    // creo fichero para mandar mensaje
    mkfifo("FIFO1", 0666);
    mkfifo("FIFO2", 0666);

    do
    {
        char cadena[100];
        char cadena2[100];

        // se envia el mensaje.
        fd = open("FIFO1", O_WRONLY);
        printf("\nPersona 1 (escribir mensaje): ");
        gets(cadena);
        if (strcmp(cadena, "salir") == 0)
        {
            printf("\n\nSalir del programa [s/n]:  ");
            scanf("%c", &salir);
            if (salir == 's' || salir == 'S')
            {
                write(fd, "offline", 13);
                puts("\n\n\n--offline--");
                exit(-1);
            }
            else if (salir == 'n' || salir == 'N')
            {
                fflush(stdin);
            }
            else
            {
                puts("\n\t\t-ERROR-");
                fflush(stdin);
            }
        }
        puts("...wait...");
        write(fd, cadena, sizeof(cadena));
        close(fd);

        // empieza a recibir el mensaje
        fd2 = open("FIFO2", O_RDONLY);
        read(fd2, cadena2, sizeof(cadena2));
        if (strcmp(cadena2, "offline") == 0)
        {
            puts("\n\n\nUsuario 2 --offline--");
            exit(-1);
        }
        printf("\nPersona 2 su mensaje es:  %s ", cadena2);
        close(fd2);

        for (i = 0; i < 100; i++)
        {
            //reiniciar la cadena a 0
            
            cadena[i] = '\0';
            cadena2[i] = '\0';
        }

    } while (1);
}
