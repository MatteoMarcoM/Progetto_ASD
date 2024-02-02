/* TEST * ANALISI COMPLESSITA': 
 * PROGETTO ASD sessione ESTIVA 2019/2020 
 * Autori: Montanari Matteo Marco, Di Fabrizio Giacomo
 * Versione leggermente modificata del programma di progetto (gli algoritmi utilizzati sono inalterati)*/

/* inclusione delle librerie */

#include <stdio.h>
#include <stdlib.h>		/* per calloc e malloc */
#include <time.h>		/* rand() */
#include <string.h> 	/* per strcmp() */

/* Definizione dei tipi di dato */

/* Tipo di dato albero binario */ 

typedef struct nodo_albero_bin
{
	int valore;
	char *stringa;
	struct nodo_albero_bin *sx_p, *dx_p;
	
} nodo_albero_bin_t;

/* Tipo di dato booleano */

typedef enum
{
	falso,
	vero
} verita_t;

/* Dichiarazione delle funzioni */

int inserisci_in_albero_bin_ric(nodo_albero_bin_t **, int, char *, int *);

void visita_albero_bin_ant(nodo_albero_bin_t *, int *);

void visita_albero_bin_simm(nodo_albero_bin_t *, int *);

void visita_albero_bin_post(nodo_albero_bin_t *, int *);

nodo_albero_bin_t *cerca_in_albero_bin_ric(nodo_albero_bin_t *, int, int *);

/* definzione delle funzioni (a partire dalla funzione main) */

int main(void)
{
	/* dichiarazione delle variabili locali alla funzione */

	nodo_albero_bin_t *radice_p = NULL;
	nodo_albero_bin_t *risultato_ricerca_p = NULL;
	
	int n,
	    i,
	    j,
	    t;
	int *appoggio_valori;
	int ricerca_val,
		genera_char,
	    genera_char1,
		genera_char2,
		genera_char3,
		prova_char,
	    esito_lettura,
	    scelta; 
	char **appoggio_stringhe;
	verita_t controllo;

	/* contatori di passi per analisi sperimentale */

	int conta_ins,
	    conta_ant,
	    conta_simm,
	    conta_simm2,
	    conta_post,
	    conta_cerca;
	
	conta_ins = conta_ant = conta_simm = conta_simm2 = conta_post = conta_cerca = 0;
	
	srand(time(NULL));	/* Seed per rand() casuale */
	
	/* acquisizione dall’utente di un valore numerico n */

	do
	{
		printf("Inserisci di quanti nodi vuoi creare l'albero (>0): ");
		esito_lettura = scanf("%d", &n);
	
		if (esito_lettura != 1 || n <= 0)
			printf("Input non accettabile!\n");
	
		while (getchar() != '\n');
	}
	while (esito_lettura != 1 || n <=0);
	
	appoggio_valori = (int *)calloc(n + 1, sizeof(int));
	appoggio_stringhe = (char **)calloc(n + 1, sizeof(char *));		/*un valore ulteriore per analisi complessità sperimentale dell'inserimento*/
	
	/* generazione casuale di n numeri interi compresi tra 0 e 3n e di n stringhe di 10 caratteri
	 * e caricamento in un albero binario di ricerca di tutte le coppie (numero, stringa) di dati generati */
	
	
	for(i = 0;
	    i < n + 1;
	    i++)
	{
		appoggio_stringhe[i] = (char *)calloc(11, sizeof(char));
	
		controllo = falso;
		
		while(!controllo)
		{
			appoggio_valori[i] = rand() % (3*n + 1);
			controllo = vero;
			for(t = 0; (t < i); t++)
			{
				if(appoggio_valori[i] == appoggio_valori[t])
				{
					controllo = falso;
				}
			}
		}
		for (j = 0; j <= 9; j++)
		{		
			genera_char1 = 'A' + rand() % ('Z' - 'A');		/*maiuscola casuale*/
			genera_char2 = 'a' + rand() % ('z' - 'a');		/*minuscola casuale*/
			genera_char3 = '0' + rand() % ('9' - '0');		/*cifra casuale*/
			
			/*scelta casuale tra maiuscole munuscole e cifre*/
			prova_char = rand() % 3;
			
			if (prova_char == 0)
				genera_char = genera_char1;
			else if(prova_char == 1)
				genera_char = genera_char2;
			else
				genera_char = genera_char3;
			
			/*inserimento del carattere casuale generato*/
			appoggio_stringhe[i][j] = (char)genera_char; 
		}
		appoggio_stringhe[i][10] = '\0';
		
		if (i < n)		
			inserisci_in_albero_bin_ric(&radice_p, appoggio_valori[i], appoggio_stringhe[i], &conta_ins);
	}
     /*	printf("\nL'inserimento degli n valori e' avvenuto in %d passi\n", conta_ins);	*/ /*elemento aggiuntivo inserito per curiosità personale*/
	
	do
	{
		printf("\nChe visita vuoi avviare?\n");
		printf("1. visita anticipata\n");
		printf("2. visita simmetrica\n");
		printf("3. visita posticipata\n");
		esito_lettura = scanf("%d", &scelta);
	
		if (esito_lettura != 1 || scelta <= 0 || scelta > 3)
			printf("Input non accettabile!\n");
	
		while (getchar() != '\n');
	}
	while (esito_lettura != 1 || scelta <= 0 || scelta > 3);
	
	
	switch (scelta)
	{
		case 1:
			printf("La visita anticipata e' avvenuta in ");
			visita_albero_bin_ant(radice_p, &conta_ant);
			printf("%d passi\n", conta_ant);
		break;
		case 2:
			printf("La visita simmetrica: e' avvenuta in ");
			visita_albero_bin_simm(radice_p, &conta_simm);
			printf("%d passi\n", conta_simm);
		break;
		case 3:
			printf("La visita posticipata e' avvenuta in ");
			visita_albero_bin_post(radice_p, &conta_post);
			printf("%d passi\n", conta_post);
		break;
	}
	
	/*inserimento valore casuale per analisi complessità*/
	conta_ins = 0;		/*reset passi*/
	inserisci_in_albero_bin_ric(&radice_p, appoggio_valori[n], appoggio_stringhe[n], &conta_ins);
	printf("L'inserimento di un valore casuale (%d) e' avvenuto in %d passi\n",appoggio_valori[n], conta_ins);
	
	/*ricerca di un elemento casuale (sulla base della chiave numero intero)*/
	ricerca_val = rand()%(3*n + 1);
	risultato_ricerca_p = cerca_in_albero_bin_ric(radice_p, ricerca_val, &conta_cerca);
	
	printf("Il valore casuale cercato ");
	if (risultato_ricerca_p != NULL)
	{
		printf("e': %d\t%s\n", risultato_ricerca_p->valore, risultato_ricerca_p->stringa);
	}
	else
		printf("(%d) non e' presente all' interno dell' albero!\n", ricerca_val);
	
	printf("La ricerca e' avvenuta in %d passi\n", conta_cerca);
	
	free(appoggio_valori);
	free(appoggio_stringhe);
	
	getchar();
	return (0);
}

