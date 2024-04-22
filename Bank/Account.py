class Account:
    def __init__(self):
        self.interBanKey=''
        self.noCard=''
        self.balance=0

    def WithdrawCash(self,amount):
            if float(self.balance)>0 and float(self.balance)>=float(amount):
                lines=[]
                with open("Bank/Cuentas.txt", "r") as fa:
                        for line in fa:
                            part=line.split()
                            if part[3] == self.noCard:
                                self.balance=float(part[5])-amount
                                part[5] = str(self.balance)
                            newLine=' '. join(part) + '\n'
                            lines.append(newLine)
                with open("Bank/Cuentas.txt","w") as fa:
                    fa.writelines(lines)
                print("El retiro se ha realizado con exito")
            else:
                print("Saldo insuficiente. Favor de ingresar otra cantidad")

                
    def DepositCash(self,amount):
        lines=[]
        with open("Bank/Cuentas.txt", "r") as fa:
                for line in fa:
                    part=line.split()
                    if part[3] == self.noCard:
                        self.balance=int(part[5])+amount
                        part[5] = str(self.balance)
                    newLine=' '. join(part) + '\n'
                    lines.append(newLine)
        with open("Bank/Cuentas.txt","w") as fa:
            fa.writelines(lines)
            


    def CheckBalance(self):
        print("No.Cuenta: ",self.interBanKey)
        print("No.Tarjeta: ",self.noCard)
        print("Saldo en cuenta: ",self.balance)

    





        
