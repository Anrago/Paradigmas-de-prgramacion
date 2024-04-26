class Account:
    def __init__(self):
        self._interBanKey=''
        self._noCard=''
        self._balance=0

    def WithdrawCash(self,amount):
            if float(self._balance)>0 and float(self._balance)>=float(amount):
                lines=[]
                with open("Bank/Cuentas.txt", "r") as fa:
                        for line in fa:
                            part=line.split()
                            if part[3] == self._noCard:
                                self._balance=float(part[5])-amount
                                part[5] = str(self._balance)
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
                    if part[3] == self._noCard:
                        self._balance=float(part[5])+amount
                        part[5] = str(self._balance)
                    newLine=' '. join(part) + '\n'
                    lines.append(newLine)
        with open("Bank/Cuentas.txt","w") as fa:
            fa.writelines(lines)
            
    def Transaction(self,amount,InterBanKey):
        lines=[]
        with open("Bank/Cuentas.txt", "r") as fa:
                for line in fa:
                    part=line.split()
                    if part[3] == self._noCard:
                        self._balance=float(part[5])-amount
                        part[5] = str(self._balance)

                    if part[4] == InterBanKey:
                        tempB = float(part[5])+amount
                        part[5] = str(tempB)

                    newLine=' '. join(part) + '\n'
                    lines.append(newLine)
        with open("Bank/Cuentas.txt","w") as fa:
            fa.writelines(lines)

    def CheckBalance(self):
        print("No.Cuenta: ",self._interBanKey)
        print("No.Tarjeta: ",self._noCard)
        print("Saldo en cuenta: ",self._balance)

    





        
