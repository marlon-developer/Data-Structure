#include <stdio.h>
#include <stdlib.h>

/*
Para manipular arquivos texto em C é preciso:
1 - declarar uma variável 'procuradora' 
2 - associar a variável 'procuradora' ao arquivo, representando-o na memória
3 - definir o modo de abertura (leitura, escrita ou inclusão)
4 - percorrer o arquivo (leitura ou escrita)
5 - fechar a variável 'procuradora', descarregando o conteúdo da memória para o disco
*/

/*
Codigo que abre um arquivo texto qualquer, o exibe na tela e faz uma cópia
no arquivo novo criado 'backup.txt'
*/

int main() {
	FILE *arquivoEntrada, *arquivoSaida;
	char nomeArquivoEmDisco[100];
	char linha[100];

	printf("Informe nome do arquivo a ser aberto: ");
	scanf("%s", nomeArquivoEmDisco);

	//verificar se arquivo existe
	arquivoEntrada = fopen(nomeArquivoEmDisco,"r"); //modo de leitura
	if (!arquivoEntrada) {
		printf("Arquivo não encontrado\n");
		exit(0);
	}

	//abrir arquivo de saida para o backup
	arquivoSaida = fopen("backup.txt", "w"); //modo escrita

	//percorrer arquivo de entrada, linha a linha
	while (fgets(linha, 100, arquivoEntrada)) {
		printf("%s", linha); //grava na tela
		fprintf(arquivoSaida,"%s", linha); //grava no arquivo de saida
		fflush(arquivoSaida); //descarrega os dados da memória para disco
	}
	fclose(arquivoEntrada);
	fclose(arquivoSaida);

	printf("\nCópia realizada com sucesso! Veja o arquivo backup.txt\n\n");

	return 1;
}