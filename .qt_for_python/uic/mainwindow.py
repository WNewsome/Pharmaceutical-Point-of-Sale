# Form implementation generated from reading ui file 'd:\ECE4574\Pharmaceutical-Point-of-Sale\mainwindow.ui'
#
# Created by: PyQt6 UI code generator 6.1.0
#
# WARNING: Any manual changes made to this file will be lost when pyuic6 is
# run again.  Do not edit this file unless you know what you are doing.


from PyQt6 import QtCore, QtGui, QtWidgets


class Ui_MainWindow(object):
    def setupUi(self, MainWindow):
        MainWindow.setObjectName("MainWindow")
        MainWindow.resize(895, 676)
        MainWindow.setAnimated(True)
        self.centralwidget = QtWidgets.QWidget(MainWindow)
        self.centralwidget.setObjectName("centralwidget")
        self.tabWidget = QtWidgets.QTabWidget(self.centralwidget)
        self.tabWidget.setGeometry(QtCore.QRect(0, 0, 901, 681))
        self.tabWidget.setLayoutDirection(QtCore.Qt.LayoutDirection.LeftToRight)
        self.tabWidget.setTabPosition(QtWidgets.QTabWidget.TabPosition.West)
        self.tabWidget.setObjectName("tabWidget")
        self.tab = QtWidgets.QWidget()
        self.tab.setObjectName("tab")
        self.label = QtWidgets.QLabel(self.tab)
        self.label.setGeometry(QtCore.QRect(400, 20, 131, 51))
        font = QtGui.QFont()
        font.setPointSize(25)
        self.label.setFont(font)
        self.label.setObjectName("label")
        self.search_button = QtWidgets.QPushButton(self.tab)
        self.search_button.setGeometry(QtCore.QRect(650, 80, 100, 50))
        self.search_button.setMaximumSize(QtCore.QSize(100, 100))
        self.search_button.setObjectName("search_button")
        self.label_4 = QtWidgets.QLabel(self.tab)
        self.label_4.setGeometry(QtCore.QRect(40, 70, 311, 31))
        font = QtGui.QFont()
        font.setPointSize(20)
        self.label_4.setFont(font)
        self.label_4.setObjectName("label_4")
        self.items_list = QtWidgets.QListWidget(self.tab)
        self.items_list.setGeometry(QtCore.QRect(50, 140, 701, 451))
        font = QtGui.QFont()
        font.setPointSize(15)
        self.items_list.setFont(font)
        self.items_list.setObjectName("items_list")
        self.search_lineEdit = QtWidgets.QLineEdit(self.tab)
        self.search_lineEdit.setGeometry(QtCore.QRect(380, 80, 271, 51))
        font = QtGui.QFont()
        font.setPointSize(13)
        self.search_lineEdit.setFont(font)
        self.search_lineEdit.setObjectName("search_lineEdit")
        self.label_3 = QtWidgets.QLabel(self.tab)
        self.label_3.setGeometry(QtCore.QRect(40, 0, 311, 71))
        font = QtGui.QFont()
        font.setPointSize(25)
        self.label_3.setFont(font)
        self.label_3.setObjectName("label_3")
        self.total = QtWidgets.QLabel(self.tab)
        self.total.setGeometry(QtCore.QRect(620, 30, 121, 41))
        font = QtGui.QFont()
        font.setPointSize(25)
        self.total.setFont(font)
        self.total.setObjectName("total")
        self.items_dropdown = QtWidgets.QListWidget(self.tab)
        self.items_dropdown.setGeometry(QtCore.QRect(380, 130, 271, 181))
        font = QtGui.QFont()
        font.setPointSize(15)
        self.items_dropdown.setFont(font)
        self.items_dropdown.setObjectName("items_dropdown")
        self.tabWidget.addTab(self.tab, "")
        self.tab_2 = QtWidgets.QWidget()
        self.tab_2.setObjectName("tab_2")
        self.gridLayoutWidget = QtWidgets.QWidget(self.tab_2)
        self.gridLayoutWidget.setGeometry(QtCore.QRect(30, 70, 801, 581))
        self.gridLayoutWidget.setObjectName("gridLayoutWidget")
        self.gridLayout_5 = QtWidgets.QGridLayout(self.gridLayoutWidget)
        self.gridLayout_5.setContentsMargins(0, 0, 0, 0)
        self.gridLayout_5.setObjectName("gridLayout_5")
        self.label_id = QtWidgets.QLabel(self.gridLayoutWidget)
        self.label_id.setAlignment(QtCore.Qt.AlignmentFlag.AlignCenter)
        self.label_id.setObjectName("label_id")
        self.gridLayout_5.addWidget(self.label_id, 1, 1, 1, 1)
        self.idEdit = QtWidgets.QLineEdit(self.gridLayoutWidget)
        self.idEdit.setObjectName("idEdit")
        self.gridLayout_5.addWidget(self.idEdit, 1, 2, 1, 1)
        self.phoneEdit = QtWidgets.QLineEdit(self.gridLayoutWidget)
        self.phoneEdit.setObjectName("phoneEdit")
        self.gridLayout_5.addWidget(self.phoneEdit, 2, 2, 1, 1)
        self.label_phone = QtWidgets.QLabel(self.gridLayoutWidget)
        self.label_phone.setAlignment(QtCore.Qt.AlignmentFlag.AlignCenter)
        self.label_phone.setObjectName("label_phone")
        self.gridLayout_5.addWidget(self.label_phone, 2, 1, 1, 1)
        self.label_address = QtWidgets.QLabel(self.gridLayoutWidget)
        self.label_address.setAlignment(QtCore.Qt.AlignmentFlag.AlignCenter)
        self.label_address.setObjectName("label_address")
        self.gridLayout_5.addWidget(self.label_address, 4, 1, 1, 1)
        self.nameEdit = QtWidgets.QLineEdit(self.gridLayoutWidget)
        self.nameEdit.setObjectName("nameEdit")
        self.gridLayout_5.addWidget(self.nameEdit, 0, 2, 1, 1)
        self.addressEdit = QtWidgets.QPlainTextEdit(self.gridLayoutWidget)
        self.addressEdit.setObjectName("addressEdit")
        self.gridLayout_5.addWidget(self.addressEdit, 4, 2, 1, 1)
        self.label_prescription = QtWidgets.QLabel(self.gridLayoutWidget)
        self.label_prescription.setObjectName("label_prescription")
        self.gridLayout_5.addWidget(self.label_prescription, 5, 1, 1, 1)
        self.prescriptionEdit = QtWidgets.QPlainTextEdit(self.gridLayoutWidget)
        self.prescriptionEdit.setObjectName("prescriptionEdit")
        self.gridLayout_5.addWidget(self.prescriptionEdit, 5, 2, 1, 1)
        self.label_ssn = QtWidgets.QLabel(self.gridLayoutWidget)
        self.label_ssn.setAlignment(QtCore.Qt.AlignmentFlag.AlignCenter)
        self.label_ssn.setObjectName("label_ssn")
        self.gridLayout_5.addWidget(self.label_ssn, 3, 1, 1, 1)
        self.ssnEdit = QtWidgets.QLineEdit(self.gridLayoutWidget)
        self.ssnEdit.setObjectName("ssnEdit")
        self.gridLayout_5.addWidget(self.ssnEdit, 3, 2, 1, 1)
        self.label_name = QtWidgets.QLabel(self.gridLayoutWidget)
        self.label_name.setAlignment(QtCore.Qt.AlignmentFlag.AlignCenter)
        self.label_name.setObjectName("label_name")
        self.gridLayout_5.addWidget(self.label_name, 0, 1, 1, 1)
        self.tableWidget = QtWidgets.QTableWidget(self.gridLayoutWidget)
        self.tableWidget.setColumnCount(5)
        self.tableWidget.setObjectName("tableWidget")
        self.tableWidget.setRowCount(0)
        self.tableWidget.horizontalHeader().setDefaultSectionSize(72)
        self.gridLayout_5.addWidget(self.tableWidget, 0, 0, 6, 1)
        self.search_lineEdit_2 = QtWidgets.QLineEdit(self.tab_2)
        self.search_lineEdit_2.setGeometry(QtCore.QRect(30, 20, 711, 31))
        self.search_lineEdit_2.setObjectName("search_lineEdit_2")
        self.search_button_2 = QtWidgets.QPushButton(self.tab_2)
        self.search_button_2.setGeometry(QtCore.QRect(750, 20, 81, 31))
        self.search_button_2.setObjectName("search_button_2")
        self.tabWidget.addTab(self.tab_2, "")
        self.tab_3 = QtWidgets.QWidget()
        self.tab_3.setObjectName("tab_3")
        self.scrollArea = QtWidgets.QScrollArea(self.tab_3)
        self.scrollArea.setGeometry(QtCore.QRect(40, 10, 701, 621))
        self.scrollArea.setMinimumSize(QtCore.QSize(0, 501))
        self.scrollArea.setWidgetResizable(True)
        self.scrollArea.setObjectName("scrollArea")
        self.scrollAreaWidgetContents = QtWidgets.QWidget()
        self.scrollAreaWidgetContents.setGeometry(QtCore.QRect(0, 0, 699, 619))
        self.scrollAreaWidgetContents.setObjectName("scrollAreaWidgetContents")
        self.gridLayout_4 = QtWidgets.QGridLayout(self.scrollAreaWidgetContents)
        self.gridLayout_4.setObjectName("gridLayout_4")
        self.label_9 = QtWidgets.QLabel(self.scrollAreaWidgetContents)
        font = QtGui.QFont()
        font.setPointSize(10)
        self.label_9.setFont(font)
        self.label_9.setObjectName("label_9")
        self.gridLayout_4.addWidget(self.label_9, 1, 1, 1, 2)
        self.line = QtWidgets.QFrame(self.scrollAreaWidgetContents)
        self.line.setFrameShape(QtWidgets.QFrame.Shape.HLine)
        self.line.setFrameShadow(QtWidgets.QFrame.Shadow.Sunken)
        self.line.setObjectName("line")
        self.gridLayout_4.addWidget(self.line, 2, 1, 1, 2)
        self.label_10 = QtWidgets.QLabel(self.scrollAreaWidgetContents)
        self.label_10.setObjectName("label_10")
        self.gridLayout_4.addWidget(self.label_10, 9, 2, 1, 2)
        spacerItem = QtWidgets.QSpacerItem(178, 48, QtWidgets.QSizePolicy.Policy.Expanding, QtWidgets.QSizePolicy.Policy.Minimum)
        self.gridLayout_4.addItem(spacerItem, 0, 3, 3, 1)
        self.label_6 = QtWidgets.QLabel(self.scrollAreaWidgetContents)
        font = QtGui.QFont()
        font.setPointSize(12)
        self.label_6.setFont(font)
        self.label_6.setObjectName("label_6")
        self.gridLayout_4.addWidget(self.label_6, 0, 1, 1, 2)
        self.graphicsView = QtWidgets.QGraphicsView(self.scrollAreaWidgetContents)
        self.graphicsView.setObjectName("graphicsView")
        self.gridLayout_4.addWidget(self.graphicsView, 8, 0, 1, 2)
        self.graphicsView_2 = QtWidgets.QGraphicsView(self.scrollAreaWidgetContents)
        self.graphicsView_2.setObjectName("graphicsView_2")
        self.gridLayout_4.addWidget(self.graphicsView_2, 9, 0, 1, 2)
        self.gridLayout_2 = QtWidgets.QGridLayout()
        self.gridLayout_2.setObjectName("gridLayout_2")
        self.label_5 = QtWidgets.QLabel(self.scrollAreaWidgetContents)
        font = QtGui.QFont()
        font.setPointSize(9)
        font.setUnderline(True)
        self.label_5.setFont(font)
        self.label_5.setObjectName("label_5")
        self.gridLayout_2.addWidget(self.label_5, 0, 0, 1, 2)
        self.label_7 = QtWidgets.QLabel(self.scrollAreaWidgetContents)
        self.label_7.setObjectName("label_7")
        self.gridLayout_2.addWidget(self.label_7, 1, 0, 1, 1)
        self.lineEdit = QtWidgets.QLineEdit(self.scrollAreaWidgetContents)
        self.lineEdit.setObjectName("lineEdit")
        self.gridLayout_2.addWidget(self.lineEdit, 1, 1, 1, 1)
        self.pushButton_5 = QtWidgets.QPushButton(self.scrollAreaWidgetContents)
        self.pushButton_5.setObjectName("pushButton_5")
        self.gridLayout_2.addWidget(self.pushButton_5, 1, 2, 1, 1)
        self.gridLayout_4.addLayout(self.gridLayout_2, 3, 0, 1, 3)
        self.label_8 = QtWidgets.QLabel(self.scrollAreaWidgetContents)
        self.label_8.setObjectName("label_8")
        self.gridLayout_4.addWidget(self.label_8, 8, 2, 1, 2)
        spacerItem1 = QtWidgets.QSpacerItem(177, 48, QtWidgets.QSizePolicy.Policy.Expanding, QtWidgets.QSizePolicy.Policy.Minimum)
        self.gridLayout_4.addItem(spacerItem1, 0, 0, 3, 1)
        spacerItem2 = QtWidgets.QSpacerItem(528, 48, QtWidgets.QSizePolicy.Policy.Expanding, QtWidgets.QSizePolicy.Policy.Minimum)
        self.gridLayout_4.addItem(spacerItem2, 6, 0, 1, 4)
        self.label_11 = QtWidgets.QLabel(self.scrollAreaWidgetContents)
        font = QtGui.QFont()
        font.setPointSize(9)
        font.setUnderline(True)
        self.label_11.setFont(font)
        self.label_11.setObjectName("label_11")
        self.gridLayout_4.addWidget(self.label_11, 7, 0, 1, 1)
        self.gridLayout_3 = QtWidgets.QGridLayout()
        self.gridLayout_3.setObjectName("gridLayout_3")
        self.label_12 = QtWidgets.QLabel(self.scrollAreaWidgetContents)
        font = QtGui.QFont()
        font.setPointSize(9)
        font.setUnderline(True)
        self.label_12.setFont(font)
        self.label_12.setObjectName("label_12")
        self.gridLayout_3.addWidget(self.label_12, 0, 0, 1, 2)
        self.label_13 = QtWidgets.QLabel(self.scrollAreaWidgetContents)
        self.label_13.setObjectName("label_13")
        self.gridLayout_3.addWidget(self.label_13, 1, 0, 1, 1)
        self.lineEdit_2 = QtWidgets.QLineEdit(self.scrollAreaWidgetContents)
        self.lineEdit_2.setObjectName("lineEdit_2")
        self.gridLayout_3.addWidget(self.lineEdit_2, 1, 1, 1, 1)
        self.pushButton_6 = QtWidgets.QPushButton(self.scrollAreaWidgetContents)
        self.pushButton_6.setObjectName("pushButton_6")
        self.gridLayout_3.addWidget(self.pushButton_6, 1, 2, 1, 1)
        self.gridLayout_4.addLayout(self.gridLayout_3, 5, 0, 1, 3)
        spacerItem3 = QtWidgets.QSpacerItem(528, 48, QtWidgets.QSizePolicy.Policy.Expanding, QtWidgets.QSizePolicy.Policy.Minimum)
        self.gridLayout_4.addItem(spacerItem3, 4, 0, 1, 4)
        self.scrollArea.setWidget(self.scrollAreaWidgetContents)
        self.tabWidget.addTab(self.tab_3, "")
        self.tab_4 = QtWidgets.QWidget()
        self.tab_4.setObjectName("tab_4")
        self.scrollArea_2 = QtWidgets.QScrollArea(self.tab_4)
        self.scrollArea_2.setGeometry(QtCore.QRect(50, 20, 581, 561))
        self.scrollArea_2.setWidgetResizable(True)
        self.scrollArea_2.setObjectName("scrollArea_2")
        self.scrollAreaWidgetContents_2 = QtWidgets.QWidget()
        self.scrollAreaWidgetContents_2.setGeometry(QtCore.QRect(0, 0, 579, 559))
        self.scrollAreaWidgetContents_2.setObjectName("scrollAreaWidgetContents_2")
        self.label_14 = QtWidgets.QLabel(self.scrollAreaWidgetContents_2)
        self.label_14.setGeometry(QtCore.QRect(30, 40, 111, 16))
        font = QtGui.QFont()
        font.setPointSize(9)
        self.label_14.setFont(font)
        self.label_14.setObjectName("label_14")
        self.label_15 = QtWidgets.QLabel(self.scrollAreaWidgetContents_2)
        self.label_15.setGeometry(QtCore.QRect(30, 260, 55, 16))
        self.label_15.setObjectName("label_15")
        self.label_16 = QtWidgets.QLabel(self.scrollAreaWidgetContents_2)
        self.label_16.setGeometry(QtCore.QRect(30, 70, 55, 16))
        font = QtGui.QFont()
        font.setPointSize(9)
        self.label_16.setFont(font)
        self.label_16.setObjectName("label_16")
        self.pushButton = QtWidgets.QPushButton(self.scrollAreaWidgetContents_2)
        self.pushButton.setGeometry(QtCore.QRect(420, 500, 121, 28))
        self.pushButton.setObjectName("pushButton")
        self.lineEdit_3 = QtWidgets.QLineEdit(self.scrollAreaWidgetContents_2)
        self.lineEdit_3.setGeometry(QtCore.QRect(150, 40, 113, 22))
        self.lineEdit_3.setObjectName("lineEdit_3")
        self.lineEdit_4 = QtWidgets.QLineEdit(self.scrollAreaWidgetContents_2)
        self.lineEdit_4.setGeometry(QtCore.QRect(150, 70, 113, 22))
        self.lineEdit_4.setObjectName("lineEdit_4")
        self.graphicsView_3 = QtWidgets.QGraphicsView(self.scrollAreaWidgetContents_2)
        self.graphicsView_3.setGeometry(QtCore.QRect(100, 280, 181, 151))
        self.graphicsView_3.setObjectName("graphicsView_3")
        self.label_17 = QtWidgets.QLabel(self.scrollAreaWidgetContents_2)
        self.label_17.setGeometry(QtCore.QRect(30, 100, 55, 16))
        font = QtGui.QFont()
        font.setPointSize(9)
        self.label_17.setFont(font)
        self.label_17.setObjectName("label_17")
        self.label_18 = QtWidgets.QLabel(self.scrollAreaWidgetContents_2)
        self.label_18.setGeometry(QtCore.QRect(30, 130, 55, 16))
        font = QtGui.QFont()
        font.setPointSize(9)
        self.label_18.setFont(font)
        self.label_18.setObjectName("label_18")
        self.lineEdit_5 = QtWidgets.QLineEdit(self.scrollAreaWidgetContents_2)
        self.lineEdit_5.setGeometry(QtCore.QRect(150, 100, 113, 22))
        self.lineEdit_5.setObjectName("lineEdit_5")
        self.lineEdit_6 = QtWidgets.QLineEdit(self.scrollAreaWidgetContents_2)
        self.lineEdit_6.setGeometry(QtCore.QRect(150, 130, 113, 22))
        self.lineEdit_6.setObjectName("lineEdit_6")
        self.label_19 = QtWidgets.QLabel(self.scrollAreaWidgetContents_2)
        self.label_19.setGeometry(QtCore.QRect(30, 170, 71, 16))
        font = QtGui.QFont()
        font.setPointSize(9)
        self.label_19.setFont(font)
        self.label_19.setObjectName("label_19")
        self.lineEdit_7 = QtWidgets.QLineEdit(self.scrollAreaWidgetContents_2)
        self.lineEdit_7.setGeometry(QtCore.QRect(150, 170, 113, 22))
        self.lineEdit_7.setObjectName("lineEdit_7")
        self.scrollArea_2.setWidget(self.scrollAreaWidgetContents_2)
        self.tabWidget.addTab(self.tab_4, "")
        MainWindow.setCentralWidget(self.centralwidget)

        self.retranslateUi(MainWindow)
        self.tabWidget.setCurrentIndex(1)
        QtCore.QMetaObject.connectSlotsByName(MainWindow)

    def retranslateUi(self, MainWindow):
        _translate = QtCore.QCoreApplication.translate
        MainWindow.setWindowTitle(_translate("MainWindow", "MainWindow"))
        self.label.setText(_translate("MainWindow", "Total:"))
        self.search_button.setText(_translate("MainWindow", "Search"))
        self.label_4.setText(_translate("MainWindow", "123 Main St. City, VA"))
        self.label_3.setText(_translate("MainWindow", "Pharmacy Name"))
        self.total.setText(_translate("MainWindow", "$ 0.00"))
        self.tabWidget.setTabText(self.tabWidget.indexOf(self.tab), _translate("MainWindow", "Sales"))
        self.label_id.setText(_translate("MainWindow", "ID:"))
        self.label_phone.setText(_translate("MainWindow", "Phone number:"))
        self.label_address.setText(_translate("MainWindow", "Address:"))
        self.label_prescription.setText(_translate("MainWindow", "Prescription:"))
        self.label_ssn.setText(_translate("MainWindow", "SSN:"))
        self.label_name.setText(_translate("MainWindow", "Name:"))
        self.search_button_2.setText(_translate("MainWindow", "Search"))
        self.tabWidget.setTabText(self.tabWidget.indexOf(self.tab_2), _translate("MainWindow", "Patients"))
        self.label_9.setText(_translate("MainWindow", "123 Main St. City, VA"))
        self.label_10.setText(_translate("MainWindow", "Profits Report"))
        self.label_6.setText(_translate("MainWindow", "Pharmacy Name"))
        self.label_5.setText(_translate("MainWindow", "Edit Drug Information"))
        self.label_7.setText(_translate("MainWindow", "Insert name:"))
        self.pushButton_5.setText(_translate("MainWindow", "Search"))
        self.label_8.setText(_translate("MainWindow", "Sales Report"))
        self.label_11.setText(_translate("MainWindow", "Reports"))
        self.label_12.setText(_translate("MainWindow", "Add New Drug"))
        self.label_13.setText(_translate("MainWindow", "Insert name:"))
        self.pushButton_6.setText(_translate("MainWindow", "Create"))
        self.tabWidget.setTabText(self.tabWidget.indexOf(self.tab_3), _translate("MainWindow", "Management"))
        self.label_14.setText(_translate("MainWindow", "Company Name:"))
        self.label_15.setText(_translate("MainWindow", "Logo:"))
        self.label_16.setText(_translate("MainWindow", "Address:"))
        self.pushButton.setText(_translate("MainWindow", "Save these changes"))
        self.label_17.setText(_translate("MainWindow", "City:"))
        self.label_18.setText(_translate("MainWindow", "State:"))
        self.label_19.setText(_translate("MainWindow", "Zip code:"))
        self.tabWidget.setTabText(self.tabWidget.indexOf(self.tab_4), _translate("MainWindow", "Settings"))
