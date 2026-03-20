# Relatório Técnico - jogo da veia Automático

**Versão:** 3.0  
**Data:** 20 de Março de 2026  
**Hora:** 10:00  

## 1. Análise de Falhas (Post-Mortem)

### 1.1 Portabilidade e Compilação
*   **Problema:** Incompatibilidade de nomes de arquivos entre Windows e Linux (Case Sensitivity).
*   **Causa:** O desenvolvedor original utilizou CamelCase em alguns locais e lower_case em outros.
*   **Solução:** Padronização rigorosa para lower_case nos arquivos fonte e manutenção de um script de compilação automatizado.

### 1.2 Layout da Interface
*   **Problema:** Tabuleiro desalinhado após a aplicação de temas coloridos.
*   **Causa:** Os códigos de escape ANSI possuem largura zero no terminal, mas ocupam espaço na contagem de strings do C++.
*   **Solução:** Implementação de uma largura fixa para cada célula do tabuleiro, independente da presença de cores, garantindo que as bordas `║` e `═` se alinhem corretamente.

### 1.3 Lógica de IA Inicial
*   **Problema:** A IA era previsível e permitia vitórias fáceis.
*   **Causa:** Algoritmo baseado apenas em condições `if/else` superficiais.
*   **Solução:** Introdução do algoritmo **Minimax** para a dificuldade "Difícil", tornando-a imbatível matematicamente.

---

## 2. Roadmap de Melhorias

### 2.1 Fase 1: Estabilidade e Experiência do Usuário
*   **Refatoração de Inputs:** Adição de proteção contra caracteres inválidos em campos numéricos.
*   **Níveis de Dificuldade:** Implementação de modos Fácil (aleatório), Médio (estratégico básico) e Difícil (Minimax).

### 2.2 Fase 2: Expansão de Recursos
*   **Temas Externos:** Migrar as definições de cores para um arquivo `.cfg` externo.
*   **Notificações Sonoras:** Implementar alertas via `\a` (bell) para eventos importantes.

### 2.3 Fase 3: Organização de Qualidade
*   **Suíte de Testes Modulares:** Criação de arquivos individuais para cada unidade de teste dentro da pasta `teste/`.
*   **Relatórios Automatizados:** Sistema de geração de logs de versão e status do projeto.

---

## 3. Conclusão
O projeto atingiu um nível de maturidade elevado com a implementação do Modo Infinito e da IA imbatível. A estrutura modular agora permite a expansão para interfaces gráficas (GUI) e rede (Socket) com mínimo esforço de refatoração.
