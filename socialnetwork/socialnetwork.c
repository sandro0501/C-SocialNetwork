/***********************************************PROGETTO SOCIAL NETWORK LAB. DI PROGRAMMAZIONE************************************************************************/
/**********************************************SANTOLO BARRETTA N86003666*********************************************************************************************/
/**********************************************GIOVANNI D'ECCLESIIS N86003669*****************************************************************************************/

//ambiente globale

//inclusione librerie
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

//definizione costanti
#define MAXU 20 //dimensione massima per il campo 'username' della struct utente (20+1 carattere di terminazione della stringa)
#define MAXP 8 //dimensione massima per il campo 'password' della struct utente (8+1 carattere di terminazione della stringa)
#define MAXPOST 10 //dimensione massima per l'array di stringhe 'post' (un utente può condividere al massimo 10 post)
#define MAXLENPOST 50 //dimensione massima per la lunghezza dei un singolo post
#define MAXF 100 //dimensione massima per l'array di stringhe seguiti

//definizione della struct 'Utente'che conterrà tutte le informazioni relative ad un singolo utente
typedef struct 
{	
  char username[MAXU+1]; //username dell'utente (MAXU+1 carattere di terminazione della stringa)
  char password[MAXP+1]; //password dell'utente (MAXP+1 carattere di terminazione della stringa)
  char post[MAXPOST][MAXLENPOST]; //array di stringhe che contiene tutti i post dell'utente (max. 10 post per utente di lunghezza 50 caratteri)
  int numpost; //contatore che tiene traccia del numero di post dell'utente
  char seguiti[MAXF][MAXU+1]; //array di stringhe che contiene tutti gli username dei seguiti dall'utente
  int utentiseguiti; //contatore che tiene traccia di quanti utenti ha seguito l'utente
}Utente;

//definizione della struct 'nodo' che comporrà con altre struct di questo tipo la linked list
struct nodo
{
  Utente u; //definizione del campo 'data' del nodo della linked list. Questo campo è di tipo "Utente"
				//per cui conterrà tutte le informazioni relative all'utente definite nella struct precedente
  struct nodo *next; //puntatore al nodo successivo della linked list
};

//dichiarazione dei prototipi di funzione
void signup(struct nodo* head, char *username, char *password); //1.funzione che effettua il signup dell'utente
int login(struct nodo* head, char *username, char *password); //2.funzione che effettua il login dell'utente
void deleteaccount(struct nodo* head, char *username); //3.funzione che effettua il delete dell'account dell'utente
void visualizzausernameutenti(struct nodo* u); //4.funzione che visualizza i nomi (username) di tutti gli utenti del social
int ricercautente(struct nodo* head, char *username); //5.funzione che cerca se esiste un utente sul social
void seguiutente(struct nodo* head, char *username, char *usernamelog); //6.funzione che permette di seguire un utente sul social
void creapost(struct nodo* head, char *username); //7.funzione che permette di creare un post all'utente
void visualizzapostutente(struct nodo* head, char *username); //8.funzione che permette di visualizzare i post di un generico utente sul social
void visualizzaultimopostseguiti(struct nodo* head, char *username); //9.funzione che visualizza l'ultimo post di ogni utente seguito
void visualizzaprofilo(struct nodo* head, char *username); //10.funzione (AGGIUNTIVA) che permette di visualizzare il profilo dell'utente loggato

/*-----------------------------------------------------------------------------------------------------------------------------------------------*/

