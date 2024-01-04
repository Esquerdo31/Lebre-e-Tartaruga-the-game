#include "lab.h"
#include <stdbool.h>


#define NUM_PERSONAGENS 5
#define TAM_PISTA 13
#define NUM_RIACHOS 2

void ecraInicial() {

	setColor(MY_COLOR_CYAN, MY_COLOR_BLACK);
	setFullScreen(true);
	system("cls");
	showRectAt(40, 10, 30, 10);
	gotoxy(35, 10); printf("Bem vindo ao Jogo da lebre e da Tartaruga!\n");
	gotoxy(50, 14); printf("by Hugo Costa");

	gotoxy(10, 22); system("pause");
}

typedef struct BARALHO {
	int maxsize;	// Tamanho máximo do baralho novo
	char cartas[81];	// Estrutura para representar o baralho total
	int size;	// Tamanho atual do baralho
	char descarte[81];	// Estrutura para representar o baralho de descarte
	char apostasIniciais[5];

}baralho;

typedef struct Apostasdejogo{
	char cartas[8];  // Estrutura para representar o baralho de aposta dentro do jogo
	int size;        // Tamanho atual do baralho de aposta
	int maxsize;     // Tamanho máximo do baralho de aposta
} baralho_aposta;

typedef struct Jogador {

	char nome[50];
	int type;
	baralho mao;
	char apostaI;//O que cada jogador vai apostar
	char apostafixa;
	int pontos;// Para a pontua��o final
	char jogo;

}jogador;

typedef struct BOT{

	char nome[50];
	int type;
	baralho mao;
	char apostaI;//O que cada jogador vai apostar
	char apostafixa;
	int pontos;// Para a pontuação final


}nothuman;

// Estrutura para representar um personagem
typedef struct {
	char nome;
	int posicao;
	int ordemChegada; // Ordem de chegada para o pódio (1, 2, 3)
} Personagem;


// Função para inicializar os personagens na pista
void inicializarPersonagens(Personagem personagens[]) {
	personagens[0].nome = 'L';
	personagens[1].nome = 'T';
	personagens[2].nome = 'W';
	personagens[3].nome = 'R';
	personagens[4].nome = 'C';

	for (int i = 0; i < NUM_PERSONAGENS; i++) {
		personagens[i].posicao = 0;    // Todos começam na posição 0 (partida)
		personagens[i].ordemChegada = 0; // Inicialmente, nenhum jogador chegou
	}
}

// Função para imprimir a pista com a posição dos personagens e riachos
void imprimirPista(const Personagem personagens[], const int riachos[]) {
	// Imprimir linha superior da pista
	for (int i = 0; i < TAM_PISTA + 2; i++) {
		printf("-");
	}
	printf("\n");

	// Imprimir pista
	for (int i = 0; i <= TAM_PISTA; i++) {
		printf("|");

		// Imprimir partida, chegada e riachos
		if (i == 0) {
			printf("P");
		}
		else if (i == TAM_PISTA) {
			printf("C");
		}
		else {
			// Imprimir riachos
			int riachoEncontrado = 0;
			for (int j = 0; j < NUM_RIACHOS; j++) {
				if (riachos[j] == i) {
					printf("~"); // Representa um riacho
					riachoEncontrado = 1;
					break;
				}
			}

			// Imprimir personagens
			for (int j = 0; j < NUM_PERSONAGENS; j++) {
				if (personagens[j].posicao == i) {
					printf("%c", personagens[j].nome);
					riachoEncontrado = 1;
				}
			}

			// Preencher espaços vazios
			if (!riachoEncontrado) {
				printf(" ");
			}
		}

		printf("|");
	}

	printf("\n");

	// Imprimir linha inferior da pista
	for (int i = 0; i < TAM_PISTA + 2; i++) {
		printf("-");
	}
	printf("\n");

	// Imprimir posições dos jogadores
	printf("Jogadores: ");
	for (int i = 0; i < NUM_PERSONAGENS; i++) {
		printf("%c(%d) ", personagens[i].nome, personagens[i].posicao);
	}
	printf("\n");
}

