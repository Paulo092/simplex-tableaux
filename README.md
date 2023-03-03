<p align="center">
    <img src="./readme-files/table-icon.png" width="130">
</p>

<h1 align="center">
    Simplex Tableaux
</h1>

<p align="center">
    <img alt="GitHub Top Language" src="https://img.shields.io/github/languages/top/Paulo092/simplex-tableaux" />
    <img alt="Github License" src="https://img.shields.io/github/license/Paulo092/simplex-tableaux" />
    <img alt="GitHub Last Commit" src="https://img.shields.io/github/last-commit/Paulo092/simplex-tableaux" />
    <br>
    Codificação do algoritmo de Simplex utilizando o método de Tableux. Com entrada de arquivos e "visualização gráfica" no terminal.
</p>

<h2>📑 Índice</h2>

- [⚙️ Pré-Requisitos](#️-pré-requisitos)
- [🔧 Setup e Utilização](#-setup-e-utilização)
  - [➕ Problem.set](#-problemset)
- [👥 Autores](#-autores)

## ⚙️ Pré-Requisitos

- GCC (GNU Compiler Collection), ou qualquer outro compilador da linguagem ```c```.

## 🔧 Setup e Utilização

1. Baixe ou clone o repositório para sua máquina, utilizando o ```GitHub Desktop``` ou pela ```Linha de Comando```, com o comando: 
```bash
git clone https://github.com/Paulo092/simplex-tableaux.git
```
2. Acesse o subdiretório do projeto clonado:
```bash
cd .\simplex-tableaux\
```
3. Compile o código:
```bash
gcc .\Main.c .\Header.c -o simplex-tableaux
```
4. Execute:
```bash
.\simplex-tableaux Problem.set
```

Observações: 
- Caso queira utilizar outro nome para o arquivo resultante da compilação so troque ```simplex-tableaux``` pelo nome desejado.
- O arquivo Problm.set deve ser passado como argumento, sendo o arquivo que possui a estrutura do problema a ser resolvido.
- O arquivo de problema não precisa nescessáriamente ter a extensão .set, portanto entradas como Problem.txt, Problem.c, etc serão aceitas.

### ➕ Problem.set

O arquivo que contem o problema tem que seguir o seguinte padrão:

```c
[maximize|minimize]: {Função Objetivo}
{Restrição-1} 
{Restrição-2}
... 
{Restrição-i}
```

- É muito importante que ao fim da função objetivo e de cada restrição haja uma quebra de linha;
- A extensão do arquivo não precisa ser nescessariamente .set, ou seja, o programa aceita arquivos de texto (.txt) ou qualquer outro tipo, desde que o conteúdo do arquivo siga a estrutura acima;
- Espaços, tabulações serão ignorados.

<!-- ## 💿 Demonstração -->

## 👥 Autores

<table align="center">
    <tr>
      <td align="center">
        <a href="https://github.com/Paulo092">
            <img src="https://avatars.githubusercontent.com/u/28546848?v=4" width="100px;" alt="Foto de Perfil"/><br>
            <sub>
              <b>Paulo Sergio</b>
            </sub>
        </a>
    </td>
    </tr>
</table>
