#include "balcao.h"

void handler_function(int s){
    //Evitar ctrl+c
    printf("\nApenas sai com [encerra]\n");
}

int getposicao(CLIENTE *c,int pid,int tam){
    if(tam==0){
        return -1;
    }else if(tam == 1){
        return 0;
    }else{
        for(int i=0;i<tam;i++){
        if(c[i].pid == pid){
                return i;
            }
        }
    }
}


//com memoria dinamica acho q fica igual
void ordenaArray(CLIENTE *c, int numClientes){
    if(numClientes>1){
     CLIENTE aux;
     for (int contador = 0; contador < numClientes; ++contador) {
        for (int i = contador + 1; i < numClientes; ++i) {
         if (c[contador].gravidade < c[i].gravidade) {
            aux = c[contador];
            c[contador] = c[i];
            c[i] = aux; 
     }
   }
 }
 //Atualiza indices de pessoas à frente
    for(int i=0;i<numClientes;i++){
       // printf("Cliente %s na pos %d",c[i].nome,i); DEBUG
        c[i].nrFila = i;
    }
}
c[0].nrFila = 0;
//else
   // printf("Nao ordenei, So 1 elemento\n");
}


void MostraUtentes(CLIENTE *c,int numClientes,char *aux){
    if(numClientes==0){
        printf("------------------------\n");
        printf("Não existem utentes na fila de espera %s\n",aux);
        printf("------------------------\n");
        return;
    }

    if(strcmp(c->especialidade,"")!=0){
        printf("-----------%s-------------\n",c->especialidade);
    }

    for(int i=0;i<numClientes;i++){
    printf("------------------------\n");
    printf("Utente %d\n",i+1);
    printf("Nome:%s\n",c[i].nome);
    printf("Especialidade:%s\n",c[i].especialidade);
    printf("Prioridade:%d\n",c[i].gravidade); 
    printf("Consulta %d\n",c[i].consulta);
    printf("------------------------\n");
    }
    
}

void MostraMedicos(MEDICO *m,int numMedicos,CONSULTA *consultas,int tamconsultas){
    if(numMedicos==0){
        printf("Sem especialistas no sistema!!\n");
        return;
    }
    
    for(int i=0;i<numMedicos;i++){
        if(m[i].ocupado==0){
             printf("Nome:%s\n",m[i].nome);
             printf("Especialidade:%s\n",m[i].especialidade);
             if(m[i].ocupado==0)
                printf("Espera de um utente\n");
            //printf("PID: %d",m[i].pid); DEBUG
        }
    }
    for(int i=0;i<tamconsultas;i++){
        printf("Em consulta:\n");
        printf("Nome Especialista: %s\n",consultas[i].nomeMED);
        printf("Nome Utente:%s\n",consultas[i].nomeCLI);
    }
}

void removerConsulta(CONSULTA *consulta,int pidAux,int *tam){
    if((*tam)>1){
    int pos = 0;
    for(int i=0; i < (*tam); i++){
        if(consulta[i].pidMED == pidAux){
            pos = i;
            printf("[Medico]Removido a consulta entre Utente %s e especialista %s\n",consulta[i].nomeCLI, consulta[i].nomeMED);
        }
    }

    for(int i=0; i < (*tam); i++){
        if(consulta[i].pidCLI == pidAux){
            pos = i;
            printf("[Cliente]Removido a consulta entre Utente %s e especialista %s\n",consulta[i].nomeCLI, consulta[i].nomeMED);        }
    }

    for(int i = pos;i < (*tam); i++){
        consulta[i] = consulta[i+1];
    }
    (*tam)--;//por em comentario
    }else if((*tam)==1){
        (*tam)--;//por em comentario
        //e dar free(c) se nao estou em erro pq fica vazio
        printf("Removido a consulta entre Utente %s e especialista %s\n",consulta[0].nomeCLI, consulta[0].nomeMED);
    }else{
        printf("Nao existe consulta a remover\n");
    }
}

void mostraConsultas(CONSULTA *consultas,int tamconsultas){
    if(tamconsultas==0){
        printf("Sem consultas\n");
        return;
    }
    printf("--->Consultas:");
    for(int i=0;i<tamconsultas;i++){
        printf("---Especialidade: %s---\n",consultas[i].especialidade);
        printf("Utente:%s de pid %d\n",consultas[i].nomeCLI,consultas[i].pidCLI);
        printf("Especialista:%s de Pid %d\n",consultas[i].nomeMED,consultas[i].pidMED);
        printf("----------------------------");
    }
}

int medicosDisp(MEDICO *m,int tam){
    int md=0;
    for(int i=0;i<tam;i++){
        if(m[i].ocupado==0)
        md++;
    }
    return md;
}

void addCliente(CLIENTE *c, CLIENTE cliente,int *tam){

    strcpy(c[*tam].nome,cliente.nome);
    strcpy(c[*tam].especialidade,cliente.especialidade);
    strcpy(c[*tam].sintomas,cliente.sintomas);
    c[*tam].gravidade= cliente.gravidade;
    c[*tam].pid=cliente.pid;
    c[*tam].consulta = cliente.consulta;
    (*tam)++;
    printf("Cliente %s adicionado a fila de espera para %s\n",cliente.nome,cliente.especialidade);
}


void addMedico(MEDICO *m, MEDICO medico, int *tam){

    strcpy(m[*tam].nome,medico.nome);
    strcpy(m[*tam].especialidade,medico.especialidade);
    m[*tam].ocupado = medico.ocupado;
    m[*tam].pid = medico.pid;
    m[*tam].ocupado = medico.ocupado;
    (*tam)++;
}

void NovaConsulta(CONSULTA consultas,char *nomemed, char *nomecli,int pidmed,char *esp,int pidcli,int *tamconsultas){
    
    printf("Adicionei a consulta entre o especialista %s e o utente %s\n",nomemed,nomecli);
    strcpy(consultas.nomeCLI,nomecli);
    strcpy(consultas.nomeMED,nomemed);
    strcpy(consultas.especialidade,esp);
    consultas.pidCLI=pidcli;
    consultas.pidMED=pidmed;
    (*tamconsultas)++;
    
}