// Função para verificar se pelo menos três jogadores passaram a linha de chegada
int verificaPodio(Personagem personagens[]) {
	int contadorChegada = 0;

	for (int i = 0; i < NUM_PERSONAGENS; i++) {
		if (personagens[i].ordemChegada != 0) {
			contadorChegada++;
		}
	}

	// Verificar se pelo menos três jogadores chegaram
	if (contadorChegada >= 3) {
		return 1; // Retorna 1 indicando que pelo menos três jogadores chegaram
	}

	return 0; // Retorna 0 se ainda não houver três jogadores que chegaram
}


void imprimirPodio(const Personagem personagens[]) {
	printf("\n\nPódio:\n");

	// Imprimir todos os jogadores que chegaram ao pódio
	for (int i = 0; i < NUM_PERSONAGENS; i++) {
		if (personagens[i].ordemChegada > 0) {
			printf("%dº lugar: Jogador %c - Posição: %d\n", personagens[i].ordemChegada, personagens[i].nome, personagens[i].posicao);
		}
	}
}

void baralhodedescarte(baralho* myB) {

	for (int i = 0; i < 80; i++) {
		myB->descarte[i] = 'x';
	}
}

void descartebaralho(baralho* myB, baralho_aposta* aposta) {


	do {
		for (int i = 0; i < myB->descarte; i++) {
			if (aposta->cartas[i] != 'x') {
				if (aposta->size != 0) {
					if (myB->descarte != 'x') {

						myB->descarte[i] = aposta->cartas[i];
						aposta->cartas[i] = 'x';
						aposta->size--;
					}
				}
				else { break; }
			}
		}
	} while (aposta->size != 0);
}

void apostasIniciaiscomecar(baralho* myB) {

		myB->apostasIniciais[0] = 'L';
		myB->apostasIniciais[1] = 'T';
		myB->apostasIniciais[2] = 'W';
		myB->apostasIniciais[3] = 'R';
		myB->apostasIniciais[4] = 'C';
	

}

void comecarbaralho(baralho* myB) {

	//L,T,W,w,R,C
	myB->maxsize = 81;
	myB->size;
	int i = 0;
	myB->size = 0;
	for (i = 0; i < 18; i++) {

		myB->cartas[i] = 'L';
		myB->size++;
		if (i == 17) {
			myB->apostasIniciais[0] = 'L';
		}
	}

	for (i = 18; i < 35; i++) {

		myB->cartas[i] = 'T';
		myB->size++;
		
	}


	for (i = 35; i < 48; i++) {

		myB->cartas[i] = 'W';
		myB->size++;
		
	}

	for (i = 48; i < 51; i++) {

		myB->cartas[i] = 'w';
		myB->size++;

	}

	for (i = 51; i < 66; i++) {

		myB->cartas[i] = 'R';
		myB->size++;
	
	}

	for (i = 66; i < 81; i++) {

		myB->cartas[i] = 'C';
		myB->size++;
		
	}


}

void printbaralho(baralho myB) {

	int i = 0;
	for (i = 0; i < 81; i++) //80 --> myB.size??
	{
		if (i == 80) {
			printf("%c", myB.cartas[i]);
		}
		else
			printf("%c,", myB.cartas[i]);


	}

	printf("\n");
}

void scrambledeck(baralho* myB) {

	int i = 0;
	for (i = 0; i < myB->size; i++) {

		if (myB->size == 0) { return; }
		trocaChars(&(myB->cartas[i]), &(myB->cartas[rand() % myB->size]));

	}

}

void embaralharapostainicial(baralho* myB, int tamanho, jogador* P1,nothuman* P2) {
	for (int i = tamanho - 1; i > 0; i--) {
		int j = rand() % (i + 1);

		// Troca as cartas i e j
		char temp = myB->apostasIniciais[i];
		myB->apostasIniciais[i] = myB->apostasIniciais[j];
		myB->apostasIniciais[j] = temp;
	}
	P1->apostafixa = myB->apostasIniciais[0];
	P2->apostafixa = myB->apostasIniciais[1];
}

void nomep1(jogador* P1) {
	gotoxy(40, 14);
	printf("Introduza o nome do Player One: \n");
	gotoxy(40, 16);
	(void)scanf("%s´", P1->nome);

}

void nomep2(nothuman* P2) {
	gotoxy(40, 14);
	printf("Introduza o nome do Player Two: \n");
	gotoxy(40, 16);
	(void)scanf("%s", P2->nome);

}

