# Jogo da Veia em C++
![c++](https://img.shields.io/static/v1?label=c%2B%2B&message=c++&color=orange&style=for-the-badge&logo=c%2B%2B)
![License](http://img.shields.io/static/v1?label=License&message=MIT&color=green&style=for-the-badge)
![Status](http://img.shields.io/static/v1?label=STATUS&message=CONCLUIDO&color=GREEN&style=for-the-badge)

> Status do Projeto: :heavy_check_mark:

## Descrição-do-projeto 

> Este projeto foi desenvolvido durante o segundo semestre da faculdade como parte da disciplina de Programação 1. O objetivo era ampliar os conceitos de programação aprendidos até a data, aplicando-os na criação de um jogo da velha em Linguagem C++.


## Problema

> Questão:

Desenvolver um jogo interativo em Linguagem C++ como projeto prático da disciplina de Programação 1, durante o segundo semestre do curso de Ciência da Computação, com o objetivo de aplicar e consolidar os conceitos aprendidos ao longo das aulas. A proposta do projeto é criar um jogo simples, como Jogo da Velha, Pedra-Papel-Tesoura ou outro jogo baseado em turnos, utilizando os fundamentos de programação. O programa deve implementar funcionalidades essenciais, como entrada de dados e validação das escolhas dos usuários, além de utilizar estruturas de controle de fluxo, como if, while e for. É necessário que o projeto apresente mensagens interativas que garantam uma experiência amigável ao jogador, explicando as regras do jogo, notificando erros e exibindo os resultados ao final de cada partida (como vitória, derrota ou empate). O código deve demonstrar modularidade por meio do uso de funções e manipulação de arrays, organizando e simplificando o programa.

## Funcionalidades

- Implementação completa do jogo da velha com interface de linha de comando.
- Utilização de conceitos fundamentais de programação, como estruturas de controle, funções e arrays.
- Projeto modularizado para facilitar a compreensão e manutenção do código

## Como rodar a aplicação :arrow_forward:

### Pré-requisitos

- **Sistema Operacional:** Windows, Linux ou MacOS com suporte a compiladores C++.  
- **Compilador:** Ter o **g++** ou qualquer outro compilador compatível com C++ instalado.  
- **Terminal:** Acesso a um terminal para executar os comandos.  
- **Git:** Ferramenta para clonar o repositório do GitHub.  

### Passo a Passo da Instalação

#### 1. Clone o repositório  
Abra o terminal e execute o comando abaixo para clonar o projeto:  
```bash  
git clone https://github.com/StellaKarolinaNunes/JogoVeia.git  
```

#### 2. Acesse o diretório do projeto  
Entre na pasta do jogo da velha:  
```bash  
cd JogoVeia  
```

#### 3. Compile o código  
Utilize um compilador como o **g++** para compilar o arquivo principal do jogo:  
```bash  
g++ jogo_veia.cpp -o jogo_veia  
```  

#### 4. Execute o programa  
Após a compilação, inicie o jogo com o comando:  
```bash  
./jogo_veia  
```  

#### 5. Aproveite o jogo!  
Siga as instruções exibidas no terminal para fazer suas jogadas e aproveite a experiência interativa.  


## fotos 

(algumas imagem do projeto )

![image](https://github.com/StellaKarolinaNunes/JogoVeia/assets/118007989/9799cbdf-64e7-4b25-87a4-ab0e3ac4afec)

![image](https://github.com/StellaKarolinaNunes/JogoVeia/assets/118007989/a9863448-3f8c-4cbd-b817-70d7b37b08b2)

![image](https://github.com/StellaKarolinaNunes/JogoVeia/assets/118007989/478f30e3-c4f1-4550-96bc-3e7dc1df17c9)

## FAQ/Perguntas Frequentes ❓❔  

### 1. Como o jogo da velha funciona?  
> **R:** O jogo da velha é uma aplicação simples baseada em turnos. Dois jogadores se alternam para marcar os espaços em uma grade 3x3. O objetivo é alinhar três marcas consecutivas (em uma linha, coluna ou diagonal).  

### 2. Quais são os requisitos para rodar o jogo?  
> **R:** Você precisa de um sistema operacional com suporte a C++ e de um compilador como **g++** para compilar e rodar o código. O jogo foi testado e funciona em Windows, Linux e MacOS.  

### 3. O que acontece quando o jogo detecta uma vitória ou empate?  
> **R:** O programa exibe uma mensagem indicando o jogador vencedor ou se houve empate, encerrando a partida.  

### 4. Como são feitas as jogadas?  
> **R:** Cada jogador insere o número correspondente à posição desejada na grade (numerada de 1 a 9). As posições correspondem a:  
```  
1 | 2 | 3  
--+---+--  
4 | 5 | 6  
--+---+--  
7 | 8 | 9  
```  

### 5. É possível jogar novamente sem fechar o programa?  
> **R:** Sim! Após o término de uma partida, o programa oferece a opção de reiniciar o jogo ou encerrar o programa.  

### 6. O que acontece se o jogador tentar marcar uma posição já ocupada?  
> **R:** O programa verifica se a posição está disponível antes de validar a jogada. Caso contrário, ele solicita que o jogador escolha outra posição.  

### 7. Como posso alterar o código para personalizar o jogo?  
> **R:** Você pode modificar o código para incluir funcionalidades extras, como placar acumulativo, alterações de tamanho da grade, ou até mesmo implementar uma IA para jogar contra o computador.  

### 8. Quais conceitos de programação são aplicados no código?  
> **R:** O projeto utiliza conceitos como entrada e validação de dados, uso de estruturas de repetição (**while** e **for**), controle de fluxo (**if/else**), funções para modularidade e manipulação de arrays para representar a grade do jogo.  

### 9. Como compilar e executar o código?  
> **R:** Siga estes passos:  
   - Compile o código com o comando:  
     ```bash  
     g++ jogo_veia.cpp -o jogo_veia  
     ```  
   - Execute o programa com o comando:  
     ```bash  
     ./jogo_veia  
     ```  

### 10. Posso compartilhar o jogo com outras pessoas?  
> **R:** Sim! Você pode compartilhar o jogo diretamente ou convidar outras pessoas para clonar o repositório no GitHub. O código é de código aberto, mas lembre-se de creditar o autor ao distribuí-lo.  



## License/Licença do Projeto  

> [MIT](./License)

## Programador


| [<img loading="lazy" src="https://github.com/StellaKarolinaNunes.png" width="115"><br><sub>STELLA KAROLINA</sub>](https://github.com/StellaKarolinaNunes) |
| :---: |




