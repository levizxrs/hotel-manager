# 🏨 Hotel Manager — Sistema de Gerenciamento de Hospedagens

![C++](https://img.shields.io/badge/C%2B%2B-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![Status](https://img.shields.io/badge/Status-Conclu%C3%ADdo-brightgreen?style=for-the-badge)
![Licença](https://img.shields.io/badge/Licen%C3%A7a-MIT-blue?style=for-the-badge)

Sistema de linha de comando (CLI) desenvolvido em **C/C++** para controle de check-in e gerenciamento de hospedagens em hotéis. O projeto aplica conceitos de programação estruturada, modularização, manipulação de registros (`struct`) e persistência de dados em arquivos binários e de texto.

---

## 📋 Funcionalidades

- **Cadastrar Hospedagem:** Registra código único (com validação contra duplicidade), nome do hóspede, CPF, telefone, número do quarto, datas de entrada/saída e valor da diária.
- **Consultar por Código:** Busca e exibe os detalhes completos de uma hospedagem ativa a partir do seu identificador numérico.
- **Listar Hospedagens:** Apresenta todas as hospedagens ativas armazenadas no sistema e o total em andamento.
- **Exclusão Lógica:** Desativa um registro alterando seu campo `status` (`1` → `0`) diretamente no arquivo binário via `fseek`, mantendo a integridade histórica da base de dados.
- **Exportar para TXT:** Gera um relatório formatado e legível (`hospedagens.txt`) contendo todas as hospedagens ativas.
- **Contabilizar Registros:** Exibe métricas gerais da base de dados (total de registros cadastrados, hospedagens ativas e hospedagens excluídas).

---

## 🛠️ Arquitetura e Tecnologias

- **Linguagem:** C / C++ (bibliotecas padrão `stdio.h`, `stdlib.h`, `string.h`)
- **Estrutura de Dados:** `typedef struct Hospedagem`
- **Persistência Binária (`hospedagens.dat`):** Armazenamento permanente em modo binário (`rb`, `ab`, `rb+`) utilizando `fread`, `fwrite` e `fseek`.
- **Relatórios (`hospedagens.txt`):** Exportação em modo texto (`w`) com `fprintf`.

---

## 🚀 Como Compilar e Executar

### Pré-requisitos
Certifique-se de ter um compilador C/C++ instalado, como o **GCC / G++** (MinGW no Windows, GCC no Linux ou Clang no macOS).

### Passo a passo

1. **Clone este repositório:**
   ```bash
   git clone [https://github.com/SEU-USUARIO/hotel-manager-cpp.git](https://github.com/SEU-USUARIO/hotel-manager-cpp.git)
   cd hotel-manager-cpp