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
int fd, fd2, fdOpcion, i;
char salir;

void main()
{
    inicio();
    mkfifo("FIFO1", 0666);
    mkfifo("FIFO2", 0666);
    mkfifo("fifopcion", 0666);
}

void inicio()
{

    int opcion = 0;
    do
    {

        printf("\n|-----------------|");
        printf("\n|    * Incio *    |");
        printf("\n|-----------------|");
        printf("\n| 1. Clientes     |");
        printf("\n| 2. Facturas     |");
        printf("\n| 3. Articulos    |");
        printf("\n| 4. Salir        |");
        printf("\n|-----------------|");
        printf("\n\n Escoja una opcion: ");
        scanf("%d", &opcion);

        switch (opcion)
        {
        case 1:
            menu_clientes();
            printf("clientes");
            break;
        case 2:
            printf("Facturas");
            menu_facturas();
            break;
        case 3:
            menu_articulos();
            printf("Articulos");
            break;
        case 4:
            printf("Cerrado correctamente\n");
            exit(-1);
            break;
        default:
            printf("\nOpcion no disponible\n");
            break;
        }
    } while (opcion != 4);
}

void menu_clientes()
{
    int opcion = 0;
    do
    {
        printf("\n|----------------------------------------------|");
        printf("\n|             * Submenu clientes *             |");
        printf("\n|----------------------------------------------|");
        printf("\n| 1.AltaCliente         | 4. Modificar cliente |");
        printf("\n| 2.Consulta cliente    | 5. Mostrar tabla     |");
        printf("\n| 3.Eliminacion cliente | 6. Regresar          |");
        printf("\n|-----------------------|----------------------|");
        printf("\n\n Escoja una opcion: ");
        scanf("%d", &opcion);

        switch (opcion)
        {
        case 1:
            printf("menu alta cliente");
            altacliente();
            break;
        case 2:
            printf("consulta cliente");
            consultaClient();
            break;
        case 3:
            printf("Eliminacion cliente");
            eliminarCliente();
            break;
        case 4:
            printf("modifcar cliente");
            modifyCliente();
            break;
        case 5:
            printf("mostrar tabla");
            break;
        case 6:
            inicio();
            break;
        default:
            printf("\nOpcion no disponible\n");
            break;
        }
    } while (opcion != 6);
}

void altacliente()
{
    char nombre[50];
    char apellido[50];
    char rfc[50];
    char direccion[50];
    char edad[10];
    char pais[50];
    char telefono[11];
    char opcionf[3] = "1";

    char cadena[100];
    char cadena2[100];
    do
    {

        // se envia el mensaje.
        fflush(stdin);
        fd = open("FIFO1", O_WRONLY);
        /*         /// para el menu del server
                fdOpcion = open("fifopcion",O_WRONLY);
                write(fdOpcion, opcionf, sizeof(opcionf));
         */

        puts("\nescribe el nombre del cliente: ");
        printf("el nombre es:\n");
        scanf("%s", &nombre);

        printf("el apellido es:\n");
        scanf("%s", &apellido);

        printf("el rfc es:\n");
        scanf("%s", &rfc);

        printf("el direccion es:\n");
        scanf("%s", &direccion);

        printf("el edad es:\n");
        scanf("%s", &edad);

        printf("el pais es:\n");
        scanf("%s", &pais);

        printf("el telefono es:\n");
        scanf("%s", &telefono);

        sprintf(cadena, "insert into clientes values (DEFAULT, '%s', '%s', '%s', '%s', '%s', '%s', '%s');", nombre, apellido, rfc, direccion, edad, pais, telefono);
        // mandamos la sentencia sql
        write(fd, cadena, sizeof(cadena));
        close(fd);

        // empieza a recibir el mensaje
        fd2 = open("FIFO2", O_RDONLY);
        // lee lo que le manda el servidor
        read(fd2, cadena2, sizeof(cadena2));
        // imprime lo que pasa
        printf("\nServidor dice:  %s ", cadena2);
        close(fd2);

        for (i = 0; i < 100; i++)
        {
            // reiniciar la cadena a 0
            cadena[i] = '\0';
            cadena2[i] = '\0';
        }
        fflush(stdin);

        menu_clientes();
    } while (1);
}

void consultaClient()
{

    char cadena[100];
    char cadena2[100];
    char id_cliente[10];

    do
    {

        // se envia el mensaje.
        fflush(stdin);
        fd = open("FIFO1", O_WRONLY);
        printf("\n escribe el id del cliente que quieres mostrar:\n");
        scanf("%s", &id_cliente);

        sprintf(cadena, "SELECT * FROM clientes WHERE id_cliente = %s;", id_cliente);
        write(fd, cadena, sizeof(cadena));
        close(fd);

        // empieza a recibir el mensaje
        fd2 = open("FIFO2", O_RDONLY);
        // lee lo que le manda el servidor
        read(fd2, cadena2, sizeof(cadena2));

        for (i = 0; i < 100; i++)
        {
            // reiniciar la cadena a 0
            cadena[i] = '\0';
            cadena2[i] = '\0';
        }
        fflush(stdin);
        menu_clientes();

    } while (1);
}

