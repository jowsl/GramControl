#include "PrecoBaseController.hpp"

PrecoBaseController::PrecoBaseController() {}

PrecoBaseController::PrecoBaseController(const PrecoBaseController& outro) {}

PrecoBaseController& PrecoBaseController::operator=(const PrecoBaseController& outro) {
    return *this;
}

PrecoBaseController::~PrecoBaseController() {}

bool PrecoBaseController::requisitarAtualizacaoPreco(std::string nomeItem, double novoPreco) {
    PrecoBase precoModel(nomeItem, novoPreco);

    if (!precoModel.atualizarPreco(novoPreco)) {
        return false;
    }

    PrecoBaseDAO dao;
    dao.inicializarBanco();
    return dao.atualizarNoBanco(precoModel);
}