int main(int argc, char *argv[]) 
{
	//ambiente locale main

	//dichiarazione delle variabili locali al main
	int scelta; //variabile di scelta nello switch per il menu' utente
  	int scelta2; //variabile di scelta nel secondo switch per il sottomenu' utente
  	char usernamelog[MAXU+1]; //variabile d'appoggio che contiene l'username dell'utente per la funzione login
  	char passwordlog[MAXP+1]; //variabile d'appoggio che contiene la password dell'utente per la funzione login
  	char usernamereg[MAXU+1]; //variabile d'appoggio che contiene l'username dell'utente per la funzione signup
  	char passwordreg[MAXP+1]; //variabile d'appoggio che contiene la password dell'utente per la funzione signup
  	char usernamepost[MAXU+1]; //variabile d'appoggio che contiene l'username dell'utente per la funzione crea post
  	char username[MAXU+1];	//variabile d'appoggio che contiene l'username dell'utente per la funzione ricerca utente
  	char usernameseguito[MAXU+1];	//variabile d'appoggio che contiene l'username dell'utente per la funzione segui utente
	int trovato; //variabile di flag per la funzione signup
  	int flaglogin; //variabile di flag per la funzione login
	int posizione; //variabile di flag per la funzione ricerca utente	
	int sceltadelete; //variabile usata per la funzione delete account

	//definizione dei nodi della linked list che rappresentano i 5 utenti predefiniti e già esistenti nel social
	//inizialmente tutti i nodi della linked list sono scollegati e puntano a NULL
	struct nodo* utente1 = NULL; //definizione del primo nodo della linked list che rappresenterà l'utente "ADMIN" cioè l' HEAD della linked list creata
  	struct nodo* utente2 = NULL; //definizione del secondo utente predefinito
   struct nodo* utente3 = NULL; //definizione del terzo utente predefinito
  	struct nodo* utente4 = NULL;	//definizione del quarto utente predefinito
  	struct nodo* utente5 = NULL;	//definizione del quinto utente predefinito
  	
   //allocazione dei 5 utenti predefiniti
	utente1 = (struct nodo*)malloc(sizeof(struct nodo)); //allocazione nodo utente1 admin (head della linked list)
	utente2 = (struct nodo*)malloc(sizeof(struct nodo)); //allocazione nodo utente2
  	utente3 = (struct nodo*)malloc(sizeof(struct nodo)); //allocazione nodo utente3
  	utente4 = (struct nodo*)malloc(sizeof(struct nodo)); //allocazione nodo utente4
  	utente5 = (struct nodo*)malloc(sizeof(struct nodo)); //allocazione nodo utente5
  	
  	//valorizzazzione dei campi "data" dei 5 nodi utente predefiniti che popoleranno inizialmente il social
  	//utente1: admin
   strcpy(utente1->u.username, "admin"); //valorizzazzione del campo username
   strcpy(utente1->u.password, "pass00"); //valorizzazzione del campo password
	//valorizzazzione dell'array post che contiene tutti i post dell'utente (10 post per utente)
   strcpy(utente1->u.post[0], "primopost piu vecchio"); //primo post in posizione 0, rappresenta il post più vecchio scritto
   strcpy(utente1->u.post[1], "secondopost");
   strcpy(utente1->u.post[2], "terzopost");
   strcpy(utente1->u.post[3], "quartopost");
   strcpy(utente1->u.post[4], "quintopost");
   strcpy(utente1->u.post[5], "sestopost");
   strcpy(utente1->u.post[6], "settimopost");
   strcpy(utente1->u.post[7], "ottavopost");
   strcpy(utente1->u.post[8], "nonopost"); 
   strcpy(utente1->u.post[9], "ultimopost piu recente"); //ultimo post in posizione 9, rappresenta il post più recente scritto
   utente1->u.numpost=10; //valorizzazzione del contatore numpost che tiene traccia dei post creati 
	//valorizzazzione dell'array seguiti che contiene tutti i seguiti dell'utente 
   strcpy(utente1->u.seguiti[0], "santolo01"); 
   strcpy(utente1->u.seguiti[1], "giovanni02");
   utente1->u.utentiseguiti=2; //valorizzazzione del contatore utentiseguiti che tiene traccia dei seguiti dell'utente
   utente1->next=utente2; //faccio puntare l'utente corrente al successivo della linked list
	
	//utente2: santolo01
   strcpy(utente2->u.username, "santolo01"); 
   strcpy(utente2->u.password, "pass01");
   strcpy(utente2->u.post[0], "buongiorno");
   strcpy(utente2->u.post[1], "ciao");
   strcpy(utente2->u.post[2], "come state?");
   strcpy(utente2->u.post[3], "oggi sono felice");
   strcpy(utente2->u.post[4], "bello questo social");
   strcpy(utente2->u.post[5], "unina");
   strcpy(utente2->u.post[6], "informatica");
   strcpy(utente2->u.post[7], "oggi vado al mare");
   strcpy(utente2->u.post[8], "ora ascolto musica");
   strcpy(utente2->u.post[9], "buonasera a tutti");
   utente2->u.numpost=10;
   strcpy(utente2->u.seguiti[0], "giovanni02");
   strcpy(utente2->u.seguiti[1], "maria03");
   utente2->u.utentiseguiti=2;
   utente2->next=utente3; //faccio puntare l'utente corrente al successivo della linked list
	
	//utente3: giovanni02
   strcpy(utente3->u.username, "giovanni02"); 
   strcpy(utente3->u.password, "pass02");
   strcpy(utente3->u.post[0], "ciao sono giovanni");
   strcpy(utente3->u.post[1], "che divertimento oggi");
   strcpy(utente3->u.post[2], "pizza");
   strcpy(utente3->u.post[3], "che noia");
   strcpy(utente3->u.post[4], "buonanotte");
   strcpy(utente3->u.post[5], "finalmente estate");
   strcpy(utente3->u.post[6], "oggi si programma");
   strcpy(utente3->u.post[7], "sono felicissimo");
   strcpy(utente3->u.post[8], "buongiorno!");
   strcpy(utente3->u.post[9], "sto leggendo");
   utente3->u.numpost=10;
   strcpy(utente3->u.seguiti[0], "santolo01");
   utente3->u.utentiseguiti=1;
   utente3->next=utente4; //faccio puntare l'utente corrente al successivo della linked list

	//utente4: maria03
	strcpy(utente4->u.username, "maria03"); 
   strcpy(utente4->u.password, "pass03");
   strcpy(utente4->u.post[0], "ciao sono maria");
   strcpy(utente4->u.post[1], "che fate?");
   strcpy(utente4->u.post[2], "oggi sono triste");
   strcpy(utente4->u.post[3], "sto mangiando la pizza");
   strcpy(utente4->u.post[4], "buon compleanno santolo");
   strcpy(utente4->u.post[5], "ciao a tutti");
   strcpy(utente4->u.post[6], "bella questa canzone");
   strcpy(utente4->u.post[7], "ora si studia");
   strcpy(utente4->u.post[8], "buon pomeriggio");
   strcpy(utente4->u.post[9], "che felicita'");
   utente4->u.numpost=10;
   strcpy(utente4->u.seguiti[0], "santolo01");
   strcpy(utente4->u.seguiti[1], "giovanni02");
   utente4->u.utentiseguiti=2;
   utente4->next=utente5; //faccio puntare l'utente corrente al successivo della linked list
	
	//utente5: vittoria04
	strcpy(utente5->u.username, "vittoria04"); 
   strcpy(utente5->u.password, "pass04");
   strcpy(utente5->u.post[0], "salve");
   strcpy(utente5->u.post[1], "oggi sono uscita");
   strcpy(utente5->u.post[2], "adoro il caffe'");
   strcpy(utente5->u.post[3], "buona serata");
   strcpy(utente5->u.post[4], "sto studiando matematica");
   strcpy(utente5->u.post[5], "che noia");
   strcpy(utente5->u.post[6], "questo social e' divertente");
   strcpy(utente5->u.post[7], "in love");
   strcpy(utente5->u.post[8], "ciao a tutti");
   strcpy(utente5->u.post[9], "rock'n'roll");
   utente5->u.numpost=10;
   strcpy(utente5->u.seguiti[0], "giovanni02");
   strcpy(utente5->u.seguiti[1], "maria03");
   utente5->u.utentiseguiti=2;
   utente5->next = NULL; //faccio puntare l'utente corrente a NULL poichè è il quinto ed ultimo predefinito

	/*-----------------------------------------------------------------------------------------------------------------------------------------------*/
  
	//creazione del menu' di scelta utente con tutte le funzioni del social
	do
	{
		menu:
		//schermata iniziale che mostra 3 possibili opzioni per l'utente: signup, login ed exit
		system("CLS");
		printf("************************************************************\n");
		printf("\t\tBENVENUTO SU UNINANETWORK\n");
		printf("************************************************************\n\n");
		printf("1) SIGNUP\n");
	   printf("2) LOGIN\n");
	   printf("0) EXIT\n");
		printf("\n************************************************************\n\n");

		printf("Inserisci la tua scelta: "); //printf all'utente per la scelta
	   scanf("%d", &scelta); //leggo la scelta dell'utente, ammessi solo numeri interi
		
		//switch per la scelta dell'utente (a seconda del valore della scelta si effettuerà un'operazione differente)
		switch(scelta)
		{
			//scelta 1: signup
      	case 1:
      	{
      		printf("\n>>>SIGNUP<<<\n\n"); //l'utente ha scelto di registrarsi al social
				//lettura della stringa username utente con relativi controlli attraverso il do-while
      		do 
				{
					printf("Username utente (max 20 caratteri): ");
					fflush(stdin); //funzione di sistema che pulisce il buffer
					gets(usernamereg); //leggo la stringa dell'username
					
					//controllo sulla stringa dell'username									    	
					if((strlen(usernamereg)<=0)||(strlen(usernamereg)>MAXU)) //se la stringa non rispetta le condizioni imposte
					{
						printf("*L'username inserito non e' consentito!\n"); //messaggio di errore
					}												
				}
				while((strlen(usernamereg)<=0)||(strlen(usernamereg)>MAXU)); //il ciclo ripete finchè non vengono soddisfatte le condizioni imposte
				
				//controllo se l'username immesso è già esistente	
				trovato=ricercautente(utente1, usernamereg); //chiamata alla funzione ricercautente

				if(trovato!=-1) //l'utente è stato trovato nella linked list, l'username scelto è occupato
				{
					printf("\nL'utente %s e' gia' esistente e registrato su UninaNetwork!\n", usernamereg);
				}
				else  //l'utente non è stato trovato nella linked list quindi posso registrarlo con l'username scelto
				{
					//per completare il signup si richiede di scegliere la password
					//leggo la password e controllo se è valida
					do
					{
						printf("Password (max 8 caratteri): ");
						fflush(stdin); //funzione di sistema che pulisce il buffer
						gets(passwordreg); //leggo la stringa della password

						//se la password non rispetta le condizioni imposte								    	
						if((strlen(passwordreg)<=0)||(strlen(passwordreg)>MAXP))
						{
							printf("*La password inserita non e' consentita!\n");
						}										
					}
					while((strlen(passwordreg)<=0)||(strlen(passwordreg)>MAXP)); //il ciclo ripete finchè non vengono soddisfatte le condizioni imposte
					
					//una volta verificati username e password si procede alla registrazione dell'utente
					signup(utente1,usernamereg,passwordreg); //chiamata alla funzione signup che registra l'utente nel social network	
				}					
      		break; //fine del case signup, torna al menu' iniziale
			} //fine case 1 primo switch 
			
			//scelta 2: login
        	case 2:
        	{
        		printf("\n>>>LOGIN<<<\n\n"); //l'utente ha scelto di fare il login nel social
				//inizialmente si leggono e controllano le stringhe relative a username e password utente

				//lettura della stringa username utente con relativi controlli attraverso il do-while
        		do
				{
					printf("Username utente (max 20 caratteri): ");
					fflush(stdin); //funzione di sistema che pulisce il buffer
					gets(usernamelog); //leggo la stringa dell'username
					
					//se la stringa non rispetta le condizioni imposte									    	
					if((strlen(usernamelog)<=0)||(strlen(usernamelog)>MAXU))
					{
						printf("*L'username inserito non e' consentito!\n");
					}												
				}
				while((strlen(usernamelog)<=0)||(strlen(usernamelog)>MAXU)); //il ciclo ripete finchè non vengono soddisfatte le condizioni imposte	
				
				//lettura della stringa password utente con relativi controlli attraverso il do-while					
				do
				{
					printf("Password (max 8 caratteri): ");
					fflush(stdin);
					gets(passwordlog); //leggo la stringa della password
					
					//se la stringa non rispetta le condizioni imposte										    	
					if((strlen(passwordlog)<=0)||(strlen(passwordlog)>MAXP))
					{
						printf("*La password inserita non e' consentita!\n");
					}
																
				}
				while((strlen(passwordlog)<=0)||(strlen(passwordlog)>MAXP)); //il ciclo ripete finchè non vengono soddisfatte le condizioni imposte

				//una volta verificata la correttezza delle stringhe di username e password immesse dall'utente si procede ad effettuare il login
        		flaglogin=login(utente1,usernamelog,passwordlog); //chiamata alla funzione login

				if(flaglogin!=-1) //l'utente è stato trovato nella linked list e il login è andato a buon fine
				{
					//una volta effettuato il login correttamente si aprirà un sottomenu' utente con tutte le funzioni disponibili per l'utente loggato
        			do
					{
						//interfaccia menu' di scelta utente con tutte le funzioni disponibili
	        			system("CLS");
		        		printf("************************************************************\n");
						printf("\t\tBENVENUTO SU UNINANETWORK,\n\t\t\t%s\n", usernamelog); //messaggio di benvenuto con l'username utente dopo il login
						printf("************************************************************\n\n");
						printf("_________________________HOME_______________________________\n\n");
						//si mostranno all'utente tutte le funzioni disponibili
		        		printf("1) VISUALIZZA USERNAME DI TUTTI GLI UTENTI\n");
			   		printf("2) CERCA UTENTE\n");
			   		printf("3) SEGUI UTENTE\n");
			   		printf("4) VISUALIZZA TUTTI I POST DI UN UTENTE\n");
			   		printf("5) VISUALIZZA ULTIMO POST DEGLI UTENTI SEGUITI\n");
			   		printf("6) CREA POST\n");
			   		printf("7) VISUALIZZA IL TUO ACCOUNT\n");
			   		printf("8) DELETE ACCOUNT\n");
			   		printf("0) LOG OUT\n");
		   			printf("___________________________________________________________\n\n");

		        		printf("Inserisci la tua scelta: ");
		   			fflush(stdin);
		   			scanf("%d", &scelta2); //lettura della scelta dell'utente nel sottomenu'
	   				
						//switch per la scelta dell'utente (a seconda del valore della scelta si effettuerà un'operazione differente)
	        			switch(scelta2)
	         		{
							//scelta 1: visualizza l'username di tutti gli utenti
		            	case 1:
		            	{
		            		printf("\n>>>VISUALIZZA USERNAME DI TUTTI GLI UTENTI<<<\n");
		            		//l'utente ha scelto di visualizzare l'username di tutti gli utenti registrati nel social
		  						visualizzausernameutenti(utente1); //chiamata alla funzione visualizzausernameutenti

		                  break; //dopo aver effettuato l'operazione ritorna alla scelta
							} //fine case 1 secondo switch
							
							//scelta 2: cerca utente
							case 2:
	            		{
		            		printf("\n>>>CERCA UTENTE<<<\n\n"); //l'utente ha scelto di cercare se esiste un utente

		  						//lettura della stringa username utente da ricercare con relativi controlli attraverso il do-while
		  						do
							  	{
									printf("Username utente (max 20 caratteri): ");
									fflush(stdin);
							    	gets(username); //leggo la stringa dell'username da ricercare
							    	
									//se la stringa non rispetta le condizioni imposte
							    	if((strlen(username)<=0)||(strlen(username)>MAXU))
							    	{
							    		printf("*L'username inserito non e' consentito!\n\n");
									}	
								}
							  	while((strlen(username)<=0)||(strlen(username)>MAXU));//il ciclo ripete finchè non vengono soddisfatte le condizioni imposte
								
								//verifico se l'username dell'utente ricercato è presente nella linked list
								posizione=ricercautente(utente1, username); //chiamata alla funzione ricercautente 

								if(posizione!=-1) //l'username dell'utente è stato trovato nella linked list
								{
									printf("\nL'utente %s e' esistente ed e' correttamente registrato su UninaNetwork!\n", username);
								}
								else //l'username dell'utente non è stato trovato nella linked list
								{
									printf("\nErrore. L'utente %s non e' registrato sul social UninaNetwork!\n", username);
								}

							 	break; //dopo aver effettuato l'operazione ritorna alla scelta
	             		} //fine case 2 secondo switch
	             		
							//scelta 3: segui utente
		               case 3:
		            	{
		            		printf("\n>>>SEGUI UTENTE<<<\n\n"); //l'utente ha scelto di seguire un utente
								
								//lettura della stringa username utente da seguire con relativi controlli attraverso il do-while
		            		do
							  	{
									printf("Username utente da seguire (max 20 caratteri): ");
									fflush(stdin);
							    	gets(usernameseguito); //leggo la stringa dell'username da seguire
							    	
									//se la stringa non rispetta le condizioni imposte
							    	if((strlen(usernameseguito)<=0)||(strlen(usernameseguito)>MAXU))
							    	{
							    		printf("*L'username inserito non e' consentito!\n\n");
									}	
								}
							  	while((strlen(usernameseguito)<=0)||(strlen(usernameseguito)>MAXU)); //il ciclo ripete finchè non vengono soddisfatte le condizioni imposte
							  	
								//controllo se la stringa immessa è uguale all'username dell'utente corrente
								//se le due stringhe sono uguali comunico l'errore: non è possibile seguire se stessi
							  	if(strcmp(usernameseguito,usernamelog)==0) //comparo le due stringhe attraverso la funzione strcmp
								{
									printf("\nErrore. Non puoi seguire te stesso!\n");
									break;
								}
								
								//una volta controllata la stringa immessa dall'utente si procede con la funzione seguiutente
							  	seguiutente(utente1, usernameseguito, usernamelog); //chiamata alla funzione seguiutente
							
		                  break; //dopo aver effettuato l'operazione ritorna alla scelta
							} //fine case 3 secondo switch
						
							//scelta 4: visualizza tutti i post di un utente
							case 4:
		            	{
		            		printf("\n>>>VISUALIZZA TUTTI I POST DI UN UTENTE<<<\n\n"); //l'utente ha scelto di visualizzare tutti i post di un utente
		            		
								//lettura della stringa username utente di cui visualizzare i post con relativi controlli attraverso il do-while
		            		do
							  	{
									printf("Username utente (max 20 caratteri): ");
									fflush(stdin);
							    	gets(usernamepost); //leggo la stringa dell'username di cui visualizzare i post
							    	
									//se la stringa non rispetta le condizioni imposte
							    	if((strlen(usernamepost)<=0)||(strlen(usernamepost)>MAXU))
							    	{
							    		printf("*L'username inserito non e' consentito!\n\n");
									}
									
								}
							  	while((strlen(usernamepost)<=0)||(strlen(usernamepost)>MAXU)); //il ciclo ripete finchè non vengono soddisfatte le condizioni imposte
								
								//una volta controllata la stringa immessa dall'utente si procede con la visualizzazzione dei post dell'utente desiderato
								visualizzapostutente(utente1, usernamepost); //chiamata alla funzione visualizzapostutente         
								
		                  break; //dopo aver effettuato l'operazione ritorna alla scelta
							} //fine case 4 secondo switch
							
							//scelta 5: visualizza ultimo post degli utenti seguiti
							case 5:
		            	{
		            		printf("\n>>>VISUALIZZA ULTIMO POST DEGLI UTENTI SEGUITI<<<\n\n"); //l'utente ha scelto di vedere gli ultimi post degli utenti che segue

		            		printf("Ecco gli ultimi post piu' recenti degli utenti che segui, %s...\n\n", usernamelog);

								//visualizza i gli ultimi post dei seguiti dell'utente corrente
		            		visualizzaultimopostseguiti(utente1,usernamelog); //chiamata alla funzione visualizzaultimopostseguiti
		            		
		                  break; //dopo aver effettuato l'operazione ritorna alla scelta
							} //fine case 5 secondo switch 
							
							//scelta 6: crea post
							case 6:
		            	{
		            		printf("\n>>>CREA POST<<<\n\n"); //l'utente ha scelto di creare un post

								//creazione del post 
		            		creapost(utente1, usernamelog); //chiamata alla funzione creapost

		                  break; //dopo aver effettuato l'operazione ritorna alla scelta
							} //fine case 6 secondo switch
							
							//scelta 7: visualizza il tuo account
							case 7:
							{
								printf("\n>>>VISUALIZZA IL TUO ACCOUNT<<<\n\n"); //l'utente ha scelto di visualizzare il suo account
								
								//viene visualizzato il profilo dell'utente col suo username, lista seguiti, i suoi post, ultimi post degli utenti seguiti
								visualizzaprofilo(utente1, usernamelog); //chiamata alla funzione visualizzaprofilo (AGGIUNTIVA)
		                  
								break; //dopo aver effettuato l'operazione ritorna alla scelta
							} //fine case 7 secondo switch
							
							//scelta 8: delete account
							case 8:
		            	{
		            	
		            		printf("\n>>>DELETE ACCOUNT<<<\n\n"); //l'utente ha scelto di cancellare il proprio account
		            		printf("Sei sicuro di voler eliminare il tuo account, %s?", usernamelog); //si chiede all'utente se è sicuro di cancellare il proprio account
		            		printf("\n1. SI\n2. NO\n");
		            		printf("\nInserisci la tua scelta: ");
		            		scanf("%d", &sceltadelete); //leggo la scelta dell'utente prima di procedere alla cancellazione del suo account
						
								//se l'utente ha scelto di procedere alla cancellazzione dell'account
		            		if(sceltadelete==1)
		            		{
									//controllo che l'utente non sia l'admin poichè è la head della linked list e non posso cancellarla
		            			if(strcmp(usernamelog,"admin")==0) //compara la stringa dell'username corrente con l'username 'admin' se sono uguali
		            			{
		            				printf("\nNon puoi cancellare l'account admin! Torno dietro...\n"); /*se l'utente corrente è l'admin 
										comunico che non può cancellare il suo account*/

										break; //ritorna alla scelta
									}
									else //se l'utente corrente non è l'admin allora procedo alla cancellazione del suo account
									{
										//comunico che l'account è stato cancellato correttamente
										printf("\nAccount %s eliminato correttamente. Verrai disconnesso...\n", usernamelog);
		            				deleteaccount(utente1, usernamelog); //chiamata alla funzione deleteaccount

		            				system("PAUSE");
		            				goto menu; //una volta cancellato l'account torno alla schermata principale attraverso la funzione goto
									}
								}
								else //l'utente ha scelto di non cancellare il proprio account
								{
									//si ritorna dietro alla scelta delle funzioni
									if(sceltadelete==2) 
									{
								   	printf("Torno dietro..\n");
										break;	
									}
									else //nel caso di una scelta non valida numericamente
									{
										printf("Scelta non ammessa. Torno dietro..\n");
										break;	
									}
								}
		                  break;

							} //fine case 8 secondo switch
							
							//scelta 0: log out
							case 0:
							{	
								printf("\n>>>LOG OUT<<<\n\n"); //l'utente ha scelto di fare il log out dall'account
								//stampa un messaggio per l'avvenuto log out
								printf("Sei stato disconnesso correttamente dall'account.\nCiao %s!\n", usernamelog);
								continue; //riporta alla schermata iniziale del primo menu' permettendo di rifare login o un signup

							} //fine case 0 
							
							//caso di default: l'utente ha inserito un numero non valido
							default:
		      			{
		        				printf("Scelta non ammessa\n"); //comunico un messaggio di errore all'utente
		      			}

	            	} //fine secondo switch 
	            	getch();
	         	}
	         	while(scelta2!=0); //fine secondo do while relativo al secondo switch	
            }
				else //il login non è andato a buon fine, l'utente non è stato trovato nella linked list o la linked list è vuota 
				{
					printf("\nLogin errato! Controlla le credenziali o che l'utente sia registrato e riprova.\n"); //comunico un messaggio di errrore
				}

         	break; //ritorna alla schermata iniziale
			} //fine case 2 primo switch 
			
			//scelta 0 primo switch menu' iniziale: l'utente ha scelto di terminare il programma
			case 0:
			{
				printf("\nBye bye!\n");
				return 0; //termina il programma
			} //fine case 0 primo switch 
			
			//caso di default: l'utente ha inserito un numero per la scelta non valido
			default:
	      {
	      	printf("Scelta non ammessa\n"); //comunico un messaggio di errore all'utente
	      } //fine default primo siwtch 

   	} //fine primo switch(scelta)
    	getch();
	}
	while(scelta!=0); //fine primo do while, ripete finchè la scelta è diversa da 0; se la scelta è uguale a 0 esce dal programma 

}//fine funzione main

