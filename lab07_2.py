#calcula o valor aproximado de PI utilizando threads com python

from threading import Thread
import math
import time

#global - numero para aproximação das threads
N = 10000000

#classe da thread
class CalculaPI(Thread): #cria o objeto compartilhado entre as threads. que nem no java
    def __init__(self, tid):
        super().__init__()
        self.tid = tid
        self.val = 0

    def run(self):
        for i in range(self.tid,N,THREADS):
            self.val += (-1)**i/(2*i + 1)

def calculaSeEstaCerto(pi_est):
    diferenca = abs(math.pi - 4 * pi_est)
    prox = 4 * ((-1) ** N / (2 * N + 1))

    if (diferenca <= prox):
       return print("\nA estimativa está correta")

#fluxo principal
if __name__ == '__main__':
    THREADS = 4
    pi_est = 0

    threads = [CalculaPI(tid) for tid in range(THREADS)]

    start = time.time()

    for thread in threads:
        thread.start()

    for thread in threads:
        thread.join()

    for thread in threads:
        pi_est += thread.val

    print(f"Valor encontrado: {4 * pi_est:.8f}")
    print(f"Referencia para o PI: {math.pi:.8f}")
    print(f"Tempo: {time.time() - start}")

    calculaSeEstaCerto(pi_est)
