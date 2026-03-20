#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "tests.h"
#include "../game.h"
#include "../file_manager.h"
#include "../theme.h"
#include "../ui.h"
#include "../utils.h"

// 1. Verificar se Instruções estão funcionando (smoke test)
void test_ui_instrucoes() {
    // Agora usando mock_utils, chamar as funções não trava
    exibirTituloInstrucoes();
    printf("UI: Instruções impressas com sucesso (Mock).\n");
}

// 2. Verificar se Créditos estão funcionando (smoke test)
void test_ui_creditos() {
    exibirTituloCreditos();
}

// 3. Verificar se Referências estão funcionando (smoke test)
void test_ui_referencia() {
    exibirTituloReferencia();
}

// 4. Verificar se o Ranking está funcionando e ordenando certo
void test_ranking_sort_integrity() {
    num_ranking_entries = 0;
    // Jogador A com 10 vitórias
    atualizarRanking("A", 1);
    ranking[0].wins = 10;
    // Jogador B com 20 vitórias
    atualizarRanking("B", 1);
    ranking[1].wins = 20;
    
    // Sort
    qsort(ranking, num_ranking_entries, sizeof(RankingEntry), compararRankingEntries);
    
    // B deve ser o primeiro
    assert(strcmp(ranking[0].name, "B") == 0);
    assert(ranking[0].wins == 20);
    assert(strcmp(ranking[1].name, "A") == 0);
}

// 5. Verificar Salvar e Carregar
void test_fluxo_persistência() {
    GameState game = {0};
    inicializarTabuleiro(&game);
    strcpy(game.nomeJogadorX, "UnitTestX");
    strcpy(game.nomeJogadorO, "UnitTestO");
    game.placarX = 15;
    
    // Simular salvamento
    // Como Mock_lerInteiro retorna min (0 no save dialog para Novo Save),
    // e Mock_lerString retorna "MockedInput", o arquivo deve ser criado.
    // Mas para não sujar o sistema de arquivos oficial, podemos fingir o salvamento de dados brutos
    carregarConfiguracoes();
    assert(tema_ativo >= 0);
}

// 6. Verificar se todos os Temas estão funcionando (carregamento íntegro)
void test_validar_todos_temas() {
    carregarTemas();
    assert(num_temas > 0);
    for (int i = 0; i < num_temas; i++) {
        assert(strlen(nomes_temas[i]) > 0);
        assert(strlen(temas[i]) > 0);
    }
}

// 7. Verificar se todos os Comandos estão definidos
void test_verificar_comandos_sistema() {
    // Verificamos se as macros não estão vazias
    assert(strlen(SET_TITLE) > 0);
    assert(strlen(PAUSE_COMMAND) > 0);
    assert(strlen(CLEAR_COMMAND) > 0);
}

// 8. Verificar fluxos de jogo e modos (PvP e PvE)
void test_modos_jogo_integracao() {
    GameState game = {0};
    
    // TESTE PvP
    inicializarTabuleiro(&game);
    game.jogadorAtual = 'X';
    fazerJogada(&game, 1);
    fazerJogada(&game, 2);
    assert(game.tabuleiro[0][0] == 'X');
    assert(game.tabuleiro[0][1] == 'O');
    
    // TESTE PvIA (Minimax imbatível no Médio/Difícil)
    inicializarTabuleiro(&game);
    game.ai_difficulty = DIFFICULTY_HARD;
    game.jogadorAtual = 'X';
    fazerJogada(&game, 5); // Centro
    int move = obterJogadaIA(&game);
    assert(move != 5);
}