void p1mao(jogador* P1, baralho* myB) {
	int i;
	P1->mao.maxsize = 7;
	P1->mao.size = 0;
	for (i = 0; i < P1->mao.maxsize; i++) {
		P1->mao.size++;
		P1->mao.cartas[i] = myB->cartas[i];
		myB->cartas[i] = 'x';
		if (i == P1->mao.maxsize) {
			printf("%c", P1->mao.cartas[i]);

		}
		else
			printf("%c,", P1->mao.cartas[i]);
	}

}

void refillp1mao(jogador* P1, baralho* myB) {

	P1->mao.maxsize = 6;
	int i = 0;
	int j = 0;
	while (P1->mao.size != P1->mao.maxsize) {
		if (myB->cartas[i] != 'x') {
			do {
				if (P1->mao.cartas[j] == 'x') {
					P1->mao.cartas[j] = myB->cartas[i];
					myB->cartas[i] = 'x';
					P1->mao.size++;

				}
				j++;
			} while (P1->mao.cartas[j] == 'x');
		}
		i++;
	}
}
		
	



void p2mao(jogador* P1,nothuman* P2, baralho* myB) {
	int i;
	int posicao_maozinha = 0;;
	P2->mao.maxsize = 7;
	P2->mao.size = 0;
	for (i = 0; i < P1->mao.maxsize + P2->mao.maxsize; i++) {
		if (myB->cartas[i] != 'x') {
			P2->mao.cartas[posicao_maozinha] = myB->cartas[i];
			myB->cartas[i] = 'x';
			posicao_maozinha++;
			P2->mao.size++;
			if (posicao_maozinha == P2->mao.maxsize) {
				break;
			}
		}
	}
			for (int i = 0; i < P2->mao.maxsize; i++) {
				if (i == P2->mao.maxsize) {
					printf("%c", P2->mao.cartas[i]);

				}
				else
					printf("%c,", P2->mao.cartas[i]);
			}
		
	
}

void removerElemento(char vetor[], int tamanho, char elemento) {
	int i, j;

	// Procura o elemento no vetor
	for (i = 0; i < tamanho; i++) {
		if (vetor[i] == elemento) {
			// Move os elementos à direita do elemento a ser removido uma posiçao para a esquerda
			for (j = i; j < tamanho - 1; j++) {
				vetor[j] = vetor[j + 1];
			}

			// Reduz o tamanho do vetor
			tamanho--;

			// Decrementa o indice para evitar pular um elemento
			i--;
		}
	}
}

void saveBaralho(FILE* fp, baralho* myB) {

	int i = 0;
	fprintf(fp, "(");
	for (i = 0; i < 81; i++) {
		if (i == 80) {
			fprintf(fp, "%c", myB->cartas[i]);
		}
		else
			fprintf(fp, "%c,", myB->cartas[i]);
	}
	fprintf(fp, ")");
	fclose(fp);
}

void savedeckplusp(FILE* fp, baralho* myB, jogador* P1,nothuman* P2) { //Funçao serve para verificar se est� a guardar tudo bem no ficheiro txt

	int i = 0;
	fprintf(fp, "(");
	for (i = 0; i < 81; i++) {
		if (i == 80) {
			fprintf(fp, "%c", myB->cartas[i]);
		}
		else
			fprintf(fp, "%c,", myB->cartas[i]); //Imprimir tudo igual hà funcao anterior e normal saveBaralho
	}
	fprintf(fp, ")");
	fprintf(fp, "\n %s -> ", P1->nome);
	for (i = 0; i < 7; i++) {
		if (i == 6) {
			fprintf(fp, " %c ", P1->mao.cartas[i]);
		}
		else
			fprintf(fp, " %c,", P1->mao.cartas[i]);
	}

	fprintf(fp, "\n %s -> ", P2->nome);
	for (i = 0; i < 7; i++) {
		if (i == 6) {
			fprintf(fp, " %c ", P2->mao.cartas[i]);
		}
		else
			fprintf(fp, " %c,", P2->mao.cartas[i]);
	}
	fclose(fp);
	printf(" \n");
}

void readBaralho(FILE* fp, baralho* myB) {

	int i = 0;
	fgetc(fp); //descarta '('
	for (i = 0; i < 80; i++) {

		myB->cartas[i] = fgetc(fp);
	}
	fgetc(fp); //descarta ','
}

