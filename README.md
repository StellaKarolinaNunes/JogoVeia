<div align="center">

# Jogo da Veia em C

### Jogo de terminal desenvolvido em C com modos, ranking, temas e personalização

<a href="https://github.com/StellaKarolinaNunes/jogo-da-veia">
  <img src="./assets/menu_principal.png" alt="Banner do projeto Jogo da Veia em C" width="100%">
</a>

<br>

<img src="https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white" alt="C">

<img src="https://img.shields.io/badge/GCC-4B8BBE?style=for-the-badge&logo=gnu&logoColor=white" alt="GCC">

<img src="https://img.shields.io/badge/Terminal-111111?style=for-the-badge&logo=gnubash&logoColor=white" alt="Terminal">

<img src="https://img.shields.io/badge/Status-Em%20desenvolvimento-F59E0B?style=for-the-badge" alt="Status do projeto">

<br><br>

<p align="center">
  <a href="https://github.com/StellaKarolinaNunes/jogo-da-veia">
    <img src="https://img.shields.io/badge/⌘%20Explorar%20Código--Fonte-181717?style=for-the-badge&logo=github&logoColor=white" alt="Explorar Código-Fonte">
  </a>
  <a href="https://github.com/StellaKarolinaNunes/jogo-da-veia/blob/main/fluxograma/FLUXOGRAMA.md">
    <img src="https://img.shields.io/badge/◈%20Ver%20Fluxograma%20do%20Projeto-00599C?style=for-the-badge&logo=diagram&logoColor=white" alt="Ver Fluxograma do Projeto">
  </a>
</p>

</div>

---

## Sobre o projeto

O **Jogo da Veia em C** é um jogo de terminal inspirado no clássico Jogo da Velha, desenvolvido em linguagem C durante a disciplina de **Programação I**.

O projeto foi criado com o objetivo de aplicar, consolidar e ampliar conceitos fundamentais de programação, como estruturas condicionais, laços de repetição, funções, matrizes, manipulação de arquivos e organização modular de código.

Além do modo clássico, o jogo evoluiu para uma experiência mais completa, com modos de jogo, temas visuais, ranking, sistema de salvamento e personalização da interface no terminal.

> Este projeto foi desenvolvido para fins educacionais e de portfólio, com foco na prática de programação estruturada, modularização e experiência de usuário em terminal.

---

## Objetivo

O projeto busca transformar um exercício tradicional de programação em uma aplicação interativa e organizada, permitindo que jogadores possam disputar partidas locais, enfrentar a inteligência artificial, acompanhar estatísticas e personalizar a aparência do jogo.

A proposta também demonstra que aplicações executadas em terminal podem possuir boa experiência visual, navegação intuitiva e recursos avançados, mesmo utilizando apenas linguagem C e códigos ANSI.

---

## Funcionalidades

* **Player vs Player:** partidas locais entre dois jogadores.
* **Player vs IA:** modo para enfrentar a inteligência artificial.
* **Níveis de Dificuldade:** opções Fácil, Médio e Difícil.
* **Modo Infinito:** peças mais antigas desaparecem após determinado número de jogadas, criando novas possibilidades estratégicas.
* **Ranking Local:** acompanhamento de vitórias, derrotas, empates e pontuação dos jogadores.
* **Sistema de Medalhas:** conquistas desbloqueadas por desempenhos específicos durante as partidas.
* **Save e Load:** possibilidade de salvar e continuar partidas posteriormente.
* **Replay de Partidas:** reprodução automática da última partida jogada.
* **Modo Torneio:** partidas configuráveis em formatos Melhor de 3 ou Melhor de 5.
* **Temas Visuais:** mais de 50 opções de temas aplicáveis à interface.
* **ASCII Art Dinâmica:** cabeçalhos e elementos visuais criados para melhorar a identidade do terminal.
* **Interface Centralizada:** layout estruturado para melhor leitura, navegação e feedback ao jogador.
* **Internacionalização:** estrutura preparada para suporte a diferentes idiomas.
* **Configurações Persistentes:** preferências do jogador armazenadas em arquivos de configuração.

