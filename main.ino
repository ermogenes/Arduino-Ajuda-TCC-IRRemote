#include <IRremote.h>

// Configurações do hardware IR
int RECV_PIN = 11; // mude para o pin que vcs usam, parece que é o 12
IRrecv irrecv(RECV_PIN);
decode_results results;

// Variáveis e constantes auxiliares

int COD_TECLA[10] = {
	16625743,
	16580863,
	16613503,
	16597183,
	16589023,
	16621663,
	16605343,
	16584943,
	16617583,
	16601263
};

int linha[14] = {22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35};

int LIMPAR = -1;

int entrada[2] = {LIMPAR, LIMPAR};
int entrada_inicial[2] = {0 ,0};

int posicao_atual = 0;

long INTERVALO_ENTRE_TECLAS = 1000;
long tempo_ultima_tecla = 0;

void setup() {
	Serial.begin(9600);

	Serial.println("\nValendo!");

	// Inicia gerador de números aleatórios
	randomSeed(analogRead(0));

	// Liga os leds na situação desejada
	situacao_inicial_leds();

	// Inicia contador de tempo
	tempo_ultima_tecla = millis();
}


void loop() {
	int tecla_recebida = 0;

	// Na linha abaixo a tecla é simulada aleatoriamente.
	// Substitua pelo código que leia o controle remoto e grave a tecla na variável tecla_recebida
	tecla_recebida = simula_tecla();
	// Ex: tecla_recebida = decodifica_tecla(le_tecla_IR());

	// Faz o shift entre a primeira e a segunda posição de exibição
	atualiza_posicao();

	// Guarda a tecla pressionada na posição certa
	entrada[posicao_atual] = tecla_recebida;

	// Caso o tempo entre teclas tenha sido atingido, atualiza a exibição
	if (millis() - tempo_ultima_tecla > INTERVALO_ENTRE_TECLAS){
		Serial.println("Demorou o suficiente para exibir");
		exibe(entrada[0], entrada[1]);
		entrada[0] = LIMPAR;
		entrada[1] = LIMPAR;
	}

	// Atualiza contador de tempo
	tempo_ultima_tecla = millis();

	// Esse delay é só para interface com usuário, pode-se retirar
	delay(500);
}

void situacao_inicial_leds() {
	exibe(entrada_inicial[0], entrada_inicial[1]);
}

void exibe(int n1, int n2){
	exibe_numero(n1, 1);
	exibe_numero(n2, 2);

	Serial.print("[");
	Serial.print(n1);
	Serial.print("][");
	if(n2>0)
		Serial.print(n2);
	Serial.println("]");
}

void exibe_numero(int numero, int posicao){
	if (posicao == 1){
		switch (numero){
			case 0:
				digitalWrite(linha[0], HIGH);
				digitalWrite(linha[1], HIGH);
				digitalWrite(linha[2], HIGH);
				digitalWrite(linha[3], HIGH);
				digitalWrite(linha[4], HIGH);
				digitalWrite(linha[5], HIGH);
				digitalWrite(linha[6], LOW);
				break;
			case 1:
				digitalWrite(linha[0], LOW);
				digitalWrite(linha[1], LOW);
				digitalWrite(linha[2], HIGH);
				digitalWrite(linha[3], HIGH);
				digitalWrite(linha[4], LOW);
				digitalWrite(linha[5], LOW);
				digitalWrite(linha[6], LOW);
			break;
			case 2:
				 // continue aqui
			break;
			case 3:
				 // continue aqui
			break;
			
			// até 9
			
			default:
				 // limpe os leds, apagando todos
				digitalWrite(linha[0], LOW);
				digitalWrite(linha[1], LOW);
				digitalWrite(linha[2], LOW);
				digitalWrite(linha[3], LOW);
				digitalWrite(linha[4], LOW);
				digitalWrite(linha[5], LOW);
				digitalWrite(linha[6], LOW);
			break;
		}
	} else {
		switch (numero){
			case 0:
				digitalWrite(linha[7], HIGH);
				digitalWrite(linha[8], HIGH);
				digitalWrite(linha[9], HIGH);
				digitalWrite(linha[10], HIGH);
				digitalWrite(linha[11], HIGH);
				digitalWrite(linha[12], HIGH);
				digitalWrite(linha[13], LOW);
			break;
			case 1:
				digitalWrite(linha[7], LOW);
				digitalWrite(linha[8], LOW);
				digitalWrite(linha[9], HIGH);
				digitalWrite(linha[10], HIGH);
				digitalWrite(linha[11], LOW);
				digitalWrite(linha[12], LOW);
				digitalWrite(linha[13], LOW);
			break;
			case 2:
					// continue aqui
			break;
			case 3:
					// continue aqui
			break;
			
			// até 9
			
			default:
				// limpe os leds, apagando todos
				digitalWrite(linha[7], LOW);
				digitalWrite(linha[8], LOW);
				digitalWrite(linha[9], LOW);
				digitalWrite(linha[10], LOW);
				digitalWrite(linha[11], LOW);
				digitalWrite(linha[12], LOW);
				digitalWrite(linha[13], LOW);
			break;
		}
	}
}

int le_tecla_IR(){
	int codigo_tecla_IR = 0;

	// Escreva aqui o código que captura a leitura da tecla do IR

	return codigo_tecla_IR;
}

// Transforma um código padrão IR em número 0-9
int decodifica_tecla(int tecla_pressionada){
	for (int i = 0; i < 10; i++)
		if (COD_TECLA[i] == tecla_pressionada)
			return i;
}

// Rotaciona a posição da próxima tecla
void atualiza_posicao(){
	if (entrada[0] == -1){
		posicao_atual = 0;
		entrada[1] = -1;
	} else if (entrada[1] == -1){
		posicao_atual = 1;
	} else {
		posicao_atual = 0;
		entrada[0] = -1;
		entrada[1] = -1;
	}
}

// Para testes, simula o controle remoto
int simula_tecla(){
	int tecla = int(random(10));
	Serial.print("Teclou ");
	Serial.println(tecla);
	delay(random(1000)); // espera um tempo aleatório para testar a parada com uma tecla só
	return tecla;
};
