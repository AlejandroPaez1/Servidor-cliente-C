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

    int fd, fd2, i;
    char salir;

void main()
{
   inicio();
    mkfifo("FIFO1", 0666);
    mkfifo("FIFO2", 0666);
}



void inicio () {

    int opcion = 0;
    do {

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

        switch(opcion) {
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
                printf("\nOpcion no disponible\n");     break;
        }
    }while (opcion != 4);

}

void menu_clientes() {
    int opcion = 0;
    do {
        printf("\n|----------------------------------------------|");
        printf("\n|             * Submenu clientes *             |");
        printf("\n|----------------------------------------------|");
        printf("\n| 1.AltaCliente         | 4. Modificar cliente |");
        printf("\n| 2.Consulta cliente    | 5. Mostrar tabla     |");
        printf("\n| 3.Eliminacion cliente | 6. Regresar          |");
        printf("\n|-----------------------|----------------------|");
        printf("\n\n Escoja una opcion: ");
        scanf("%d", &opcion);

        switch(opcion) {
            case 1:
                printf("menu alta cliente");
                altacliente();
                break;
            case 2:
                printf("consulta cliente");                       
                break;
            case 3:
                printf("Eliminacion cliente");          
                break;
            case 4:
                printf("modifcar cliente");
                break;
            case 5:
                printf("mostrar tabla");        
                break;                
            case 6:
                 inicio ();
                 break;
            default:
                printf("\nOpcion no disponible\n");     break;
        }
    }while (opcion != 6);
}

void altacliente(){
 char nombre[100];
 char apellido[100];
 char rfc[100];
 char direccion[100];
 char edad[100];
 char pais[100];
 char telefono[100];
 

        char cadena[100];
        char cadena2[100];
do    {

        // se envia el mensaje.
        fflush(stdin);
        fd = open("FIFO1", O_WRONLY);

        puts("\nescribe el nombre del cliente: ");
        printf("el nombre es:\n");
        scanf("%s",&nombre);

        printf("el apellido es:\n");
        scanf("%s",&apellido);  

        printf("el rfc es:\n");
        scanf("%s",&rfc);

        printf("el direccion es:\n");
        scanf("%s",&direccion);

        printf("el edad es:\n");
        scanf("%s",&edad);

        printf("el pais es:\n");
        scanf("%s",&pais);        

       printf("el telefono es:\n");
        scanf("%s",&telefono);        
         sprintf( cadena,"insert into clientes values (DEFAULT, '%s', '%s', '%s', '%s', '%s', '%s', '%s');",nombre,apellido, rfc, direccion, edad, pais, telefono);
      

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
        
        write(fd, cadena, sizeof(cadena));
        close(fd);

        // empieza a recibir el mensaje
        fd2 = open("FIFO2", O_RDONLY);
        //lee lo que le manda el servidor
        read(fd2, cadena2, sizeof(cadena2));

    /*     if (strcmp(cadena2, "offline") == 0)
        {
            puts("\n\n\nUsuario 2 --offline--");
            exit(-1);
        }
      */   
        //imprime lo que pasa
        printf("\nServidor dice:  %s ", cadena2);
        close(fd2);

        for (i = 0; i < 100; i++)
        {
            //reiniciar la cadena a 0
            
            cadena[i] = '\0';
            cadena2[i] = '\0';
        }
    fflush(stdin);
    menu_clientes();
    } while (1);        

}


void menu_facturas() {
    int opcion = 0;
    do {
        printf("\n|----------------------------------------------|");
        printf("\n|             * Submenu Facturas *             |");
        printf("\n|----------------------------------------------|");
        printf("\n| 1.insertar factura | 4. Regresar menu inicio |");
        printf("\n| 2.Actualizar       | 5. ...          |");
        printf("\n| 3.Eliminar factura | 6. ...          |");
        printf("\n|--------------------|-----------------|");
        printf("\n\n Escoja una opcion: ");
        scanf("%d", &opcion);

        switch(opcion) {
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
                inicio ();
                break;

            default:
                printf("\nOpcion no disponible\n");     break;
        }
    }while (opcion != 4);
}


void menu_articulos() {
    int opcion = 0;
    do {
        printf("\n|----------------------------------------------|");
        printf("\n|             * Submenu articulos *             |");
        printf("\n|----------------------------------------------|");
        printf("\n| 1.insertar articulo   | 4. Regresar menu inicio |");
        printf("\n| 2.Actualizar articulo | 5. ...     |");
        printf("\n| 3.Eliminar articulo   | 6. ...     |");
        printf("\n|-----------------------|------------|");
        printf("\n\n Escoja una opcion: ");
        scanf("%d", &opcion);

        switch(opcion) {
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
                inicio ();
                break;

            default:
                printf("\nOpcion no disponible\n");     break;
        }
    }while (opcion != 4);
}
