#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
//*inicializacion de variables
int fd1, fd2, fde = 0, i;
int fcons1;
char txt[2];
//?Funcion principal
int main()

{
    int menu;
    while (1)
    {
    remove("/home/alejandro/Escritorio/carpeta/SQLDATA1");
    remove("/home/alejandro/Escritorio/carpeta/FIFOCONSULTA10");
    remove("/home/alejandro/Escritorio/carpeta/listaclientes1");
    remove("/home/alejandro/Escritorio/carpeta/sqldelete1");
    remove("/home/alejandro/Escritorio/carpeta/updatesql");

        printf("\n|-----------------|");
        printf("\n|    * Incio *    |");
        printf("\n|-----------------|");
        printf("\n| 1. Clientes     |");
        printf("\n| 2. Facturas     |");
        printf("\n| 3. Articulos    |");
        printf("\n| 4. Salir        |");
        printf("\n|-----------------|");
        printf("\n\n Escoja una opcion: ");
        scanf("%i", &menu);

        fd2 = open("menu_principal", O_WRONLY);
        sprintf(txt, "%i", menu);
        write(fd2, txt, sizeof(txt));
        close(fd2);

        switch (menu)
        {
        // clientes
        case 1:
            printf("Entrando a la seccion de clientes\n");
            menuCliente();
            break;
        // Articulos
        case 2:
        // Facturas
             menuFacturas();
            break;
        case 3:

            break;
        case 4:
            exit(EXIT_SUCCESS);
            break;
        default:
            printf("No tenemos esa opcion, vuelva a intentarlo\n");
            break;
        }
    }
}

//?Menu para acciones con clientes
int menuCliente()
{
    int menu;
    char txt[5];
    fd2 = open("menu_secundario", O_WRONLY);
    printf("\n|----------------------------------------------|");
    printf("\n|             * Submenu clientes *             |");
    printf("\n|----------------------------------------------|");
    printf("\n| 1.AltaCliente         | 4. Modificar cliente |");
    printf("\n| 2.Consulta cliente    | 5. Mostrar tabla     |");
    printf("\n| 3.Eliminacion cliente | 6. Regresar          |");
    printf("\n|-----------------------|----------------------|");
    printf("\n\n Escoja una opcion: ");
    scanf("%i", &menu);
    sprintf(txt, "%i", menu);
    write(fd2, txt, sizeof(txt));
    close(fd2);

    switch (menu)
    {
    //*agregar clientes
    case 1:
        //*Se manda al server la funcion que se solicita para que su propio menu sepa que hacer
        printf("Parte de agregar cliente\n");
        addCliente();
        break;
    //*borrar clientes
    case 2:
        printf("Parte de CONSULTA cliente\n");
        consultas();
        break;
    //*borrar cliente
    case 3:
        delete ();
        break;
    //*Mostrar clientes
    case 4:
        // showClientes();
        updateDatos();
        break;
    case 5:
        showtables();
    break;
    }
}



int menuFacturas(){
int opcion;

        printf("\n|--------------------------------------|");
        printf("\n|         * Submenu Facturas *         |");
        printf("\n|--------------------------------------|");
        printf("\n| 1.insertar factura | 4. modificar    |");
        printf("\n| 2.Actualizar       | 5. mostrar fact |");
        printf("\n| 3.Eliminar factura | 6. regresar     |");
        printf("\n|--------------------|-----------------|");
        printf("\n\n Escoja una opcion: ");
        scanf("%d", &opcion);

        switch (opcion)
        {
        case 1:
            printf("Insertar facturas");
        addFactura();
            

            break;
        case 2:
            printf("Actualizar facturas");
            break;
        case 3:
            printf("Eliminacion facturas");
            break;
        case 4:
            printf("modificcar");
            break;
        case 5:
            printf("mostrar");
            break;

        default:
            printf("\nOpcion no disponible\n");
            break;
        }


}
int addFactura(){

    fflush(stdin);

    char importe_total[50];
    char importe_letra[50];
    char id_cliente[50];
    
    char sql[1024], sql2[900], er[5], sqltel[900];
    int SQLDAT1, s2, ier, phone;

    puts("\nEscribe la factura: ");
    printf("escribe el importe total:\n");
    scanf("%s", &importe_total);

    printf("el importe letra:\n");
    scanf("%s", &importe_letra);

    printf("Id de cliente al que se va aumentar:\n");
    scanf("%s", &id_cliente);

    SQLDAT1 = open("SQLDATA1", O_WRONLY);

    sprintf(sql,"INSERT INTO facturas(importe_total,importe_letra,id_cliente) VALUES ('%s','%s',%s);",importe_total,importe_letra,id_cliente);
    printf("Instruccion:%s\n", sql);

    // sprintf(sql, "SELECT insertar_cliente ('%s','%s' ,'%s', '%s', '%s', '%s')",nombre,apellido,rfc,direccion,edad,pais);
    write(SQLDAT1, sql, sizeof(sql));
    close(SQLDAT1);

}