/* Definizione della funzione inserisci in albero binario di ricerca */

int inserisci_in_albero_bin_ric(nodo_albero_bin_t **radice_p, int valore, char *stringa, int *conta_ins)
{
	
	/* dichiarazione delle variabili locali alla funzione */
	
	int inserito;
	nodo_albero_bin_t *nodo_p,
			  *padre_p,
			  *nuovo_p;
	
	*conta_ins += 1;
	for (nodo_p = padre_p = *radice_p;
	/* verifica anche chiave secondaria se la primaria e' uguale */
	((nodo_p != NULL) && ((nodo_p -> valore != valore) || strcmp(nodo_p -> stringa,stringa) != 0));	
        padre_p = nodo_p, nodo_p = (valore < nodo_p -> valore)?	
				nodo_p ->sx_p:
				nodo_p ->dx_p)
				{
					*conta_ins += 2;
				}
	*conta_ins += 1;
	
	*conta_ins += 1;
	if (nodo_p != NULL)
	{
		inserito = 0;
		*conta_ins += 1;
	}
	
	else
	{
		inserito = 1;
		nuovo_p = (nodo_albero_bin_t *)malloc(sizeof(nodo_albero_bin_t));
		nuovo_p -> valore = valore;
		nuovo_p -> stringa = calloc(11,sizeof(char));
		strcpy(nuovo_p -> stringa, stringa);
		nuovo_p -> sx_p = nuovo_p -> dx_p = NULL;
        
		*conta_ins += 6;
		if (nodo_p == *radice_p)
		{
			*radice_p = nuovo_p;
			*conta_ins += 1;
		}
		else
		{
			*conta_ins += 1;
			if (valore < padre_p -> valore)
			{
				padre_p -> sx_p = nuovo_p;
				*conta_ins += 1;
			}
			else 
			{
				padre_p -> dx_p = nuovo_p;
				*conta_ins += 1;
			}
		}
    }
    return(inserito);
}


/* Dichiarazione della funzione visita in albero binario in ordine anticipato */

void visita_albero_bin_ant(nodo_albero_bin_t *nodo_p, int *conta_ant)
{
	*conta_ant += 1;
	if (nodo_p != NULL)
	{
		*conta_ant += 1;		/*elabora*/
		visita_albero_bin_ant(nodo_p->sx_p, conta_ant);
		visita_albero_bin_ant(nodo_p->dx_p, conta_ant);
	}
}

/* Dichiarazione della funzione visita in albero binario in ordine simmetrico */

void visita_albero_bin_simm(nodo_albero_bin_t *nodo_p, int *conta_simm)
{
	*conta_simm += 1;
	if (nodo_p != NULL)
 	{
		visita_albero_bin_simm(nodo_p->sx_p, conta_simm);
		*conta_simm += 1;		/*elabora*/
		visita_albero_bin_simm(nodo_p->dx_p, conta_simm);
	}
}

/* Dichiarazione della funzione visita in albero binario in ordine posticipato */

void visita_albero_bin_post(nodo_albero_bin_t *nodo_p, int *conta_post)
{
	*conta_post += 1;
	if (nodo_p != NULL)
	{
		visita_albero_bin_post(nodo_p->sx_p, conta_post);
		visita_albero_bin_post(nodo_p->dx_p, conta_post);	
		*conta_post += 1;		/*elabora*/
	}
}

/* Dichiarazione della funzione cerca in albero binario di ricerca */

nodo_albero_bin_t *cerca_in_albero_bin_ric(nodo_albero_bin_t *radice_p, int valore, int *conta_cerca)
{
	nodo_albero_bin_t *nodo_p;

	*conta_cerca += 1;
	for (nodo_p = radice_p;	
	     ((nodo_p != NULL) && (nodo_p->valore != valore));
	 	nodo_p = (valore < nodo_p->valore)?
				  nodo_p->sx_p:
				  nodo_p->dx_p)
				  {
					*conta_cerca += 2;
				  }
				  
	*conta_cerca += 1;
				  
	return(nodo_p);
}
