from Account import Account
from Person import Person
from random import randint

class User(Person):
    def __init__(self):
        super().__init__('','','')
        self.password=''
        self.noClient=0
        self.account=Account()

    def register(self,name,age,password,valPass,gender): 
        self.name=name
        self.age=age
        if int(self.age)<18:
            print("Lo sentimos, para crear una cuenta se debe de contar con una edad minima de 18 años:")
            return
        self.gender=gender
        self.password=password
        while(True):
            if self.password!=valPass:
                print("Las contraseñas no coincide. Favor de intentarlo nuevamente")
            else:
                break
        print("La cuenta ha sido creada con exito")
        print("Bienvenido al la familia de LOS NACOS.")
        self.account.noCard=randint(1000000000000000,9999999999999999)
        self.account.interBanKey='542965'+str(randint(10000000000,99999999999))+str(randint(0,5))
        self.noClient=randint(10000,99999)
        print("Su numero de cliente es: ",self.noClient)
        print("Su No. de tarjeta es: ",self.account.noCard) 
        print("Su clave interbacaria es: ",self.account.interBanKey)
        print("Su saldo inicial sera de : ",self.account.balance," $")
        print("Con cualquiera de estos dos numero podra realizar transferencias")
        fa=open("Bank/Cuentas.txt","a")
        
        fa.write(str(self.noClient) + ' ' + self.name + ' ' + self.password + ' ' + str(self.account.noCard) + ' ' + str(self.account.interBanKey) + ' ' + str(self.account.balance) + '\n')
        fa.close()

    def Login(self,noCard, password):
        fa=open("Bank/Cuentas.txt","r")
        for line in fa:
            part=line.split()
            if part[2] == password and part[3]==noCard:
                print("Login Realizado con exito")
                self.account.balance=part[5]
                self.account.interBanKey=part[4]
                self.account.noCard=part[3]
                fa.close()
                return True
        print("Te falla pa")
        fa.close()
        return False
    

  

        
        


    








