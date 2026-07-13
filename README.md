# GramControl

## Overview

O GramControl é uma plataforma desenvolvida para automatizar e organizar a gestão comercial de empresas que trabalham com gramados esportivos. O sistema concentra as principais operações de vendas, cadastro de clientes, definição de preços e criação de orçamentos em um ambiente único, facilitando o trabalho de vendedores e administradores.

### O que o sistema oferece

- Cadastro e gestão de clientes
- Criação e acompanhamento de orçamentos
- Controle de preços base e atualização de valores
- Autenticação por perfil de usuário
- Persistência de dados para uso contínuo

### Para quem é voltado

- Vendedores: podem registrar clientes e montar orçamentos com mais rapidez
- Administradores: controlam configurações, cadastros e regras de negócio
- Equipes operacionais: recebem informações mais organizadas para execução

### Objetivo principal

Reduzir processos manuais, agilizar o fechamento de propostas e centralizar a comunicação entre os envolvidos no fluxo comercial e operacional.

## Compilação

Para compilar o projeto, execute os seguintes comandos no terminal:

### Cria o executavel da aplicação ./bin/gramcontrol
```bash
make app
```
### Cria e roda os testes unitários
```bash
make test
```

### Criar Dlls/OS e mostra que nossa aplicação é desacoplada
```bash
make dlls
```

## Execução
```bash
rm -f gramcontrol.db
./bin/gramcontrol
```

Isso irá gerar os arquivos executáveis na pasta `bin/`.
=======

