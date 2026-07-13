# Variavel QT intocada (obrigatoria para rodar no WSL)
QT = -I/usr/include/x86_64-linux-gnu/qt5 -I/usr/include/x86_64-linux-gnu/qt5/QtCore -I/usr/include/x86_64-linux-gnu/qt5/QtWidgets -I/usr/include/x86_64-linux-gnu/qt5/QtSql -I/usr/include/x86_64-linux-gnu/qt5/QtGui -lQt5Core -lQt5Widgets -lQt5Sql -lQt5Gui

# O "Motor" do sistema (todos os .cpp, EXCETO os arquivos main)
CORE_SRC = src/GramControl.cpp \
           src/AtualizarPrecoDialog.cpp \
           src/CadastrarClienteDialog.cpp \
           src/PrecoBase.cpp \
           src/PrecoBaseController.cpp \
           src/PrecoBaseDAO.cpp \
           src/Orcamento.cpp \
           src/OrcamentoController.cpp \
           src/Cliente.cpp \
           src/ClienteController.cpp \
           src/ClienteDAO.cpp \
           src/ui/LoginWindow.cpp \
           src/ui/AdminWindow.cpp \
           src/ui/OrcamentoDialog.cpp

dlls:
	@echo "Gerando componentes de servico (DLLs/.so)..."
	g++ -shared -fPIC -std=c++17 -I src -I includes src/GramControl.cpp -o bin/libAuth.so -lsqlite3
	g++ -shared -fPIC -std=c++17 -I src -I includes src/Cliente*.cpp -o bin/libClientes.so $(QT) -lsqlite3
	g++ -shared -fPIC -std=c++17 -I src -I includes src/PrecoBase*.cpp -o bin/libPrecos.so $(QT) -lsqlite3
	g++ -shared -fPIC -std=c++17 -I src -I includes src/Orcamento*.cpp -o bin/libOrcamentos.so $(QT) -lsqlite3
	@echo "Componentes gerados com sucesso na pasta bin/!"

moc:
	moc src/ui/LoginWindow.h -o src/moc_LoginWindow.cpp
	moc src/ui/AdminWindow.h -o src/moc_AdminWindow.cpp
	moc src/AtualizarPrecoDialog.hpp -o src/moc_AtualizarPrecoDialog.cpp
	moc src/ui/OrcamentoDialog.h -o src/moc_OrcamentoDialog.cpp
	moc src/CadastrarClienteDialog.hpp -o src/moc_CadastrarClienteDialog.cpp

app: moc
	# Compila o app puxando o main do src + os mocs
	g++ -fPIC -std=c++17 -I src -I src/ui -I includes src/main.cpp $(CORE_SRC) src/moc_*.cpp $(QT) -o bin/gramcontrol -lsqlite3

test:
	# Compila os testes puxando os testes + o motor (sem interface grafica)
	g++ -fPIC -std=c++17 -I src -I includes -DPROJECT_ROOT_DIR='"$(PWD)"' tests/unit/*.cpp src/GramControl.cpp src/PrecoBase.cpp src/PrecoBaseController.cpp src/PrecoBaseDAO.cpp src/Orcamento.cpp src/OrcamentoController.cpp src/Cliente.cpp src/ClienteController.cpp src/ClienteDAO.cpp $(QT) -o bin/testes -lsqlite3
	rm -f gramcontrol.db
	./bin/testes

clean:
	rm -f bin/gramcontrol bin/testes bin/*.so gramcontrol.db src/moc_*.cpp