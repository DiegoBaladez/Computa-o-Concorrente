import java.util.Scanner;
import java.lang.Math;

class SumPiMembers extends Thread {
    private double partialSum;
    private int n; //numero casas decimais do pi para sererem somadas
    private final int threadId;
    private final int nThreads;

    private SumOfAllNumbers sumOfAllNumbers;


    public SumPiMembers(int n, int threadId, int nThreads, SumOfAllNumbers sumOfAllNumbers){
        this.n = n; //quantidade de casas decimais do pi que quero contabilizar
        this.threadId = threadId;
        this.nThreads = nThreads;
        this.sumOfAllNumbers = sumOfAllNumbers;
        this.partialSum = 0;
    }

    public void run(){
        for(int i = this.threadId; i < this.n; i += nThreads){
            this.partialSum = ( Math.pow(-1.0 ,i) ) * (1.0) / ((2.0 * i) + 1.0);
            //System.out.printf("sou a thread %d, e calculei o valor %f \n", this.threadId,this.partialSum);
            sumOfAllNumbers.addTotalSum(partialSum);
        }
    }
}

class SumOfAllNumbers{

    private double totalSum;

    public void addTotalSum(double num){
        this.totalSum += num;
    }

    public double getResult(){
        return this.totalSum;
    }
    public double testaFuncao(double calculatedPi){
        double pi_1000000000_1thread = 3.141592652588050400000000000000;
        double relativeError;

        relativeError = (Math.abs( (pi_1000000000_1thread) - (calculatedPi)) ) / pi_1000000000_1thread;

        return relativeError;
    }
}

public  class SumAllMembersOfPi {

    public static void  main(String[] arg){
        Scanner input = new Scanner(System.in);
        int pimMembers;
        final int threadsNumber;

//        System.out.println("Type the number of pi members");
//        pimMembers = input.nextInt();

        pimMembers = 1000000000;

        System.out.println("Type the number of threads");
        threadsNumber = input.nextInt();

        //--reserva espaço para um vetor de threads
        Thread[] thread = new Thread[threadsNumber];
        SumOfAllNumbers[] objetos = new SumOfAllNumbers[threadsNumber];

        for(int i = 0; i < threadsNumber; i++){
            objetos[i] = new SumOfAllNumbers();
        }


        //--PASSO 2: cria threads da classe que estende Thread
        for (int i = 0; i < thread.length; i++){
            thread[i] = new SumPiMembers(pimMembers, i, thread.length, objetos[i]);
        }

        //--PASSO 3: iniciar as threads
        for (int i=0; i < thread.length; i++) {
            thread[i].start();
        }

        //--PASSO 4: esperar pelo termino de todas as threads
        for (int i=0; i<thread.length; i++) {
            try { thread[i].join(); }
            catch (InterruptedException e) { return; }
        }

        double totalDaSomaDasThreads = 0;
        for(int i =0; i < objetos.length; i++){
            totalDaSomaDasThreads += objetos[i].getResult();
        }

       System.out.printf("A aproximacao do PI foi  %.30f\n", totalDaSomaDasThreads * 4);

       double errorResult =objetos[0]
                .testaFuncao(totalDaSomaDasThreads * 4);

       System.out.printf("Relative error equals to: %.30f\n", errorResult);

       if(errorResult <= Math.pow(10,-10)){
           System.out.println("Erro relativo abaixo de 10^-10");
       }
    }
}

/**
 * Resultados obtidos
 *
 * A base que usei para calcular o pi foi n = 1000000000 com 1 thread. Logo, o erro relativo leva em considercao o valor
 * de PI = 3,141592652588050400000000000000.
 *
 *
 * 2 threads
 * Valor Encontrado = 3,141592652585554600000000000000
 * Erro = 0,000000000000794431880689981300
 *
 *
 * 2 threads
 * valor encontrado = 3,14149265359004900000
 * Erro = 0,00000000000000466496
 *
 *
 * 4 threads
 * valor encontrado = 3,141592652591443300000000000000
 * erro relativo = 0,000000000001079975012183533300
 *
 *
 * 6 threads
 * valor encontrado =  3,141592652597565500000000000000
 * erro relativo = 0,000000000003028736205634081500
 *
 *
 * 8 threads
 * valor encontrado = 3,141592652593080000000000000000
 * erro relativo = 0,000000000001601020548166321600
 *
 *
 *
 *
 *
 *
 * 16 threads
 * valor encontrado =  3,141592652586497400000000000000
 * erro relativo = 0,000000000000494328876649975900
 *
 * 24 threads (todas as threads do pc)
 * valor encontrado = 3,141592652588465000000000000000
 * erro relativo = 0,000000000000132028358819295810
 *
 *
 */