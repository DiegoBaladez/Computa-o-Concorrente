import java.util.ArrayList;
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
            System.out.printf("sou a thread %d, e calculei o valor %f \n", this.threadId,this.partialSum);
            sumOfAllNumbers.addarray(partialSum);
        }
    }
}

class SumOfAllNumbers{
    private int sum;
    private ArrayList <Double> meuArrrey = new  ArrayList();
    public SumOfAllNumbers(){
        this.sum = 0;
    }

    public double getSum(){
        return sum;
    }

    public void addarray(double num){
        meuArrrey.add(num);
    }
    public double totalSum(){
        double soma = 0;
        for (int i = 0; i < meuArrrey.size(); i++){
            soma += meuArrrey.get(i);
        }
        return soma;
    }
}

public  class SumAllMembersOfPi {

    public static void  main(String[] arg){
        Scanner input = new Scanner(System.in);
        int pimMembers;
        final int threadsNumber;

        SumOfAllNumbers abc = new SumOfAllNumbers();

        System.out.println("Type the number of pi members");
        pimMembers = input.nextInt();

        System.out.println("Type the number of threads");
        threadsNumber = input.nextInt();

        //--reserva espaço para um vetor de threads
        Thread[] thread = new Thread[threadsNumber];

        //--PASSO 2: cria threads da classe que estende Thread
        for (int i = 0; i < thread.length; i++){
            thread[i] = new SumPiMembers(pimMembers, i, thread.length, abc);
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

       System.out.printf("A soma total das casas decimais foi  %f", abc.totalSum());
    }
}