/*-----------------------------------------------------------------------------------------------------------------------------------------------*/

//funzioni implementate

//1.funzione signup
void signup(struct nodo* head, char *username, char *password) //riceve in ingresso il puntatore all'inizio della linked list, username e password dell'utente
{
	struct nodo *nuovoutente; //puntatore per il nuovo utente da registrare
	struct nodo *utente; //puntatore per scorrere la linked list 

	nuovoutente=(struct nodo*)malloc(sizeof(struct nodo)); //alloca il nuovo nodo utente

    if(nuovoutente==NULL) //verifica se c'è un problema di allocazione
    {
        printf("Errore di allocazione");
    }
    else //setta il campo "data" del nuovo utente registrato valorizzando i campi "Utente"
    {
   	//valorizzo il nuovo utente
   	strcpy(nuovoutente->u.username, username); //setta l' username del nuovo utente copiando nel campo username la stringa username data in ingresso alla funzione
   	strcpy(nuovoutente->u.password, password); //setta la password del nuovo utente copiando nel campo password la stringa password data in ingresso alla funzione
  		nuovoutente->u.numpost=0; //setta il numero di post del nuovo utente a 0
  		nuovoutente->u.utentiseguiti=0; //setta il numero di seguiti del nuovo utente a 0
   	nuovoutente->next=NULL; //setta il puntatore al nodo successivo dell'utente appena creato a NULL (inserimento del nodo in coda nella linked list)
		
      utente=head; //faccio puntare il puntatore utente alla head della linked list ossia utente1 (admin)
		
		//INSERIMENTO IN CODA DEL NUOVO NODO UTENTE NELLA LINKED LIST
      //scorro la lista partendo dalla haed fino ad arrivare all'ultimo nodo
      while(utente!=NULL && utente->next!=NULL)
      {
      	utente=utente->next; //punta al nodo successivo
		}
      
		//una volta arrivati all'ultimo nodo utente che punta a NULL 
		//lo si collega al nuovo nodo utente appena inserito che sarà quindi il nuovo ultimo nodo     
		utente->next = nuovoutente;

      printf("\nRegistrazione su UninaNetwork correttamente effettuata!\n"); //comunico il buon esito del sign up
    }
}//fine funzione signup

