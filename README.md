   <h1 align="center">
       Jogo da Veia em C
    <br />
    <br />
    <a href="https://github.com/StellaKarolinaNunes/jogo-da-veia">
     <img src="./assets/banner.png " alt="Jogo da Veia Banner " width="100%">
    </a>
  </h1>

</div>

<p align="center">
  <img src="https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white" alt="C">
  <img src="https://img.shields.io/badge/Status-Gratuito-green?style=for-the-badge" alt="Status">
  <a href="https://github.com/StellaKarolinaNunes/lipo-docs-mintlify/blob/main/LICENSE"><img src="https://img.shields.io/github/license/StellaKarolinaNunes/lipo-docs-mintlify?style=flat&logo=open-source-initiative&logoColor=white" alt="Licença"></a>
</p>

<br>

---

##  Introdução
Este projeto foi desenvolvido durante o segundo semestre da faculdade como parte da disciplina de Programação 1. O objetivo foi consolidar e ampliar os conceitos de programação aprendidos até o momento, por meio da criação de um jogo da velha utilizando a linguagem C.

---

## Qual o Problema? 
Desenvolver um jogo interativo em linguagem C como projeto prático da disciplina de Programação 1, com o objetivo de aplicar e reforçar os conceitos fundamentais estudados ao longo das aulas.

A proposta consiste na criação de um jogo simples baseado em turnos, como o jogo da velha, utilizando conceitos essenciais de programação, tais como:

* Entrada e validação de dados do usuário
* Estruturas de controle de fluxo (if, while, for)
* Modularização por meio de funções
* Manipulação de arrays
*e entre outras funções

<br>


## A Solução
A solução desenvolvida utiliza uma matriz 3x3 de caracteres para representar o tabuleiro do jogo. O sistema foi estruturado de forma modular, com funções específicas responsáveis por:

* Exibir o tabuleiro
* Validar as jogadas dos jogadores
* Controlar os turnos
* Verificar condições de vitória ou empate

O fluxo principal do programa utiliza estruturas de repetição para alternar os turnos entre os jogadores até que uma condição de término seja atingida. Dessa forma, o jogo proporciona uma experiência interativa, organizada e eficiente, aplicando na prática os principais conceitos da linguagem C.

 <br>

## Funcionalidades

* **Múltiplos Modos de Jogo**:
  - **Player vs Player**: Desafie um amigo localmente.
  - **Player vs IA**: Enfrente a inteligência artificial com 3 níveis de dificuldade (Fácil, Médio, Difícil).
  - **Modo Infinito**: Uma variação dinâmica onde as peças mais antigas desaparecem após 3 jogadas, forçando novas estratégias.
* **Personalização Estética**: 
  - Mais de 50 temas visuais diferentes aplicáveis em tempo real.
  - Cabeçalhos em ASCII Art dinâmicos e vibrantes.
* **Competição e Progressão**:
  - **Ranking Global**: Acompanhe vitórias, derrotas, empates e saldo de pontos.
  - **Sistema de Medalhas**: Conquiste medalhas por feitos específicos (ex: vencer a IA no nível difícil).
* **Gestão de Partidas**:
  - **Save/Load**: Salve o estado da sua partida  
  - **Replay**: Assista à repetição automática da última partida jogada.
* **Modo Torneio**: Configure partidas "Melhor de 3" ou "Melhor de 5".
* **Interface Refinada**: Layout fixo de 102 colunas com centralização dinâmica de textos e feedback de status integrado.

>  **Fluxograma do Projeto**: Caso queira entender a lógica de navegação e processos do aplicativo, acesse o arquivo [fluxograma/FLUXOGRAMA.md](fluxograma/FLUXOGRAMA.md).

<br>

##  Estrutura de Pastas

 A estrutura do projeto segue o padrão de organização por camadas, facilitando a manutenção e escalabilidade.

 ```bash
jogo_veia/
├── assets/                     # Imagens e banners do projeto
├── build/                      # Arquivos gerados pela compilação
├── fluxograma/                 # Fluxogramas do projeto
├── saves/                      # Arquivos de saves
├── teste/                      # Arquivos de teste
├── .gitignore                  # Arquivos e pastas ignorados pelo Git
├── compile.sh                  # Script de compilação
├── config.h                    # Configurações do projeto
├── doyfile                     # Arquivo de compilação
├── file_manager.c              # Gerenciamento de arquivos
├── file_manager.h              # Gerenciamento de arquivos
├── game.c                      # Lógica do jogo
├── game.h                      # Lógica do jogo
├── globals.c                   # Variáveis globais
├── jogo_velha                  # Executável do jogo
├── main.c                      # Função principal
├── maintenace.c                # Manutenção do jogo
├── maintenace.h                # Manutenção do jogo
├── menu.c                      # Menu do jogo
├── menu.h                      # Menu do jogo
├── ranking.dat                 # Ranking de jogadores
├── ranking.h                   # Ranking de jogadores
├── settings.cfg                # Configurações do jogo
├── theme.c                     # Temas do jogo
├── theme.h                     # Temas do jogo
├── themes.cfg                  # Temas do jogo
├── ui.c                        # Interface do jogo
├── ui.h                        # Interface do jogo
├── utils.c                     # Utilitários do jogo
├── utils.h                     # Utilitários do jogo
├── README.md                   # README do projeto
```

 <br>

##  Instalação

