package app.model;

public class BST<T> {
    Node<T> root;

    public BST() {
        this.root = null; 
    }; 

    public class Node<T> implements Comparable<T>  {
        T value;
        Node<T> left, right, parent;

        public Node(T value) {
            this.value = value;
        }

        public Node<T> getLeft() {
            return left;
        }

        public Node<T> getRight() {
            return right;
        }

        public T getValue() {
            return value;
        }
    }

    public void insert(T value) {
        Node<T> n = new Node<T>(value);
        // todo
    }

    public void remove(T value) {

    }

    public void search(T value) {

    }

    public String print() {

    }
}
