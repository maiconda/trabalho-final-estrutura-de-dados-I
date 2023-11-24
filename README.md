# trabalho-final-estrutura-de-dados-I

o projeto se trada de uma implementação de uma tabela hash em C, utilizando lista encadeada e QuickSort, constitui um exemplo robusto de estrutura de dados eficiente. Composta por uma gama de funcionalidades, desde a inserção inicial até operações avançadas como exclusão, busca, ordenação e análise estatística, o código demonstra versatilidade e utilidade no gerenciamento de grandes conjuntos de dados.

O código inicia com a inicialização da tabela hash e a inserção inicial de palavras provenientes de um arquivo externo, nomeado nomes.txt. Esse método prático permite a manipulação de dados preexistentes, ilustrando a adaptabilidade do código a diferentes fontes de informação. A função de hash, baseada no resto da divisão pelo número de slots da tabela a partir da soma dos valores ASCII dos caracteres da palavra, propicia uma distribuição aparentemente uniforme dos dados pelos slots da tabela.

A funcionalidade de inserção de palavras, apresentada pela função insercaoPalavras, facilita a adição manual de um número predefinido de termos. Uma característica notável é a conversão dessas palavras para maiúsculas, promovendo consistência e simplificando comparações. Após a inserção, a tabela é ordenada por meio do algoritmo QuickSort, promovendo eficiência em operações que exigem uma ordem específica.

A função de exclusão, excluirDaTabela, opera de maneira eficiente, localizando a palavra desejada e removendo-a da lista encadeada correspondente ao slot. A busca na tabela, realizada por meio da função buscarNaTabela, oferece informações sobre a presença e a posição de uma palavra específica. Essa funcionalidade é crucial para aplicações que requerem recuperação rápida e eficiente de dados.

A função imprimirTabelaHash proporciona uma visão geral do número de palavras em cada slot, oferecendo insights sobre a distribuição dos dados na tabela. Por outro lado, a função imprimirSlot permite uma análise mais detalhada, exibindo as palavras em um slot específico. Essas funcionalidades contribuem para a transparência e compreensão do conteúdo armazenado na tabela.

Um importante recurso adicional ao projeto é a função mediaDesvioPadrao, que calcula a média e o desvio padrão do número de palavras em cada slot da tabela. Esse recurso proporciona informações estatísticas valiosas sobre a distribuição dos dados, permitindo uma avaliação mais aprofundada do comportamento da tabela. A inclusão de funcionalidades estatísticas amplia a utilidade do código para cenários onde a análise quantitativa é crucial.

Em resumo, a implementação da tabela hash em C apresenta uma solução robusta e completa para o gerenciamento eficiente de dados. Suas funcionalidades abrangentes tornam o código uma ferramenta versátil para diversos propósitos, desde armazenamento de dados até análises mais avançadas. O código é uma base sólida para construção e expansão, proporcionando uma estrutura confiável para aplicações que demandam organização e manipulação eficazes de conjuntos de dados extensos.
