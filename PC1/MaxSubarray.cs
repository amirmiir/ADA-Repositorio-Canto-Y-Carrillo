using System;
using System.Diagnostics;

public class MaxSubarray
{
    static void Main(string[] args)
    {
        ExecuteProcedure(10);
        ExecuteProcedure(100);
        ExecuteProcedure(1000);
        ExecuteProcedure(10000);
        ExecuteProcedure(100000);
    }

    private static void ExecuteProcedure(int size)
    {
        int left = 0, right = 0;
        int maxSum = 0, maxSumDNC = 0;
        int[] array = GenerateRandomArray(size);
        Stopwatch stopwatch = new Stopwatch();
        stopwatch.Start();
        
        maxSum = BruteForce(array, ref left, ref right);

        stopwatch.Stop();
        TimeSpan ts = stopwatch.Elapsed;
        if(size < 100) PrintArray(array);
        Console.WriteLine("Brute Force: ");
        Console.WriteLine("Suma máxima: " + maxSum + "\nLeft: " + left + "\nRight: " + right);
        Console.WriteLine("Tiempo de ejecución: " + ts.TotalMilliseconds + "ms");

        stopwatch.Reset();
        stopwatch.Start();

        maxSumDNC = DivideNConquer(array, 0, array.Length - 1, ref left, ref right);

        stopwatch.Stop();
        ts = stopwatch.Elapsed;
        Console.WriteLine("Divide and Conquer: ");
        Console.WriteLine("Suma máxima: " + maxSumDNC + "\nLeft: " + left + "\nRight: " + right);
        Console.WriteLine("Tiempo de ejecución: " + ts.TotalMilliseconds + "ms\n\n");
    }

    private static int BruteForce(int[] array, ref int left, ref int right)
    {
        int n = array.Length;
        int maxSum = int.MinValue;

        for (int i = 0; i < n; i++)
        {
            int auxSum = 0;

            for (int j = i; j < n; j++)
            {
                auxSum += array[j];

                if (auxSum > maxSum)
                {
                    left = i;
                    right = j;
                    maxSum = auxSum;
                }
            }
        }
        return maxSum;
    }

    private static int DivideNConquer(int[] array, int low, int high, ref int left, ref int right)
    {
        int leftSum = 0, rightSum = 0, crossSum = 0;
        int leftLow = 0, leftHigh = 0;
        int rightLow = 0, rightHigh = 0;
        int crossLow = 0, crossHigh = 0;

        if(high == low)
        {
            left = low;
            right = high;
            return array[low];
        }
        else 
        {
            int mid =(int) Math.Floor(low + (high - low)/2.0);
            leftSum = DivideNConquer(array, low, mid, ref leftLow, ref leftHigh);
            rightSum = DivideNConquer(array, mid + 1, high, ref rightLow, ref rightHigh);
            crossSum = MaxCrossingSubArray(array, low, mid, high, ref crossLow, ref crossHigh);

            if(leftSum >= rightSum && leftSum >= crossSum)
            {
                left = leftLow;
                right = leftHigh;
                return leftSum;
            }
            else if(rightSum >= leftSum && rightSum >= crossSum)
            {
                left = rightLow;
                right = rightHigh;
                return rightSum;
            }
            else
            {
                left = crossLow;
                right = crossHigh;
                return crossSum;
            }
        }
    }

    private static int MaxCrossingSubArray(int[] array, int low, int mid, int high, ref int left, ref int right)
    {
        int leftSum = int.MinValue;
        int auxSum = 0;

        for(int i = mid; i >= low; i--)
        {
            auxSum += array[i];
            if(auxSum > leftSum)
            {
                leftSum = auxSum;
                left = i;
            }
        }

        int rightSum = int.MinValue;
        auxSum = 0;

        for(int i = mid + 1; i <= high; i++)
        {
            auxSum += array[i];
            if(auxSum > rightSum)
            {
                rightSum = auxSum;
                right = i;
            }
        }

        return leftSum + rightSum;
    }

    private static int[] GenerateRandomArray(int size)
    {
        Random rand = new Random();
        int[] array = new int[size];

        for(int i = 0; i < size; i++)
        {
            array[i] = rand.Next(-100, 101);
        }

        return array;
    }

    private static void PrintArray(int[] array)
    {
        Console.Write("Array = [");

        for(int i = 0; i < array.Length - 1; i++)
        {
            Console.Write(array[i] + ", ");
        }

        Console.WriteLine(array[array.Length - 1] + "]");
    }

}


