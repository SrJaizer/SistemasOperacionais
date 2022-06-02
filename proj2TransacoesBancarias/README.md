## Compilar o programa:
```bash
gcc -pthread proj2.c -lpthread -o proj2
```
## Executar o programa:
```bash
./proj2
```
## Requisitos
1. A conta to pode receber mais de uma transferência simultânea;
2. A conta from pode enviar mais de uma transferência simultânea;
3. A conta from não pode enviar dinheiro se não tiver mais saldo;
4. A conta to pode trocar de ordem com a conta from, ou seja, a conta que enviava pode
receber e a conta que recebia pode enviar;
5. Poderão ser realizadas até 100 transações simultâneas de transferência.

## Resultados
Cada thread representa uma transação a ser feita,
a cada transação é atribuída um índice único mostrada
na mensagem de saída entre parênteses.

<div align="center">
  <img src="https://i.imgur.com/yM97EMs.png" alt="100 Threads In Race Condition00">
  <img src="https://i.imgur.com/fo6ppA2.png" alt="100 Threads In Race Condition01">
  <img src="https://i.imgur.com/axysF8Z.png" alt="100 Threads In Race Condition02">
  <img src="https://i.imgur.com/eWy77t9.png" alt="100 Threads In Race Condition03">
  <img src="https://i.imgur.com/qWK9x24.png" alt="100 Threads In Race Condition04">
</div>

No seguinte caso específico, após 10 transações da conta c1 para conta c2,
a conta c1 tenta realizar mais uma transação mas não pode
pois possuí saldo menor que o valor da transação, para realizar
a transação a thread terá que esperar que ocorra
alguma transação a favor de c1 e em seguida irá verifica se
o valor depositado é maior ou igual ao valor da transação.

<div align="center">
  <img src="https://i.imgur.com/mFVABHX.png" alt="12 Threads In Particular Case00">
  <img src="https://i.imgur.com/dLQJ6t3.png" alt="12 Threads In Particular Case01">
  <img src="https://i.imgur.com/UoTl1cA.png" alt="12 Threads In Particular Case02">
</div>
