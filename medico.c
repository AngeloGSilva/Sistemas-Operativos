#include "medico.h"

//void cheio(int s){
    //printf("Nao existe vagas para mais especialistas!\n");
    //exit(0);
//}

//Variaveis globais (Ajuda o sigalarm)
int pidmed;
int pidconec;
int EmConsulta;
MEDICO temp;
void handler_function(int s){
    //Evitar ctrl+c
    printf("\nApenas sai com [sair]\n");
}

void sig_handler(int signum){
    int fd;
    CHAT buf;
    char aux[20];
    printf("Tempo de execucao acabou!(20 segundos)\n");
    //Avisa servidor que acabou inesperadamente
    fd=open(FIFO_SERVMED,O_WRONLY);
    strcpy(temp.chat.mensagem,"afk");
    write(fd,&temp,sizeof(MEDICO));
    close(fd);
    //Informa o cliente associado se existir
    if(EmConsulta==1){
        sprintf(aux,FIFO_CLIENTEMSG,pidconec);
        fd = open(aux,O_WRONLY);
        strcpy(buf.mensagem,"afk");
        strcpy(buf.nomeconectado,temp.nome);
        write(fd,&buf,sizeof(CHAT));
        close(fd);
    }
    sprintf(aux,FIFO_MEDICO,getpid());
    unlink(aux);
    sprintf(aux,FIFO_MEDICOMSG,getpid());
    unlink(aux);
    exit(0);
}

//void removido(int s){
    //printf("Removido da Lista de Especialistas!\n");
    //exit(0);
//}

void printMedicos(MEDICO med){
    printf("Nome:%s\n",med.nome);
    printf("Especialidade:%s\n",med.especialidade);
    printf("PID:%d\n",med.pid);
    printf("Ocupado:%d\n",med.ocupado);
}

