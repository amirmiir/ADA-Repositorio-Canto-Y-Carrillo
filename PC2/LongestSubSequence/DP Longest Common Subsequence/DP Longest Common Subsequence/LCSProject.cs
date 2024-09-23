using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Serialization;
using System.Diagnostics;

namespace LongestCommonSubsequence
{
    public class LCSProject
    {
        
        public static void Main(string[] args)
        {
            int choice = 1;
            while (choice != 0)
            {
                LCSProject main = new LCSProject();

                Console.WriteLine("MENU\n" +
                                "1. Predeterminado\n" +
                                "2. Ingresar Cadenas\n" +
                                "0. Salir\n\n" +
                                "Ingrese la opcion:");

                choice = Convert.ToInt32(Console.ReadLine());

                switch (choice)
                {
                    case 0: break;
                    case 1:
                        main.Custom();
                        choice = 0;
                        break;
                    case 2:
                        main.InputStrings();
                        choice = 0;
                        break;
                    default:
                        Console.WriteLine("Opcion invalida.\n\n");
                        break;
                }
            }
        }

        public void Custom()
        {
            string str1 = "AGGTAB";
            string str2 = "GXTXAYB";

            int m = str1.Length;
            int n = str2.Length;

            Console.WriteLine("La subcadena de carácteres : ");
            LcsDP(str1, str2, m, n);
            Console.WriteLine("");

        }

        public void InputStrings()
        {
            string str1, str2;
            Console.WriteLine("Ingrese la primera cadena: ");
            str1=Console.ReadLine();
            Console.WriteLine("Ingrese la segunda cadena: ");
            str2=Console.ReadLine();

            int m = str1.Length;
            int n = str2.Length;

            Console.WriteLine("La subcadena de carácteres es: ");

            Stopwatch cronometro = new Stopwatch();
            cronometro.Start();
            if (m <= 35 && n <= 35)
            {
                cronometro.Reset();

                Console.WriteLine("Recursiva: ");
                cronometro.Start();
                LcsRecursive(str1, str2, m, n);
                cronometro.Stop();
                Console.WriteLine("El tiempo para Recursiva: {0} ms", Convert.ToDouble(cronometro.ElapsedTicks) / 10000);
            }
            cronometro.Reset();

            Console.WriteLine("Dynamic Programming: ");
            cronometro.Start();
            LcsDP(str1, str2, m, n);
            cronometro.Stop();
            Console.WriteLine("El tiempo para DP: {0} ms", Convert.ToDouble(cronometro.ElapsedTicks) / 10000);



        }


        /* Método estático que implementa el algoritmo para LCS con programación dinámica.
         * Este método implementa Bottom-Up de 2 Dimensiones DP
         */

        static void LcsDP(string str1, string str2, int m, int n)
        {
            int[,] L = new int[m + 1, n + 1];

            /* Siguiendo los pasos, construimos la matriz con (m+1)(n+1)
             * Observar que L[i][j] contiene la longitud LCS de str1[0..i-1]
             * y de str2[0..j-1]
             */
            for (int i = 0; i <= m; i++)
            {
                for (int j = 0; j <= n; j++)
                {
                    if (i == 0 || j == 0)
                        L[i, j] = 0;
                    else if (str1[i - 1] == str2[j - 1])
                        L[i, j] = L[i - 1, j - 1] + 1;
                    else
                        L[i, j] = Math.Max(L[i - 1, j],
                                        L[i, j - 1]);
                }
            }

            /*
             * ETAPA DE IMPRESIÓN
             * 
             */

            /* Para realizar la impresión, utilizamos el siguiente código:
             */
            int index = L[m, n];
            int temp = index;

            /* Creamos un array de carácteres para almacenar la string LCS
             */
            char[] lcs = new char[index + 1];

            lcs[index] = '\0';


            /* Empezamos desde la esquina inferior derecha y uno a uno
             * añadimos los caracteres a lcs[]
             */
            int k = m, l = n;
            while (k > 0 && l > 0)
            {
                /*Si el caracter en str1[] y str2[] son el mismo,
                 * entonces el caracter actual es parte de LCS
                 */
                if (str1[k - 1] == str2[l - 1])
                {
                    lcs[index - 1] = str1[k - 1];

                    k--;
                    l--;
                    index--;
                }

                /*De lo contrario, encontramos el mayor de los dos
                 * y nos vemos en dirección del mayor valor.
                 */
                else if (L[k - 1, l] > L[k, l - 1])
                    k--;
                else
                    l--;
            }

            /* 
             * Impresión
             */
            Console.Write("LCS: ");
            for (int q = 0; q <= temp; q++)
                Console.Write(lcs[q]);
        }




        static string LcsRecursive(string str1, string str2, int m, int n)
        {
            /* Caso base: si cualquiera de las dos cadenas está vacía, retornas vacío.*/
            if (m == 0 || n == 0)
            {
                return "";
            }

            /* Si los últimos caracteres de ambas cadenas coinciden.*/
            if (str1[m - 1] == str2[n - 1])
            {
                /*Añadir este caracter a la LCS y recursivamente encontrar las cadenas restantes.*/
                return LcsRecursive(str1, str2, m - 1, n - 1) + str1[m - 1];
            }
            else
            {
                /* Si el último de los caracteres no coinciden, recursivamente encontrar
                 * la LCS, sea ignorando el ultimo caracter de str1 o el ultimo caracter
                 * de str2.
                 */
                string lcs1 = LcsRecursive(str1, str2, m, n - 1);
                string lcs2 = LcsRecursive(str1, str2, m - 1, n);

                /*Retornas el más grande los dos LCS*/
                return (lcs1.Length > lcs2.Length) ? lcs1 : lcs2;
            }
        }

    }

}
