using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace QueueADT
{
    public class LinkedQueueADT<E> : IQueueADT<E>
    {
        public NodeTDA.Node<E> front;
        public NodeTDA.Node<E> back;
        private int contador;

        public LinkedQueueADT()
        {
            clear();
        }

        public void add(E item)
        {
            NodeTDA.Node<E> newNode = new NodeTDA.Node<E>(item);
            if (isEmpty())
            {
                front = back = newNode;
            }
            else
            {
                back.SetNext(newNode);
                back = newNode;
            }
            contador++;
        }

        public E remove()
        {
            E item;
            if (isEmpty())
            {
                throw new Exception();
            }
            else
            {
                item = (E)front.GetData();
                front = front.GetNext();
                contador--;
            }

            return item;
        }

        public E peek()
        {
            if (isEmpty())
            {
                return default(E);
            }
            else
            {
                return (E)front.GetData();
            }
        }
        public void clear()
        {
            front = back = null;
            contador = 0;
        }

        public bool isEmpty()
        {
            return (contador == 0);
        }

        public int size()
        {
            return contador;
        }

        public override string ToString()
        {
            string result = "";
            NodeTDA.Node<E> current = front;

            while (current != null)
            {
                result = result + "->" + current.GetData().ToString();
                current = current.GetNext();
            }
            return result;
        }

        public void offer(E item, int priority)
        {
            throw new NotSupportedException("Not supported yet.");

        }

        public E poll()
        {

            if (isEmpty())
            {
                return default(E);
            }
            else
            {
                E item = (E)front.GetData();
                front = front.GetNext();
                contador--;

                return item;
            }

        }
    }

}
