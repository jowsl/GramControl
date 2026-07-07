QT = -I/usr/include/x86_64-linux-gnu/qt5 -I/usr/include/x86_64-linux-gnu/qt5/QtCore -I/usr/include/x86_64-linux-gnu/qt5/QtWidgets -I/usr/include/x86_64-linux-gnu/qt5/QtSql -I/usr/include/x86_64-linux-gnu/qt5/QtGui -lQt5Core -lQt5Widgets -lQt5Sql -lQt5Gui

app:
	g++ -fPIC -std=c++17 -I src -I src/ui -I includes src/main.cpp src/GramControl.cpp src/AtualizarPrecoDialog.cpp src/moc_AtualizarPrecoDialog.cpp src/moc_LoginWindow.cpp src/moc_AdminWindow.cpp src/PrecoBase.cpp src/PrecoBaseController.cpp src/PrecoBaseDAO.cpp src/ui/LoginWindow.cpp src/ui/AdminWindow.cpp $(QT) -o bin/gramcontrol

test:
	g++ -fPIC -std=c++17 -I src -I includes -DPROJECT_ROOT_DIR='"$(PWD)"' tests/unit/main.cpp tests/unit/test_login_reg.cpp tests/unit/test_persistencia.cpp tests/unit/test_PrecoBase.cpp src/GramControl.cpp src/PrecoBase.cpp src/PrecoBaseDAO.cpp $(QT) -o bin/testes && rm -f gramcontrol.db && ./bin/testes

clean:
	rm -f bin/gramcontrol bin/testes gramcontrol.db
