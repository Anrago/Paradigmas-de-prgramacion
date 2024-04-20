class Account:
    def __init__(self):
        self.interBanKey=''
        self.noCard=''
        self.balance=0

    def WithdrawCash(self):
        amount=float(input("Ingrese cantidad a retirar: "))
        while(True):
            if self.balance>0 and self.balance>amount:
                self.balance-=amount
                print("El retiro se ha realizado con exito")
                break
            else:
                amount=float(input("Saldo insuficiente. Favor de ingresar otra cantidad: "))

                
    def DepositCash(self):
        amount = float(input("Ingrese cantidad a depositar: "))
        self.balance+=amount

    def CheckBalance(self):
        print("No.Cuenta: ",self.interBanKey)
        print("No.Tarjeta: ",self.noCard)
        print("Saldo en cuenta: ",self.balance)

    





        