// Função para verificar se uma carta está na mao
bool cartaNaMao(char mao[], int tamanhoDaMao, char cartaProcurada) {
	for (int i = 0; i < tamanhoDaMao; i++) {
		if (mao[i] == cartaProcurada) {
			return true; // Carta encontrada na m�o
		}
	}
	return false; // Carta n�o encontrada na m�o
}

void apostaInicial(jogador* P1, baralho* myB) {

	int verdadeiro = 0;
	printf("\nTens estas cartas na tua mão:");
	for (int i = 0; i < 7; i++) {
		if (i == 6) {
			printf("%c", P1->mao.cartas[i]);
		}
		else
			printf("%c,", P1->mao.cartas[i]);
	}

	do {
		// Solicita uma carta para fazer de aposta Inicial
		printf("\nEscolhe agora a tua carta da aposta inicial: ");
		(void)scanf(" %c", &P1->apostaI);
		if (P1->apostaI == 'l') {
			P1->apostaI = 'L';
		}
		else {
			if (P1->apostaI == 'r') {
				P1->apostaI = 'R';
			}
			else {
				if (P1->apostaI == 'c') {
					P1->apostaI = 'C';
				}
				else
				{
					if (P1->apostaI == 't') {
						P1->apostaI = 'T';
					}
				}
			}
		}

		if (cartaNaMao(P1->mao.cartas, 7, P1->apostaI))
		{
			printf("Carta encontrada na mao!\n");
			verdadeiro = 1;
			switch (P1->apostaI) {

			case 'L': {
				int j = 0;
				for (j = 0; j < 7; j++) {

					if (P1->apostaI == P1->mao.cartas[j]) {

						P1->mao.cartas[j] = 'x';
						break;
					}
				}

				break;
			}

			case 'l': {
				int j = 0;
				P1->apostaI = 'L';
				for (j = 0; j < 7; j++) {

					if (P1->apostaI == P1->mao.cartas[j]) {

						P1->mao.cartas[j] = 'x';
						break;
					}
				}

				break;
			}
			case 'W': {
				int j = 0;
				for (j = 0; j < 7; j++) {

					if (P1->apostaI == P1->mao.cartas[j]) {

						P1->mao.cartas[j] = 'x';
						break;
					}
				}

				break;
			}
			case 'w': {
				int j = 0;
				for (j = 0; j < 7; j++) {

					if (P1->apostaI == P1->mao.cartas[j]) {

						P1->mao.cartas[j] = 'x';
						break;
					}
				}

				break;
			}
			case 'R': {
				int j = 0;
				for (j = 0; j < 7; j++) {

					if (P1->apostaI == P1->mao.cartas[j]) {

						P1->mao.cartas[j] = 'x';
						break;
					}
				}

				break;
			}
			case 'r': {
				int j = 0;
				P1->apostaI = 'R';
				for (j = 0; j < 7; j++) {

					if (P1->apostaI == P1->mao.cartas[j]) {

						P1->mao.cartas[j] = 'x';
						break;
					}
				}

				break;
			}
			case 'C': {
				int j = 0;
				for (j = 0; j < 7; j++) {

					if (P1->apostaI == P1->mao.cartas[j]) {

						P1->mao.cartas[j] = 'x';
						break;
					}
				}

				break;
			}
			case 'c': {
				int j = 0;
				P1->apostaI = 'C';
				for (j = 0; j < 7; j++) {

					if (P1->apostaI == P1->mao.cartas[j]) {

						P1->mao.cartas[j] = 'x';
						break;
					}
				}

				break;
			}
			case 'T': {

				int j = 0;

				for (j = 0; j < 7; j++) {

					if (P1->apostaI == P1->mao.cartas[j]) {

						P1->mao.cartas[j] = 'x';
						break;
					}
				}

				break;
			}
			case 't': {
				int j = 0;
				P1->apostaI = 'T';
				for (j = 0; j < 7; j++) {

					if (P1->apostaI == P1->mao.cartas[j]) {

						P1->mao.cartas[j] = 'x';
						break;
					}
				}

				break;

			}
			}


			printf("Aposta principal: %c\n", P1->apostaI);
			printf("Ficaste com estas cartas no teu deck :");
			for (int i = 0; i < 7; i++) {
				if (i == 6) {
					printf("%c", P1->mao.cartas[i]);
				}
				else
					printf("%c,", P1->mao.cartas[i]);
			}
		}
		else {
			printf("Carta nao encontrada na mao.\n");

		}
	} while (verdadeiro != 1);
}

