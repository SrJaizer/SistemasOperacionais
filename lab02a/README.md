Nome: Jair Gino Paca Huaman - 42081092
Nome: Eduardo Pollastrini Barbagallo - 32069928

1) Sim, as mensagens sempre estarão ordenadas pelo valor de i, mas
nem sempre seu repectivo PID em relação aos processos pais e filhos
estarão ordenados na ordem crescente.

2) Acontece a mesma coisa usando os dois tipos de saida, a cha
mada sys.stdout armazena a string em buffer enquanto em 
sys.stderr envia diretamente para a tela do terminal, ideal 
para saida de erros.
