# 🏨 Hotel Manager — Sistema de Gestão de Hospedagens

![Linguagem](https://img.shields.io/badge/Linguagem-C%20%2F%20C%2B%2B-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![Paradigma](https://img.shields.io/badge/Paradigma-Programa%C3%A7%C3%A3o%20Estruturada-informational?style=for-the-badge)
![Persistência](https://img.shields.io/badge/Persist%C3%AAncia-Arquivos%20Bin%C3%A1rios%20%26%20TXT-success?style=for-the-badge)
![Status](https://img.shields.io/badge/Status-Conclu%C3%ADdo-brightgreen?style=for-the-badge)

Aplicação de linha de comando (CLI) desenvolvida em **C/C++** para automação de check-in e gestão de hospedagens hoteleiras. Construída integralmente com bibliotecas padrão (*zero dependências externas*), a solução aplica **arquitetura modular**, **persistência binária com acesso direto em disco (`fseek`)**, **exclusão lógica (*soft delete*)** para integridade histórica e **exportação automatizada de relatórios** em texto.

---

## 📑 Sumário

- [Visão Geral](#-visão-geral)
- [Funcionalidades](#-funcionalidades)
- [Arquitetura e Modelo de Dados](#-arquitetura-e-modelo-de-dados)
- [Como Compilar e Executar](#-como-compilar-e-executar)
- [Interface do Sistema (CLI)](#-interface-do-sistema-cli)
- [Estrutura do Repositório](#-estrutura-do-repositório)
- [Autor](#-autor)

---

## 🎯 Visão Geral

Em rotinas de recepção hoteleira, falhas no registro de hóspedes, conflitos de identificadores e a exclusão definitiva de registros comprometem o controle operacional e a auditoria de dados. O **Hotel Manager** resolve esse cenário por meio de uma arquitetura leve em terminal que separa o **armazenamento estruturado** da **camada de visualização**:

- **Integridade e Auditoria:** Os dados são persistidos em formato binário (`hospedagens.dat`) com validação prévia de chave primária e **exclusão lógica** (`status`), preservando o histórico completo de check-ins encerrados ou cancelados sem fragmentar o arquivo.
- **Portabilidade e Controle:** Para facilitar a leitura externa e o acompanhamento gerencial, o sistema desacopla a base binária da emissão de relatórios em texto puro (`hospedagens.txt`) e oferece contagem instantânea de registros ativos e inativos.

---

## ✨ Funcionalidades

- **Cadastro com Validação de Chave:** Insere novas hospedagens verificando previamente (`codigoExiste`) se o identificador numérico já está em uso, evitando conflitos de registro.
- **Consulta Direta por Código:** Localiza e exibe os dados completos de um hóspede ativo a partir do seu código de identificação.
- **Listagem de Hospedagens Ativas:** Percorre a base binária filtrando registros ativos (`status == 1`) e contabiliza o total de check-ins em andamento.
- **Exclusão Lógica (*Soft Delete*):** Inativa registros alterando o campo `status` de `1` para `0` diretamente na posição do arquivo (`fseek` + `fwrite`), mantendo a integridade estrutural da base e o histórico para auditoria.
- **Exportação de Relatório (`TXT`):** Converte os dados binários em um relatório formatado e legível (`hospedagens.txt`) contendo apenas as hospedagens ativas.
- **Painel de Métricas:** Contabiliza em tempo real o total de registros gravados, a quantidade de hospedagens ativas e o total de registros excluídos.

---

## 🏗️ Arquitetura e Modelo de Dados

### Estrutura Principal (`struct Hospedagem`)

Cada registro armazenado no arquivo binário segue um layout fixo de bytes definido pela seguinte estrutura:

| Campo | Tipo | Tamanho | Descrição |
| :--- | :--- | :---: | :--- |
| `codigo` | `int` | 4 bytes | Identificador único da hospedagem (chave primária) |
| `nome` | `char[]` | 100 bytes | Nome completo do hóspede |
| `cpf` | `char[]` | 20 bytes | Documento de identificação do hóspede |
| `telefone` | `char[]` | 20 bytes | Telefone para contato |
| `quarto` | `int` | 4 bytes | Número do quarto ocupado |
| `entrada` | `char[]` | 20 bytes | Data de check-in (`DD/MM/AAAA`) |
| `saida` | `char[]` | 20 bytes | Data prevista de check-out (`DD/MM/AAAA`) |
| `valorDiaria` | `float` | 4 bytes | Valor unitário da diária em reais (`R$`) |
| `status` | `int` | 4 bytes | Flag de controle (`1` = Ativa \| `0` = Desativada) |

### Estratégia de Persistência e I/O

- **Acesso Binário (`hospedagens.dat`):** Utiliza `fopen` nos modos `"ab"` (inserção sequencial), `"rb"` (leitura) e `"rb+"` (atualização *in-place*). Na exclusão lógica, o ponteiro do arquivo retrocede exatamente `sizeof(Hospedagem)` bytes via `fseek(..., SEEK_CUR)` para sobrescrever apenas o registro alvo sem reescrever todo o arquivo.
- **Tratamento Seguro de Buffer (`stdin`):** Implementa `lerTexto()` com `fgets` e limpeza dinâmica de excedentes (`limparBuffer()`), prevenindo falhas de leitura causadas por quebras de linha residuais.

---

## 🚀 Como Compilar e Executar

### Pré-requisitos
- Compilador **GCC / G++** (MinGW no Windows, GCC no Linux ou Clang no macOS).

### Passo a passo

1. **Clone o repositório:**
   ```bash
   git clone [https://github.com/levizxrs/](https://github.com/levizxrs/)