---

## Tecnologias utilizadas

| Tecnologia        | Aplicação no projeto                           |
| ----------------- | ---------------------------------------------- |
| C                 | Linguagem principal do jogo                    |
| GCC               | Compilação do código-fonte                     |
| Bash              | Automação da compilação e execução             |
| ANSI Escape Codes | Cores, posicionamento e formatação no terminal |
| Git               | Controle de versão                             |
| Doxygen           | Estrutura de documentação técnica              |
| ASCII Art         | Elementos visuais e identidade do jogo         |

---

## Destaques técnicos

* Arquitetura modular dividida em arquivos `.c` e `.h`;
* Separação entre lógica do jogo, interface, menus, temas e utilitários;
* Manipulação de matrizes para construção do tabuleiro;
* Validação de jogadas e controle de turnos;
* Leitura e escrita de arquivos para ranking, saves e configurações;
* Estrutura de internacionalização para expansão futura;
* Sistema visual baseado em códigos ANSI;
* Organização preparada para novos modos de jogo e recursos de rede;
* Script de compilação para agilizar a execução do projeto.

---

## Preview

<div align="center">

<img width="48%" src="./assets/menu_principal.png" alt="Menu principal do Jogo da Veia">

<img width="48%" src="./assets/ranking.png" alt="Tela de ranking do Jogo da Veia">

<img width="48%" src="./assets/tema.png" alt="Tela de temas do Jogo da Veia">

<img width="48%" src="./assets/gameplay.png" alt="Gameplay do Jogo da Veia">

</div>

---

## Estrutura do projeto

```bash
jogo-da-veia/
├── assets/
│   ├── menu_principal.png
│   ├── ranking.png
│   ├── tema.png
│   └── gameplay.png
│
├── fluxograma/
│   └── FLUXOGRAMA.md
│
├── saves/
│   └── arquivos-de-partidas-salvas/
│
├── compile.sh
├── config.h
├── main.c
│
├── game.c
├── game.h
│
├── menu.c
├── menu.h
│
├── ui.c
├── ui.h
│
├── theme.c
├── theme.h
│
├── utils.c
├── utils.h
│
├── file_manager.c
├── file_manager.h
│
├── i18n.c
├── i18n.h
│
├── globals.c
├── settings.cfg
├── themes.cfg
├── ranking.dat
├── Doxyfile
├── ROADMAP.md
├── CONTRIBUTING.md
├── LICENSE
└── README.md
```

> Arquivos gerados durante a compilação, como executáveis e pastas de build, não aparecem na estrutura principal porque não devem ser versionados no Git.

---

## Como executar o projeto

### Pré-requisitos

Antes de iniciar, é necessário ter instalado:

* **GCC:** compilador C recomendado para compilar o projeto;
* **Git:** necessário para clonar o repositório;
* **Bash:** utilizado pelo script de compilação;
* **Terminal com suporte ANSI:** necessário para visualizar corretamente cores, efeitos e formatações;
* **Linux, macOS ou Git Bash no Windows:** recomendado para executar os comandos do projeto.

### 1. Clone o repositório

```bash
git clone https://github.com/StellaKarolinaNunes/jogo-da-veia.git
```

### 2. Acesse a pasta do projeto

```bash
cd jogo-da-veia
```

### 3. Dê permissão ao script de compilação

```bash
chmod +x compile.sh
```

### 4. Compile e execute o jogo

```bash
./compile.sh
```

### Compilação manual

Caso queira compilar diretamente pelo terminal:

```bash
gcc *.c -o jogo-da-veia
```

Em sistemas Linux ou macOS:

```bash
./jogo-da-veia
```

No Windows:

```bash
jogo-da-veia.exe
```

---

## Roadmap

### Inteligência Artificial