int remMedico(MEDICO *m, int pidAux, int *tam){
    if((*tam)>1){
    int pos = 0;
    for(int i=0; i < (*tam); i++){
        if(m[i].pid == pidAux && m[i].ocupado == 0){
            pos = i;
            printf("Removido o especialista %s\n",m[i].nome);
            for(int i = pos;i < (*tam); i++){
                m[i] = m[i+1];
            }
        }else if(m[i].pid == pidAux && m[i].ocupado == 1){
            printf("Especialista a atender um utente!\n");
            return 0;
        }
    }
    (*tam)--;
    return 1;
    }else if(m[0 ].pid == pidAux && *tam == 1 && m[0].ocupado == 0){
        (*tam)--;
        printf("Removido o especialista %s\n",m[0].nome);
        return 1;
    }else if(m[0].pid == pidAux && m[0].ocupado == 1){
        printf("Especialista a atender um utente!\n");
        return 0;
    }
    printf("Nehum especialista existe com esse Pid\n");
    return 0;
}


void remCliente(CLIENTE *c, int pidAux, int *tam){
    if((*tam)>1){
    int pos = 0;
    for(int i=0; i < (*tam); i++){
        if(c[i].pid == pidAux){
            pos = i;
            printf("Removido o utente %s da fila de espera %s\n",c[i].nome,c[i].especialidade);
        }
    }

    for(int i = pos;i < (*tam); i++){
        c[i] = c[i+1];
    }
    (*tam)--;//por em comentario
    }else{
        (*tam)--;//por em comentario
        printf("Removido o utente %s da fila de espera %s\n",c[0].nome,c[0].especialidade);
    }
}

int encontrarFila(CLIENTE *geral,int tamG,CLIENTE *oft,int tamO,CLIENTE *est,int tamE,CLIENTE *neu,int tamN,CLIENTE *ort,int tamOr, int pidAux){
   for(int i=0; i < tamG; i++){
        if(geral[i].pid == pidAux && geral[i].consulta == 0){
            return 1;
        }else if(geral[i].consulta == 1){
            printf("Utente em consulta!\n");
            return 0;
        }
    }
    for(int i=0; i < tamO; i++){
        if(oft[i].pid == pidAux && oft[i].consulta == 0){
            return 2;
        }else if(oft[i].consulta == 1){
            printf("Utente em consulta!\n");
            return 0;
        }
    }
    for(int i=0; i < tamE; i++){
        if(est[i].pid == pidAux && est[i].consulta == 0){
            return 3;
        }else if(est[i].consulta == 1){
            printf("Utente em consulta!\n");
            return 0;
        }
    }
    for(int i=0; i < tamN; i++){
        if(neu[i].pid == pidAux && neu[i].consulta == 0){
            return 4;
        }else if(neu[i].consulta == 1){
            printf("Utente em consulta!\n");
            return 0;
        }
    }
    for(int i=0; i < tamOr; i++){
        if(ort[i].pid == pidAux && ort[i].consulta == 0){
            return 5;
        }else if(ort[i].consulta == 1){
            printf("Utente em consulta!\n");
            return 0;
        }
    }
    //return 0;
}


void medico(MEDICO *m, int tamMed){
    for(int i=0; i<tamMed;i++){
        if(m[i].ocupado == 0){
            //associaConsulta();
        }
    }
}

void poeDesocupado(MEDICO *m, int pidAux, int tam){
    for(int i= 0; i<tam; i++){
        if(m[i].pid == pidAux){
            m[i].ocupado = 0;
        }
    }
}


void associar(MEDICO *medicos, int *medicosTam, CONSULTA *consultas,int *tamconsultas,CLIENTE *especialidades,int *espTam){
        CHAT buf;
        char auxPid[30];
        int n=0, fd_utmsg, fd_espmsg;
        for(int i=0;i<*medicosTam; i++){
            for(int j=0;j<*espTam;j++){
                if(medicos[i].ocupado==0){
                if(especialidades[j].consulta==0 && strcmp(especialidades[j].especialidade,medicos[i].especialidade)==0){
                    
                    //remove cliente e adiciona ao array das consultas
                    especialidades[j].consulta=1;
                    medicos[i].ocupado=1;

                    //Adicionar a consulta ao array
                    strcpy(consultas[*tamconsultas].nomeCLI,especialidades[j].nome);
                    strcpy(consultas[*tamconsultas].nomeMED,medicos[i].nome);
                    strcpy(consultas[*tamconsultas].especialidade,especialidades[j].especialidade);
                    consultas[*tamconsultas].pidCLI=especialidades[j].pid;
                    consultas[*tamconsultas].pidMED=medicos[i].pid;
                    (*tamconsultas)++;

                    //Envia a informação ao cliente
                    sprintf(auxPid,FIFO_CLIENTEMSG,especialidades[j].pid);
                    fd_utmsg = open(auxPid,O_WRONLY);
                    strcpy(buf.mensagem,"conectado");
                    strcpy(buf.nomeconectado,medicos[i].nome);
                    buf.pidconectado = medicos[i].pid;
                    n = write(fd_utmsg,&buf,sizeof(CHAT));
                    //printf("Enviei %d bytes ao utente\n",n);

                    //Envia informacao ao especialista
                    sprintf(auxPid,FIFO_MEDICOMSG,medicos[i].pid);
                    fd_espmsg = open(auxPid,O_WRONLY);
                    strcpy(buf.mensagem,"conectado");
                    strcpy(buf.nomeconectado,especialidades[j].nome);
                    buf.pidconectado = especialidades[j].pid;
                    //printf("Enviei %d bytes ao especialista\n",n);
                    n = write(fd_espmsg,&buf,sizeof(CHAT));

                    //remover do array geral
                    remCliente(especialidades,especialidades[j].pid,*(&espTam));
                    ordenaArray(especialidades,*espTam);
                    printf("Comecou a consulta da especialidade %s entre o utente %s e o especialista %s\n",especialidades->especialidade,especialidades[j].nome,medicos[i].nome);
                    close(fd_utmsg);
                    close(fd_espmsg);
                }
            }
        }
    }
}


int proConsulta(CONSULTA *c,int consultaTam,int pidAux){
    for(int i=0;i<consultaTam;i++){
        if(c[i].pidCLI == pidAux){
            return 1;
        }
    }
    return 0;
}