int main(int argc,char *argv[]){
    if(argc<3){
        printf("ERRO no numero de inputs (nome)!\n");
        exit(33);
    }
    if(strcmp(argv[2],"ortopedia")!=0 && strcmp(argv[2],"estomatologia")!=0 && strcmp(argv[2],"neurologia")!=0 && strcmp(argv[2],"oftalmologia")!=0 && strcmp(argv[2],"geral")!=0){
        printf("[ERRO]Especialidade desconhecida!\n Nao lhe irá ser atribuido nenhum tipo de clientes!\n");
    }
    //signal(SIGUSR1,cheio);
    //signal(SIGUSR2,removido);
    signal(SIGALRM,sig_handler);
    signal(SIGINT, handler_function); //Ignorar ctrl+c
    int fd_med,fd,n,fd_medmsg,fd_aux,fdboth;
    int pidconectado,consultaOcupado;
    char str[40],auxfdMed[30],auxfdMEDmsg[30];
    char cmd[20];
    float res = -1;
    fd_set fds;
    struct timeval tempo = {5 , 0};
    CHAT buf;
    MEDICO med;
    strcpy(med.nome,argv[1]);
    strcpy(med.especialidade,argv[2]);
    med.ocupado=0; //valor inicial desocupado
    med.pid=getpid();
    strcpy(med.chat.mensagem,"default");
    printMedicos(med);
    //estrutura global
    temp.pid=getpid();
    strcpy(temp.nome,argv[1]);

    //Acesso ao fifo do servidor
    if(access(FIFO_SERVMED,F_OK)!= 0){
        printf("[ERRO]Fifo do servidor nao existe!\n");
        exit(1);
    }

    //Abrir fifo do servidor para escrita
    fd = open(FIFO_SERVMED,O_WRONLY);
    //printf("Abri o fifo do servidor");

    //Criar fifo do medico
    sprintf(auxfdMed,FIFO_MEDICO,med.pid);
    mkfifo(auxfdMed,0700);

    //Verificar se criou fifo do cliente
    if(access(auxfdMed,F_OK)!=0){
        printf("[ERRO]Fifo do medico nao existe!\n");
        exit(1);
    }

    fd_med = open(auxfdMed,O_RDWR);

    //Criar fifo do medico msg
    sprintf(auxfdMEDmsg,FIFO_MEDICOMSG,med.pid);
    mkfifo(auxfdMEDmsg,0700);

    //Verificar se criou fifo do medico msg
    if(access(auxfdMEDmsg,F_OK)!=0){
        printf("[ERRO]Fifo do medico nao existe!\n");
        exit(1);
    }
    
    fd_medmsg = open(auxfdMEDmsg,O_RDWR);

    //Enviar a informação para o servidor
    n = write(fd,&med,sizeof(MEDICO));
    //Esperar informação do balcao
    int flag=0;
    do{
    FD_ZERO(&fds);
    FD_SET(0,&fds);
    FD_SET(fd_med,&fds);
    FD_SET(fd_medmsg,&fds);
    tempo.tv_sec = 5;
    tempo.tv_usec = 0;
    fdboth = (fd_med > fd_medmsg)? fd_med : fd_medmsg;
    res = select(fdboth+1, &fds, NULL, NULL, &tempo);
    if(res == 0){
        if(flag == 0){
        flag = 1;
        alarm(20);
        }
        if(consultaOcupado==0)
            printf("Esperando um utente da especialidade %s...\n",med.especialidade);
        
    }else if(res>0 && FD_ISSET(0,&fds)){
        //alarm(20); //Acabar com 20 segundos de afk
        flag=0;
        scanf(" %[^\n]",cmd);
        
        if(strcmp(cmd,"sair")==0){
            //avisa o balcao 
            strcpy(med.chat.mensagem,"sair");
            n = write(fd,&med,sizeof(MEDICO));
            //Avisa o utente se existir
            if(consultaOcupado == 1){
                //printf("notificar cliente");
                printf("Consulta com o Utente %s acabou\n",buf.nomeconectado);
                sprintf(str,FIFO_CLIENTEMSG,pidconectado);
                fd_aux = open(str,O_WRONLY);
                strcpy(buf.mensagem,"desistir");
                strcpy(buf.nomeconectado,med.nome);
                n = write(fd_aux,&buf,sizeof(CHAT));
                close(fd_aux);
            }
        }else if(strcmp(cmd,"adeus")==0){
            //avisa o balcao
            strcpy(med.chat.mensagem,"adeus");
            n = write(fd,&med,sizeof(MEDICO));
            //avisa o Cliente 
            if(consultaOcupado == 1){
                printf("Consulta com o Utente %s acabou\n",buf.nomeconectado);
                sprintf(str,FIFO_CLIENTEMSG,pidconectado);
                fd_aux = open(str,O_WRONLY);
                strcpy(buf.mensagem,"adeus");
                strcpy(buf.nomeconectado,med.nome);
                n = write(fd_aux,&buf,sizeof(CHAT));
                close(fd_aux);
                med.ocupado = 0;
                consultaOcupado = 0;
                pidconec=0;
                EmConsulta=0;
            }else{
                printf("Nao existe consulta para terminar!\n");
            }
        }else if(strcmp(cmd,"print")==0){
                printMedicos(med);
        }else{
            strcpy(buf.mensagem,cmd);
            //buf.pidconectado=pidconectado;
            sprintf(str,FIFO_CLIENTEMSG,pidconectado);
            fd_aux = open(str,O_WRONLY);
            n = write(fd_aux,&buf,sizeof(CHAT));
            close(fd_aux);
        }
    }else if(res>0 && FD_ISSET(fd_med,&fds)){
        n=read(fd_med,&med,sizeof(MEDICO));
        consultaOcupado=med.ocupado;
        //receber a estrurura do medico de volta
        if(strcmp(med.chat.mensagem,"sucesso")==0){
            printf("Medico adicionado ao programa com sucesso!\n");
        }else if(strcmp(med.chat.mensagem,"kick")==0){
            printf("Balcao encerrou!\n");
            strcpy(cmd,"sair");
        }else if(strcmp(med.chat.mensagem,"cheio")==0){ //falta
            printf("Numero de medicos maximo!\n");
            strcpy(cmd,"sair");
        }else if(strcmp(med.chat.mensagem,"expulso")==0){ //falta
            printf("Expulso do programa pelo administrador\n");
            strcpy(cmd,"sair");
        }
    }else if(res>0 && FD_ISSET(fd_medmsg,&fds)){
        //Tratamento de mensagens
        n = read(fd_medmsg,&buf,sizeof(CHAT));
        if(strcmp(buf.mensagem,"conectado")==0){
        printf("%s %s\n",buf.mensagem,buf.nomeconectado);
        pidconec=buf.pidconectado;//GLOBAL
        EmConsulta=1; //Global
        pidconectado=buf.pidconectado;
        med.ocupado=1;
        consultaOcupado=1;
        }else if(strcmp(buf.mensagem,"desistir")==0){
            med.ocupado=0;
            consultaOcupado=0;
            pidconec=0;
            EmConsulta=0;
            printf("Utente %s acabou a consulta\n",buf.nomeconectado);
            //Avisa balcao que medico esta disponivel
            strcpy(med.chat.mensagem,"Disponivel");
            n=write(fd,&med,sizeof(MEDICO));

        }else if(strcmp(buf.mensagem,"adeus")==0){
            med.ocupado=0;
            consultaOcupado=0;
            pidconec=0;
            EmConsulta=0;
            printf("Consulta com o Utente %s acabou\n",buf.nomeconectado);
            strcpy(med.chat.mensagem,"Disponivel");
            n=write(fd,&med,sizeof(MEDICO));

        }else {
            printf("[Recebi]:%s\n",buf.mensagem);
        }
    }

    }while(strcmp(cmd,"sair")!=0 );
close(fd);
close(fd_med);
close(fd_medmsg);
unlink(auxfdMed);
unlink(auxfdMEDmsg);
}