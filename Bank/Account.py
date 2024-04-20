class Account:
    def __init__(self,noAccount,noCard):
        self.noAcount=noAccount
        self.noCard=noCard
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
        print("No.Cuenta: ",self.noAcount)
        print("No.Tarjeta: ",self.noCard)
        print("Saldo en cuenta: ",self.balance)

    
cuenta=Account("12345","54321",5000)




        
