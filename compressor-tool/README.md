# Huffman Tree Compression Tool

This project implements a Huffman Tree compression tool in C. The tool reads a string, counts the frequency of each character, builds a Huffman Tree, and encodes the string using the Huffman coding algorithm. The encoded message is stored in a linked list.

## Features

- Count character frequencies in a string
- Build a Huffman Tree based on character frequencies
- Encode the string using Huffman coding
- Print the encoded message
- Free all allocated memory to avoid memory leaks

## Files

- `huffman_tree.c`: Main implementation file for the Huffman Tree compression tool
- `memoryManager.c`: Memory management utility for tracking and freeing allocated memory

## Usage

1. Compile the code:
    ```sh
    gcc huffman_tree.c -o huffman_tree
    ```

2. Run the executable:
    ```sh
    ./huffman_tree
    ```

3. Enter a string when prompted. The tool will display the Huffman Tree, encoded message.

## Functions

### `createNodeForLinkedLIst`

Creates a new node for the encoded message linked list.

### `createNode`

Creates a new node for the Huffman Tree.

### `joinNode`

Joins a new node to the existing linked list.

### `inorderTraversal`

Performs an inorder traversal of the Huffman Tree and prints the nodes.

### `traverse`

Traverses and prints the linked list.

### `checkEle`

Checks if a character exists in the linked list and updates its frequency.

### `count`

Counts the frequency of each character in the input string.

### `sortLinkedList`

Sorts the linked list based on character frequencies in descending order.

### `addFrq`

Creates a parent node by adding the frequencies of two nodes.

### `huffmanTree`

Builds the Huffman Tree from the sorted linked list.

### `printEncodedMessage`

Prints the encoded message stored in the linked list.

### `findchar`

Finds the path to a character in the Huffman Tree.

### `encodingMessage`

Encodes the input string using the Huffman Tree and stores the encoded message in a linked list.

### `freeHuffmanTree`

Frees all nodes in the Huffman Tree.

### `freeEncodedList`

Frees all nodes in the encoded message linked list.

## Memory Management

This project uses a custom memory management utility to track and free allocated memory. The memory management functions are provided by the [Hemang Gour - Memory Manager](https://github.com/Hemanggour/C-Projects/tree/main/Memory-Manager) repository.

### Credits

Special thanks to the [Hemang Gour - Memory Manager](https://github.com/Hemanggour/C-Projects/tree/main/Memory-Manager) repository for providing the memory management utility used in this project.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.