void apostaInicialBot(nothuman* P2, baralho* myB) {

	int indicedecartas = rand() % 7;
	P2->apostaI = P2->mao.cartas[indicedecartas];
	P2->mao.cartas[indicedecartas] = 'x';

}

//Adicionar ao baralho de aposta as cartas jogadas
baralho_aposta adicionar_carta_ao_baralho(char carta, baralho_aposta aposta) {
	aposta.maxsize = 8;
	if (aposta.size < aposta.maxsize) {
		for (int i = 0; i < aposta.size; i++) {
			aposta.cartas[i] = carta;
		}
		
	}
	else {
		printf("O baralho de aposta está cheio. Não é possível adicionar mais cartas.\n");
	}

	return aposta;
}

jogador remover_cartas_da_mao(char carta, int quantidade,jogador* P1) {
	

	int removidas = 0;
	for (int j = 0; j < P1->mao.size; j++) {
		if (carta ==P1->mao.cartas[j]) {
			P1->mao.cartas[j] = 'x';
			removidas++;

			if (removidas == quantidade) {
				break;  // Sai do loop se o número desejado de cartas iguais foi removido
			}
		}
	}

	return *P1;
}


// Verificar se a mao do jogador realmente tem cartas iguais para se jogar
int contar_cartas_na_mao(char carta, jogador* P1) {
	int contador = 0;
	for (int i = 0; i < P1->mao.maxsize; i++) {
		if (P1->mao.cartas[i] == carta) {
			contador++;
		}
	}
	return contador;
}

void escolher_cartajogo(jogador *P1, baralho* myB,baralho_aposta* aposta) {
	
	
	int verdadeiro = 0;
	int quantidade;

	do {
		// Solicita uma carta para fazer de aposta Inicial
		printf("\nEscolhe agora a tua carta da aposta : ");
		(void)scanf(" %c", &P1->jogo);
		if (P1->jogo == 'l') {
			P1->jogo = 'L';
		}
		else {
			if (P1->jogo == 'r') {
				P1->jogo = 'R';
			}
			else {
				if (P1->jogo == 'c') {
					P1->jogo = 'C';
				}
				else
				{
					if (P1->jogo == 't') {
						P1->jogo = 'T';
					}
				}
			}
		}

		if (cartaNaMao(P1->mao.cartas, 7, P1->jogo))
		{
			printf("Carta encontrada na mao!\n");
			verdadeiro = 1;
			printf("Quantas cartas iguais queres jogar: ");
			(void)scanf(" %d", &quantidade);

			int quantidade_na_mao = contar_cartas_na_mao(P1->jogo, P1);

			if (quantidade_na_mao < quantidade) {
				printf("Você não tem cartas suficientes na mão.\n");
				verdadeiro = 0;
				continue;  // Reinicia o loop para nova escolha
			}

			remover_cartas_da_mao(P1->jogo, quantidade, P1);
			aposta->size = quantidade;
			*aposta = adicionar_carta_ao_baralho(P1->jogo, *aposta);

			int h = 0;
			for (int i = 0; i < quantidade; i++) {
				
				if (quantidade == 1) {
					printf(" %c\n", P1->jogo);
				}
				else
				{
					if (i == quantidade - 1) {
						printf(" %c\n", P1->jogo);
					}
					else
					{
						if (h == 1) {
							printf(" %c,", P1->jogo);

						}
						else
					
					printf("Jogaste: %c,", P1->jogo);
					h++;
				}

			}
		}
	P1->mao.size= P1->mao.size - quantidade;

			printf("\nFicaste com estas cartas no teu deck :");
			for (int i = 0; i < 6; i++) {
				if (i == 5) {
					printf("%c", P1->mao.cartas[i]);
				}
				else
					printf("%c,", P1->mao.cartas[i]);
			}
			printf("\nBaralho de aposta atual: ");
			for (int i = 0; i < aposta->size; i++) {
				if (i == aposta->size - 1) {
					printf("%c", aposta->cartas[i]);
				}
				else {
					printf("%c, ", aposta->cartas[i]);
				}
			}
			printf("\n");
		}
		else {
			printf("Carta nao encontrada na mao.\n");

		}
	} while (verdadeiro != 1);
	
}

