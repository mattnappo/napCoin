# Blockchain
This is a simple blockchain that uses the [Argon2 hashing algorithm](https://github.com/P-H-C/phc-winner-argon2).

# Usage
Get up and running using this blockchain!

## Blockchain class
Create a new blockchain class:<br>
``Blockchain *blockchain = new Blockchain;``<br>

### Methods
Methods of the blockchain class.

### build
``build`` builds a specified amount of blocks onto the blockchain.
Arguments:
* ``int blockchain_size`` - Specifies the amount of blocks to build onto the blockchain.
* ``bool show_blocks`` - Specifies whether to display the contents of each newly-created block to the console.

### export_blockchain
``export_blockchain`` exports the current blockchain into a json file in the 'blockchains' subdirectory.
Arguments:
* ``string blockchain_name`` - Specifies the name of the file to write the current blockchain to.

### import_blockchain
``import_blockchain`` imports a blockchain from a json file in the 'blockchains' subdirectory.
Arguments:
* ``string blockchain_name`` - Specifies the name of the file to read the blockchain from.
* ``bool show_blocks`` - Specifies whether to display the contents of each newly-imported block to the console.

### print_blockchain
``print_blockchain`` prints the blockchain in its current state.
Arguments: (None)

## Example code
Some examples to get started

### Build and export
```
#include "blockchain.hpp"

int main() {
  // Create a new blockchain class
  Blockchain *blockchain = new Blockchain;

  // Build a blockchain of size 10 and show each block upon addition to the chain.
  blockchain->build(10, true);

  // Export the blockchain to "blockchains/blockchain_0.json"
  blockchain->export_blockchain("blockchain_0");

  return 0;
}
```

### Import and print
```
#include "blockchain.hpp"

int main() {
  // Create a new blockchain class
  Blockchain *blockchain = new Blockchain;

  // Import the blockchain from "blockchains/blockchain_0.json" to the blockchain object and print the new blockchain.
  blockchain->import_blockchain("blockchain_0", true);

  return 0;
}

```
## Building
``make blockchain`` builds ``blockchain.cpp`` as ``blockchain.o`` in the root directory.

## Features to Add:
* Command line interface
* Validation
* Public-key cryptography
* Networking validation nodes
