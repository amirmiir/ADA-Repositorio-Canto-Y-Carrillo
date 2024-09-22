using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Serialization;
using System.Diagnostics;



namespace ADATreeSearch
{
    public class BSTMain
    {
        public static void Main(string[] args)
        {
            
            BSTMain bSTMain = new BSTMain();
            /*
             * 
             */
            int choice = 1;
            while (choice != 0)
            {
                Console.WriteLine("MENU\n" +
                                "1. Arbol predeterminado\n" +
                                "2. Arbol generado al azar\n" +
                                "0. Salir\n\n" +
                                "Ingrese la opcion:");

                choice = Convert.ToInt32(Console.ReadLine());

                switch (choice)
                {
                    case 0: break;
                    case 1:
                        bSTMain.Custom();
                        break;
                    case 2:
                        bSTMain.FillRandom();
                        break;
                    default:
                        Console.WriteLine("Opcion invalida.\n\n");
                        break;
                }
            }
        }

        public void Custom()
        {
            BSTMain bSTMain=new BSTMain();
            BST tree = new BST();
            tree.Insert(10);
            tree.Insert(5);
            tree.Insert(20);
            tree.Insert(4);
            tree.Insert(6);
            tree.Insert(15);
            tree.Insert(30);
            tree.Insert(0);
            tree.Insert(7);
            tree.Insert(13);
            tree.Insert(8);

            bSTMain.Actions(tree);
        }

        public void FillRandom()
        {
            BSTMain bSTMain = new BSTMain();
            BST tree = new BST();
            Console.WriteLine("Ingrese la cantidad de nodos para el árbol: ");
            int n = Convert.ToInt32(Console.ReadLine());
            Random rand = new Random();
            /*Making use of a hashmap to make sure we do not have duplicates due to the data structure*/
            HashSet<int> uniqueNumbers = new HashSet<int>();

            /* Generate random numbers without duplicates*/
            while (uniqueNumbers.Count < n)
            {
                int randomNumber = rand.Next(1, 2*n); // Random number between 1 and 2*n
                if (uniqueNumbers.Add(randomNumber)) // If the number is added to the HashSet, it means it's unique
                {
                    tree.Insert(randomNumber);
                }
            }

            bSTMain.Actions(tree);
        }

        public void Actions(BST tree)
        {
            Stopwatch cronometro = new Stopwatch();
            Console.WriteLine("Se realizará la tarea BFS:");
            Console.ReadLine();
            cronometro.Start();
            tree.BreadthFirstSearch();
            cronometro.Stop();
            Console.WriteLine("El tiempo para realizar BFS: {0} ms", Convert.ToDouble(cronometro.ElapsedTicks)/10000);
            Console.WriteLine("El tiempo para realizar BFS: {0} ms", cronometro.ElapsedMilliseconds);
            Console.ReadLine();

            cronometro.Reset();

            Console.WriteLine("Se realizará la tarea preorder:");
            Console.ReadLine();
            cronometro.Start();
            tree.PreorderTraversal();
            cronometro.Stop();
            Console.WriteLine("El tiempo para realizar BFS: {0} ms", Convert.ToDouble(cronometro.ElapsedTicks) / 10000);
            Console.WriteLine("El tiempo para realizar PreOrder: {0} ms", cronometro.ElapsedMilliseconds);
            Console.ReadLine();

        }


    }
}
