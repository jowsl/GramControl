#include "PrecoBaseController.hpp"

PrecoBaseController::PrecoBaseController() {}

PrecoBaseController::PrecoBaseController(const PrecoBaseController& outro) {
    // Como o controller não tem atributos de classe, não há o que copiar
}

PrecoBaseController& PrecoBaseController::operator=(const PrecoBaseController& outro) {
    if (this != &outro) {
        // Como o controller não tem atributos, não há o que atribuir
    }
    return *this;
}

PrecoBaseController::~PrecoBaseController() {}

bool PrecoBaseController::requisitarAtualizacaoPreco(QString nomeItem, double novoPreco) {
    // Cria o objeto com o valor real capturado da tela
    PrecoBase precoModel(nomeItem, novoPreco);

    // Validação da regra de negócio (se existir)
    if (!precoModel.atualizarPreco(novoPreco)) {
        return false;
    }

    PrecoBaseDAO dao;
    dao.inicializarBanco(); 

    // Envia para persistência
    return dao.atualizarNoBanco(precoModel);
}

