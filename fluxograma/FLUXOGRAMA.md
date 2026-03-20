flowchart TD
    Start([Início do App]) --> Menu[Menu Principal]
    
    Menu -->|Opção 1| Play[Modo de Jogo]
    Menu -->|Opção 2| Instr[Instruções]
    Menu -->|Opção 3| Cred[Créditos]
    Menu -->|Opção 4| Ref[Referências]
    Menu -->|Opção 5| Themes[Configurações de Tema]
    Menu -->|Opção 6| SaveLoad[Salvar/Carregar]
    Menu -->|Opção 7| Rank[Ranking]
    Menu -->|Opção 8| Exit([Sair])

    %% Sub-seção Play
    Play --> Mode{Escolher Tipo}
    Mode -->|PVP| NameInput[Nomes dos Jogadores]
    Mode -->|IA| AIDiff{Dificuldade}
    Mode -->|Infinito| NameInput
    
    AIDiff --> Easy[Fácil]
    AIDiff --> Med[Médio]
    AIDiff --> Hard[Difícil]
    
    NameInput --> Sorteio[Sorteio do Primeiro Jogador]
    Sorteio --> GameLoop[Loop da Partida]
    
    GameLoop --> Input[Entrada de Jogada]
    Input --> Valid{Válida?}
    Valid -->|Não| ErrorMsg[Exibir Erro e Redesenhar]
    Valid -->|Sim| UpdateBoard[Atualizar Tabuleiro]
    
    UpdateBoard --> WinCheck{Vitória/Empate?}
    WinCheck -->|Não| Switch[Trocar Jogador]
    Switch --> GameLoop
    
    WinCheck -->|Sim| PostGame[Pós-Partida]
    PostGame --> Replay{Ver Replay?}
    Replay -->|Sim| ExecReplay[Reproduzir Histórico]
    PostGame --> MedalCheck[Verificar Medalhas]
    MedalCheck --> UpdateRank[Atualizar Ranking Global]
    UpdateRank --> Menu

    %% Sub-seção Themes
    Themes --> ThemeGrid[Grade de 50 Temas]
    ThemeGrid --> ThemePreview[Visualizar Prévia]
    ThemePreview --> Apply[Aplicar Novo Tema]
    Apply --> Menu

    %% Sub-seção SaveLoad
    SaveLoad --> ListSaves[Listar Saves Disponíveis]
    ListSaves --> Load{Carregar Partida?}
    Load -->|Sim| ResumeGame[Retomar do Tabuleiro Salvo]
    ResumeGame --> GameLoop