* [ ] Implementar IA Mestre utilizando Minimax com poda Alfa-Beta;
* [ ] Criar dificuldade adaptável conforme o desempenho do jogador;
* [ ] Desenvolver modo Impossível com estratégia ótima para o tabuleiro clássico;
* [ ] Melhorar a tomada de decisão da IA em modos alternativos.

### Multiplayer e Rede

* [ ] Adicionar multiplayer via rede local utilizando sockets TCP/IP;
* [ ] Criar modo espectador para acompanhar partidas em andamento;
* [ ] Integrar leaderboard global utilizando API externa;
* [ ] Permitir sincronização de estatísticas entre jogadores.

### Novos modos de jogo

* [ ] Adicionar tabuleiros dinâmicos como 4x4, 5x5 e 10x10;
* [ ] Implementar modo Gomoku, com vitória ao alinhar cinco peças;
* [ ] Criar modo Misère, em que alinhar três peças resulta em derrota;
* [ ] Desenvolver modo Quântico inspirado em Quantum Tic-Tac-Toe;
* [ ] Adicionar modo Nevoeiro, ocultando partes do tabuleiro durante a partida.

### Perfis e progressão

* [ ] Criar perfis locais de jogadores;
* [ ] Salvar histórico de partidas, tempo de jogo e desempenho;
* [ ] Expandir sistema de medalhas e conquistas;
* [ ] Liberar temas e símbolos personalizados por objetivos concluídos;
* [ ] Implementar estatísticas detalhadas por modo de jogo.

### Experiência visual e áudio

* [ ] Adicionar animações de entrada e transições no terminal;
* [ ] Criar efeitos visuais para jogadas, vitórias e derrotas;
* [ ] Implementar feedback sonoro durante navegação e partidas;
* [ ] Adicionar suporte a mouse com `ncurses` ou recursos compatíveis;
* [ ] Melhorar a adaptação do layout para diferentes tamanhos de terminal.

### Melhorias técnicas

* [ ] Criar sistema ampliado de configurações;
* [ ] Permitir exportação de ranking e estatísticas em `.txt`, `.csv` e `.json`;
* [ ] Adicionar backups automáticos de saves;
* [ ] Melhorar compatibilidade entre Linux, Windows e macOS;
* [ ] Ampliar a documentação automática com Doxygen;
* [ ] Criar testes para as principais regras do jogo.

---

## Contribuição

Contribuições são bem-vindas.

```bash
# Faça um fork do projeto

# Crie uma branch para sua funcionalidade
git checkout -b feature/nova-funcionalidade

# Faça suas alterações
git add .

# Crie um commit descritivo
git commit -m "feat: adiciona nova funcionalidade"

# Envie sua branch
git push origin feature/nova-funcionalidade
```

Depois, abra um Pull Request explicando as alterações realizadas.

### Diretrizes

* Mantenha o código organizado e bem comentado;
* Utilize nomes claros para variáveis, funções e estruturas;
* Preserve a separação entre arquivos de interface, lógica e utilitários;
* Teste as funcionalidades antes de enviar alterações;
* Atualize a documentação quando necessário;
* Evite adicionar executáveis, arquivos temporários ou builds ao repositório.

---

## Licença

Este projeto está licenciado sob a [Licença MIT](LICENSE).

```text
MIT License

Você pode usar, modificar e distribuir este projeto,
desde que mantenha os créditos e a referência ao repositório original.
```

---

## Créditos

* **Desenvolvimento:** [Stella Karolina Nunes](https://github.com/StellaKarolinaNunes)
* **Linguagem:** [C — ISO C11](https://en.cppreference.com/w/c/11)
* **Compilador:** [GCC](https://gcc.gnu.org/)
* **Interface de Terminal:** ANSI Escape Codes
* **ASCII Art:** [FIGlet / TAAG](https://patorjk.com/software/taag/)
* **Documentação Técnica:** [Doxygen](https://www.doxygen.nl/)
* **Professor Orientador:** Douglas Bechara Santos
* **Instituição:** IFPA Campus Tucuruí
* **Curso:** Bacharelado em Ciência da Computação
