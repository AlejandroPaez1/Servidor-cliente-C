#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <libpq-fe.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

PGconn *con = NULL;
PGresult *result = NULL;

char *host = "127.0.0.1";
char *port = "5432";
char *dataBase = "tienda";
char *user = "postgres";
char *passwd = "1234";

int i, j, fd1, fd2, SQLDAT1;
int fcons1;
char txt[5], sql[1234];

int main()
{

    int menup;
    while (1)
    {
        // remove("/home/alejandro/Escritorio/carpeta/SQLDATA1");

        mkfifo("menu_principal", 0666);
        mkfifo("menu_secundario", 0666);
        //*menu principal---------------------------------------
        fd1 = open("menu_principal", O_RDONLY);
        read(fd1, txt, sizeof(txt));
        menup = atoi(txt);
        close(fd1);
        printf("------------------------------------\n");
        printf("                MENU                \n");
        printf("------------------------------------\n");
        printf("|1-Clientes                        |\n");
        printf("|2-fac                       |\n");
        printf("|3-art                        |\n");
        printf("------------------------------------\n");
        printf("->%i\n", menup);
        switch (menup)
        {
            //*clientes
        case 1:
            printf("Entrando a la seccion de clientes\n");

            menuCliente();
            break;
        //*Articulos
        case 2:
            printf("Entrando a la seccion de articulos\n");
            // menuArticulo();
            break;
        //*Facturas
        case 3:
            printf("Entrando a la seccion de articulos\n");
            break;
        }
    }
}

int menuCliente()
{
    char txt[5];
    int menu;
    fd1 = open("menu_secundario", O_RDONLY);
    read(fd1, txt, sizeof(txt));
    close(fd1);
    printf("\n|----------------------------------------------|");
    printf("\n|             * Submenu clientes *             |");
    printf("\n|----------------------------------------------|");
    printf("\n| 1.AltaCliente         | 4. Modificar cliente |");
    printf("\n| 2.Consulta cliente    | 5. Mostrar tabla     |");
    printf("\n| 3.Eliminacion cliente | 6. Regresar          |");
    printf("\n|-----------------------|----------------------|");
    menu = atoi(txt);
    printf("-->%i\n", menu);
    switch (menu)
    {
    //*Caso para añadir el cliente
    case 1:
        printf("Entrando a la parte de añadir cliente\n");

        addDatos();
        break;
    case 2:
        printf("Entrando a la parte de consultar clientes\n");
        consultaDatos();
        break;
    case 3:
        printf("Entrando a la parte de eliminar clientes\n");
        eliminarDatos();
        break;
    case 4:
        printf("Entrando a la parte de actualizar clientes\n");
        updateDatos();
        break;
    case 5:
        printf("Entrando a mostrar clientes\n");
        showtables();
        break;
    }
}

int addDatos()
{
    mkfifo("SQLDATA1", 0666);

    printf("Entrando al servicio de añadir clientes/facturas\n");
    con = PQsetdbLogin(host, port, NULL, NULL, dataBase, user, passwd); //*abro conexion

    char sql2[1234], sqltel[900], er[5];
    int ier, error, tel;

    SQLDAT1 = open("SQLDATA1", O_RDONLY);

    read(SQLDAT1, sql2, sizeof(sql2));

    printf(":::::%s \n", sql2);
    con = PQexec(con, sql2);
    close(SQLDAT1);

    if (PQstatus(con) != CONNECTION_OK)
    {
        printf("Error de consulta valores invalido\n");
    }
    else
    {
        printf("Query exitoso\n");
    }

    PQfinish(con); //*cierro conexion
    fflush(stdin);
}

int consultaDatos()
{

   
    char squery[1234];
    char bf[900], cad[2024];

         for (int i = 0; i < 100; i++)
        {
            // reiniciar la cadena a 0
            bf[i] = '\0';
            cad[i] = '\0';
            squery[i] = '\0';
        }

    printf("Entrando a la parte de consulta cliente\n");
    // PARA CONSULTAR DATOS
    mkfifo("FIFOCONSULTA10", 0666);
    mkfifo("listaclientes1", 0666);

    fcons1 = open("FIFOCONSULTA10", O_RDONLY);
    read(fcons1, squery, sizeof(squery));
    printf("\n esto trae:\n %s\n", squery);

    con = PQsetdbLogin(host, port, NULL, NULL, dataBase, user, passwd);
    result = PQexec(con, squery);

    printf("Filas:%d, Columnas:%d \n", PQntuples(result), PQnfields(result));

    fd1 = open("listaclientes1", O_WRONLY);

    if (PQntuples(result) == 0)
    {
        sprintf(cad,"NO HAY DATOS ");
        write(fd1, cad, sizeof(cad));
    }else{

    if (result != NULL)
    {
        for (i = 0; i < PQntuples(result); i++)
        {
            for (j = 0; j < PQnfields(result); j++)
            {
                sprintf(bf, "%s | ", PQgetvalue(result, i, j));
                strcat(cad, bf);
            }
            strcat(cad, "\n");
        }
        printf("\n %s", cad);

        write(fd1, cad, sizeof(cad));
    }
    else
    {
        printf("No hay clientes\n");
    }
        
    }
    





        fflush(stdin);
    close(fd1);
    close(fcons1);
}

int eliminarDatos()
{
    printf("Entrando al int de eliminar cliente\n");
  mkfifo("sqldelete1",0666);


      int i_id;
  char sqldelete[500],id[30];
  con = PQsetdbLogin(host,port,NULL,NULL,dataBase,user,passwd);


  i_id=open("sqldelete1",O_RDONLY);
  read(i_id,id,sizeof(id));
  close(i_id);
  sprintf(sqldelete, "DELETE FROM clientes WHERE id_cliente = %s", id);

  //sprintf(sqldelete,"delete from clientes where id_cliente = %s;",id);
  printf("%s\n",sqldelete);
  PQexec(con,sqldelete);
}

int updateDatos()
{
    printf("Entrando a la parte de update cliente\n");
    mkfifo("updatesql",0666);

      int menu3,p;
  char menu[3],sql[900],dato[500],problema[3];
  con = PQsetdbLogin(host,port,NULL,NULL,dataBase,user,passwd);

    fd1=open("updatesql",O_RDONLY);
    read(fd1,sql,sizeof(sql));
    printf("%s\n",sql);
    PQexec(con,sql);
    close(fd1);


}

int showtables(){

    
}