void printcartasparaapostaI(jogador P1) {
	printf("\n%s cartas na mão: ", P1.nome);
	for (int i = 0; i < 7; i++) {
		if (i == 6) {
			printf("%c ", P1.mao.cartas[i]);
		}
		else {
			printf("%c, ", P1.mao.cartas[i]);
		}
	}
	printf("\n");
}

void imprimirCartasNaMaoparajogada(jogador P1) {
	printf("\n%s cartas na mão: ", P1.nome);
	for (int i = 0; i < 6; i++) {
		if (i == 5) {
			printf("%c ", P1.mao.cartas[i]);
		}
		else {
			printf("%c, ", P1.mao.cartas[i]);
		}
	}
	printf("\n");
	printf("Cartas de aposta: %c, %c", P1.apostaI, P1.apostafixa);
}

void imprimirCartasNaMaoparajogadabot(nothuman P2) {
	printf("\n%s cartas na mão: ", P2.nome);
	for (int i = 0; i < 6; i++) {
		if (i == 5) {
			printf("%c ", P2.mao.cartas[i]);
		}
		else {
			printf("%c, ",P2.mao.cartas[i]);
		}
	}
	printf("\n");
	printf("Cartas de aposta: %c, %c\n", P2.apostaI, P2.apostafixa);
}


//void mover(Personagem* personagem,baralho_aposta cartas) {
//	int avanco = 0;
//	personagem->posicao += avanco;
//	
//	for (int i=0; i< cartas.size;i++){
//		switch (cartas.cartas[i]) {
//		case 'L': {
//			avanco = 1;
//			break;
//		}
//		case 'W': {
//			avanco = 3;
//			break;
//		}
//		case 'T': {
//			avanco = 6;
//			break;
//		}
//		case 'R': {
//			avanco = -6;
//			break;
//		}
//		case 'C': {
//			avanco = -3;
//			break;
//		}
//		}
//
//	if (personagem->posicao >= TAM_PISTA) {
//		personagem->posicao = TAM_PISTA;
//		if (personagem->ordemChegada == 0) {
//			// Se o jogador ainda não chegou, registra a ordem de chegada como 1º, 2º ou 3º
//			static int ordemChegadaAtual = 1;
//			personagem->ordemChegada = ordemChegadaAtual++;
//		}
//	}
//}
	

// Função para verificar se há uma carta 'W' no deck de cartas
	int temCartaW(baralho_aposta cartas[], int num_cartas) {
		for (int i = 0; i < num_cartas; i++) {
			if (cartas->cartas[i] == 'w') {
				return 1; // Encontrou uma carta 'w'
			}
		}
		return 0; // Não encontrou nenhuma carta 'w'
	}



	// Função para mover um personagem com base nas cartas da aposta
	void mover(Personagem* personagem, char cartas[], int num_cartas) {
		int avancoL = 0;
		int avancoT = 0;
		int avancoW = 0;
		int avancoR = 0;
		int avancoC = 0;


		if (!temCartaW(cartas, num_cartas)) {

			// Se não há carta 'w', o personagem avança de acordo com as cartas
			for (int i = 0; i < num_cartas; i++) {
				switch (cartas[i]) {
				case 'L': {
					int pos=0;
					pos++;
					avancoL+= pos ;
					break;
				}
				case 'T': {
					int pos = 0;
					pos++;
					avancoT += pos;
					break;
				}
				case 'W': {
					int pos = 0;
					
					pos++;
					avancoW += pos;
					break;
				}
				case 'R': {
					int pos = 0;
				
					pos++;
					avancoR += pos;
					break;
				}
				case 'C': {
					int pos = 0;
					
					pos++;
					avancoC += pos;
					break;
				}
				}

			}

			personagem[0].posicao =+avancoL;
			personagem[1].posicao =+avancoT;
			personagem[2].posicao =+avancoW;
			personagem[3].posicao =+avancoR;
			personagem[4].posicao =+avancoC;

		}
		else
		{

			// Se há carta 'w', o personagem avança pos
			int pos=0;
			
				for (int i = 0; i < num_cartas; i++) {
					switch (cartas[i]) {
			case 'W': {
				pos += 1;
				break;
			}
				}
					if (pos == 1) {
						personagem['W'].posicao = pos;
						
					}
					else {
						personagem['W'].posicao = pos-1;
					}
	

					if (personagem->posicao >= TAM_PISTA) {
						personagem->posicao = TAM_PISTA;
						if (personagem->ordemChegada == 0) {
							// Se o jogador ainda não chegou, registra a ordem de chegada como 1º, 2º ou 3º
							static int ordemChegadaAtual = 1;
							personagem->ordemChegada = ordemChegadaAtual++;
						}
						break;  // Saia do loop se o personagem já chegou
					}
			}
		}


		}


