# Form implementation generated from reading ui file 'd:\ECE4574\Pharmaceutical-Point-of-Sale\salescreen.ui'
#
# Created by: PyQt6 UI code generator 6.1.0
#
# WARNING: Any manual changes made to this file will be lost when pyuic6 is
# run again.  Do not edit this file unless you know what you are doing.


from PyQt6 import QtCore, QtGui, QtWidgets


class Ui_SaleScreen(object):
    def setupUi(self, SaleScreen):
        SaleScreen.setObjectName("SaleScreen")
        SaleScreen.resize(728, 589)
        self.label_4 = QtWidgets.QLabel(SaleScreen)
        self.label_4.setGeometry(QtCore.QRect(20, 80, 311, 31))
        font = QtGui.QFont()
        font.setPointSize(20)
        self.label_4.setFont(font)
        self.label_4.setObjectName("label_4")
        self.items_dropdown = DoubleClickList(SaleScreen)
        self.items_dropdown.setGeometry(QtCore.QRect(330, 60, 271, 181))
        font = QtGui.QFont()
        font.setPointSize(15)
        self.items_dropdown.setFont(font)
        self.items_dropdown.setMouseTracking(True)
        self.items_dropdown.setObjectName("items_dropdown")
        self.search_button = QtWidgets.QPushButton(SaleScreen)
        self.search_button.setGeometry(QtCore.QRect(600, 10, 100, 50))
        self.search_button.setMaximumSize(QtCore.QSize(100, 100))
        self.search_button.setObjectName("search_button")
        self.items_list = DoubleClickList(SaleScreen)
        self.items_list.setGeometry(QtCore.QRect(10, 150, 391, 361))
        font = QtGui.QFont()
        font.setPointSize(15)
        self.items_list.setFont(font)
        self.items_list.setMouseTracking(True)
        self.items_list.setObjectName("items_list")
        self.label_3 = QtWidgets.QLabel(SaleScreen)
        self.label_3.setGeometry(QtCore.QRect(20, 10, 311, 71))
        font = QtGui.QFont()
        font.setPointSize(25)
        self.label_3.setFont(font)
        self.label_3.setObjectName("label_3")
        self.search_lineEdit = QtWidgets.QLineEdit(SaleScreen)
        self.search_lineEdit.setGeometry(QtCore.QRect(330, 10, 271, 51))
        font = QtGui.QFont()
        font.setPointSize(13)
        self.search_lineEdit.setFont(font)
        self.search_lineEdit.setObjectName("search_lineEdit")
        self.clearButton = QtWidgets.QPushButton(SaleScreen)
        self.clearButton.setGeometry(QtCore.QRect(600, 70, 101, 51))
        self.clearButton.setObjectName("clearButton")
        self.label = QtWidgets.QLabel(SaleScreen)
        self.label.setGeometry(QtCore.QRect(430, 240, 71, 16))
        self.label.setObjectName("label")
        self.drug_name = QtWidgets.QLabel(SaleScreen)
        self.drug_name.setGeometry(QtCore.QRect(530, 240, 191, 16))
        self.drug_name.setText("")
        self.drug_name.setObjectName("drug_name")
        self.comboBox = QtWidgets.QComboBox(SaleScreen)
        self.comboBox.setGeometry(QtCore.QRect(430, 270, 69, 16))
        font = QtGui.QFont()
        font.setPointSize(8)
        self.comboBox.setFont(font)
        self.comboBox.setEditable(False)
        self.comboBox.setObjectName("comboBox")
        self.comboBox.addItem("")
        self.comboBox.addItem("")
        self.comboBox.addItem("")
        self.comboBox.addItem("")
        self.drug_code = QtWidgets.QLabel(SaleScreen)
        self.drug_code.setGeometry(QtCore.QRect(530, 270, 191, 16))
        self.drug_code.setText("")
        self.drug_code.setObjectName("drug_code")
        self.label_2 = QtWidgets.QLabel(SaleScreen)
        self.label_2.setGeometry(QtCore.QRect(430, 300, 54, 12))
        self.label_2.setObjectName("label_2")
        self.drug_stock = QtWidgets.QLabel(SaleScreen)
        self.drug_stock.setGeometry(QtCore.QRect(530, 290, 191, 16))
        self.drug_stock.setText("")
        self.drug_stock.setObjectName("drug_stock")
        self.label_5 = QtWidgets.QLabel(SaleScreen)
        self.label_5.setGeometry(QtCore.QRect(430, 450, 91, 41))
        font = QtGui.QFont()
        font.setPointSize(13)
        self.label_5.setFont(font)
        self.label_5.setObjectName("label_5")
        self.spinBox = QtWidgets.QSpinBox(SaleScreen)
        self.spinBox.setGeometry(QtCore.QRect(580, 460, 101, 31))
        font = QtGui.QFont()
        font.setPointSize(14)
        self.spinBox.setFont(font)
        self.spinBox.setMinimum(1)
        self.spinBox.setObjectName("spinBox")
        self.cartButton = QtWidgets.QPushButton(SaleScreen)
        self.cartButton.setGeometry(QtCore.QRect(600, 530, 101, 51))
        font = QtGui.QFont()
        font.setPointSize(11)
        self.cartButton.setFont(font)
        self.cartButton.setObjectName("cartButton")
        self.graphicsView = QtWidgets.QGraphicsView(SaleScreen)
        self.graphicsView.setGeometry(QtCore.QRect(480, 330, 121, 121))
        self.graphicsView.setObjectName("graphicsView")

        self.retranslateUi(SaleScreen)
        self.comboBox.setCurrentIndex(0)
        QtCore.QMetaObject.connectSlotsByName(SaleScreen)

    def retranslateUi(self, SaleScreen):
        _translate = QtCore.QCoreApplication.translate
        SaleScreen.setWindowTitle(_translate("SaleScreen", "Form"))
        self.label_4.setText(_translate("SaleScreen", "123 Main St. City, VA"))
        self.search_button.setText(_translate("SaleScreen", "Search"))
        self.label_3.setText(_translate("SaleScreen", "Pharmacy Name"))
        self.clearButton.setText(_translate("SaleScreen", "Clear"))
        self.label.setText(_translate("SaleScreen", "Drug Name :"))
        self.comboBox.setItemText(0, _translate("SaleScreen", "UPC"))
        self.comboBox.setItemText(1, _translate("SaleScreen", "DEA"))
        self.comboBox.setItemText(2, _translate("SaleScreen", "GPI"))
        self.comboBox.setItemText(3, _translate("SaleScreen", "NDC"))
        self.label_2.setText(_translate("SaleScreen", "Stock  :"))
        self.label_5.setText(_translate("SaleScreen", "Quantity :"))
        self.cartButton.setText(_translate("SaleScreen", "Add to cart"))
from Doubleclicklist import DoubleClickList