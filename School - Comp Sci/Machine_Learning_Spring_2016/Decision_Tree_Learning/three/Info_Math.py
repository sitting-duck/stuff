from decimal import Decimal


class Info_Math:

    def __init__(self):
        pass

    @staticmethod
    def prec(number, precision = 3):
        return round(Decimal(number), precision)

    @staticmethod
    def abs(value):
        if value < 0:
            return -value
        else:
            return value