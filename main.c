#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>
#include <signal.h>
#include <sys/wait.h>
#include <pthread.h>

// Cuenten con este codigo monolitico en una funcion
// main como punto de partida.
// Idealmente, el codigo del programa deberia estar
// adecuadamente modularizado en distintas funciones,
// e incluso en archivos separados, con dependencias
// distribuidas en headers. Pueden modificar el Makefile
// libremente para lograr esto.
  int count = 0;
  int totalTransactions = 200;
  int t = 0;
  char conversionBuffer[70];

  int *sucList;
  int *accountList;
  int *transactionList;

  int type[300];
  int media[300];
  int origin[300];
  int destiny[300];



typedef struct transaction{
  int o_suc; //sucursal de origen
  int d_suc; //sucursal de destino
  int o_account; //cuenta de origen
  int d_account; //cuenta de destino
  int amount;
  int type; //1: deposito, 2: retiro, 3: transferencia
};


//malloc(totalTransactions * sizeof (transaction));


//malloc(totalTransactions * sizeof *totalTransactions);
void *ejecucion_sucursal(){

  // Aca hacer todo lo que deberia hacer una sucursal , retirar, depositar , transferir entre sucursales etc , generar transacciones aleatorias.
}

void *ejecucion_banco(){
    //for (size_t i = 0; i < count; i++) {
        //leer transcaciones creo
  //  }
      char buff[2];
    //  while(read(sucPipe[0] , buff , 1 ) > 0 {
    //    printf("Soy la sucursal '%d' y me llego mensaje '%s'\n",
    //      sucId, buff);

  //    }
  // Aca leer las transacciones y
}



int RandRange(int Min, int Max){
    int diff = Max-Min;
    return (int) (((double)(diff+1)/RAND_MAX) * rand() + Min);
}

void *makeTransactions(void *thread){
  int ran_num = RandRange(0,count);

  struct transaction t1;
  //transaction *transaction_data = (transaction*)thread;
  t1.amount = RandRange(1000, 500000000);
  //printf("%d\n", t1.amount );
  t1.type = RandRange(1, 3);
  t1.o_suc = sucList[ran_num];
  printf("%d\n", t1.o_suc );
  t1.o_account = accountList[ran_num];
  t1.d_suc = sucList[ran_num];
  t1.d_account = accountList[ran_num];


  if (t1.type== 1) {
    //deposito
    //printf("%d, %s\n",t1.d_account, "Deposito" );
    t1.d_account = t1.d_account + t1.amount;
    //printf("%d, %s\n",t1.d_account, "Deposito" );

  }else if (t1.type == 2) {
    //retiro
    if (  t1.d_account <= 0) {
      printf("%s\n", "Error, no tiene dinero suficiente para hacer un retiro \n" );
      /* code */
    }else{
      t1.d_account = t1.d_account - t1.amount;
    }

  }else if (t1.type == 3) {
    //transferencia
    if (t1.o_account <= 0) {
      /* code */
      printf("%s\n", "Error, no tiene dinero suficiente para hacer una transferencia \n" );

    }else{
      t1.o_account = t1.o_account - t1.amount;
      t1.d_account = t1.d_account + t1.amount;
    }
  }
  //for (size_t i = 0; i < totalTransactions; i++) {
    //transactionList[i].o_suc = t1.o_suc;
    //transactionList[i].d_suc = t1.d_suc;
    //transactionList[i].o_account = t1.o_account;
    //transactionList[i].d_account = t1.d_account;
    //transactionList[i].amount = t1.amount;
    //transactionList[i].type = t1.type;
  //}

  type[t] = t1.type;
  media[t] = t1.o_suc;
  origin[t] = t1.o_account;
  destiny[t] = t1.d_account;


  t++;



return NULL;
}


