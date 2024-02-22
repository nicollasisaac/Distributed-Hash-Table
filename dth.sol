// SPDX-License-Identifier: GPL-3.0
pragma solidity >=0.8.2 <0.9.0;

contract ProductContract {
    // Estrutura para armazenar informações dos produtos
    struct Product {
        string productName;
    }

    // Mapeamento de produtos
    mapping(address => Product) public products;

    // Lista para armazenar produtos
    string[] private productList;

    // Evento emitido quando um produto é registrado
    event ProductRegistered(string indexed productName);

    // Função para registrar um novo produto
    function registerProduct(string memory _productName) public {
        // Verifica se o produto já está registrado
        require(
            bytes(products[msg.sender].productName).length == 0,
            "Product already registered."
        );

        // Registra o produto
        products[msg.sender] = Product(_productName);

        // Adiciona o endereço da carteira do usuário à lista de endereços
        productList.push(_productName);

        // Emite o evento de registro
        emit ProductRegistered(_productName);
    }

    // Função para retornar todos os produtos
    function getProducts() public view returns (string[] memory) {
        return productList;
    }
}
