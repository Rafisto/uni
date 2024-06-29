package model;

/**
 * Represents a Binary Search Tree (BST) data structure.
 * The BST class allows insertion, deletion, searching, and printing of elements in the tree.
 * It uses a generic type parameter T that must implement the Comparable interface.
 *
 * @param <T> the type of elements stored in the BST
 */
public class BST<T extends Comparable<T>> {
    Node<T> root;

    /**
     * Constructs an empty BST.
     */
    public BST() {
        this.root = null;
    };

    /**
     * Represents a node in the BST.
     * Each node has a value of type E, and may have a left child, right child, and parent node.
     *
     * @param <E> the type of value stored in the node
     */
    public class Node<E extends Comparable<E>> {
        E value;
        Node<E> left, right;

        public Node(E value) {
            this.value = value;
        }
    }

    /**
     * Inserts a value into the BST.
     *
     * @param value the value to insert
     */
    public void insert(T value) {
        System.out.println("Inserting value: " + value);
        if (root == null) {
            System.out.println("Inserting root");
            root = new Node<T>(value);
        } else {
            System.out.println("Inserting node");
            insertNode(root, value);
        }
    }

    /**
     * Deletes a value from the BST.
     *
     * @param value the value to delete
     */
    public void delete(T value) {
        root = deleteNode(root, value);
    }

    /**
     * Searches for a value in the BST.
     *
     * @param value the value to search for
     * @return true if the value is found, false otherwise
     */
    public boolean search(T value) {
        return searchRecursive(root, value);
    }

    /**
     * Prints the BST in a readable format.
     *
     * @return a string representation of the BST
     */
    public String print() {
        return printRecursive(root,0);
    }

    /**
     * Inserts a value into the BST recursively.
     * @param node the current node
     * @param value the value to insert
     */
    private void insertNode(Node<T> node, T value) {
        if (value.compareTo(node.value) < 0) {
            if (node.left == null) {
                node.left = new Node<T>(value);
            } else {
                insertNode(node.left, value);
            }
        } else {
            if (node.right == null) {
                node.right = new Node<T>(value);
            } else {
                insertNode(node.right, value);
            }
        }
    }

    /**
     * Deletes a value from the BST recursively.
     * @param node the current node
     * @param value the value to delete
     * @return the node after deletion
     */
    private Node<T> deleteNode(Node<T> node, T value) {
        if (node == null) {
            return null;
        }

        if (value.compareTo(node.value) < 0) {
            node.left = deleteNode(node.left, value);
        } else if (value.compareTo(node.value) > 0) {
            node.right = deleteNode(node.right, value);
        } else {
            if (node.left == null && node.right == null) {
                node = null;
            } else if (node.left == null) {
                node = node.right;
            } else if (node.right == null) {
                node = node.left;
            } else {
                Node<T> temp = node.right;
                while (temp.left != null) {
                    temp = temp.left;
                }
                node.value = temp.value;
                node.right = deleteNode(node.right, temp.value);
            }
        }

        return node;
    }

    /**
     * Searches for a value in the BST recursively.
     * @param node the current node
     * @param value the value to search for
     * @return true if the value is found, false otherwise
     */
    private boolean searchRecursive(Node<T> node, T value) {
        if (node == null) {
            return false;
        }
        if (value.compareTo(node.value) < 0) {
            return searchRecursive(node.left, value);
        } else if (value.compareTo(node.value) > 0) {
            return searchRecursive(node.right, value);
        } else {
            return true;
        }
    }

    /**
     * Prints the BST in a readable format recursively.
     * @param node the current node
     * @param indent the indentation level
     * @return a string representation of the BST
     */
    private String printRecursive(Node<T> node, int indent) {
        StringBuilder sb = new StringBuilder();
        if (node != null) {
            sb.append(printRecursive(node.right, indent + 4));
            for (int i = 0; i < indent; i++) {
                sb.append(" ");
            }
            sb.append("").append(node.value).append("\n");
            sb.append(printRecursive(node.left, indent + 4));
        }
        return sb.toString();
    }
}
