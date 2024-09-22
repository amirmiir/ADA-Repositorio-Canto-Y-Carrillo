using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace NodeTDA

{
    public class Node<E>
    {
        private E data;
        private Node<E> next;

        public Node(E data)
        {
            this.data = data;
            this.next = null;
        }

        public void SetData(E data)
        {
            this.data = data;
        }

        public void SetNext(Node<E> next)
        {
            this.next = next;
        }

        public E GetData()
        {
            return this.data;
        }

        public NodeTDA.Node<E> GetNext()
        {
            return this.next;
        }
    }
}