/*-----------------------------------------------------------------------------------------------------------------------------------------------*/

//2.funzione login
int login(struct nodo* head, char *username, char *password) //riceve in ingresso il puntatore all'inizio della linked list, username e password dell'utente
{
	int i; //contatore che indicherà la posizione del nodo della linked list
   struct nodo *current; //puntatore che scorre la linked list
					
	i=0; //inizializza il contatore a zero
   current=head; //fa puntare il puntatore current alla head della linked list utenti
	
	/*RICERCA SEQUENZIALE DEL NODO UTENTE NELLA LINKED LIST 
	il ciclo fa scorrere il puntatore nella linked list alla ricerca del nodo utente con l'username e la password dati in ingresso
	avviene un confronto fra il campo username e password del nodo utente corrente nella linked list con l'username e la password dati in ingresso
	attraverso la funzione strcmp*/
   while((current!=NULL)&&((strcmp(current->u.username,username)!=0)||(strcmp(current->u.password,password)!=0))) //cicla finchè non trova l'utente
   {	
		i++; //se non trova l'utente avanza il contatore posizione nella linked list
   	current=current->next; //fa puntare il puntatore al nodo successivo della linked list
	}
	
	//una volta terminato il ciclo while si controlla il puntatore current
   if(current!=NULL) //se il puntatore current è diverso da null vuol dire che il ciclo while si è interrotto trovando l'utente desiderato
	{
		return i; //ritorna la posizione dell'utente al main per completare il login
	}
	else //se il puntatore current è uguale a null vuol dire che l'utente desiderato non è stato trovato nella linked list
	{
		i=-1; //setto il valore del contatore posizione ad un valore "null" che indica il fatto che l'utente non è stato trovato in linked list
		return i; //ritorna la posizione nulla al main per completare il login con un messaggio di errore
	}
}//fine funzione login
/*-----------------------------------------------------------------------------------------------------------------------------------------------*/

