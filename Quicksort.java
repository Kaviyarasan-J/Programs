import java.util.Random;

public class Quicksort {
    public static void main(String[] args) {
        Random rand=new Random();
        int[] numbers=new int[1000000];
        for(int i=0;i<numbers.length;i++){
            numbers[i]=rand.nextInt(100);
        }
        System.out.println("Before Sorting :");
        printArray(numbers);

        quicksort(numbers);

        System.out.println("After Sorting :");
        printArray(numbers);

    }
    private static void printArray(int[] numbers){
        for(int i=0;i<numbers.length;i++){
            System.out.println(numbers[i]);
        }
    }

    private static void quicksort(int[] numbers){
        quicksort(numbers,0,numbers.length-1);
    }

    private static void quicksort(int[] numbers,int lowIndex,int highIndex) {
        if(lowIndex>highIndex){
            return;
        }
        int pivot = numbers[highIndex];

        int leftPointer = lowIndex;
        int rightPointer = highIndex;

        while (leftPointer < rightPointer) {

            while (numbers[leftPointer] <= pivot && leftPointer < rightPointer) {
                leftPointer++;
            }

            while (numbers[rightPointer] >= pivot && leftPointer < rightPointer) {
                rightPointer--;
            }

            swap(numbers, leftPointer, rightPointer);
        }
        swap(numbers,leftPointer,highIndex);

        quicksort(numbers,lowIndex,leftPointer-1);
        quicksort(numbers,leftPointer+1,highIndex);
    }
    private static void swap(int[] numbers,int leftIndex,int rightIndex){
        int temp=numbers[leftIndex];
        numbers[leftIndex]=numbers[rightIndex];
        numbers[rightIndex]=temp;
    }
}
