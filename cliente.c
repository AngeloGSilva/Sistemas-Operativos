#include "cliente.h"

void handler_function(int s){
    //Evitar ctrl+c
    printf("\nApenas sai com [desistir] e [adeus]\n");
}

void printClientes(CLIENTE cli){
    printf("Nome:%s\n",cli.nome);
    printf("Sintomas:%s",cli.sintomas);
    if(strlen(cli.especialidade)>0)
    printf("Especialidade:%s\n",cli.especialidade);
    if(cli.gravidade==1 || cli.gravidade==2 || cli.gravidade==3)
    printf("Gravidade:%d\n",cli.gravidade);
    printf("Pessoas a frente: %d\n",cli.nrFila);
    printf("Numero de especialistas no sistema:%d\n",cli.nrEsp);

}

int main(int argc,char *argv[]){
    if(argc<2){
        printf("ERRO no numero de inputs (nome)!\n");
        exit(33);
    }
    signal(SIGINT, handler_function); //Ignorar ctrl+c
    //signal(SIGUSR1,morri);
    //signal(SIGUSR2,sair);
    int fd_cli,fd,n,clibuf=0,fd_climsg,fd_aux,fdboth;
    int pidconectado,consultaOcupado=0;
    char str[40],cmd[20];
    char buf_menu,pidaux[40];
    char msgCli[40],auxfdcli[30],auxfdclimsg[30];
    float res = -1;
    fd_set fds;
    struct timeval tempo = {5 , 0};
    CLIENTE cliente;
    CHAT buf;
    //Nome do cliente (linha de comandos)
    strcpy(cliente.nome,argv[1]);
    //Pid do processo cliente
    cliente.pid = getpid();
    strcpy(cliente.chat.mensagem,"default");
    cliente.consulta = 0;

    //Acesso ao fifo do servidor
    if(access(FIFO_SERVCLI,F_OK)!= 0){
        printf("[ERRO]Fifo do servidor nao existe!\n");
        exit(1);
    }
    //Abrir fifo do servidor para escrita
    fd = open(FIFO_SERVCLI,O_WRONLY);
    //Criar fifo do cliente
    sprintf(auxfdcli,FIFO_CLIENTE,cliente.pid);
    mkfifo(auxfdcli,0700);

    //Verificar se criou fifo do cliente
    if(access(auxfdcli,F_OK)!=0){
        printf("[ERRO]Fifo do cliente nao existe!\n");
        exit(1);
    }
    fd_cli = open(auxfdcli,O_RDWR);
    //Criar fifo do cliente MSG
    sprintf(auxfdclimsg,FIFO_CLIENTEMSG,cliente.pid);
    mkfifo(auxfdclimsg,0700);

    //Verificar se criou fifo do cliente MSG
    if(access(auxfdclimsg,F_OK)!=0){
        printf("[ERRO]Fifo do clientemsg nao existe!\n");
        exit(1);
    }
    fd_climsg = open(auxfdclimsg,O_RDWR);
    
    printf("Dados de cliente:\n");
    do{
        if(buf_menu=='N' || buf_menu=='n')
            printf("Reeinsira os dados\n");
    printf("\nSintomas:");
    scanf(" %[^\n]" , cliente.sintomas);
    printf("\nDados Inseridos:\n");
    printClientes(cliente);
    printf("\nDeseja continuar?[S/N]\n");
    scanf(" %c",&buf_menu);
    }while(buf_menu!='s' && buf_menu!='S');
    //printf("PID  AENVIAR:%d",cliente.pid);
    n = write(fd,&cliente,sizeof(CLIENTE));
    
    do{
    FD_ZERO(&fds);
    FD_SET(0,&fds);
    FD_SET(fd_cli,&fds);
    FD_SET(fd_climsg,&fds);
    tempo.tv_sec = 5;
    tempo.tv_usec = 0;
    fdboth = (fd_cli > fd_climsg)? fd_cli : fd_climsg;
    res = select(fdboth + 1 , &fds, NULL, NULL, &tempo);
    if(res == 0){
        if(cliente.consulta == 0)
            printf("Espera por um especialista...\n");
        //comandos do cliente
    }else if(res>0 && FD_ISSET(0,&fds)){
        //sleep(0); //temporario
        scanf(" %[^\n]",cmd);
        //fflush(stdout);
        if(strcmp(cmd,"desistir")==0){
            //Avisa o balcao
            strcpy(cliente.chat.mensagem,"sair");
            n = write(fd,&cliente,sizeof(CLIENTE));
            //Avisar o cliente
            if(consultaOcupado==1){
                sprintf(pidaux,FIFO_MEDICOMSG,pidconectado);
                strcpy(buf.mensagem,"adeus");
                strcpy(buf.nomeconectado,cliente.nome);
                fd_aux = open(pidaux,O_WRONLY);
                n=write(fd_aux,&buf,sizeof(CHAT));
                close(fd_aux);
            }
            printf("Programa Cliente a terminar\n");
        }else if(strcmp(cmd,"adeus")==0){
            
            //Avisa o medico associado
            if(consultaOcupado==1){
                strcpy(cliente.chat.mensagem,"sair");
                n = write(fd,&cliente,sizeof(CLIENTE));
                sprintf(pidaux,FIFO_MEDICOMSG,pidconectado);
                strcpy(buf.mensagem,"adeus");
                strcpy(buf.nomeconectado,cliente.nome);
                fd_aux = open(pidaux,O_WRONLY);
                n=write(fd_aux,&buf,sizeof(CHAT));
                close(fd_aux);
                printf("Consulta Terminada\n");
                strcpy(cmd,"desistir");
            }else if(consultaOcupado==0){
                printf("Nao ha consulta a terminar\n");
            }
        }else{
            if(consultaOcupado==1){
            strcpy(buf.mensagem,cmd);
            //buf.pidconectado=pidconectado;
            sprintf(str,FIFO_MEDICOMSG,pidconectado);
            fd_aux = open(str,O_WRONLY);
            //verificar se abriu o pipe
            n = write(fd_aux,&buf,sizeof(CHAT));
            close(fd_aux);
            }
        }
       
    }else if(res>0 && FD_ISSET(fd_cli,&fds)){
    //Receber informação do servidor
    n = read(fd_cli,&cliente,sizeof(CLIENTE));
    if(strcmp(cliente.chat.mensagem,"sucesso")==0){
        printf("Cliente adicionado com sucesso a fila da especialidade %s\n",cliente.especialidade);
        printClientes(cliente);
    }
    else if(strcmp(cliente.chat.mensagem,"atualiza")==0){
        printf("Numero da fila: %d\n",cliente.nrFila);
        printf("Numero de Especialistas de %s: %d",cliente.especialidade,cliente.nrEsp);
    }else if(strcmp(cliente.chat.mensagem,"cheio")==0){
        printf("Fila de espera da especialidade %s esta cheia!!\n",cliente.especialidade);
        strcpy(cmd,"desistir");
    }else if(strcmp(cliente.chat.mensagem,"expulso")==0){
        printf("Expulso da fila de espera %s por um administrador!!\n",cliente.especialidade);
        strcpy(cmd,"desistir");
    }else if(strcmp(cliente.chat.mensagem,"kick")==0){
        printf("Balcao encerrou!\n");
        strcpy(cmd,"desistir");
    }
        
    }else if(res>0 && FD_ISSET(fd_climsg,&fds)){
       n = read(fd_climsg,&buf,sizeof(CHAT));
       if(strcmp(buf.mensagem,"conectado")==0){
        printf("%s %s\n",buf.mensagem,buf.nomeconectado);
        pidconectado=buf.pidconectado;
        consultaOcupado=1;
        cliente.consulta=1;
       }else if(strcmp(buf.mensagem,"adeus")==0){

           printf("O Especialista %s acabou a consulta\n",buf.nomeconectado);
           cliente.consulta=0;
           consultaOcupado=0;
           strcpy(cmd,"desistir");
       }else if(strcmp(buf.mensagem,"desistir")==0){
            printf("O Especialista %s saiu do programa!\n",buf.nomeconectado);
            strcpy(cmd,"desistir");
        }else if(strcmp(buf.mensagem,"afk")==0){
            printf("O Especialista %s nao responde!\n",buf.nomeconectado); 
            strcpy(cmd,"desistir"); 
        }else{
            printf("[Recebi]:%s\n",buf.mensagem);
        }

    }
    }while(strcmp(cmd,"desistir")!=0);
    close(fd);
    close(fd_cli);
    close(fd_climsg);
    unlink(auxfdcli);
    unlink(auxfdclimsg); 
}