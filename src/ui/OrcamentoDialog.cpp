#include "OrcamentoDialog.h"
#include <QVBoxLayout>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QLocale>
#include <QDesktopServices> //para abrir o email
#include <QUrl>

OrcamentoDialog::OrcamentoDialog(QWidget* parent) : QDialog(parent) {
    setWindowTitle("GramControl - Novo Orcamento (Req. 5.7)");
    resize(420, 300); // Aumentei um pouco a altura para caber o novo campo

    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    QLabel* titulo = new QLabel("=== INSERIR METRAGEM E TIPO DE GRAMA ===", this);
    titulo->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(titulo);

    QFormLayout* form = new QFormLayout();

    // [SPRINT 2] Novo campo de E-mail
    inputEmail = new QLineEdit(this);
    inputEmail->setPlaceholderText("cliente@email.com");
    form->addRow("E-mail do Cliente:", inputEmail);

    comboTipoGrama = new QComboBox(this);
    form->addRow("Tipo de grama:", comboTipoGrama);

    inputMetragem = new QDoubleSpinBox(this);
    inputMetragem->setRange(0.0, 1000000.0);
    inputMetragem->setDecimals(2);
    inputMetragem->setSuffix(" m2");
    inputMetragem->setValue(0.0);
    form->addRow("Metragem do terreno:", inputMetragem);

    labelPrecoUnitario = new QLabel("Preco unitario: --", this);
    form->addRow("", labelPrecoUnitario);

    mainLayout->addLayout(form);

    labelResultado = new QLabel("Valor parcial do servico: --", this);
    labelResultado->setAlignment(Qt::AlignCenter);
    QFont f = labelResultado->font();
    f.setBold(true);
    f.setPointSize(f.pointSize() + 2);
    labelResultado->setFont(f);
    mainLayout->addWidget(labelResultado);

    QHBoxLayout* botoes = new QHBoxLayout();
    btnCalcular = new QPushButton("Calcular Orcamento", this);
    
    // [SPRINT 2] Novo botão
    btnGerarDigital = new QPushButton("Gerar e Salvar", this); 
    
    btnFechar   = new QPushButton("Fechar", this);
    botoes->addWidget(btnCalcular);
    botoes->addWidget(btnGerarDigital); // Adicionando ao layout
    botoes->addWidget(btnFechar);
    mainLayout->addLayout(botoes);

    // Conexões originais mantidas
    connect(btnCalcular, &QPushButton::clicked, this, &OrcamentoDialog::calcularOrcamento);
    connect(btnFechar,   &QPushButton::clicked, this, &QDialog::accept);
    connect(comboTipoGrama, QOverload<int>::of(&QComboBox::currentIndexChanged), this,
            [this](int) {
                double preco = comboTipoGrama->currentData().toDouble();
                labelPrecoUnitario->setText(
                    QString("Preco unitario: R$ %1 / m2")
                        .arg(QLocale(QLocale::Portuguese, QLocale::Brazil).toString(preco, 'f', 2)));
            });

    // [SPRINT 2] Conectando o novo botão
    connect(btnGerarDigital, &QPushButton::clicked, this, &OrcamentoDialog::gerarOrcamentoDigital);

    carregarTiposDeGrama();
}

void OrcamentoDialog::carregarTiposDeGrama() {
    OrcamentoController controller;
    auto gramas = controller.listarTiposDeGrama();

    comboTipoGrama->clear();
    if (gramas.empty()) {
        comboTipoGrama->addItem("(Nenhum tipo de grama cadastrado)", 0.0);
        btnCalcular->setEnabled(false);
        btnGerarDigital->setEnabled(false);
        return;
    }

    for (const auto& g : gramas) {
        comboTipoGrama->addItem(QString::fromStdString(g.first), g.second);
    }
    btnCalcular->setEnabled(true);
    btnGerarDigital->setEnabled(true);
}

// Lógica original mantida intacta
void OrcamentoDialog::calcularOrcamento() {
    double metragem = inputMetragem->value();

    if (metragem <= 0.0) {
        QMessageBox::warning(this, "Metragem invalida",
                             "Informe uma metragem valida (maior que zero) para calcular o orcamento.");
        return;
    }

    std::string tipo = comboTipoGrama->currentText().toStdString();

    OrcamentoController controller;
    Orcamento orc;
    if (!controller.calcularOrcamento(tipo, metragem, orc)) {
        QMessageBox::critical(this, "Erro",
                              "Nao foi possivel calcular o orcamento. Verifique o tipo de grama selecionado.");
        return;
    }

    double total = orc.calcularTotal();
    QLocale ptBR(QLocale::Portuguese, QLocale::Brazil);

    labelResultado->setText(
        QString("Valor parcial do servico: R$ %1")
            .arg(ptBR.toString(total, 'f', 2)));

    QMessageBox::information(this, "Orcamento calculado",
        QString("Tipo de grama: %1\n"
                "Metragem: %2 m2\n"
                "Preco unitario: R$ %3 / m2\n"
                "-----------------------------\n"
                "Valor parcial: R$ %4")
            .arg(QString::fromStdString(orc.getTipoGrama()))
            .arg(ptBR.toString(orc.getMetragem(), 'f', 2))
            .arg(ptBR.toString(orc.getPrecoUnitario(), 'f', 2))
            .arg(ptBR.toString(total, 'f', 2)));
}

void OrcamentoDialog::gerarOrcamentoDigital() {
    QString email = inputEmail->text();
    double metragem = inputMetragem->value();

    if (email.trimmed().isEmpty()) {
        QMessageBox::warning(this, "E-mail Ausente", "Por favor, informe o e-mail do cliente para gerar o orcamento digital.");
        return;
    }

    if (metragem <= 0.0) {
        QMessageBox::warning(this, "Metragem invalida", "Informe uma metragem valida (maior que zero).");
        return;
    }

    std::string tipo = comboTipoGrama->currentText().toStdString();

    OrcamentoController controller;
    Orcamento orc;
    
    // Calcula primeiro para instanciar o objeto Orcamento corretamente
    if (!controller.calcularOrcamento(tipo, metragem, orc)) {
        QMessageBox::critical(this, "Erro", "Erro ao preparar os dados do orcamento.");
        return;
    }

    // Chama o Controller para salvar e gerar o ID
    if (controller.salvarOrcamentoDigital(orc, email.toStdString())) {
        std::string detalhes = controller.buscarDetalhamento(orc.getId());
        
        QMessageBox::information(this, "Orcamento Digital Gerado com Sucesso!", QString::fromStdString(detalhes));
        
        // --- INICIO DO DISPARO DE E-MAIL ---
        QString subject = QString("Orcamento GramControl #%1").arg(orc.getId());
        QString body = QString::fromStdString(detalhes);
        
        // Monta a URL convertendo explicitamente o QByteArray do encoding para QString
        QString mailto = QString("mailto:%1?subject=%2&body=%3")
                            .arg(email)
                            .arg(subject)
                            .arg(QString(QUrl::toPercentEncoding(body))); 
        
        // Pede ao sistema operacional para abrir o cliente de e-mail padrão
        QDesktopServices::openUrl(QUrl(mailto));
        // --- FIM DO DISPARO DE E-MAIL ---

        // Limpa a tela para o proximo
        inputEmail->clear();
        inputMetragem->setValue(0.0);
        labelResultado->setText("Valor parcial do servico: --");
    } else {
        // --- TRATAMENTO DE ERRO ADICIONADO ---
        QMessageBox::critical(this, "Erro de Banco de Dados", "Ocorreu um erro ao tentar salvar o orcamento digital no SQLite.");
    }
}