private staticclass Node<V extendsComparable<V>> {



        private Node parent;

        private Node left;

        private Node right;

        private int k = 0;

        private final V data;



        public Node(V data) {

this.data = data;

this.parent = null;

this.left = null;

this.right = null;

        }



    }



public abstract classHashTree<E extendsComparable<E>> {



    private Node root = null;

    private Node[] nodes;



    public HashTree(int capacity) {

this.nodes = new Node[capacity];

    }



    public abstract int getElementHash(E element);

…

}



Добавлениеузла:

public void addElement(E element) {

	    int index = getElementHash(element);

	    if (nodes[index] != null) {

	return;

	    }

	    Node<E> node = new Node<>(element);

	    nodes[index] = node;

	this.root = connectNodes(this.root, node);

	}



Удалениеузла:

public E removeElement(E element) {

        int index = getElementHash(element);

        Node node = nodes[index];

        if (node == null) {

returnnull;

        }

        nodes[index] = null;

        E data = (E) node.data;

        Node l = getElemInArray(node.left);

        Node r = getElemInArray(node.right);

        if (l != null) {

            l.parent = null;

        }

        if (r != null) {

            r.parent = null;

        }

        l = connectNodes(l, r);

        if (node.parent == null) {

this.root = l;

            if (this.root != null) {

this.root.parent = null;

            }

return data;

        }

        int p = getElementHash((E) node.parent.data);

        if (nodes[p] != null) {//здесь сравниваются ИМЕННО значение указателей, 

//интересует равенство адресов памяти, а не значений

            if (nodes[p].left == node) {

                nodes[p].left = null;

            }

            if (nodes[p].right == node) {

                nodes[p].right = null;

            }

        }

        connectNodes(nodes[p], l);

return data;



    }



Присоединение узла или поддерева:

private Node connectNodes(Node parent, Node node) {

        if (node == null) {

return parent;

        }

        if (parent == null) {

return node;

        } else {

            if (compare(node, parent) < 0) {

return connectNodes(node, parent);

            }

            Node cur = parent;

            Node n = node;

while (cur != null) {

                if (cur.left == null) {

                    cur.left = n;

                    n.parent = cur;

                    cur.k++;

break;

                }

                if (cur.right == null) {

                    if (compare(n, cur.left) <= 0) {

                        cur.right = cur.left;

                        cur.left = n;

                        n.parent = cur;

                        cur.k++;

break;

                    } else {

                        cur.right = n;

                        n.parent = cur;

                        cur.k++;

break;

                    }

                }

                if (compare(n, cur.left) <= 0) {

                    Node tmp = cur.left;

                    cur.left = n;

                    n.parent = cur;

                    cur.k++;

                    cur = n;

                    n = tmp;

                    continue;

                }

                if (compare(n, cur.right) <0

&& compare(n, cur.left) > 0) {

                    cur.k++;

                    if (cur.right.k < cur.left.k) {

                        Node tmp = cur.right;

                        cur.right = n;

                        n.parent = cur;

                        cur = n;

                        n = tmp;

                    } else {

                        cur = cur.left;

                    }

                    continue;

                }

                if (compare(n, cur.left) > 0) {

                    cur.k++;

                    cur = cur.left.k < cur.right.k ? cur.left : cur.right;

                }

            }

return parent;

        }
