using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace QueueADT
{
    public interface IQueueADT<E>
    {
        void add(E elemento);
        E remove();
        E poll();
        E peek();
        void clear();
        bool isEmpty();
        int size();
        void offer(E elemento, int priority);



    }
}