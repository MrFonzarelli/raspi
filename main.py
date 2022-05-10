# This is a sample Python script.

# Press Shift+F10 to execute it or replace it with your code.
# Press Double Shift to search everywhere for classes, files, tool windows, actions, and settings.


import random
import re
import sys
from PySide6 import QtCore, QtWidgets, QtGui
from PySide6.QtGui import QShortcut


def randomize_selection(set_of_things):
    return random.choice(set_of_things)


def str_merge(where, what):
    str2 = f"{where}{what}"
    return str2


class MyWidget(QtWidgets.QWidget):
    def __init__(self):
        super().__init__()

        self.button0 = QtWidgets.QPushButton('0')
        self.button0.setShortcut("0")
        self.button1 = QtWidgets.QPushButton('1')
        self.button1.setShortcut("1")
        self.button2 = QtWidgets.QPushButton('2')
        self.button2.setShortcut("2")
        self.button3 = QtWidgets.QPushButton('3')
        self.button3.setShortcut("3")
        self.button4 = QtWidgets.QPushButton('4')
        self.button4.setShortcut("4")
        self.button5 = QtWidgets.QPushButton('5')
        self.button5.setShortcut("5")
        self.button6 = QtWidgets.QPushButton('6')
        self.button6.setShortcut("6")
        self.button7 = QtWidgets.QPushButton('7')
        self.button7.setShortcut("7")
        self.button8 = QtWidgets.QPushButton('8')
        self.button8.setShortcut("8")
        self.button9 = QtWidgets.QPushButton('9')
        self.button9.setShortcut("9")
        self.button_dot = QtWidgets.QPushButton('.')
        self.button_dot.setShortcut(",")
        self.button_eq = QtWidgets.QPushButton('=')
        self.button_eq.setShortcut("Enter")
        self.button_res = QtWidgets.QPushButton('C')
        self.button_res.setShortcut("Delete")
        self.button_mlt = QtWidgets.QPushButton('*')
        self.button_mlt.setShortcut("*")
        self.button_div = QtWidgets.QPushButton('/')
        self.button_div.setShortcut("/")
        self.button_pls = QtWidgets.QPushButton('+')
        self.button_pls.setShortcut("+")
        self.button_min = QtWidgets.QPushButton('-')
        self.button_min.setShortcut("-")

        self.textbox = QtWidgets.QLabel(None)

        self.num_buttons = [self.button0, self.button1, self.button2, self.button3, self.button4, self.button5,
                            self.button6, self.button7, self.button8, self.button9]

        self.op_buttons = [self.button_eq, self.button_dot]

        self.layout = QtWidgets.QGridLayout(self)
        self.layout.setHorizontalSpacing(5)
        self.layout.setVerticalSpacing(5)
        self.layout.addWidget(self.textbox, 1, 2, 1, 3)
        self.layout.addWidget(self.button7, 2, 1)
        self.layout.addWidget(self.button8, 2, 2)
        self.layout.addWidget(self.button9, 2, 3)
        self.layout.addWidget(self.button4, 3, 1)
        self.layout.addWidget(self.button5, 3, 2)
        self.layout.addWidget(self.button6, 3, 3)
        self.layout.addWidget(self.button1, 4, 1)
        self.layout.addWidget(self.button2, 4, 2)
        self.layout.addWidget(self.button3, 4, 3)
        self.layout.addWidget(self.button0, 5, 1, 1, 2)
        self.layout.addWidget(self.button_dot, 5, 3, 1, 1)
        self.layout.addWidget(self.button_eq, 5, 4, 1, 2)
        self.layout.addWidget(self.button_min, 2, 5)
        self.layout.addWidget(self.button_pls, 3, 5)
        self.layout.addWidget(self.button_res, 4, 4)
        self.layout.addWidget(self.button_mlt, 2, 4)
        self.layout.addWidget(self.button_div, 3, 4)

        self.button_eq.setDefault(True)
        self.button_eq.setAutoDefault(True)

        self.button0.clicked.connect(self.num_action)
        self.button1.clicked.connect(self.num_action)
        self.button2.clicked.connect(self.num_action)
        self.button3.clicked.connect(self.num_action)
        self.button4.clicked.connect(self.num_action)
        self.button5.clicked.connect(self.num_action)
        self.button6.clicked.connect(self.num_action)
        self.button7.clicked.connect(self.num_action)
        self.button8.clicked.connect(self.num_action)
        self.button9.clicked.connect(self.num_action)
        self.button_dot.clicked.connect(self.num_action)
        self.button_mlt.clicked.connect(self.num_action)
        self.button_div.clicked.connect(self.num_action)
        self.button_pls.clicked.connect(self.num_action)
        self.button_min.clicked.connect(self.num_action)
        self.button_eq.clicked.connect(self.calculate)
        self.button_res.clicked.connect(self.reset)

        self.textbox.setText(None)

    @QtCore.Slot()
    def num_action(self):
        self.textbox.setText(str_merge(self.textbox.text(), self.sender().text()))

    def calculate(self):
        numbers = re.split("[-+/*.]", self.textbox.text())
        while '' in numbers:
            numbers.remove('')
        operations = re.split('\d', self.textbox.text())
        while '' in operations:
            operations.remove('')
        print(numbers)
        print(operations)
        equasion = []
        i = 0
        eq = 0
        for value in numbers:
            val1 = int(numbers[value])
            if i+1 > len(operations):
                break
            else:
                for operator in range(1):
                    if operations[operator] == "+":
                        val2 = int(numbers[i+operator])
                        eq = eq + (val1 + val2)
                    elif operations[operator] == "-":
                        val2 = int(numbers[i + operator])
                        eq = eq + (val1 - val2)
                    elif operations[operator] == "*":
                        val2 = int(numbers[i + operator])
                        eq = eq + (val1 * val2)
                    elif operations[operator] == "/":
                        val2 = int(numbers[i + operator])
                        eq = eq + (val1 * val2)
                i += operator+1
        self.textbox.setText(eq)

    def reset(self):
        self.textbox.setText(None)


if __name__ == "__main__":
    app = QtWidgets.QApplication([])

    widget = MyWidget()
    widget.resize(200, 180)
    widget.show()

    sys.exit(app.exec())