//3.funzione deleteaccount
void deleteaccount(struct nodo* head, char *username) //riceve in ingresso il puntatore all'inizio della linked list e l'username dell'utente loggato attualmente
{         
	struct nodo *utenteprev; //puntatore all'utente precedente
	struct nodo *utentecurr; //puntatore all'utente corrente
	struct nodo *temp; //puntatore d'appoggio per la cancellazione dell'account                       
                           
	utenteprev = NULL; //fa puntare il puntatore a NULL                               
	utentecurr = head; //fa puntatre il puntatore all'inizio della linked list
	
	/*CANCELLAZIONE DI UN NODO DALLA LINKED LIST
	il ciclo fa scorrere il puntatore fino alla fine della linked list alla ricerca del nodo utente da eliminare
	si confronta la stringa username dell'utente corrente con la stringa username data in ingresso attraverso la funzione strcmp
	se le due stringhe sono uguali allora il nodo è stato trovato e si procede con la cancellazione del nodo utente*/
	while(utentecurr!=NULL)
	{                            
		if(strcmp(utentecurr->u.username,username)==0) //le due stringhe sono uguali, è stato trovato il nodo da cancellare
		{         
  			temp=utentecurr; //assegna il puntatore dell'utente corrente ad un puntatore d'appoggio 
			                              
  			if(utenteprev==NULL) //verifica se il puntatore all'utente precedente è uguale a NULL
			{							                      
    			head=utentecurr->next; //se il nodo utente precedente è uguale a NULL la nuova head sarà il nodo successivo a quello dell'utente corrente 
    		}
  			else
  			{
  				utenteprev->next = utentecurr->next; //lega il nodo precedente di quello corrente da eliminare a quello successivo del nodo corrente   
  				utentecurr = utentecurr->next; //passa al nodo successivo da esaminare della linked list                          
  				free(temp); //dealloca lo spazio occupato nella linked del nodo corrente da eliminare                         
  				break;
			}
		} //se le due stringhe non sono ugali, non è stato trovato il nodo da cancellare e passa al nodo successivo della linked list
		else
		{                               
    		utenteprev = utentecurr;  //il puntatore al nodo corrente che non è quello da eliminare sarà il nuovo nodo utente precedente                       
    		utentecurr = utentecurr->next; //fa puntatre il nodo utente corrente al nodo utente successivo della linked list               
		}   
	}
}//fine funzione deleteaccount
/*-----------------------------------------------------------------------------------------------------------------------------------------------*/

