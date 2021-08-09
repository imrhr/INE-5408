# INE-5408

- [ ] Criar arquivo de processamento XML;
- [ ] Classe da matriz para a Segunda questão;
- [ ] Criar arquivo main. 

Primeiro problema: validação de arquivo XML

Para esta parte, pede-se exclusivamente a verificação de aninhamento e fechamento das marcações (tags) no arquivo XML (qualquer outra fonte de erro pode ser ignorada). Um identificador (por exemplo: img) constitui uma marcação entre os caracteres < e >, podendo ser de abertura (por exemplo: <img>) ou de fechamento com uma / antes do identificador (por exemplo: </img>). Como apresentando em sala de aula, o algoritmo para resolver este problema é baseado em pilha (LIFO):

   - Ao encontrar uma marcação de abertura, empilha o identificador
   - Ao encontrar uma marcação de fechamento, verifica se o topo da pilha tem o mesmo identificador e desempilha. Aqui duas situações de erro podem ocorrer:
       - Ao consultar o topo, o identificador é diferente (ou seja, uma marcação aberta deveria ter sido fechada antes)
       - Ao consultar o topo, a pilha encontra-se vazia (ou seja, uma marcação é fechada sem que tenha sido aberta antes)
   - Ao finalizar a análise (parser) do arquivo, é necessário que a pilha esteja vazia. Caso não esteja, mais uma situação de erro ocorre, ou seja, há marcação sem fechamento