int addCliente()
{

    fflush(stdin);

    char nombre[50];
    char apellido[50];
    char rfc[50];
    char direccion[50];
    char edad[10];
    char pais[50];
    char telefono[11];

    char sql[1024], sql2[900], er[5], sqltel[900];
    int SQLDAT1, s2, ier, phone;

    puts("\nEscribe el nombre del cliente: ");
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
    SQLDAT1 = open("SQLDATA1", O_WRONLY);

    sprintf(sql, "insert into clientes values (DEFAULT, '%s', '%s', '%s', '%s', %s, '%s', '%s');", nombre, apellido, rfc, direccion, edad, pais, telefono);
    printf("Instruccion:%s\n", sql);

    // sprintf(sql, "SELECT insertar_cliente ('%s','%s' ,'%s', '%s', '%s', '%s')",nombre,apellido,rfc,direccion,edad,pais);
    write(SQLDAT1, sql, sizeof(sql));
    close(SQLDAT1);
}

int consultas()

{
    char cad[2024];
    char id_cliente[20];

    for (int i = 0; i < 100; i++)
    {
        // reiniciar la cadena a 0
        cad[i] = '\0';
    }
    // do    {
    /* code */
    printf("\n escribe el id del cliente que quieres mostrar:\n");
    scanf("%s", &id_cliente);
    fcons1 = open("FIFOCONSULTA10", O_WRONLY);
    sprintf(cad, "SELECT * FROM clientes WHERE id_cliente = %s;", id_cliente);
    // sprintf(cad, "SELECT * FROM clientes;");
    // printf("\n consulta que va es:\n %s",cad);

    write(fcons1, cad, sizeof(cad));
    close(fcons1);

    fd1 = open("listaclientes1", O_RDONLY);
    read(fd1, cad, sizeof(cad));

    printf("  id |  nombre | apellido |  RFC   |  Direcccion  | edad  |  pais | telefono  \n");
    printf("%s\n", cad);
    close(fd1);
    //    } while (1);
}

int delete ()
{
    int i_id, data;

    char id[30];
    char id_usuario[20];
    printf("Inserte el id del usuario\n");
    scanf("%s", &id_usuario);
    // sprintf(id,"%i",data);
    sprintf(id, "%s", id_usuario);
    i_id = open("sqldelete1", O_WRONLY);
    write(i_id, id, sizeof(id));
    close(i_id);
}

int updateDatos()
{
    char nombre[50];
    char apellido[50];
    char rfc[50];
    char direccion[50];
    char edad[10];
    char pais[50];
    char telefono[11];

    char menu[3], sql[900], data[100], id[40], p[3];

    int opcion;

    char id_cliente[20];
    printf(" Que id de Cliente quieres editar:\n ");
    scanf("%s", &id_cliente);

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
        scanf("%s", &data);

        sprintf(sql, "UPDATE clientes SET nombre = '%s' WHERE id_cliente = %s;", data, id_cliente);
        // sprintf(cadena, "UPDATE clientes SET nombre = '%s' WHERE id_cliente = %s", nombre, id_cliente);
        fflush(stdin);
        break;

    case 2:
        printf("\n Escribe el Apellido  :\n");
        scanf("%s", &data);
        sprintf(sql, "UPDATE clientes SET apellidos = '%s' WHERE id_cliente = %s", data, id_cliente);

        fflush(stdin);
        break;

    case 3:
        printf("\n Escribe el RFC :\n");
        scanf("%s", &data);
        sprintf(sql, "UPDATE clientes SET rfc = '%s' WHERE id_cliente = %s", data, id_cliente);
        fflush(stdin);
        break;

    case 4:
        printf("\n Escribe la nueva Direccion :\n");
        scanf("%s", &data);
        sprintf(sql, "UPDATE clientes SET direccion = '%s' WHERE id_cliente = %s", data, id_cliente);
        fflush(stdin);

        break;

    case 5:
        printf("\n Escribe la nueva edad  :\n");
        scanf("%s", &data);
        sprintf(sql, "UPDATE clientes SET edad = '%s' WHERE id_cliente = %s", data, id_cliente);

        fflush(stdin);

        break;

    case 6:
        printf("\n Escribe el Telefono nuevo  :\n");
        scanf("%s", &data);
        sprintf(sql, "UPDATE clientes SET telefono = '%s' WHERE id_cliente = %s", data, id_cliente);
        fflush(stdin);
        break;

    }

        //printf("%s\n",sql);
        fd1=open("updatesql",O_WRONLY);
        write(fd1,sql,sizeof(sql));
        close(fd1);
    
}

int showtables(){
    char cad[2024];
    char id_cliente[20];

    for (int i = 0; i < 100; i++)
    {
        // reiniciar la cadena a 0
        cad[i] = '\0';
    }

    fcons1 = open("FIFOCONSULTA10", O_WRONLY);
    sprintf(cad, "SELECT * FROM clientes;");
    // printf("\n consulta que va es:\n %s",cad);

    write(fcons1, cad, sizeof(cad));
    close(fcons1);

    fd1 = open("listaclientes1", O_RDONLY);
    read(fd1, cad, sizeof(cad));

    printf("  id |  nombre | apellido |  RFC   |  Direcccion  | edad  |  pais | telefono  \n");
    printf("%s\n", cad);
    close(fd1);
}

