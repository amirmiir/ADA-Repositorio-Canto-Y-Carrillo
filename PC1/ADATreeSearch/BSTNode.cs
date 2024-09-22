using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ADATreeSearch
{
    public class BSTNode
    {
        private int key;
        public BSTNode left, right;

        public BSTNode()
        {
            left = right = null;
        }

        public BSTNode(int key)
        {
            this.key = key;
        }

        public BSTNode(int key, BSTNode left, BSTNode right) : this(key)
        {
            this.left = left;
            this.right = right;
        }

        public int GetKey()
        {
            return key;
        }

        public void SetKey(int key)
        {
            this.key = key;
        }
    }
}