//4.funzione visualizzausernameutenti
void visualizzausernameutenti(struct nodo* head) //riceve in ingresso il puntatore all'inizio della linked list
{
	int i; //contatore utenti
	
	i=0; //inizializzazione del contatore
	
	printf("\nUsername di tutti gli utenti di UninaNetwork:\n\n");
	
	//VISUALIZZAZIONE DEL CAMPO USERNAME DEI NODI DELLA LINKED LIST
	//se la testa è uguale a null vuol dire che non esiste nessun utente nella linked list
	if(head==NULL)
	{
		printf("Nessun utente presente in UninaNetwork!\n\n");
	}
	
	while(head!=NULL) //il ciclo stampa il campo username di tutti i nodi utente presenti nella linked list
	{
   	printf("%d. %s\n", i+1, head->u.username); //stampa l'username
   	head=head->next; //sposta il puntatore al nodo successivo
   	i++; //incrementa il contatore utenti
   }
   
   return; //ritorna al main
}//fine funzione visualizzausernameutenti
/*-----------------------------------------------------------------------------------------------------------------------------------------------*/

//5.funzione ricercautente
int ricercautente(struct nodo* head, char *username) //riceve in ingresso il puntatore all'inizio della linked list e l'username dell'utente da ricercare
{
	int i; //contatore che indicherà la posizione del nodo della linked list
   struct nodo *current; //puntatore che scorre la linked list

   i=0; //inizializzazione del contatore a zero
   current=head; //fa puntare il puntatore current alla head della linked list utenti

	//RICERCA SEQUENZIALE DEL NODO UTENTE NELLA LINKED LIST 
	//il ciclo fa scorrere il puntatore nella linked list alla ricerca del nodo utente con l'username dato in ingresso
	//avviene un confronto fra il campo username del nodo utente corrente nella linked list con l'username dato in ingresso attraverso la funzione strcmp
   while(current!=NULL&&strcmp(current->u.username,username)!=0) //cicla finchè non trova l'utente
   {
   	i++; //se non trova l'utente avanza il contatore posizione nella linked list
   	current=current->next; //fa puntare il puntatore al nodo successivo della linked list
	}
	
	//una volta terminato il ciclo while si controlla il puntatore current
   if(current!=NULL) //se il puntatore current è diverso da null vuol dire che il ciclo while si è interrotto trovando l'utente desiderato
	{
		return i; //ritorna la posizione dell'utente al main per completare la ricerca
	}
	else
	{
		i=-1; //setto il valore del contatore posizione ad un valore "null" che indica il fatto che l'utente non è stato trovato
		return i; //ritorna la posizione nulla al main per completare la ricerca con un messaggio di errore ossia l'utente non è stato trovato
	}
}//fine funzione ricercautente

/*-----------------------------------------------------------------------------------------------------------------------------------------------*/

//6.funzione segui utente
//riceve in ingresso il puntatore all'inizio della linked list,l'username dell'utente da seguire,l'username dell'utente corrente loggato
void seguiutente(struct nodo* head, char *username, char *usernamelog) 
{
	int posizioneutente; //flag che contiene il risultato della ricerca dell'username da seguire
	int posizionecurrent; //flag che contiene la posizione dell'utente corrente nella linked list
	struct nodo* current; //puntatore al nodo utente corrente che scorre la linked list
	struct nodo* temp; //puntatore di appoggio
	int contatore; //contatore che viene confrontato con la posizione dell'utente corrente
	int contatoreseguiti; //contatore di appoggio per i seguiti
	int i; //contatore usato per il ciclo for 
	
	temp=head; //assegna l'head della linked list al puntatore d'appoggio
	
	//inizialmente si stabilisce se l'username dell' utente da seguire è presente in linked list attraverso la ricerca utente
	posizioneutente=ricercautente(temp, username); //si richiama la funzione ricercautente	
					
	if(posizioneutente==-1) //se l'utente da seguire non è stato trovato nella linked list
	{
		//comunico all'utente che non è possibile seguire l'utente desiderato poichè non è presente in linked list e quindi non è registrato
		printf("\nErrore. Non puoi seguire l' utente %s perche'\nnon e' registrato sul social UninaNetwork!\n", username); 
		return;
	}
	
	i=0; //inizializzazione del contatore del ciclo for
	contatore=0; //inizializzazione del contatore confrontato con la posizione dell'utente corrente
	current=head; //assegna la testa della linked list al puntatore current
	
	//stabilisco la posizione del nodo dell'utente corrente nella linked list attraverso la ricercautente
	posizionecurrent=ricercautente(current,usernamelog); //si richiama la funzione ricercautente 
	
	//AGGIUNTA DELLA STRINGA RELATIVA ALL'USERNAME DELL'UTENTE DA SEGUIRE IN CODA ALL'ARRAY 'seguiti' DEL NODO UTENTE CORRENTE
	while(current!=NULL) //scorre la linked list
	{
   	if(contatore==posizionecurrent) //se ha trovato l'utente corrente nella linked list 
      {
      	//ciclo for che scorre tutto l'array seguiti dell'utente fino al contatore del numero di utenti seguiti corrente (utentiseguiti)
      	for(i=0; i<current->u.utentiseguiti; i++) 
     		{
     			if(strcmp(current->u.seguiti[i],username)==0) //controllo che l'utente da seguire non sia già stato seguito e quindi che sia già presente nell'array dei seguiti
     			{
     				printf("\nNon puoi seguire un utente che gia' segui!\n"); //comunico all'utente che non può seguire un utente che già segue
     				printf("\nPer visualizzare la lista degli utenti seguiti\ninserisci (7) VISUALIZZA IL TUO ACCOUNT\n");
					return; //ritorna al main
				}
			}
			
      	if(current->u.utentiseguiti>=MAXF) //se l'utente ha raggiunto la dimensione massima dei seguiti MAXF non può seguirne altri
        	{
				printf("\nHey %s, hai raggiunto la dimensione massima dei seguiti (100) per cui non puoi seguirne altri.\n",usernamelog); //messagggio di errore
			}
			else //è possibile seguire l'utente, dunque aggiungo l'username dell'utente da seguire nell'array di stringhe 'seguiti'
			{
				contatoreseguiti=current->u.utentiseguiti; //tengo traccia degli utenti seguiti con una variabile d'appoggio
				strcpy(current->u.seguiti[contatoreseguiti],username); //copia l'username del nuovo utente seguito dato in ingresso nell'array dei seguiti del nodo corrente in coda 
				current->u.utentiseguiti++; //incrementa il contatore degli utenti seguiti
				
				printf("\n%s hai appena iniziato a seguire l'utente %s.\n\n",usernamelog,username); //mostra un messaggio per avvisare che l'utente è stato seguito correttamente
				printf(">>>LISTA DEGLI UTENTI SEGUITI<<<\n");
				for(i=0; i<current->u.utentiseguiti; i++) //stampa tutti i seguiti dell'utente compreso il nuovo utente seguito
     			{
					printf("%d. %s\n", i, current->u.seguiti[i]);	
				}		
			}
		}
		contatore++; //incrementa il contatore da confrontare con la posizione utente 
      current=current->next; //scorre al nodo successivo della linked list		
	} //fine ciclo while
	
   return; //ritorna al main
}//fine funzione seguiutente
/*-----------------------------------------------------------------------------------------------------------------------------------------------*/