int medicosEsp(MEDICO *m, int tamMed, char *str){
    int cont=0;
    for(int i=0;i<tamMed;i++){
        if(strcmp(m[i].especialidade,str)==0)
            cont++;
    }
    return cont;
}   
/*
void atualizaNrEsp(MEDICO *m, int tamMed,CLIENTE *geral,int tamG,CLIENTE *oft,int tamO,CLIENTE *est,int tamE,CLIENTE *neu,int tamN,CLIENTE *ort,int tamOr){
     char auxPid[30];
     int fd_aux, n;
     for(int i=0; i < tamMed; i++){
        if(strcmp(m[i].especialidade,"geral")==0){
            int cont = medicosEsp(m,tamMed,"geral");
            for(int j=0; j<tamG; j++){
                geral[j].nrEsp = cont;
                sprintf(auxPid,FIFO_CLIENTE,geral[j].pid);
                fd_aux = open(auxPid,O_WRONLY);
                n=write(fd_aux,&geral[j],sizeof(CLIENTE));
                close(fd_aux);
            }
        }else if(strcmp(m[i].especialidade,"oftalmologia")==0){
            int cont = medicosEsp(m,tamMed,"oftalmologia");
            for(int j=0; j<tamO; j++){
                    oft[j].nrEsp=cont;
                    sprintf(auxPid,FIFO_CLIENTE,oft[j].pid);
                    fd_aux=open(auxPid,O_WRONLY);
                    n=write(fd_aux,&oft[j],sizeof(CLIENTE));
                    close(fd_aux);
            }
        }else if(strcmp(m[i].especialidade,"estomatologia")==0){
            int cont = medicosEsp(m,tamMed,"estomatologia");
            for(int j=0; j<tamE; j++){
                est[j].nrEsp = cont;
                sprintf(auxPid,FIFO_CLIENTE,est[j].pid);
                fd_aux = open(auxPid,O_WRONLY);
                n=write(fd_aux,&est[j],sizeof(CLIENTE));
                close(fd_aux);
            }
        }else if(strcmp(m[i].especialidade,"neurologia")==0){
            int cont = medicosEsp(m,tamMed,"neurologia");
            for(int j=0; j<tamN; j++){
                neu[j].nrEsp = cont;
                sprintf(auxPid,FIFO_CLIENTE,neu[j].pid);
                fd_aux = open(auxPid,O_WRONLY);
                n=write(fd_aux,&neu[j],sizeof(CLIENTE));
                close(fd_aux);
            }
        }else if(strcmp(m[i].especialidade,"ortopedia")==0){
            int cont = medicosEsp(m,tamMed,"ortopedia");
            for(int j=0; j<tamOr; j++){
                ort[j].nrEsp = cont;
                sprintf(auxPid,FIFO_CLIENTE,ort[j].pid);
                fd_aux = open(auxPid,O_WRONLY);
                n=write(fd_aux,&ort[j],sizeof(CLIENTE));
                close(fd_aux);
            }
        }   
    }
}
*/
void *ThreadmostraUtentes(void *dados){
    TDADOS *td=(TDADOS *)dados;
    do{
        printf("\n------------------------------------------------\n");
        printf("Ocupacao da fila Oftalmologia: %d\n",td->oftalTam);
        printf("Ocupacao da fila Neurologia: %d\n",td->neuroTam);
        printf("Ocupacao da fila Estomatologia: %d\n",td->estoTam);
        printf("Ocupacao da fila Ortopedia: %d\n",td->ortoTam);
        printf("Ocupacao da fila Geral: %d\n",td->geraltam);
        printf("------------------------------------------------\n");
        sleep(td->temp);
    }while(td->continua);
    pthread_exit(NULL);
}

void kickClientes(CLIENTE *c, int tamEsp){
    char auxfdcli[30];
    int fd_ut, n;    
    if(tamEsp>0){
        for(int i=0;i<tamEsp;i++){
                sprintf(auxfdcli,FIFO_CLIENTE,c[i].pid);
                strcpy(c[i].chat.mensagem,"kick");
                fd_ut = open(auxfdcli,O_WRONLY);
                n=write(fd_ut,&c[i],sizeof(CLIENTE));
                close(fd_ut);
        }
    }
}