int verifica_cartas(baralho_aposta cartas, int tamanho) {
	int contagem[5] = { 0 }; // L, W, T, R, C

	for (int i = 0; i < tamanho; i++) {
		switch (cartas.cartas[i]) {
		case 'L':
			contagem[0]++;
			break;
		case 'W':
			contagem[1]++;
			break;
		case 'T':
			contagem[2]++;
			break;
		case 'R':
			contagem[3]++;
			break;
		case 'C':
			contagem[4]++;
			break;
		}
	}

	for (int i = 0; i < 5; i++) {
		if (contagem[i] >= 4) {
			return 1; // Pelo menos quatro cartas de um tipo encontrado
		}
	}

	return 0; // Quatro cartas do tipo não encontradas
}


void novoJogo() {

	baralho myB;
	jogador P1;
	nothuman P2;
	baralho_aposta aposta = { .size = 0,.maxsize = 8 };
	Personagem personagens[NUM_PERSONAGENS];
	int riachos[NUM_RIACHOS];
	
	
	// Inicializar riachos em posições aleatórias
	for (int i = 0; i < NUM_RIACHOS; i++) {
		riachos[i] = rand() % (TAM_PISTA - 1) + 1; // Evitar posicionar riachos na partida ou chegada
	}

	inicializarPersonagens(personagens);

	baralhodedescarte(&myB);

	comecarbaralho(&myB);

	scrambledeck(&myB);
	apostasIniciaiscomecar(&myB);
	embaralharapostainicial(&myB, 5, &P1, &P2);

	nomep1(&P1);
	system("cls");
	nomep2(&P2);
	system("cls");

	p1mao(&P1, &myB);
	p2mao(&P1, &P2, &myB);
	printcartasparaapostaI(P1);
	apostaInicial(&P1, &myB);
	apostaInicialBot(&P2, &myB);
	removerElemento(&P1.mao.cartas, 7, 'x');
	removerElemento(&P2.mao.cartas, 7, 'x');

	while (!verificaPodio(personagens)) {
		system("clear || cls"); // Limpar a tela (pode variar dependendo do sistema operacional)

		imprimirPista(personagens, riachos);


		imprimirCartasNaMaoparajogada(P1);
		escolher_cartajogo(&P1, &myB, &aposta);
		int fourcards = verifica_cartas(aposta, aposta.size);

		mover(&personagens, aposta.cartas, aposta.size);
		descartebaralho(&myB, &aposta);
		refillp1mao(&P1, &myB);
		
		printf("Pressiona enter para prosseguir:\n");
		getch(); // Aguarda o usuário pressionar uma tecla

	}
	 

	/*baralhodedescarte(&myB);
	//comecarbaralho(&myB);
	//
	//scrambledeck(&myB);
	//
	//embaralharapostainicial(&myB, 5, &P1,&P2);
	//
	//nomep1(&P1);
	//system("cls");
	//nomep2(&P2);
	//system("cls");
	//
	//FILE* fp = NULL;
	//fopen_s(&fp, "maindeck.txt", "w");
	//if (fp) {
	//	saveBaralho(fp, &myB);
	//	fclose(fp);
	//}
	//gotoxy(40, 15);
	//printf("Baralho inicial:\n");
	//printbaralho(myB);
	//system("pause");
	//
	//p1mao(&P1, &myB);
	//p2mao(&P1,&P2,&myB);*/

	FILE* fp = NULL;
	fopen_s(&fp, "maindeck.txt", "w");
	if (fp) {
		savedeckplusp(fp, &myB, &P1,&P2);

		fclose(fp);
	}
	printbaralho(myB);
	system("pause");
	system("cls");

	printcartasparaapostaI(P1);
	apostaInicial(&P1, &myB);
	apostaInicialBot(&P2, &myB);

	removerElemento(&P1.mao.cartas, 7, 'x');
	removerElemento(&P2.mao.cartas, 7, 'x');


	imprimirCartasNaMaoparajogada(P1);
	imprimirCartasNaMaoparajogadabot(P2);
	system("cls");

	imprimirPista(personagens, riachos);

	system("pause");
	imprimirCartasNaMaoparajogada(P1);
	escolher_cartajogo(&P1, &myB, &aposta);
	system("pause");
	system("cls");
	printf("Posições após mover Personagem:\n");
	
	descartebaralho(&myB, &aposta);

	// Imprimir o pódio final

	imprimirPodio(personagens);

	// Exibir os jogadores ordenados por ordem de chegada
	printf("\n\nPosições de Chegada Ordenadas:\n");
	for (int ordem = 1; ordem <= 3; ordem++) {
		for (int i = 0; i < NUM_PERSONAGENS; i++) {
			if (personagens[i].ordemChegada == ordem) {
				printf("Jogador %c - Posição: %d - Ordem de Chegada: %d\n", personagens[i].nome, personagens[i].posicao, personagens[i].ordemChegada);
			}
		}
	}

	return 0;

}

