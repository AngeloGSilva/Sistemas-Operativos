#define TAMNOME 20
#define TAMSINTOMA 50
#define TAMESPECIALIDADE 25
#define TAMDEFAULT 40
#define TamFila 5
#define TAMMENSAGEM 100

#define FIFO_SERVCLI "balcli" //Server

#define FIFO_SERVMED "balcmed" //Server

#define FIFO_CLIENTE "Ut%d" //Receber estrutras CLIENTE

#define FIFO_CLIENTEMSG "CliMsg%d" //Receber estruturas CHAT

#define FIFO_MEDICO "Esp%d" //Receber estruturas MEDICO

#define FIFO_MEDICOMSG "EspMsg%d" //Receber estruturas CHAT



typedef struct {
	char mensagem[TAMMENSAGEM];
	char nomeconectado[TAMNOME];
	int pidconectado;
}CHAT;

typedef struct {
	char nome[TAMNOME];
	char sintomas[TAMSINTOMA];
	char especialidade[TAMESPECIALIDADE];
	int gravidade;
	int consulta; // 0 se nao está, 1 se está
	int nrFila;
	int nrEsp;
	int pid;
	CHAT chat;
}CLIENTE;

typedef struct{
	char nome[TAMNOME];
	char especialidade[TAMESPECIALIDADE];
	int ocupado; //1 ocupado,0 desocupado
	int pid;
	CHAT chat;
}MEDICO;

typedef struct{
	char nomeCLI[TAMNOME];
	int pidCLI;
	char nomeMED[TAMNOME];
	int pidMED;
	char especialidade[TAMESPECIALIDADE];
}CONSULTA;

//estruturas com os arrays das filas (p/memoria dinamica)

typedef struct{
	int continua;
	CLIENTE *geral;
	int geraltam;
	CLIENTE *oftalmologia;
	int oftalTam;
	CLIENTE *estomatologia;
	int estoTam;
	CLIENTE *neurologia;
	int neuroTam;
	CLIENTE *ortopedia;
	int ortoTam;
	CONSULTA *consultas;
	int consultaTam;
	int temp;
}TDADOS;