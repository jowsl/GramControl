# Variavel QT intocada (obrigatoria para rodar no WSL)
QT = -I/usr/include/x86_64-linux-gnu/qt5 -I/usr/include/x86_64-linux-gnu/qt5/QtCore -I/usr/include/x86_64-linux-gnu/qt5/QtWidgets -I/usr/include/x86_64-linux-gnu/qt5/QtSql -I/usr/include/x86_64-linux-gnu/qt5/QtGui -lQt5Core -lQt5Widgets -lQt5Sql -lQt5Gui

# O "Motor" do sistema (todos os .cpp, EXCETO os arquivos main)
CORE_SRC = src/GramControl.cpp \
           src/AtualizarPrecoDialog.cpp \
           src/PrecoBase.cpp \
           src/PrecoBaseController.cpp \
           src/PrecoBaseDAO.cpp \
           src/ui/LoginWindow.cpp \
           src/ui/AdminWindow.cpp

moc:
	moc src/ui/LoginWindow.h -o src/moc_LoginWindow.cpp
	moc src/ui/AdminWindow.h -o src/moc_AdminWindow.cpp
	moc src/AtualizarPrecoDialog.hpp -o src/moc_AtualizarPrecoDialog.cpp

app: moc
	# Compila o app puxando o main do src + os mocs
	g++ -fPIC -std=c++17 -I src -I src/ui -I includes src/main.cpp $(CORE_SRC) src/moc_*.cpp $(QT) -o bin/gramcontrol -lsqlite3

test:
	# Compila os testes puxando os testes + o motor (sem interface grafica)
	g++ -fPIC -std=c++17 -I src -I includes -DPROJECT_ROOT_DIR='"$(PWD)"' tests/unit/*.cpp src/GramControl.cpp src/PrecoBase.cpp src/PrecoBaseDAO.cpp $(QT) -o bin/testes -lsqlite3
	rm -f gramcontrol.db
	./bin/testes

clean:
	rm -f bin/gramcontrol bin/testes gramcontrol.db src/moc_*.cpp