int main(int argc, char** argv) {
  int N;
  int T;
  int err;
  int l = 0;
  char line[256];
  int *accounts;

  size_t bufsize = 512;
  char* commandBuf = malloc(sizeof(char)*bufsize);

  transactionList = (int*)malloc(sizeof(int)*totalTransactions);

  pthread_t t_banco, t_sucursal[8];



  sucList = (int*)malloc(sizeof(int)*200);



  accountList = (int*)malloc(sizeof(int)*200);

  int *terminalList;
  terminalList = (int*)malloc(sizeof(int)*200);


  // Para guardar descriptores de pipe
  // el elemento 0 es para lectura
  // y el elemento 1 es para escritura.
  int sucPipe[2];
  int bankPipe[2];
  char readbuffer[80]; // buffer para lectura desde pipe

  // Se crea un pipe...
  pipe(bankPipe);
  pipe(sucPipe);

  const int bankId = getpid() % 1000;
  printf("Bienvenido a Banco '%d'\n", bankId);

  pthread_create(&t_banco,NULL,ejecucion_banco,NULL);
  while (true) {
    printf(">>");
    getline(&commandBuf, &bufsize, stdin);

    // Manera de eliminar el \n leido por getline
    commandBuf[strlen(commandBuf)-1] = '\0';

    printf("Comando ingresado: '%s'\n", commandBuf);

    if (!strncmp("quit", commandBuf, strlen("quit"))) {
        break;
    }else if (!strncmp("list", commandBuf, strlen("list"))){
        //system("ps -a");
        printf("%s\n", "Sucursales actualmente activas: \n" );
        for (size_t i = 0; i < count; i++) {
          printf("ID: '%d'", sucList[i]);
          printf("  Cuentas actualmente activas: '%d'", accountList[i] );
          printf("  Terminales actualmente activas: '%d'\n", terminalList[i]);
        }
    }
    else if (!strncmp("dump_accs", commandBuf, strlen("dump_accs"))){
      int id;
      int j = 0;
      char id_cast[20];
      FILE *fp;
      printf("%s\n", "Ingrese ID de sucursal para generar el archivo CSV: " );
      if (fgets(line, sizeof(line) , stdin)) {
        if(1 == sscanf(line,"%d" , &id)) {

          for (int i = 0; i < N; i++) {

            if ( id == sucList[i] ){
              sprintf(id_cast,"dump_accss_%d.csv",id);
              fp = fopen (id_cast, "w+");
              fprintf(fp, "%s,%s\n", "Numero de cuenta" , "Saldo" );
              while (j < N) {

              char inicial_buffer[100];
              fprintf(fp, "%d,%d\n", j , accounts[j] );
              j++;
            }
              fclose (fp);

            }
            else {
              printf("%s\n", "Error, ID no registrado" );
              break;
            }
          }
        }
    }
  }else if(!strncmp("dump", commandBuf, strlen("dump"))){
    //printf("%s\n", "Este es el comando de dump" );
    int id;
    int j = 0;
    char id_cast[20];
    FILE *fp;
    printf("%s\n", "Ingrese ID de sucursal para generar el archivo CSV: " );
    if (fgets(line, sizeof(line) , stdin)) {
      if(1 == sscanf(line,"%d" , &id)) {

        for (int i = 0; i < N; i++) {

          //if ( id == sucList[i] ){
            sprintf(id_cast,"dump_%d.csv",id);
            fp = fopen (id_cast, "w+");
            fprintf(fp, "%s,%s,%s,%s\n", "Tipo de transaccion" , "Medio de origen", "Cuenta origen", "Cuenta destino" );
            while (j < N) {

            char inicial_buffer[100];
            fprintf(fp, "%d,%d,%d,%d\n" ,type[j], media[j], origin[j], destiny[j] );
            j++;
          }
            fclose (fp);

          //}
          //else {
            //printf("%s\n", "Error, ID no registrado" );
            //break;
          //}
        }
      }
  }
  }
    else if (!strncmp("kill", commandBuf, strlen("kill"))){
      int id;
      printf("%s\n", "Ingrese PID de sucursal para detenerla: " );  //Debiese ser ID :/
      if (fgets(line, sizeof(line) , stdin)) {
        if(1 == sscanf(line,"%d" , &id)) {
          kill(id, SIGTERM);
          bool died = false;
          for (int loop = 0;!died && loop < 5; loop++) {
            int status;
            sleep(1);
            if(waitpid(id,&status, WNOHANG) == id) died = true;

          }
          if (!died) kill(id,SIGKILL);
            printf("%s\n", "Proceso detenido");
          }
        }
      }

    else if (!strncmp("init", commandBuf, strlen("init"))) {
      // OJO: Llamar a fork dentro de un ciclo
      // es potencialmente peligroso, dado que accidentalmente
      // pueden iniciarse procesos sin control.
      // Buscar en Google "fork bomb"

      printf("%s\n", "Ingrese numero de cuentas , sino ingrese 0 para crear 1000 por defecto: " );
      if (fgets(line, sizeof(line) , stdin)) {
        if(1 == sscanf(line,"%d" , &N)) {
          if (N == 0){
            N = 1000;
          }
        }
      }
      printf("%s\n", "Ingrese numero de terminales que desee crear: " );
      if (fgets(line, sizeof(line) , stdin)) {
        if(1 == sscanf(line,"%d" , &T)) {
          while(T<1 || T>8){
            printf("%s\n", "Numero de terminales no permitido,ingrese nuevamente entre 1 y 8: " );
            if (fgets(line, sizeof(line) , stdin)) {
              if(1 == sscanf(line,"%d" , &T)) {
                  continue;
              }
            }
           }
          }
        }
      terminalList[count] = T;
      accountList[count] = N;

      //Llenamos el arreglo de estructuras de transacciones




      accounts = (int*)malloc(sizeof(int)*N);

      pid_t sucid = fork();
      if (sucid > 0) {
        printf("Sucursal creada con ID '%d'\n", sucid);
        //Arreglo de 1000 cuentas por sucursal
        //Llenar el arreglo con los montos para las 1000 cuentas

        sucList[count] = sucid % 1000;
        for (size_t i = 0; i < N; i++) {
          accounts[i] = RandRange(1000, 500000000);
        }
        // Enviando saludo a la sucursal
        char msg[] = "Hola sucursal, como estas?";
        write(bankPipe[1], msg, (strlen(msg)+1));

        count++;

        continue;
      }
      // Proceso de sucursal
      else if (!sucid) {
        int sucId = getpid() % 1000;
        //pthread_join(t_sucursal[l],NULL);

        while ( l < T ){
            err = pthread_create(&t_sucursal[l],NULL, makeTransactions,NULL);
            if ( err != 0) {
              printf("%s%d\n", "No se puede crear thread " , strerror(err) );
            }
            else {
               printf("%s\n", "Creacion exitosa" );

            }
            l++;

        }
        for (size_t i = 0; i < T; i++) {
          pthread_join(t_sucursal[i],NULL);
       }

        printf("Hola, soy la sucursal '%d'\n", sucId);
        //while (count < sizeof(sucList))
        while (true) {
          // 100 milisegundos...
          int bytes = read(bankPipe[0], readbuffer, sizeof(readbuffer));
          printf("Soy la sucursal '%d' y me llego mensaje '%s' de '%d' bytes.\n",
            sucId, readbuffer, bytes);


          // Usar usleep para dormir una cantidad de microsegundos
          // usleep(100000);

          // Cerrar lado de lectura del pipe
          close(bankPipe[0]);

          // Para terminar, el proceso hijo debe llamar a _exit,
          // debido a razones documentadas aqui:
          // https://goo.gl/Yxyuxb
          _exit(EXIT_SUCCESS);
        }
      }
      // error
      else {
        fprintf(stderr, "Error al crear proceso de sucursal!\n");
        return (EXIT_FAILURE);
      }
    }
    else {
      fprintf(stderr, "Comando no reconocido.\n");
    }
    // Implementar a continuacion los otros comandos
  }

  printf("Terminando ejecucion limpiamente...\n");
  free(commandBuf);
  free(accounts);
  free(sucList);
  // Cerrar lado de escritura del pipe
  close(bankPipe[1]);

  return(EXIT_SUCCESS);
}