void eliminarCliente()
{
    char id_cliente[10];
    char cadena[100];
    char cadena2[100];
    do
    {
        // se envia el mensaje.
        fflush(stdin);
        fd = open("FIFO1", O_WRONLY);
        puts("\nescribe el ID del cliente a eliminar: ");
        printf("el ID es:\n");
        scanf("%s", &id_cliente);

        sprintf(cadena, "DELETE FROM clientes WHERE id_cliente = %s", id_cliente);
        // mandamos la sentencia sql
        write(fd, cadena, sizeof(cadena));
        close(fd);

        // empieza a recibir el mensaje del server
        fd2 = open("FIFO2", O_RDONLY);
        // lee lo que le manda el servidor
        read(fd2, cadena2, sizeof(cadena2));
        // imprime lo que pasa
        printf("\nServidor dice:  %s ", cadena2);
        close(fd2);
        fflush(stdin);

        for (i = 0; i < 100; i++)
        {
            // reiniciar la cadena a 0
            cadena[i] = '\0';
            cadena2[i] = '\0';
        }

        fflush(stdin);
        sleep(10);
        menu_clientes();
    } while (1);
}

void modifyCliente()
{
    char id_cliente[10];
    char cadena[100];
    char cadena2[100];

    char nombre[50];
    char apellido[50];
    char rfc[50];
    char direccion[50];
    char edad[10];
    char pais[50];
    char telefono[11];
    int opcion;
    do
    {
        // se envia el mensaje.
        fflush(stdin);
        fd = open("FIFO1", O_WRONLY);
        printf(" Que id de Cliente quieres editar:\n ");
        scanf("%s", &id_cliente);
        do
        {
            printf("\n|----------------|");
            printf("\n| editar cliente |");
            printf("\n|----------------|");
            printf("\n| 1. Nombre      |");
            printf("\n| 2. Apellidos   |");
            printf("\n| 3. RFC         |");
            printf("\n| 4. Direccion   |");
            printf("\n| 5. Edad        |");
            printf("\n| 6. telefono    |");
            printf("\n| 7. regresar    |");
            printf("\n|----------------|");
            printf("\n\n Escoja una opcion: ");
            scanf("%d", &opcion);

            switch (opcion)
            {
            case 1:
                printf("el nuevo nombre es:\n");
                scanf("%s", &nombre);

                sprintf(cadena, "UPDATE clientes SET nombre = '%s' WHERE id_cliente = %s", nombre, id_cliente);
                // mandamos la sentencia sql
                write(fd, cadena, sizeof(cadena));
                close(fd);

                // empieza a recibir el mensaje del server
                fd2 = open("FIFO2", O_RDONLY);
                // lee lo que le manda el servidor
                read(fd2, cadena2, sizeof(cadena2));
                // imprime lo que pasa
                printf("\nServidor dice:  %s ", cadena2);
                close(fd2);
                fflush(stdin);

                for (i = 0; i < 100; i++)
                {
                    // reiniciar la cadena a 0
                    cadena[i] = '\0';
                    cadena2[i] = '\0';
                }

                fflush(stdin);
                sleep(10);
                menu_clientes();
                break;

            case 2:
                printf("\n Escribe el Apellido  :\n");
                scanf("%s", &apellido);

                sprintf(cadena, "UPDATE clientes SET apellidos = '%s' WHERE id_cliente = %s", apellido, id_cliente);
                // mandamos la sentencia sql
                write(fd, cadena, sizeof(cadena));
                close(fd);

                // empieza a recibir el mensaje del server
                fd2 = open("FIFO2", O_RDONLY);
                // lee lo que le manda el servidor
                read(fd2, cadena2, sizeof(cadena2));
                // imprime lo que pasa
                printf("\nServidor dice:  %s ", cadena2);
                close(fd2);
                fflush(stdin);

                for (i = 0; i < 100; i++)
                {
                    // reiniciar la cadena a 0
                    cadena[i] = '\0';
                    cadena2[i] = '\0';
                }

                fflush(stdin);
                menu_clientes();
                break;

            case 3:
                printf("\n Escribe el RFC :\n");
                scanf("%s", &rfc);

                sprintf(cadena, "UPDATE clientes SET rfc = '%s' WHERE id_cliente = %s", rfc, id_cliente);
                // mandamos la sentencia sql
                write(fd, cadena, sizeof(cadena));
                close(fd);

                // empieza a recibir el mensaje del server
                fd2 = open("FIFO2", O_RDONLY);
                // lee lo que le manda el servidor
                read(fd2, cadena2, sizeof(cadena2));
                // imprime lo que pasa
                printf("\nServidor dice:  %s ", cadena2);
                close(fd2);
                fflush(stdin);

                for (i = 0; i < 100; i++)
                {
                    // reiniciar la cadena a 0
                    cadena[i] = '\0';
                    cadena2[i] = '\0';
                }

                fflush(stdin);
                menu_clientes();
                break;

            case 4:
                printf("\n Escribe la nueva Direccion :\n");
                scanf("%s", &direccion);

                sprintf(cadena, "UPDATE clientes SET direccion = '%s' WHERE id_cliente = %s", direccion, id_cliente);
                // mandamos la sentencia sql
                write(fd, cadena, sizeof(cadena));
                close(fd);

                // empieza a recibir el mensaje del server
                fd2 = open("FIFO2", O_RDONLY);
                // lee lo que le manda el servidor
                read(fd2, cadena2, sizeof(cadena2));
                // imprime lo que pasa
                printf("\nServidor dice:  %s ", cadena2);
                close(fd2);
                fflush(stdin);

                for (i = 0; i < 100; i++)
                {
                    // reiniciar la cadena a 0
                    cadena[i] = '\0';
                    cadena2[i] = '\0';
                }

                fflush(stdin);

                menu_clientes();
                break;

            case 5:
                printf("\n Escribe la nueva edad  :\n");
                scanf("%s", &edad);

                sprintf(cadena, "UPDATE clientes SET edad = '%s' WHERE id_cliente = %s", edad, id_cliente);
                // mandamos la sentencia sql
                write(fd, cadena, sizeof(cadena));
                close(fd);

                // empieza a recibir el mensaje del server
                fd2 = open("FIFO2", O_RDONLY);
                // lee lo que le manda el servidor
                read(fd2, cadena2, sizeof(cadena2));
                // imprime lo que pasa
                printf("\nServidor dice:  %s ", cadena2);
                close(fd2);
                fflush(stdin);

                for (i = 0; i < 100; i++)
                {
                    // reiniciar la cadena a 0
                    cadena[i] = '\0';
                    cadena2[i] = '\0';
                }

                fflush(stdin);

                menu_clientes();
                break;

            case 6:
                printf("\n Escribe el Telefono nuevo  :\n");
                scanf("%s", &telefono);

                sprintf(cadena, "UPDATE clientes SET telefono = '%s' WHERE id_cliente = %s", telefono, id_cliente);
                // mandamos la sentencia sql
                write(fd, cadena, sizeof(cadena));
                close(fd);

                // empieza a recibir el mensaje del server
                fd2 = open("FIFO2", O_RDONLY);
                // lee lo que le manda el servidor
                read(fd2, cadena2, sizeof(cadena2));
                // imprime lo que pasa
                printf("\nServidor dice:  %s ", cadena2);
                close(fd2);
                fflush(stdin);

                for (i = 0; i < 100; i++)
                {
                    // reiniciar la cadena a 0
                    cadena[i] = '\0';
                    cadena2[i] = '\0';
                }

                fflush(stdin);

                menu_clientes();
                break;
            case 7:
                menu_clientes();
                break;
            default:
                printf("\nOpcion no disponible\n");
                break;
            }
        } while (opcion != 7);

    } while (1);
}