int main(int argc,char *argv[],char *envp[]){

    //https://fsymbols.com/text-art/
printf("\n");
printf(" ███╗░░░███╗███████╗██████╗░██╗░█████╗░░█████╗░██╗░░░░░░██████╗░█████╗░\n");
printf(" ████╗░████║██╔════╝██╔══██╗██║██╔══██╗██╔══██╗██║░░░░░██╔════╝██╔══██╗\n");
printf(" ██╔████╔██║█████╗░░██║░░██║██║██║░░╚═╝███████║██║░░░░░╚█████╗░██║░░██║\n");
printf(" ██║╚██╔╝██║██╔══╝░░██║░░██║██║██║░░██╗██╔══██║██║░░░░░░╚═══██╗██║░░██║\n");
printf(" ██║░╚═╝░██║███████╗██████╔╝██║╚█████╔╝██║░░██║███████╗██████╔╝╚█████╔╝\n");
printf(" ╚═╝░░░░░╚═╝╚══════╝╚═════╝░╚═╝░╚════╝░╚═╝░░╚═╝╚══════╝╚═════╝░░╚════╝░\n");

    //signal(SIGINT, handler_function); //Ignorar ctrl+c
    int pEscrita[2];
    int pLeitura[2];
    int fd,fd_ut,fd_esp,fd_med,fdboth,n;
    int res;//apagar
    fd_set fds;
    float resS;
    //int estado;
    int buffer_admin;//Variaveis dos comandos do admin
    char *split;
    char auxPid[30],cmd[30],auxPidRemove[30],auxfdcli[30],auxfdmed[30];
    char resposta[30]= "\0";
    int flag_Out=0;
    struct timeval tempo= {5,0};
    int n_freq = 30;
    int maxClientes, maxMedicos;

    if(getenv ("MAXCLIENTES")  == NULL)
        maxClientes = 25;
    else
        maxClientes = atoi(getenv ("MAXCLIENTES"));
    
    if(getenv ("MAXMEDICOS")  == NULL)
        maxMedicos = 5;
    else
        maxMedicos = atoi(getenv ("MAXMEDICOS"));
        
    //Estrutura de Mensagens
    CHAT buf;

    //Estrutura de consultas
    CONSULTA consultas[maxMedicos];
    int tamconsultas=0;
    MEDICO medicos[maxMedicos]; //Array de medicos
    MEDICO m; //Medico teste buffer
    int medicosTam=0;

    //CLIENTE clientes[maxClientes]; //Array de clientes
    //int clientesTam=0;
    int oftalTam=0,neuroTam=0,estoTam=0,ortoTam=0,geralTam=0; //numero de elementos em cada array
    //Filas de espera
    CLIENTE oftalmologia[TamFila];
    CLIENTE neurologia[TamFila];
    CLIENTE estomatologia[TamFila];
    CLIENTE ortopedia[TamFila];
    CLIENTE geral[TamFila];
    CLIENTE c;      //Cliente teste buffer
    //printf("Criei o Classificador[FILHO]...\n"); //DEBUG;

    if(pipe(pEscrita)==-1){
        printf("Erro ao criar o pipe de escrita\n");
        exit(33);
    }
    if(pipe(pLeitura)==-1){
        printf("Erro ao criar o pipe de escrita\n");
        exit(33);
    }
    
    res=fork();
        if(res==0){
                // pipe escrita
                close(0);
                dup(pEscrita[0]);
                close(pEscrita[0]);
                close(pEscrita[1]);
                // pipe leitura
                close(1);
                dup(pLeitura[1]);
                close(pLeitura[1]);
                close(pLeitura[0]);
                //printf("[FILHO]Sou o %d\n",getpid());
                execl("classificador", "classificador",NULL);
                printf("[FILHO] Erro,Comando nao existe!\n");
                exit(33);
        }
        close(pEscrita[0]);

 //setup do pipe do server

//verificar se existe o fifo (Cliente)

    if(access(FIFO_SERVCLI, F_OK) == 0){
        printf("[ERRO] Fifo ja existe!\n");
        exit(1);
    }
//criar o fifo
    mkfifo(FIFO_SERVCLI,0700);
   // printf("Criei o fifo do servidor com o cliente\n");

//Abrir o fifo
    fd = open(FIFO_SERVCLI,O_RDWR); //RD_ONLY
    //printf("Abri o fifo do cliente\n");

    //verificar se existe o fifo (medico)

    if(access(FIFO_SERVMED, F_OK) == 0){
        printf("[ERRO] Fifo ja existe!\n");
        exit(1);
    }
    //criar o fifo
    mkfifo(FIFO_SERVMED,0700);
    //printf("Criei o fifo do servidor com o medico\n");

    //Abrir o fifo
    fd_med = open(FIFO_SERVMED,O_RDWR); //RD_ONLY
    //printf("Abri o fifo do medico\n");

    //Thread de mostrar utentes
    TDADOS tdata[1];
    pthread_t tid[1];
    pthread_create(&tid[0],NULL,ThreadmostraUtentes,(void *)&tdata[0]);
do{
    fflush(stdout);
    FD_ZERO(&fds);
    FD_SET(0,&fds);
    FD_SET(fd,&fds);
    FD_SET(fd_med,&fds);
    tempo.tv_sec= 5;
    tempo.tv_usec = 0;
    //Preencher com novos dados para leitura na thread
    tdata[0].continua=1;
    tdata[0].geral = geral;
    tdata[0].oftalmologia = oftalmologia;
    tdata[0].estomatologia = estomatologia;
    tdata[0].neurologia = neurologia;
    tdata[0].ortopedia = ortopedia;
    tdata[0].consultas = consultas;
    tdata[0].geraltam = geralTam;
    tdata[0].oftalTam = oftalTam;
    tdata[0].estoTam = estoTam;
    tdata[0].neuroTam = neuroTam;
    tdata[0].ortoTam = ortoTam;
    tdata[0].consultaTam = tamconsultas;
    tdata[0].temp=n_freq;

    fdboth = (fd > fd_med)  ? fd : fd_med;
    resS = select(fdboth + 1,&fds,NULL,NULL,&tempo);
    if(resS==0){ //LINHA DE COMANDOS
        //Tornar em thread
        //printf("Ocupacao da fila Oftalmologia: %d\n",oftalTam);
        //printf("Ocupacao da fila Neurologia: %d\n",neuroTam);
        //printf("Ocupacao da fila Estomatologia: %d\n",estoTam);
        //printf("Ocupacao da fila Ortopedia: %d\n",ortoTam);
        //printf("Ocupacao da fila Geral: %d\n",geralTam);
        
    }else if(resS > 0 && FD_ISSET(0,&fds)){//LINHA DE COMANDOS
        //Implementar comandoss
        scanf("%s",cmd);
        
        if(strcmp(cmd,"utentes")==0){
            MostraUtentes(oftalmologia,oftalTam,"oftalmologia");
            MostraUtentes(neurologia,neuroTam,"neurologia");
            MostraUtentes(estomatologia,estoTam,"estomatologia");
            MostraUtentes(ortopedia,ortoTam,"ortopedia");
            MostraUtentes(geral,geralTam,"geral");
            mostraConsultas(consultas,tamconsultas);
        }else if(strcmp(cmd,"especialistas")==0){
            MostraMedicos(medicos,medicosTam,consultas,tamconsultas);
        }else if(strcmp (cmd,"delut")==0){ //SEGMENTATION FAULT SE NAO FOR COMO DEVE DE SER
            scanf("%d",&buffer_admin);
            if(proConsulta(consultas, tamconsultas,buffer_admin)==0){
                CLIENTE cliAux;
            switch (encontrarFila(geral,geralTam,oftalmologia,oftalTam,estomatologia,estoTam,neurologia,neuroTam,ortopedia,ortoTam,buffer_admin)){
            case 1:
                remCliente(geral,buffer_admin,&geralTam);
                ordenaArray(geral,geralTam);
                sprintf(auxPid,FIFO_CLIENTE,buffer_admin);
                fd_ut=open(auxPid,O_WRONLY);
                strcpy(cliAux.chat.mensagem,"expulso");
                write(fd_ut,&cliAux,sizeof(CLIENTE));
                close(fd_ut);
                //kill(buffer_admin,SIGUSR2);
                break;
            case 2:
                remCliente(oftalmologia,buffer_admin,&oftalTam);
                ordenaArray(oftalmologia,oftalTam);
                sprintf(auxPid,FIFO_CLIENTE,buffer_admin);
                fd_ut=open(auxPid,O_WRONLY);
                strcpy(cliAux.chat.mensagem,"expulso");
                write(fd_ut,&cliAux,sizeof(CLIENTE));
                close(fd_ut);
                break;
            case 3:
                remCliente(estomatologia,buffer_admin,&estoTam);
                ordenaArray(estomatologia,estoTam);
                sprintf(auxPid,FIFO_CLIENTE,buffer_admin);
                fd_ut=open(auxPid,O_WRONLY);
                strcpy(cliAux.chat.mensagem,"expulso");
                write(fd_ut,&cliAux,sizeof(CLIENTE));
                close(fd_ut);
                break;
            case 4:
                remCliente(neurologia,buffer_admin,&neuroTam);
                ordenaArray(neurologia,neuroTam);
                sprintf(auxPid,FIFO_CLIENTE,buffer_admin);
                fd_ut=open(auxPid,O_WRONLY);
                strcpy(cliAux.chat.mensagem,"expulso");
                write(fd_ut,&cliAux,sizeof(CLIENTE));
                close(fd_ut);
                break;
            case 5:
                remCliente(ortopedia,buffer_admin,&ortoTam);
                ordenaArray(ortopedia,ortoTam);
                sprintf(auxPid,FIFO_CLIENTE,buffer_admin);
                fd_ut=open(auxPid,O_WRONLY);
                strcpy(cliAux.chat.mensagem,"expulso");
                write(fd_ut,&cliAux,sizeof(CLIENTE));
                close(fd_ut);
                break;
            default:
                printf("Pid nao existe!\n");
                break;
            }
            }else
            printf("Cliente nao removido.Em consulta\n");
            //elimina por pid clientes
        }else if(strcmp(cmd,"delesp")==0){
            scanf("%d",&buffer_admin);
            if(remMedico(medicos,buffer_admin, &medicosTam)==1){
                MEDICO medAux;
                sprintf(auxPid,FIFO_MEDICO,buffer_admin);
                fd_esp=open(auxPid,O_WRONLY);
                strcpy(medAux.chat.mensagem,"expulso");
                write(fd_esp,&medAux,sizeof(MEDICO));
                close(fd_esp);

            }
            //kill(buffer_admin,SIGUSR2)
            //elimina por pid medicos
        }else if(strcmp (cmd,"freq")==0){
            scanf("%d",&buffer_admin);
            if(buffer_admin>=0){
                n_freq=buffer_admin;
                printf("Intervalo novo:%d\n",buffer_admin);
                //muda o tempo    
            }
        }else if(strcmp (cmd,"encerra")==0){
            //acabar os clientes que nao estao em consulta
            kickClientes(geral,geralTam);
            kickClientes(neurologia,neuroTam);
            kickClientes(oftalmologia,oftalTam);
            kickClientes(estomatologia,estoTam);
            kickClientes(ortopedia,ortoTam);

            //eliminar mais clientes que estao em consulta
            for(int i=0;i<tamconsultas;i++){
                sprintf(auxfdcli,FIFO_CLIENTE,consultas[i].pidCLI);
                strcpy(c.chat.mensagem,"kick");
                fd_ut = open(auxfdcli,O_WRONLY);
                n=write(fd_ut,&c,sizeof(CLIENTE));
                close(fd_ut);
            }
            //acabar os medicos
            for(int i=0;i<medicosTam;i++){
                sprintf(auxfdmed,FIFO_MEDICO,medicos[i].pid);
                strcpy(m.chat.mensagem,"kick");
                fd_esp = open(auxfdmed,O_WRONLY);
                n=write(fd_esp,&m,sizeof(MEDICO));
                close(fd_esp);
            }

        }else{
            printf("Comando nao identificado\n");
            }
/*
            MostraMedicos(medicos,medicosTam);
            remMedico(medicos,medicos[0].pid, &medicosTam);
            remMedico(medicos,medicos[1].pid, &medicosTam);
            MostraMedicos(medicos,medicosTam);
*/
    }else if(resS>0 && FD_ISSET(fd,&fds)){
    //printf("Receber informacao do cliente...\n");
    n=read(fd,&c,sizeof(CLIENTE));
    if(strcmp(c.chat.mensagem,"default")==0){
    strcat(c.sintomas,"\n"); // porque faz o classificador funcionar
    //Comunicação com o classificador
    res = write(pEscrita[1],c.sintomas,strlen(c.sintomas));
    if(res==-1){
        printf("[Erro]Falha na Escrita \n");
        exit(33);
    }
    //Teste de acesso ao classificador
    //printf("Enviei %d bytes..\n",res);
    res = read(pLeitura[0],resposta,sizeof(resposta));
    if(res == -1){
        printf("[Erro]Falha na Leitura \n");
        exit(33);
    }
    
    split = strtok(resposta, " "); //percorre a string até encontrar um espaço

                    strcpy(c.especialidade, split);

                    split = strtok(NULL, "\n"); // continua a percorrer a string até ao fim

                    int num = atoi(split); // converte o valor para inteiro

                    c.gravidade = num;

                //Teste do output do classificador
                //printf("%s %d\n",c.especialidade,c.gravidade);
    //mostra cliente quando é adicionado
    printf("Nome:%s\n",c.nome);
    //printf("Sintomas:%s",c.sintomas);
    printf("Especialidade:%s\n",c.especialidade);
    printf("Prioridade:%d\n",c.gravidade);
    printf("Pid :%d\n",c.pid); //DEBUG
    if(strcmp(c.especialidade,"oftalmologia")==0){
        //printf("NO ARRAY oftalmologia\n");
        if(oftalTam<TamFila){
            //adiciona ao array
            addCliente(oftalmologia, c, &oftalTam);
            ordenaArray(oftalmologia,oftalTam);
            c.nrFila = getposicao(oftalmologia,c.pid,oftalTam);
            c.nrEsp = medicosEsp(medicos,medicosTam,"oftalmologia");
            //mensagem de sucesso
            //coloca(clientes,c,&clientesTam);
            associar(medicos,&medicosTam,consultas,&tamconsultas,oftalmologia,&oftalTam);
        }else{
            printf("Tentativa de contacto do cliente:%s, com os sintomas %s. \n[SEM ESPACO NA FILA %s]\n",c.nome,c.sintomas,c.especialidade);
            sprintf(auxPid,FIFO_CLIENTE,c.pid);
            fd_ut=open(auxPid,O_WRONLY);
            strcpy(c.chat.mensagem,"cheio");
            write(fd_ut,&c,sizeof(CLIENTE));
            close(fd_ut);
            //kill(c.pid,SIGUSR1); : DEBUG
            c.pid=-1; //para nao dar write
        }
            
    }else if(strcmp(c.especialidade,"neurologia")==0){
        //printf("NO ARRAY neurologia\n");
        if(neuroTam<TamFila){
            //adiciona ao array
            addCliente(neurologia, c, &neuroTam);
            ordenaArray(neurologia,neuroTam);
            c.nrFila = getposicao(neurologia,c.pid,neuroTam);
            c.nrEsp = medicosEsp(medicos,medicosTam,"neurologia");
            //coloca(clientes,c,&clientesTam);
            associar(medicos,&medicosTam,consultas,&tamconsultas,neurologia,&neuroTam);
        }else{
            printf("Tentativa de contacto do cliente:%s, com os sintomas %s. \n[SEM ESPACO NA FILA %s]\n",c.nome,c.sintomas,c.especialidade);
            sprintf(auxPid,FIFO_CLIENTE,c.pid);
            fd_ut=open(auxPid,O_WRONLY);
            strcpy(c.chat.mensagem,"cheio");
            write(fd_ut,&c,sizeof(CLIENTE));
            close(fd_ut);
            //kill(c.pid,SIGUSR1); : DEBUG
            c.pid=-1; //para nao dar write
        }

    }else if(strcmp(c.especialidade,"estomatologia")==0){
        //printf("NO ARRAY estomatologia\n");
        if(estoTam<TamFila){
            //adiciona ao array
            addCliente(estomatologia, c, &estoTam);
            ordenaArray(estomatologia,estoTam);
            c.nrFila = getposicao(estomatologia,c.pid,estoTam);
            c.nrEsp = medicosEsp(medicos,medicosTam,"estomatologia");
            //coloca(clientes,c,&clientesTam);
            associar(medicos,&medicosTam,consultas,&tamconsultas,estomatologia,&estoTam);
        }else{
            printf("Tentativa de contacto do cliente:%s, com os sintomas %s. \n[SEM ESPACO NA FILA %s]\n",c.nome,c.sintomas,c.especialidade);
            sprintf(auxPid,FIFO_CLIENTE,c.pid);
            fd_ut=open(auxPid,O_WRONLY);
            strcpy(c.chat.mensagem,"cheio");
            write(fd_ut,&c,sizeof(CLIENTE));
            close(fd_ut);
            //kill(c.pid,SIGUSR1); : DEBUG
            c.pid=-1; //para nao dar write
        }
            

    }else if(strcmp(c.especialidade,"ortopedia")==0){
        //printf("NO ARRAY ortopedia\n");
        if(ortoTam<TamFila){
            //adiciona ao array
            addCliente(ortopedia, c, &ortoTam);
            ordenaArray(ortopedia,ortoTam);
            c.nrFila = getposicao(ortopedia,c.pid,ortoTam);
            c.nrEsp = medicosEsp(medicos,medicosTam,"ortopedia");
            //coloca(clientes,c,&clientesTam);
            associar(medicos,&medicosTam,consultas,&tamconsultas,ortopedia,&ortoTam);
        }else{
            printf("Tentativa de contacto do cliente:%s, com os sintomas %s. \n[SEM ESPACO NA FILA %s]\n",c.nome,c.sintomas,c.especialidade);
            sprintf(auxPid,FIFO_CLIENTE,c.pid);
            fd_ut=open(auxPid,O_WRONLY);
            strcpy(c.chat.mensagem,"cheio");
            write(fd_ut,&c,sizeof(CLIENTE));
            close(fd_ut);
            //kill(c.pid,SIGUSR1); : DEBUG
            c.pid=-1; //para nao dar write
        }
    }else{
        if(geralTam<TamFila){
            //adiciona ao array
            addCliente(geral, c, &geralTam);
            ordenaArray(geral,geralTam);
            c.nrFila = getposicao(geral,c.pid,geralTam);
            c.nrEsp = medicosEsp(medicos,medicosTam,"geral");
            //coloca(clientes,c,&clientesTam);
            associar(medicos,&medicosTam,consultas,&tamconsultas,geral,&geralTam);
        }else{
            printf("Tentativa de contacto do cliente:%s, com os sintomas %s. \n[SEM ESPACO NA FILA %s]\n",c.nome,c.sintomas,c.especialidade);
            sprintf(auxPid,FIFO_CLIENTE,c.pid);
            fd_ut=open(auxPid,O_WRONLY);
            strcpy(c.chat.mensagem,"cheio");
            write(fd_ut,&c,sizeof(CLIENTE));
            close(fd_ut);
            //kill(c.pid,SIGUSR1); : DEBUG
            c.pid=-1; //para nao dar write
        }
    }

if(c.pid!=-1){ //Se foi aceite
    //Abrir pipe do cliente para comunicação
    sprintf(auxPid,FIFO_CLIENTE,c.pid);
    //TESTE printf("%s",auxPid);
    fd_ut = open(auxPid,O_WRONLY);
    //Envia a informação ao cliente
    strcpy(c.chat.mensagem,"sucesso");
    n = write(fd_ut,&c,sizeof(CLIENTE));
}
    }else if(strcmp(c.chat.mensagem,"sair")==0){ //Comando de sair
    if(strcmp(c.especialidade,"oftalmologia")==0){
        if(c.consulta == 1){
            remCliente(oftalmologia,c.pid,&oftalTam);
            ordenaArray(oftalmologia,oftalTam);
        }

        for(int i=0;i<tamconsultas;i++){
            if(c.pid == consultas[i].pidCLI){
                removerConsulta(consultas,consultas[i].pidCLI,&tamconsultas);
            }
        }

        printf("Cliente %s saiu do programa\n",c.nome);
        
        //Informa clientes de neurologia do seu número na fila
        
        for(int j=0;j<oftalTam;j++){
            strcpy(oftalmologia[j].chat.mensagem,"atualiza");
            sprintf(auxPidRemove,FIFO_CLIENTE,oftalmologia[j].pid);
            fd_ut = open(auxPidRemove,O_WRONLY);
            //printf("%s %d",c.nome,c.nrFila); DEBUG
            n=write(fd_ut,&oftalmologia[j],sizeof(CLIENTE));
            close(fd_ut);
        }
        
        
           // printf("Atualizei os clientes do seu numero da fila\n");

    }else if(strcmp(c.especialidade,"neurologia")==0){
        if(c.consulta==0){
            remCliente(neurologia,c.pid,&neuroTam);
            ordenaArray(neurologia,neuroTam);
        }

        for(int i=0;i<tamconsultas;i++){
            if(c.pid == consultas[i].pidCLI){
                removerConsulta(consultas,consultas[i].pidCLI,&tamconsultas);
            }
        }
        printf("Cliente %s saiu do programa\n",c.nome);
        //Informa clientes de neurologia do seu número na fila
        
        for(int j=0;j<neuroTam;j++){
            strcpy(neurologia[j].chat.mensagem,"atualiza");
            sprintf(auxPidRemove,FIFO_CLIENTE,neurologia[j].pid);
            fd_ut = open(auxPidRemove,O_WRONLY);
            //printf("%s %d",c.nome,c.nrFila);
            n=write(fd_ut,&neurologia[j],sizeof(CLIENTE));
            close(fd_ut);
        }
            
    }else if(strcmp(c.especialidade,"estomatologia")==0){
        //So deve remover utente se nao estava em consulta
        if(c.consulta==0){
            remCliente(estomatologia,c.pid,&estoTam);
            ordenaArray(estomatologia,estoTam);
        }

        for(int i=0;i<tamconsultas;i++){
            if(c.pid == consultas[i].pidCLI){
                removerConsulta(consultas,consultas[i].pidCLI,&tamconsultas);
            }
        }

        printf("Cliente %s saiu do programa\n",c.nome);
        //Informa clientes de neurologia do seu número na fila
        
        for(int j=0;j<estoTam;j++){
            strcpy(estomatologia[j].chat.mensagem,"atualiza");
            sprintf(auxPidRemove,FIFO_CLIENTE,estomatologia[j].pid);
            fd_ut = open(auxPidRemove,O_WRONLY);
            //printf("%s %d",c.nome,c.nrFila);
            n=write(fd_ut,&estomatologia[j],sizeof(CLIENTE));
            close(fd_ut);
        }

    }else if(strcmp(c.especialidade,"ortopedia")==0){
        //So deve remover utente se nao estava em consulta
        if(c.consulta==0){
            //printf("nao esta em consulta\n\n\n");
            remCliente(ortopedia,c.pid,&ortoTam);
            ordenaArray(ortopedia,ortoTam);
        }

        for(int i=0;i<tamconsultas;i++){
            if(c.pid == consultas[i].pidCLI){
                removerConsulta(consultas,consultas[i].pidCLI,&tamconsultas);
            }
        }

        printf("Cliente %s saiu do programa\n",c.nome);

        //Informa clientes de neurologia do seu número na fila
        
        for(int j=0;j<ortoTam;j++){
            strcpy(ortopedia[j].chat.mensagem,"atualiza");
            sprintf(auxPidRemove,FIFO_CLIENTE,ortopedia[j].pid);
            fd_ut = open(auxPidRemove,O_WRONLY);
            //printf("%s %d",c.nome,c.nrFila);
            n=write(fd_ut,&ortopedia[j],sizeof(CLIENTE));
            close(fd_ut);
        }

    }else if(strcmp(c.especialidade,"geral")==0){
        //printf("\n\nO cliente vai sair\n\n %d",geralTam);
        //So deve remover utente se nao estava em consulta
        if(c.consulta==0){
            remCliente(geral,c.pid,&geralTam);
            ordenaArray(geral,geralTam);
        }

        for(int i=0;i<tamconsultas;i++){
            if(c.pid == consultas[i].pidCLI){
                removerConsulta(consultas,consultas[i].pidCLI,&tamconsultas);
            }
        }

        printf("Cliente %s saiu do programa\n",c.nome);
        
        //Informa clientes de neurologia do seu número na fila
        
        for(int j=0;j<geralTam;j++){
            strcpy(geral[j].chat.mensagem,"atualiza");
            sprintf(auxPidRemove,FIFO_CLIENTE,geral[j].pid);
            fd_ut = open(auxPidRemove,O_WRONLY);
            //printf("%s %d",c.nome,c.nrFila);
            n=write(fd_ut,&geral[j],sizeof(CLIENTE));
            close(fd_ut);
        }
    }else{
        printf("Comando nao identificado\n");
    }
    }
    
    }else if(resS>0 && FD_ISSET(fd_med,&fds)){
        n=read(fd_med,&m,sizeof(MEDICO));
        //printf("Nome:%s, Especialidade:%s,Ocupado:%d,PID:%d\n",m.nome,m.especialidade,m.ocupado,m.pid);
        if(strcmp(m.chat.mensagem,"default") == 0){
            if(medicosTam<maxMedicos){
                sprintf(auxPid,FIFO_MEDICO,m.pid);
                strcpy(m.chat.mensagem,"sucesso");
                fd_esp = open(auxPid,O_WRONLY);
                n = write(fd_esp,&m,sizeof(MEDICO)); //Dados de volta ao medico
                close(fd_esp);
                addMedico(medicos,m,&medicosTam);
                //Avisa balcao
                printf("Medico %s da especialidade %s juntou-se\n",m.nome,m.especialidade);
                //MostraMedicos(medicos,medicosTam,consultas,tamconsultas);
                //Atualiza numero de medicos nos clientes
                //atualizaNrEsp(medicos,medicosTam,geral,geralTam,oftalmologia,oftalTam,estomatologia,estoTam,neurologia,neuroTam,ortopedia,ortoTam);
                //Na criação do medico,associa
                associar(medicos,&medicosTam,consultas,&tamconsultas,geral,&geralTam);
                associar(medicos,&medicosTam,consultas,&tamconsultas,oftalmologia,&oftalTam);
                associar(medicos,&medicosTam,consultas,&tamconsultas,estomatologia,&estoTam);
                associar(medicos,&medicosTam,consultas,&tamconsultas,neurologia,&neuroTam);
                associar(medicos,&medicosTam,consultas,&tamconsultas,ortopedia,&ortoTam);
        }else{
            printf("[Erro] Numero maximo de medicos alcancado!\n");
            sprintf(auxPid,FIFO_MEDICO,buffer_admin);
            fd_med=open(auxPid,O_WRONLY);
            strcpy(m.chat.mensagem,"cheio");
            write(fd_med,&m,sizeof(MEDICO));
            close(fd_med);
            //kill(m.pid,SIGUSR1);
            m.pid=-1;
        }
        }else if(strcmp(m.chat.mensagem,"sair") == 0){
            //nao interessa estar ocupado ou desocupado, tem de terminar
            poeDesocupado(medicos,m.pid,medicosTam); //para passar a verificação da função
            if(remMedico(medicos,m.pid,&medicosTam)==1){
                printf("Medico %s saiu do sistema\n",m.nome);
                removerConsulta(consultas,m.pid,&tamconsultas);
                //remove a consulta das consultas, pelo pid do medico
            }
        
        }else if(strcmp(m.chat.mensagem,"afk") == 0){
            poeDesocupado(medicos,m.pid,medicosTam); //para passar a verificação da função
            if(remMedico(medicos,m.pid,&medicosTam)==1){
                printf("Medico %s sem resposta(20 segundos)\n",m.nome);
                removerConsulta(consultas,m.pid,&tamconsultas);
                //remove a consulta das consultas, pelo pid do medico
            }
        }else if(strcmp(m.chat.mensagem,"adeus")==0){
            //poe o medico desocupado
            for(int i=0;i<medicosTam;i++){
                if(medicos[i].pid == m.pid){
                    medicos[i].ocupado=0;
                }
            }
            for(int i=0;i<tamconsultas;i++){
                if(consultas[i].pidMED == m.pid){
                    printf("[Medico]Consulta do Medico %s com o utente %s acabou!\n",consultas[i].nomeMED,consultas[i].nomeCLI);
                    removerConsulta(consultas,consultas[i].pidMED,&tamconsultas);
                    //remover a consulta das consultas, pelo Pid do medico
                }
            }
            associar(medicos,&medicosTam,consultas,&tamconsultas,geral,&geralTam);
            associar(medicos,&medicosTam,consultas,&tamconsultas,oftalmologia,&oftalTam);
            associar(medicos,&medicosTam,consultas,&tamconsultas,estomatologia,&estoTam);
            associar(medicos,&medicosTam,consultas,&tamconsultas,neurologia,&neuroTam);
            associar(medicos,&medicosTam,consultas,&tamconsultas,ortopedia,&ortoTam);
            //remover a consulta das consultas, pelo Pid do medico OU AQUI TANTO FAZ
        }else if(strcmp(m.chat.mensagem,"Disponivel")==0){
            for(int i=0;i<medicosTam;i++){
                if(medicos[i].pid == m.pid){
                    medicos[i].ocupado=0;
                }
            }
            associar(medicos,&medicosTam,consultas,&tamconsultas,geral,&geralTam);
            associar(medicos,&medicosTam,consultas,&tamconsultas,oftalmologia,&oftalTam);
            associar(medicos,&medicosTam,consultas,&tamconsultas,estomatologia,&estoTam);
            associar(medicos,&medicosTam,consultas,&tamconsultas,neurologia,&neuroTam);
            associar(medicos,&medicosTam,consultas,&tamconsultas,ortopedia,&ortoTam);
        }
        /*else if(strcmp(m.chat.mensagem,"adeus")==0 && m.ocupado == 1){
               for(int i=0;i<tamconsultas;i++){
                if(consultas[i].pidMED == m.pid){
                    strcpy(c.chat.mensagem,"EspAdeus");
                    remCliente(geral,consultas[i].pidCLI,&geralTam);
                    ordenaArray(geral,geralTam);
                    sprintf(auxPid,FIFO_CLIENTE,consultas[i].pidCLI);
                    fd_ut = open(auxPid,O_WRONLY);
                    n = write(fd_ut,&c,sizeof(CLIENTE));
                    close(fd_ut);
                    for(int k=0;k<medicosTam;k++){
                        if(medicos[k].pid == m.pid){
                            medicos[k].ocupado=0;
                        }
                    }
                }
            } 
            printf("Especialista %s tentou terminar consulta que nao existe!\n",m.nome);
        }*/
    }
    //Associar os medicos aos clientes estrutura
    /*
    for(int i=0;i<medicosTam;i++){
            //printf("Medico disponivel\n");
        for(int j=0;j < geralTam;j++){
            if(medicos[i].ocupado==0){
                if(geral[j].consulta==0 && strcmp(geral[j].especialidade,medicos[i].especialidade)==0){
                    medicos[i].ocupado=1;

                    //Envia a informação ao cliente
                    sprintf(auxPid,FIFO_CLIENTEMSG,geral[j].pid);
                    fd_utmsg = open(auxPid,O_WRONLY);
                    strcpy(buf.mensagem,"conectado");
                    strcpy(buf.nomeconectado,medicos[i].nome);
                    buf.pidconectado = medicos[i].pid;
                    n = write(fd_utmsg,&buf,sizeof(CHAT));
                    printf("Enviei %d bytes ao utente\n",n);

                    //Envia informacao ao especialista
                    sprintf(auxPid,FIFO_MEDMSG,medicos[i].pid);
                    fd_espmsg = open(auxPid,O_WRONLY);
                    strcpy(buf.mensagem,"conectado");
                    strcpy(buf.nomeconectado,geral[j].nome);
                    buf.pidconectado = geral[j].pid;
                    printf("Enviei %d bytes ao especialista\n",n);
                    n = write(fd_espmsg,&buf,sizeof(CHAT));

                    //Adicionar a consulta ao array
                    strcpy(consultas[tamconsultas].nomeCLI,geral[j].nome);
                    strcpy(consultas[tamconsultas].nomeMED,medicos[i].nome);
                    strcpy(consultas[tamconsultas].especialidade,geral[j].especialidade);
                    consultas[tamconsultas].pidCLI=geral[j].pid;
                    consultas[tamconsultas].pidMED=medicos[i].pid;
                    tamconsultas++;

                    //remover do array geral
                    remCliente(geral,geral[0].pid,&geralTam);
                    ordenaArray(geral,geralTam);
                    
                    printf("\n\nConsultas TAM:%d\n\n",tamconsultas);
                    close(fd_utmsg);
                    close(fd_espmsg);
                }
            }
        }
    }
    */

    //Ordenar as filas por prioridade
}while(strcmp(cmd,"encerra") != 0);
write(pEscrita[1],"#fim\n",5); //Acabar o processo filho (classificador)
//wait(&estado);
//printf("[PAI] O filho terminou com %d.\n",WEXITSTATUS(estado));
tdata[0].continua=0; // acabar a thread

close(pEscrita[0]);
close(pLeitura[1]);
close(fd);
close(fd_med);
unlink(FIFO_SERVCLI);
unlink(FIFO_SERVMED);
}