//7.funzione crea post
void creapost(struct nodo* head, char *username) //riceve in ingresso il puntatore all'inizio della linked list e l'username dell'utente corrente loggato
{
	int posizioneutente; //flag che contiene la posizione dell'utente corrente nella linked list
	struct nodo* current; //puntatore al nodo utente corrente che scorre la linked list
	int contatore; //contatore che viene confrontato con la posizione dell'utente corrente
	int i; //contatore usato per il ciclo for 
	char post[MAXLENPOST]; //stringa di appoggio che contiene il nuovo post creato di dimensione MAXLENPOST (max. 50 caratteri)
	
	//faccio scrivere il nuovo post all'utente e controllo la sua validità
	do
	{
		printf("Scrivi il tuo post (max 50 caratteri): ");
		fflush(stdin);
		gets(post); //acquisisce la stringa relativa al nuovo post dell'utente
							    	
		if((strlen(post)<=0)||(strlen(post)>MAXLENPOST)||(strcmp(post," ")==0)) //se la stringa relativa al post non rispetta le condizioni imposte
		{
			printf("*Il post scritto non e' accettabile!\n\n"); //messaggio di errore
		}							
	}
	while((strlen(post)<=0)||(strlen(post)>MAXLENPOST)||(strcmp(post," ")==0)); //il ciclo ripete finchè non vengono soddisfatte le condizioni imposte
	
	i=0; 
	contatore=0; //inizializzazione del contatore confrontato con la posizione dell'utente corrente
	current=head; //assegna la testa della linked list al puntatore current
	
	//stabilisco la posizione del nodo dell'utente corrente nella linked list attraverso la ricercautente
	posizioneutente=ricercautente(current, username); //si richiama la funzione ricercautente	
	
	//AGGIUNTA DELLA STRINGA RELATIVA AL POST CREATO DALL'UTENTE IN CODA ALL'ARRAY 'post' DEL NODO UTENTE CORRENTE				
	if(posizioneutente!=-1) //se l'utente è presente nella linked list
	{	
    	while(current!= NULL) //scorre la linked list fino a quando non arriva al nodo utente corrispondente alla posizione data dalla ricerca utente
		{
      	if(contatore==posizioneutente) //confronta il contatore corrente con la posizione dell'utente, se corrispondono allora accede al nodo utente altrimenti passa al nodo successivo
        	{
        		/*se l'utente ha raggiunto il massimo numero di post (10) indicato dal contatore 'numpost', per creare un nuovo post bisogna cancellare il post 
        		più vecchio dell'utente: si applica uno shift dell'array verso sinistra di una posizione, cancellando quindi il primo post più vecchio
				dopodiché si aggiunge in ultima posizione (9, ora libera) il nuovo post appena creato dall'utente*/
        		if(current->u.numpost==MAXPOST) //se l'utente ha raggiunto il massimo numero di post MAXPOST (10)
        		{
        			printf("\n%s hai appena scritto un post.\n",username); //comunica all'utente della creazione del post
					printf("\nHey %s, hai raggiunto la dimensione massima dei post (10).\n",username); //comunica all'utente che ha raggiunto la massima dimensione dei post
					printf("Il tuo post piu' vecchio sara' eliminato, UninaNetwork e' un social attento ai problemi ecologici!\n\n");	//comunica all'utente che il post più vecchio sarà eliminato
					
					//operazione di shift dell'array post dell'utente di una posizione verso sinistra per eliminare il post più vecchio
					for(i=0; i<(MAXPOST-1); i++) 
					{
  						strcpy(current->u.post[i],current->u.post[i+1]);
					}
					strcpy(current->u.post[9],post); //aggiunge alla fine dello shift il nuovo post più recente in ultima posizione
				}
				else //se l'utente non ha nessun post scritto aggiungo il nuovo post creato in prima posizione nell'array dei post
				{
					if(current->u.numpost==0) //verifica che l'utente non abbia nuessn post attraverso il contatore dei post
					{
						strcpy(current->u.post[0],post); //copia la stringa del post creato nella prima posizone dell'array post dell'utente
						current->u.numpost=1; //setta il contatore dei post a 1
						printf("\n%s hai appena scritto un post.\n",username); //comunica l'avvenuta creazione del post all'utente
					}
					else //l'utente ha scritto già alcuni post ma l'array post non è pieno
					{
						strcpy(current->u.post[current->u.numpost],post); //aggiungo il nuovo post creato in coda nell'array post dell'utente alla posizione "numpost" corrente
						current->u.numpost++; //aumenta di 1 il contatore del numero di post dell'utente
						printf("\n%s hai appena scritto un post.\n",username); //comunica l'avvenuta creazione del post all'utente
					}
				}
		  	}
		  	contatore++; //incrementa il contatore da confrontare con la posizione utente 
      	current=current->next; //scorre al nodo successivo della linked list			
		}
	}
	else //se per qualche motivo l'utente non è stato trovato nella linked list
	{
		printf("\nErrore.");
	}
    
   return; //ritorna al main
}//fine funzione creapost
/*-----------------------------------------------------------------------------------------------------------------------------------------------*/

//8.funzione visualizzapostutente
//riceve in ingresso il puntatore all'inizio della linked list e l'username dell'utente di cui si vogliono visualizzare i post
void visualizzapostutente(struct nodo* head, char *username) 
{
	int posizioneutente; //variabile che contiene la posizione dell'utente ricercato in linked list
	struct nodo* current; //puntatore al nodo utente corrente che scorre la linked list
	int contatore; //contatore che viene confrontato con la posizione dell'utente corrente
	int i; //contatore usato per il ciclo for 
	
	i=0; 
	contatore=0; //inizializzazione del contatore confrontato con la posizione dell'utente corrente
	current=head; //assegna la testa della linked list al puntatore current

	//stabilisco se l'utente di cui si vogliono visualizzare i post esiste nella linked list attraverso la fuunzione ricercautente che restituisce anche la sua posizione
	posizioneutente=ricercautente(current, username); //si richiama la funzione ricercautente	
	
					
	if(posizioneutente!=-1) //se l'utente è stato trovato ed esiste nella linked list
	{
		//scorre la linked list fino a quando non arriva al nodo utente corrispondente alla posizione data dalla ricerca utente
    	while(current!= NULL)
		{
      	if(contatore==posizioneutente) //confronta il contatore corrente con la posizione dell'utente, se corrispondono allora accede al nodo utente altrimenti passa al nodo successivo
        	{
        		if(current->u.numpost>0) //se l'utente di cui si vogliono vedere i post ha scritto dei post allora li mostra
        		{
        			printf("\n\tI post piu' recenti di %s...\n\n", username);
        			for(i=current->u.numpost-1; i>=0; i--) //stampa l'array post dell'utente desiderato a partire dal post più nuovo inserito fino al post più vecchio
     				{
     					printf("\t %d. %s\n\n", i, current->u.post[i]); //stampa l'iesimo post dell'utente contenuto nell'array post
					}		
				}
				else //l'utente di cui si vogliono visualizzare i post non ne ha scritto nessuno
				{
					printf("*Non esiste alcun post dell'utente %s da mostrare!\n", username); //comunico all'utente che non esiste nessun post dell'utente desiderato da mostrare
				}
      			
		  	}
		  	contatore++; //incrementa il contatore da confrontare con la posizione utente 
      	current=current->next; //scorre al nodo successivo della linked list 		
		}
	}
	else //l'utente non è stato trovato nella linked list
	{
		//comunico all'utente che non può visualizzare i post perchè ha inserito l'username di un utente che non è presente in linked list
		printf("\nErrore. Non puoi visualizzare i post dell' utente %s perche'\nnon e' registrato sul social UninaNetwork!\n", username);
	}
    
   return; //ritorna al main
}//fine funzione visualizzapostutente
/*-----------------------------------------------------------------------------------------------------------------------------------------------*/