### Pré-requisitos para Rodar jogo da veia na sua maquina 
* **Compilador C**: Recomendado [GCC](https://gcc.gnu.org/) (versão 9.0 ou superior).
* **Bash Environment**: O script de automação `./compile.sh` requer um ambiente shell (Nativo no Linux/macOS, Git Bash no Windows).
* **Terminal**: Suporte a sequências de escape ANSI (Cores e formatação) para a experiência visual completa.
* **Git**: Para clonar o repositório.
* **gcc (compilador C)**: Para compilar o projeto.
* **make (automação)**: Para automatizar a compilação.

<br>

### Tecnologias utilizadas
* **C**: Linguagem de programação utilizada.
* **Bash**: Script de automação.
* **Git**: Controle de versão.

<br>


###  Instalação Rápida

####  1. Clone o repositório

```bash
git clone https://github.com/StellaKarolina/jogo_velha.git
```

####  2. Acesse pasta

```bash
cd jogo_velha
```

####  3. Compile o código Usando o Script de Compilação (Recomendado)

```bash
chmod +x compile.sh    # Dá permissão de execução (se necessário)
./compile.sh           # Compila e inicia o jogo
```

####  4. Manualmente via Terminal (Caso queira saber o comando exato)

```bash
gcc *.c -o jogo_velha   # Compila o projeto
./jogo_velha            # Executa o projeto
```

### 5. Scripts Disponíveis

* `./compile.sh`  Compila o projeto 
* `./run.sh`  Executa o projeto 
* `./clean.sh`  Limpa o projeto 

<br>

> Saiba mais sobre a linguagem C (so click no texto desejado): [COMO INSTALAR C WINDOWS](https://www-digitalocean-com.translate.goog/community/tutorials/c-compiler-windows-gcc?_x_tr_sl=en&_x_tr_tl=es&_x_tr_hl=es&_x_tr_pto=tc&_x_tr_hist=true); [COMO INSTALAR C LINUX](https://www.bosontreinamentos.com.br/linux/como-instalar-gcc-e-pacotes-de-desenvolvimento-no-linux-debian-10/); [Documentação](https://port70.net/~nsz/c/c11/n1570.html); [Documentação ISO C Draft](https://www.open-std.org/jtc1/sc22/wg14/www/docs/n2310.pdf); [Guia](https://www.geeksforgeeks.org/c-programming-language/); [Referência](https://en.cppreference.com/w/c/language.html);

<br>
 
##  Roadmap

 Atualmente estamos trabalhando nas seguintes frentes:

 - [ ] **IA Mestre (Minimax)**: Implementar algoritmo minimax com poda alfa-beta para invencibilidade total no nível Hard.
 - [ ] **Multiplayer Online**: Suporte a partidas via rede local ou internet utilizando Sockets TCP/IP.
 - [ ] **Customização de Tabuleiro**: Opções de tamanhos dinâmicos como 4x4, 5x5 ou até 10x10.
 - [ ] **Perfis de Usuário**: Cadastro individual para salvar estatísticas e conquistas personalizadas.
 - [ ] **Internacionalização**: Sistema de tradução para suporte a Inglês, Português e Espanhol.
 - [ ] **Interface Gráfica (GUI)**: Futura versão em janela utilizando bibliotecas como Raylib ou SDL para maior imersão.
 
<br>

 ## Contribuição

Contribuições são o que tornam a comunidade de código aberto um lugar incrível para aprender, inspirar e criar. Qualquer contribuição que você fizer será **muito apreciada**.

Para saber como colaborar, por favor leia o nosso [Guia de Contribuição](CONTRIBUTING.md).

### Resumo do Processo:
1. Faça um Fork do projeto
2. Crie sua Branch de Funcionalidade (`git checkout -b feature/NovaFuncionalidade`)
3. Faça o Commit de suas alterações (`git commit -m 'Adiciona uma Nova Funcionalidade'`)
4. Faça o Push para a Branch (`git push origin feature/NovaFuncionalidade`)
5. Abra um Pull Request


<br>

###  Diretrizes

- Código limpo e bem comentado
- Mensagens de commit claras e objetivas
- Teste todas as funcionalidades
- Mantenha a documentação atualizada
- Siga os padrões de código existentes

<br>

##  Licença

Este projeto está licenciado sob a [Licença MIT](LICENSE).

``` bash
MIT License - você pode usar, modificar e distribuir livremente,
mantendo a referência ao repositório original.
```

 <br>

## Créditos

O **Jogo da Veia** é construído com o apoio de tecnologias e comunidades incríveis:

- **Linguagem:** [C (Padrão ISO C11)](https://en.cppreference.com/w/c/11)
- **Compilador:** [GCC](https://gcc.gnu.org/)
- **Interface:** [ANSI Escape Codes](https://en.wikipedia.org/wiki/ANSI_escape_code) (Cores e Formatação)
- **ASCII Art:** [FIGlet / TAAG](https://patorjk.com/software/taag/)
- **Documentação:** [Doxygen](https://www.doxygen.nl/)
- **Professor Orientador:** [Douglas Bechara Santos](https://github.com/douglasbechara)
- **Instituição:** [IFPA CAMPUS - TUCURUÍ] - Curso de Ciência da Computação

 <br>

 
### Desenvolvimento Principal

<table>
  <tr>
    <td align="center">
      <a href="https://github.com/StellaKarolinaNunes">
        <img src="https://github.com/StellaKarolinaNunes.png" width="100px" alt="Stella Karolina"/>
        <br />
        <sub><b>Stella Karolina (Desenvolvedora)</b></sub>
        <br />
      </a>
    </td>
  </tr>
</table>