void menu_facturas()
{
    int opcion = 0;
    do
    {
        printf("\n|----------------------------------------------|");
        printf("\n|             * Submenu Facturas *             |");
        printf("\n|----------------------------------------------|");
        printf("\n| 1.insertar factura | 4. Regresar menu inicio |");
        printf("\n| 2.Actualizar       | 5. ...          |");
        printf("\n| 3.Eliminar factura | 6. ...          |");
        printf("\n|--------------------|-----------------|");
        printf("\n\n Escoja una opcion: ");
        scanf("%d", &opcion);

        switch (opcion)
        {
        case 1:
            printf("Insertar facturas");
            break;
        case 2:
            printf("Actualizar facturas");
            break;
        case 3:
            printf("Eliminacion facturas");
            break;
        case 4:
            printf("regresando");
            inicio();
            break;

        default:
            printf("\nOpcion no disponible\n");
            break;
        }
    } while (opcion != 4);
}

void menu_articulos()
{
    int opcion = 0;
    do
    {
        printf("\n|----------------------------------------------|");
        printf("\n|             * Submenu articulos *             |");
        printf("\n|----------------------------------------------|");
        printf("\n| 1.insertar articulo   | 4. Regresar menu inicio |");
        printf("\n| 2.Actualizar articulo | 5. ...     |");
        printf("\n| 3.Eliminar articulo   | 6. ...     |");
        printf("\n|-----------------------|------------|");
        printf("\n\n Escoja una opcion: ");
        scanf("%d", &opcion);

        switch (opcion)
        {
        case 1:
            printf("insertar articulos");
            break;
        case 2:
            printf("consultar articulos");
            break;
        case 3:
            printf("Eliminar articulos");
            break;
        case 4:
            printf("regresando");
            inicio();
            break;

        default:
            printf("\nOpcion no disponible\n");
            break;
        }
    } while (opcion != 4);
}