int main(void) {
	
	srand(time(NULL));
	ecraInicial();
	
	setlocale(LC_ALL, "Portuguese");
	int escolha_menu;
	char content[1000];


	FILE* Rules;

	do {
		system("cls");
		gotoxy(10, 8); printf("Escolha agora o que deseja fazer:\n");
		gotoxy(10, 10);	printf("1-Jogar uma Partida do Jogo ""A Lebre e a Tartaruga""\n");//Escolha A
		gotoxy(10, 11);	printf("2-Carregar uma partida a partir de um ficheiro e continuar o jogo\n");//Escolha B
		gotoxy(10, 12);	printf("3-Descrição do jogo\n");//Escolha C | Op��o configurada e concluida :CHECKMARK:
		gotoxy(10, 13); printf("0-Sair\n");//Sair do jogo | Op��o configurada e concluida :CHECKMARK:

		gotoxy(10, 15); printf("Escolha agora o que deseja fazer:");
		(void)scanf("%d", &escolha_menu);//Escolher a op��o do menu

		switch (escolha_menu) {

		case 1: {

			system("cls");//Limpar o texto anterior 
			novoJogo();

			printf("\nO programa foi bem executado ate aqui\n");//Ponto de verifica��o
			system("pause");//Parar o programa para verificar
			break;//N�o esquecer deste malandro
		}

		case 2: {
			setBackColor(MY_COLOR_DARK_GRAY);

			system("cls"); //Limpar o texto anterior 

			//carregarjogo();
			int i = 0;
			for (i = 0; i < 15; i++) {
				setForeColor(0 + i, i + 1);
				showRectAt(3 + i * 4, 5, 3, 3);

			}


			gotoxy(20, 20);
			printf("O programa foi bem executado ate aqui\n");//Ponto de verifica��o
			system("pause");//Parar o programa para verificar
			break;//N�o esquecer deste malandro
		}

		case 3: {
			setlocale(LC_ALL, "pt_PT.UTF-8");// UTF-8 para ler ficheiros .txt para pt-pt
			system("cls");
			printf("Descricao do jogo:");
			Rules = fopen("rules.txt", "r");
			while (fgets(content, sizeof(content), Rules) != NULL) {
				printf("%s", content);
			}
			fclose(Rules);
			system("pause");
			break;//N�o esquecer deste malandro

		}

		case 0: {
			printf("Saiu do programa\n");//Sair do programa
			break;
		}
		default: {
			//Default para voltar ao ciclo e escolher novamente um n�mero

			printf("Escolha um numero pertencente ha lista!\n");
			system("pause");
			break;

		}
		}

	} while (escolha_menu != 0);//Sair do jogo e fechar o programa



}