# Guia de Contribuição

Obrigado por considerar contribuir para o Jogo da Velha em C. Este documento fornece diretrizes para garantir que o processo de contribuição seja produtivo e eficiente para todos os envolvidos.

## Código de Conduta

Ao participar deste projeto, você concorda em manter um ambiente respeitoso, profissional e colaborativo. Assédio, linguagem ofensiva ou comportamento inadequado não serão tolerados.

## Como Reportar Bugs

Se você encontrar um erro no projeto, por favor siga estes passos:

1. Verifique se o erro já foi reportado nas 'Issues' do repositório.
2. Caso não exista, abra uma nova 'Issue' descrevendo:
   - O comportamento esperado.
   - O comportamento observado.
   - Passos detalhados para reproduzir o problema.
   - Informações sobre o seu ambiente (sistema operacional, versão do compilador GCC, etc.).

## Sugestões de Melhorias

Sugestões para novas funcionalidades ou melhorias no código são bem-vindas. Para sugerir algo:

1. Abra uma 'Issue' para discutir a mudança proposta antes de iniciar o desenvolvimento.
2. Descreva claramente o objetivo da melhoria e como ela beneficia o projeto.

## Processo de Pull Request

Para enviar suas alterações, siga o fluxo de trabalho abaixo:

1. Realize um 'Fork' do repositório.
2. Crie uma nova 'branch' para sua funcionalidade ou correção:
   `git checkout -b feature/nome-da-mudanca` ou `git checkout -b fix/nome-da-correcao`.
3. Certifique-se de que seu código segue os padrões do projeto e está devidamente comentado.
4. Execute todos os testes e verifique se o projeto compila sem alertas (warnings) extras.
5. Realize o 'commit' de suas alterações com mensagens claras e objetivas.
6. Envie as alterações para o seu 'Fork':
   `git push origin sua-branch`.
7. Abra um 'Pull Request' (PR) detalhando o que foi alterado e por quê.

## Padrões de Código

Para manter a consistência do projeto, solicitamos que:

1. Utilize indentação consistente (espaços ou tabs conforme o padrão do arquivo).
2. Dê nomes descritivos a variáveis e funções (em português ou inglês, seguindo o padrão já existente no arquivo).
3. modularize o código sempre que possível, utilizando os arquivos .h e .c de forma apropriada.
4. Documente funções complexas com comentários explicativos sobre parâmetros e retorno.

## Licença

Ao contribuir para este repositório, você concorda que suas contribuições serão licenciadas sob a Licença MIT contida no arquivo LICENSE deste projeto.