//9.funzione visualizzaultimopostseguiti
void visualizzaultimopostseguiti(struct nodo* head, char *username) //riceve in ingresso il puntatore all'inizio della linked list e l'username dell'utente corrente loggato
{
	int posizioneutente; //variabile che contiene la posizione dell'utente corrente in linked list
	struct nodo* current; //puntatore al nodo utente corrente che scorre la linked list
	struct nodo* temp; //puntatore al nodo utente 'seguito' di cui si vuole vedere l'ultimo post
	int contatore; //contatore che viene confrontato con la posizione dell'utente corrente
	int i; //contatore per il ciclo for
	char tempseguiti[MAXF][MAXU+1]; //array di stringhe di appoggio che contiene gli username degli utenti seguiti dall'utente corrente

	
	i=0;
	contatore=0; //inizializzazione del contatore confrontato con la posizione dell'utente corrente
	current=head; //assegna la testa della linked list al puntatore current

	//stabilisco la posizione del nodo dell'utente corrente nella linked list attraverso la ricercautente
	posizioneutente=ricercautente(current, username); //si richiama la funzione ricercautente	
	
	//scorre la linked list fino a quando non arriva al nodo utente corrispondente alla posizione data dalla ricerca utente			
   while(current!= NULL)
	{
   	if(contatore==posizioneutente) //confronta il contatore corrente con la posizione dell'utente, se corrispondono allora accede al nodo utente altrimenti passa al nodo successivo
      {
        	if(current->u.utentiseguiti>0) //se l'utente ha un numero di seguiti maggiore di zero
        	{
        		
        		for(i=0; i<MAXF; i++) 
     			{
     				strcpy(tempseguiti[i],current->u.seguiti[i]); //copia le stringhe degli username degli utenti seguiti in un array di stringhe di appoggio chiamato tempseguiti
				}
			}
			else //l'utente non segue nessun altro utente per cui non visualizzerà alcun post
			{
				printf("\n*Non e' possibile visualizzare nessun ultimo post\nperche' non segui nessun utente!\n"); //viene comunicato un messaggio di errore
				return; //ritorna al main
			}
   	}
   	
		contatore++; //incrementa il contatore da confrontare con la posizione utente 
   	current=current->next; //scorre al nodo successivo della linked list	
	}
	
	temp=head; //assegna la testa della linked list al puntatore temp
	
	/* a questo punto si scorre la linked list alla ricerca dei seguiti dell'utente corrente, memorizzati nell'array di stringhe tempseguiti.	
	una volta trovato l'utente seguito si mostrerà il suo ultimo post, che si trova in posizione numpost-1 dell'array post dell'utente*/
	while(temp!=NULL) //scorre la linked list fino a quando non arriva al nodo utente seguito
	{
		for(i=0; i<MAXF; i++)
		{
			//compara la stringa dell'username dell'utente corrente in linked list con la stringa dell'utente seguito nell'array tempseguiti
			if((strcmp(temp->u.username,tempseguiti[i])==0))  //se le due stringhe sono uguali vuol dire che devo accedere al nodo dell'utente per visualizzare il suo ultimo post
			{	
				if(temp->u.numpost>0) //se l'utente seguito ha un numero di post maggiore di 0, allora mostro quello in ultima posizione numpost-1
				{
					printf("\t [*] %s: %s\n\n", tempseguiti[i], temp->u.post[temp->u.numpost-1]); //mostra l'ultimo post (il più recente) dell'utente seguito
				}
				else //l'utente seguito non ha scritto alcun post
				{
					printf("\t [*] %s: l'utente non ha alcun post da mostrare.\n\n", tempseguiti[i], tempseguiti[i]); //comunico che l'utente seguito non ha post da mostrare	
				}	
			}
		}
   	temp=temp->next; //scorre al nodo successivo della linked list
   }
   
   return; //ritorna al main
}//fine funzione visualizzaultimopostseguiti
/*-----------------------------------------------------------------------------------------------------------------------------------------------*/

//10.funzione visualizza profilo
/* funzione aggiuntiva che permette di visualizzare il profilo dell'utente corrente compreso di lista dei seguiti, lista dei post dell'utente e
l'ultimo post dei seguiti*/
void visualizzaprofilo(struct nodo* head, char *username) //riceve in ingresso il puntatore all'inizio della linked list e l'username dell'utente corrente loggato
{
	int posizioneutente; //variabile che contiene la posizione dell'utente corrente in linked list
	struct nodo* current; //puntatore al nodo utente corrente che scorre la linked list
	int contatore; //contatore che viene confrontato con la posizione dell'utente corrente
	int i; //contatore usato per il for
	
	//struttura grafica del profilo utente
	system("CLS");
	printf("************************************************************\n");
	printf("\t\tBENVENUTO SU UNINANETWORK,\n\t\t\t%s\n", username);
	printf("************************************************************\n\n");
	printf("_________________________MY ACCOUNT_________________________\n\n");
	printf("[*] %s \n", username);
	printf("\t\n>>>LISTA DEGLI UTENTI SEGUITI<<<\n");
	printf("(Questa lista tiene traccia anche degli utenti eliminati in runtime)\n\n");
	
	i=0;
	contatore=0; //inizializzazione del contatore confrontato con la posizione dell'utente corrente
	current=head; //assegna la testa della linked list al puntatore current
	
	//stabilisco la posizione del nodo dell'utente corrente nella linked list attraverso la ricercautente
	posizioneutente=ricercautente(current, username); //si richiama la funzione ricercautente	
	
	//scorre la linked list fino a quando non arriva al nodo utente corrispondente alla posizione data dalla ricerca utente			
   while(current!= NULL)
	{
      if(contatore==posizioneutente) //confronta il contatore corrente con la posizione dell'utente, se corrispondono allora accede al nodo utente altrimenti passa al nodo successivo
      {
      	//mostra la lista dei seguiti stampando l' array di strighe 'seguiti'
      	for(i=0; i<current->u.utentiseguiti; i++) 
     		{
     			printf("%d. %s\n", i, current->u.seguiti[i]);	
			}			
		}
		contatore++; //incrementa il contatore da confrontare con la posizione utente 
     	current=current->next; //scorre al nodo successivo della linked list 		
	}
	printf("\t\n>>>I TUOI POST<<<\n\n"); //stampa dei post dell'utente
	visualizzapostutente(head, username); //si richiama la funzione visualizzapostutente
	printf("\t\n>>>I NUOVI POST DEI TUOI SEGUITI<<<\n\n", username); //stampa dell'ultimo post dei seguiti
	visualizzaultimopostseguiti(head,username); //si richiama la funzione visualizzaultimopostseguiti
	printf("___________________________________________________________ \n\n");
	
	return; //ritorna al main
}//fine funzione visualizzaprofilo

/*-----------------------------------------------------------------------------------------------------------------------------------------------*/

